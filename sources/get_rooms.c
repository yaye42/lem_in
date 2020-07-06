/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 13:27:40 by yaye              #+#    #+#             */
/*   Updated: 2020/06/19 13:27:41 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** RETURNS 0 IF (x;y) IS NOT ALREADY USED BY AN OTHER EXISTING ROOM
** ELSE leaves();
*/

size_t	is_saved_coord(t_farm *f, int x, int y)
{
	t_room	*r;

	r = f->head;
	while (r)
	{
		if (x == r->x && y == r->y)
			leave(f, ": 2 rooms with same (coord_x; coord_y).\n");
		r = r->next;
	}
	return (0);
}

t_room	*new_room(t_farm *f)
{
	t_room	*new_room;

	if (!(new_room = malloc(sizeof(t_room))))
		leave(f, ": malloc failure in new_room().\n");
	new_room->name = NULL;
	new_room->level = 0;
	new_room->n_links = 0;
	new_room->len = 0;
	new_room->ants = 0;
	new_room->links = NULL;
	new_room->epath = NULL;
	new_room->spath = NULL;
	new_room->next = NULL;
	if (f->starting == 1 && (++f->starting))
		f->start = new_room;
	else if (f->ending == 1 && (++f->ending))
		f->end = new_room;
	if (f->tail)
		f->tail->next = new_room;
	else
		f->head = new_room;
	f->tail = (f->tail) ? f->tail->next : f->head;
	return (new_room);
}

void	add_room(t_farm *f, char *buf)
{
	t_room	*room;
	size_t	t;

	room = new_room(f);
	t = 0;
	while (buf[t] != ' ')
		t = t + 1;
	if (!(room->name = malloc(sizeof(char) * t + 1)))
		leave(f, ": malloc failure in add_room().\n");
	t = 0;
	while (buf[t] != ' ')
	{
		room->name[t] = buf[t];
		t = t + 1;
	}
	room->name[t] = 0;
	if (f->n_rooms == N_ROOMS_MAX)
		leave(f, ": reached N_ROOMS_MAX (edit value in lem_in.h).\n");
	f->n_rooms = f->n_rooms + 1;
	get_map(f, buf);
}

int		is_room(t_farm *f, char *buf)
{
	size_t	t;
	size_t	k;
	int		x;
	int		y;

	t = 0;
	if (!ft_isprint(buf[t]) || ft_isblanc(buf[t]) \
		|| buf[t] == 'L' || buf[t] == '-' || buf[t] == '#')
		return (0);
	while (buf[t] && ft_isprint(buf[t]) && !ft_isblanc(buf[t]) \
		&& buf[t] != '-')
		t = t + 1;
	if (t == 0 || buf[t] != ' ' || !(k = ft_stoi(buf + t + 1, &x, ' ')) \
		|| buf[t + k + 1] != ' ' || !ft_stoi(buf + t + k + 2, &y, 0))
		return (0);
	if (is_saved_name(f, buf, t) || is_saved_coord(f, x, y))
		leave(f, ": 2 rooms with same name.\n");
	add_room(f, buf);
	f->tail->x = x;
	f->tail->y = y;
	return (1);
}

int		get_rooms(t_farm *f, char *buf)
{
	if (is_com(f, buf))
		return (1);
	else if (is_room(f, buf))
		return (1);
	if (f->starting == 1)
		leave(f, ": no valid room after ##start command.\n");
	else if (f->ending == 1)
		leave(f, ": no valid room after ##end command.\n");
	if (f->starting != 2 || f->ending != 2)
		leave(f, ": no starting or ending room after last valid room.\n");
	return (0);
}
