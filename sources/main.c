/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 11:34:11 by yaye              #+#    #+#             */
/*   Updated: 2020/07/06 11:34:13 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_farm	f;
	int		n;

	f.n_ants = 0;
	f.n_rooms = 0;
	f.starting = 0;
	f.ending = 0;
	f.head = NULL;
	f.tail = NULL;
	f.start = NULL;
	f.end = NULL;
	f.buf = NULL;
	if (!(f.map = malloc(sizeof(char) * MSIZE)))
		return (0);
	ft_memset(f.map, 0, MSIZE);
	get_farm(&f);
	get_paths(&f);
	set_ants(&f);
	n = 0;
	lem_in(&f, n);
	release(&f);
}
