/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_farm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 13:27:34 by yaye              #+#    #+#             */
/*   Updated: 2020/06/19 13:27:36 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** RETURN links WHICH IS A BOARD CONTAINING THE ROOMS NEXT TO IT
** BOARD'S SIZE == TOTAL NUMBER OF ROOMS
*/

t_room	**new_links(t_farm *f)
{
	t_room	**links;
	int		j;

	if (!(links = malloc(sizeof(t_room *) * f->n_rooms)))
		leave(f, ": malloc failure in new_links().\n");
	j = 0;
	while (j < f->n_rooms)
		links[j++] = NULL;
	return (links);
}

/*
** buf == "room1-room2"
** ADD room1 IN room2->links[] AND VICE VERSA
*/

void	add_link(t_farm *f, char *buf)
{
	t_room	*r;
	t_room	*r2;
	size_t	i;

	i = 0;
	while (buf[i] != '-')
		i = i + 1;
	r = is_saved_name(f, buf, i);
	if (!r->links)
		r->links = new_links(f);
	r2 = is_saved_name(f, buf + i + 1, 0);
	if (!r2->links)
		r2->links = new_links(f);
	i = 0;
	get_map(f, buf);
	while (r->links[i])
		if (ft_strequ(r->links[i++]->name, r2->name))
			return ;
	r->links[i] = r2;
	r->n_links = r->n_links + 1;
	i = 0;
	while (r2->links[i])
		i = i + 1;
	r2->links[i] = r;
	r2->n_links = r2->n_links + 1;
}

/*
** CHECK IF buf IS A VALID FORMAT OF A LINK
*/

int		is_link(t_farm *f, char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!buf)
		leave(f, ": incomplete map.\n");
	if (!ft_isprint(buf[i]) || ft_isblanc(buf[i]) \
		|| buf[i] == 'L' || buf[i] == '#')
		return (0);
	while (buf[i] && ft_isprint(buf[i]) && !ft_isblanc(buf[i]) \
		&& buf[i] != '-')
		i = i + 1;
	if (i == 0 || buf[i] != '-' || !is_saved_name(f, buf, i))
		return (0);
	j = i + 1;
	if (!ft_isprint(buf[j]) || ft_isblanc(buf[j]) \
		|| buf[j] == 'L' || buf[j] == '#')
		return (0);
	while (buf[j] && ft_isprint(buf[j]) && !ft_isblanc(buf[j]) \
		&& buf[j] != '-')
		j = j + 1;
	if (j - i - 1 == 0 || buf[j] != 0 || !is_saved_name(f, buf + i + 1, 0))
		return (0);
	add_link(f, buf);
	return (1);
}

/*
** f->ending == 0
**		ERROR: no starting and/or ending room.
** f->ending == 1
**		ERROR: no valid valid room after ##end command.
** f->ending == 2
**		OK
**
** CHECK IF THERE IS AT LEAST 1 SOLUTION
** THEN SORT ROOMS NEXT TO THE f->end ENDING ROOM BY INCREASING LEVEL
*/

void	check_farm(t_farm *f)
{
	int		i;
	int		j;
	t_room	*p;

	leveling(NULL, f->start, -1);
	leveling(f, f->start, 0);
	if (f->end->level < 1)
		leave(f, ": no solution.\n");
	f->end->n_links = 0;
	i = -1;
	while (f->end->links[++i])
	{
		j = i;
		while (f->end->links[++j])
			if (f->end->links[j]->level < f->end->links[i]->level)
			{
				p = f->end->links[i];
				f->end->links[i] = f->end->links[j];
				f->end->links[j] = p;
			}
		if (f->end->links[i]->level > 0)
			f->end->n_links = f->end->n_links + 1;
	}
	ft_printf("%s\n", f->map);
}

/*
** FARM PARSING
*/

void	get_farm(t_farm *f)
{
	if (read(0, &f->buf, 0) < 0)
		leave(f, ": couldn't read.\n");
	while (get_next_line(0, &f->buf) > 0)
	{
		if (ft_stoi(f->buf, &f->n_ants, 0) && f->n_ants > 0 \
			&& get_map(f, f->buf))
			break ;
		else if (is_com(f, f->buf) == COMMENT)
			ft_memdel((void **)&f->buf);
		else
			leave(f, ": no valid number for n_ants.\n");
	}
	ft_memdel((void **)&f->buf);
	while ((get_next_line(0, &f->buf) > 0) && get_rooms(f, f->buf))
		ft_memdel((void **)&f->buf);
	is_link(f, f->buf) ? ft_memdel((void **)&f->buf) \
		: leave(f, ": no valid link after last valid room.\n");
	while ((get_next_line(0, &f->buf) > 0))
	{
		if (!is_com(f, f->buf) && !is_link(f, f->buf))
			leave(f, ": bad link format or room does not exist.\n");
		ft_memdel((void **)&f->buf);
	}
	ft_memdel((void **)&f->buf);
	check_farm(f);
}
