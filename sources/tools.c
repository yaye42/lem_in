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

#include <stdlib.h>
#include <unistd.h>
#include "lem_in.h"

void	show_room(t_room *r)
{
	ft_printf("%s 	lv.%d 	n_links = %d\n", r->name, r->level, r->n_links);
}

void	show_links(t_room *r)
{
	int	i;

	i = 0;
	ft_printf("%s's links:\n", r->name);
	while (r->links[i])
	{
		ft_printf("				");
		ft_printf("%s\n", r->links[i]->name);
		i = i + 1;
	}
	if (r->spath)
		ft_printf("     spath: %s\n", r->spath->name);
	if (r->epath)
		ft_printf("     epath: %s\n", r->epath->name);
}

/*
** print all rooms (if s == NULL)
** or a specific room (if s)
*/

void	print_rooms(t_farm *f, char *s)
{
	t_room	*r;

	r = f->head;
	while (r)
	{
		if (s == NULL || ft_strequ(s, r->name))
		{
			show_room(r);
			if (r->links)
				show_links(r);
		}
		r = r->next;
	}
}

void	print_paths(t_farm *f)
{
	t_room	*r;
	int		i;
	t_room	*p;
	int		j;

	r = f->start;
	i = 0;
	while ((p = f->start->links[i]))
	{
		j = 0;
		if (p->spath)
			ft_printf("lenght: %d 	ants: %d\nstart(%s)->", r->links[i]->len, r->links[i]->ants, r->name);
		while (p && p->spath)
		{
			ft_printf("%s->", p->name);
			p = p->spath;
			j = j + 1;
			if (p->spath == f->start)
				ft_printf("\nlenght: %d 	ants: %d\n", p->len, p->ants);
		}
		if (j)
			ft_printf("end(%s)\n\n", p->name);
		i = i + 1;
	}
	if (r->spath)
		ft_printf("start(%s)->end(%s)\n", f->start->name, r->spath);
}

/*
** FREES ALL ALLOCATED MEMORY BY malloc()
*/

void	release(t_farm *f)
{
	t_room	*p;

	if (f->buf)
		ft_memdel((void **)&f->buf);
	while (f && f->head)
	{
		p = f->head->next;
		if (f->head->name)
			ft_memdel((void **)&f->head->name);
		if (f->head->links)
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
** RETURNS 1 IF buf IS A KNOWN COMMAND
** RETURNS 2 IF buf IS AN UNKNOW COMMAND OR COMMENT
** ELSE IT RETURNS 0
*/

int		is_com(t_farm *f, char *buf)
{
	if (ft_strequ(buf, "##start"))
	{
		if (f->starting == 1 || f->ending == 1)
			return (0);
		if (f->starting)
			leave(f, ": no valid room after ##start command.\n");
		return (f->starting = 1);
	}
	else if (ft_strequ(buf, "##end"))
	{
		if (f->starting == 1 || f->ending == 1)
			return (0);
		if (f->ending)
			leave(f, ": no valid room after ##end command.\n");
		return (f->ending = 1);
	}
	else if (buf[0] == '#')
	{
		if (f->starting == 1 || f->ending == 1)
			return (0);
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
