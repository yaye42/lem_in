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

#include "lem_in.h"

/*
** k + 1 == INDEX OF SHORTEST PATH
** j == INDEX OF NEXT "NOT FILLED PATH"
** ADDS 1 ANT IN EACH PATH FROM path(k) to path(j - 1)
** REMOVES AS MUCH ANTS FROM TOTAL n_ants
*/

void	dispantser(t_farm *f, int j, int k, int *ants)
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
			dispantser(f, j, i - 1, &ants);
	}
	while (ants > 0)
		dispantser(f, j, i - 1, &ants);
	while (f->start->links[i] && !(f->start->links[i]->len = 0))
		f->start->links[i++]->level = 0;
	if (f->start->spath && (f->start->ants = f->end->ants))
		f->end->ants = 0;
}

int		send_ant(t_room *room, int *k, int n, int ret)
{
	room->ants = room->ants + 1;
	room->len = n;
	*k = (*k != 0) ? write(1, " ", 1) : 1;
	ft_printf("L%d-%s", n, room->name);
	return (ret);
}

/*
** DURING PATHING, room->len IS THE ANT'S NUMBER
*/

void	lem_in(t_farm *f, int n)
{
	int		k;
	int		i;
	t_room	*p;

	if (f->end->ants == f->n_ants)
		return ;
	k = 0;
	i = -1;
	while ((p = f->end->links[++i]))
	{
		if (p == f->start && f->start->ants > 0)
			p->ants -= send_ant(p->spath, &k, ++n, 1);
		while (p->epath && p->epath != f->start)
		{
			p->ants -= (p->ants) ? send_ant(p->spath, &k, p->len, 1) : 0;
			p = p->epath;
		}
		if (p->epath == f->start && p->ants \
			&& (p->level = (p->level) ? send_ant(p->spath, &k, p->len, 1) : 1))
			p->ants -= send_ant(p, &k, ++n, 2);
		else if (p->epath == f->start && p->ants == 0 && p->level == 1)
			p->level = send_ant(p->spath, &k, p->len, 0);
	}
	write(1, "\n", 1);
	lem_in(f, n);
}
