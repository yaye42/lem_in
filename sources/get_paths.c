/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:07:55 by yaye              #+#    #+#             */
/*   Updated: 2020/06/30 19:07:56 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** if (f == NULL) : RESET THE "LEVEL" OF EVERY "REACHABLE ROOMS" FROM THE
** STARTING ROOM TO 0
** else : ASSIGN EACH "REACHABLE ROOMS" ITS RESPECTIVE "LEVEL"
**
** REACHABLE ROOMS : ROOMS THAT CAN BE REACHED FROM THE "f->start" STARTING
** ROOM WITHOUT CROSSING ANY ROOM THAT ARE INCLUDED IN A PATH
**
** LEVEL : DISTANCE BETWEEN A GIVEN ROOM AND THE STARTING ROOM
** f->start->level == 1
*/

void	leveling(t_farm *f, t_room *room, int lv)
{
	int		i;
	t_room	*p;

	room->level = (f == NULL) ? -1 : lv;
	i = -1;
	if (f == NULL)
	{
		if (room->epath)
			return ;
		while ((p = room->links[++i]))
			if (p->epath == NULL && p->level > -1)
				leveling(NULL, p, -1);
	}
	else
	{
		if (room == f->end || room->epath)
			return ;
		while ((p = room->links[++i]))
			if ((p->level == -1 || p->level > lv + 1))
				leveling(f, p, lv + 1);
	}
}

/*
** BIND room-room_2 FOR pathfind()
** UN_BIND room-room_2 | IS CALLED WHEN pathfind() FAILED TO BUILD A PATH
**                       WITH room_2
*/

void	un_bind(t_farm *f, t_room *room, t_room *room_2, t_room **tmp)
{
	if (f)
	{
		*tmp = (room_2->epath) ? room_2->spath : NULL;
		room->epath = room_2;
		if (room_2 != f->start)
			room_2->spath = room;
		if (*tmp)
			(*tmp)->epath = NULL;
	}
	else
	{
		room_2->spath = *tmp;
		room->epath = NULL;
		if (*tmp)
			(*tmp)->epath = room_2;
	}
}

/*
** SEEKS A VALID ROOM NEXT TO room FOR path_builder()
** IF A VALID ROOM IS ALREADY TAKEN, TAKES IT IF THE PREVIOUS OWNER
** MANAGES TO BUILD A NEW PATH
*/

int		pathfind(t_farm *f, t_room *room, t_room *excl)
{
	int		i;
	t_room	*tmp;

	if (room == f->start)
		return (1);
	if (!room || room == f->end)
		return (0);
	leveling(NULL, f->start, -1);
	leveling(f, f->start, 0);
	i = -1;
	while (room->links[++i])
		if (room->links[i]->level == room->level - 1 && room->links[i] != excl)
		{
			un_bind(f, room, room->links[i], &tmp);
			if (room->links[i]->epath)
			{
				if (pathfind(f, tmp, room->links[i]))
					return (1);
			}
			else if (pathfind(f, room->links[i], NULL))
				return (1);
			un_bind(NULL, room, room->links[i], &tmp);
		}
	return (0);
}

/*
** TRIES TO BUILD A PATH FROM END TO START
*/

void	path_builder(t_farm *f, t_room *end_linki)
{
	t_room	*tmp;

	if (end_linki->spath == NULL)
	{
		end_linki->spath = f->end;
		if (pathfind(f, end_linki, NULL))
			f->ending = f->ending + 1;
		else
			end_linki->spath = NULL;
	}
	else
	{
		tmp = end_linki->spath;
		end_linki->spath = f->end;
		while (tmp->spath)
		{
			tmp = tmp->spath;
			tmp->epath->epath = NULL;
			tmp->epath->spath = NULL;
		}
	}
}

/*
** f->ending == 0
**		ERROR: no starting and/or ending room.
** f->ending == 1
**		ERROR: no valid valid room after ##end command.
** f->ending == 2
**		OK
**
** f->ending THEN BECOMES <NUMBER OF PATHS FOUND>
*/

int		get_paths(t_farm *f)
{
	int		i;

	f->ending = 0;
	i = -1;
	while (f->end->links[++i])
	{
		if (f->end->links[i] == f->start)
		{
			f->start->spath = f->end;
			f->end->epath = f->start;
			f->ending = f->ending + 1;
		}
		else
			path_builder(f, f->end->links[i]);
	}
	return (f->ending);
}
