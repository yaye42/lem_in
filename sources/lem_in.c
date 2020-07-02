/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:59:44 by yaye              #+#    #+#             */
/*   Updated: 2020/02/25 14:59:45 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"

/*
** k + 1 == INDEX OF SHORTEST PATH
** j == INDEX OF NEXT "NOT FILLED PATH"
** ADDS 1 ANT IN EACH PATH FROM path(k) to path(j - 1)
** REMOVES AS MUCH ANTS FROM TOTAL n_ants
*/

void	disp_ants_ser(t_farm *f, int j, int k, int *ants)
{
	while (++k < j && *ants > 0 && f->start->links[k])
	{
		f->start->links[k]->ants = f->start->links[k]->ants + 1;
		*ants = *ants - 1;
	}
}

/*
** i == INDEX OF SHORTEST PATH
** GETS THE LENGHT OF EACH PATH
** AND SORT THEM FROM SHORTEST TO LONGEST
*/

void	set_paths(t_farm *f)
{
	int		i;
	int		j;
	t_room	*p;

	i = -1;
	while ((p = f->start->links[++i]))
		if ((p->spath || p == f->end) && (j = 1))
		{
			while (p && p->spath && (++j))
				p = p->spath;
			f->start->links[i]->len = j;
		}
	i = -1;
	while (f->start->links[++i])
	{
		j = i;
		while (f->start->links[++j])
			if (f->start->links[j]->len < f->start->links[i]->len)
			{
				p = f->start->links[i];
				f->start->links[i] = f->start->links[j];
				f->start->links[j] = p;
			}
	}
}

/*
** ASSIGNS EACH PATH ITS RESPECTIVE NUMBER OF ANTS IT HAS TO DELIVER
** i == INDEX OF SHORTEST PATH
** j == INDEX OF NEXT "NOT FILLED PATH"
*/

void	set_ants(t_farm *f)
{
	int		i;
	int		j;
	int		ants;

	set_paths(f);
	i = 0;
	while (f->start->links[i] && f->start->links[i]->len == 0)
		i = i + 1;
	j = i;
	ants = f->n_ants;
	while (f->start->links[++j] && ants > 0)
	{
		while (f->start->links[j - 1]->len + f->start->links[j - 1]->ants \
			< f->start->links[j]->len && ants > 0)
			disp_ants_ser(f, j, i - 1, &ants);
	}
	while (ants > 0)
		disp_ants_ser(f, j, i - 1, &ants);
	while (f->start->links[i] && !(f->start->links[i]->len = 0))
		f->start->links[i++]->level = 0;
	if (f->start->spath && (f->start->ants = f->end->ants))
		f->end->ants = 0;
}

int		send_ant(t_room *room, int *k, int ret)
{
	room->ants = room->ants + 1;
	room->len = room->len + 1;
	*k = (*k != 0) ? write(1, " ", 1) : 1;
	ft_printf("L%d-%s", room->len, room->name);
	return (ret);
}

void	lem_in(t_farm *f)
{
	int		i;
	int		k;
	t_room	*q;

	if (f->n_ants == f->end->len)
		return ;
	i = -1;
	k = 0;
	while ((q = f->end->links[++i]) != NULL)
	{
		if (q == f->start)
		{
			send_ant(q->spath, &k, 1);
			q->len = q->len + 1;
			q->ants = q->ants - 1;
		}
		while (q->epath && q->epath != f->start)
		{
			if (q->ants)
				q->ants = q->ants - send_ant(q->spath, &k, 1);
			q = q->epath;
		}
		if (q->epath == f->start)
		{
			if (q->ants)
			{
				q->level = (q->level) ? send_ant(q->spath, &k, 1) : 1;
				q->len = q->len + 1;
				q->ants = q->ants - 1;
				k = (k != 0) ? write(1, " ", 1) : 1;
				ft_printf("L%d-%s", q->len, q->name);
			}
			else if (q->ants == 0 && q->level == 1)
				q->level = send_ant(q->spath, &k, 0);
		}
	}
	write(1, "\n", 1);
	lem_in(f);
}

int		main(void)
{
	t_farm	f;

	f.n_ants = 0;
	f.n_rooms = 0;
	f.starting = 0;
	f.ending = 0;
	f.head = NULL;
	f.tail = NULL;
	f.start = NULL;
	f.end = NULL;
	f.buf = NULL;
	get_farm(&f);
	get_paths(&f);
	set_ants(&f);
	lem_in(&f);
	release(&f);
}
