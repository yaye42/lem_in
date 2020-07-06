/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 13:26:16 by yaye              #+#    #+#             */
/*   Updated: 2020/06/19 13:26:17 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** FREES ALL ALLOCATED MEMORY BY malloc()
*/

void	release(t_farm *f)
{
	t_room	*p;

	if (f->buf && ft_memset(f->buf, 0, ft_strlen(f->buf)))
		ft_memdel((void **)&f->buf);
	if (f->map && ft_memset(f->map, 0, ft_strlen(f->map)))
		ft_memdel((void **)&f->map);
	while (f && f->head)
	{
		p = f->head->next;
		if (f->head->name \
			&& ft_memset(f->head->name, 0, ft_strlen(f->head->name)))
			ft_memdel((void **)&f->head->name);
		if (f->head->links \
			&& ft_memset(f->head->links, 0, f->n_rooms * 4))
			ft_memdel((void **)&f->head->links);
		ft_memdel((void **)&f->head);
		f->head = p;
	}
}

/*
** LEAVES THE PROGRAM AFTER RELEASING ALL ALLOCATED MEMORY
*/

void	leave(t_farm *f, char *s)
{
	release(f);
	write(2, "ERROR", 5);
	if (!s)
		write(2, "\n", 1);
	else
		write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

/*
** COPIES f->buf IN f->map
*/

int		get_map(t_farm *f, char *buf)
{
	int			i;
	int			j;
	char		*new;

	if (!f->map)
		leave(f, "\n");
	i = ft_strlen(f->map);
	if (((i % MSIZE) + (j = ft_strlen(buf) + 2)) >= MSIZE)
	{
		if (!(new = malloc(sizeof(char) * MSIZE * (((i + j) / MSIZE) + 1))))
			leave(f, ": malloc failure in get_map().\n");
		i = -1;
		while (f->map[++i])
			new[i] = f->map[i];
		ft_memset(f->map, 0, ft_strlen(f->map));
		ft_memdel((void **)&f->map);
		f->map = new;
	}
	j = -1;
	while (buf[++j])
		f->map[i++] = buf[j];
	f->map[i] = '\n';
	f->map[++i] = 0;
	return (1);
}

/*
** RETURNS 1 IF buf IS A KNOWN COMMAND
** RETURNS 2 IF buf IS AN UNKNOW COMMAND OR COMMENT
** ELSE IT RETURNS 0
*/

int		is_com(t_farm *f, char *buf)
{
	if (buf[0] == '#')
	{
		if (f->starting == 1 || f->ending == 1)
			return (0);
		get_map(f, buf);
		if (ft_strequ(buf, "##start"))
		{
			if (!f->starting)
				return (f->starting = 1);
			leave(f, ": multiple ##start command.\n");
		}
		else if (ft_strequ(buf, "##end"))
		{
			if (!f->ending)
				return (f->ending = 1);
			leave(f, ": multiple ##end command.\n");
		}
		else
			return (2);
	}
	return (0);
}

/*
** CHECK IF buf IS AN ALREADY EXISTING NAME IN THE FARM
*/

t_room	*is_saved_name(t_farm *f, char *buf, size_t n)
{
	t_room	*r;

	r = f->head;
	while (r)
	{
		if (ft_strnequ(r->name, buf, (n != 0) ? n : ft_strlen(r->name) + 1))
			return (r);
		r = r->next;
	}
	return (NULL);
}
