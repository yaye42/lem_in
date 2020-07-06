/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:22:47 by yaye              #+#    #+#             */
/*   Updated: 2020/02/13 15:22:49 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define N_ROOMS_MAX 32767
# define MSIZE 16384
# define COMMENT 2
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

/*
** >---------------------------- LEM_IN STRUCTURES ---------------------------<
*/

typedef struct	s_room
{
	char				*name;
	int					x;
	int					y;
	int					level;
	int					n_links;
	int					len;
	int					ants;
	struct s_room		**links;
	struct s_room		*epath;
	struct s_room		*spath;
	struct s_room		*next;
}				t_room;

typedef struct	s_farm
{
	char				*buf;
	char				*map;
	int					n_ants;
	int					n_rooms;
	int					starting;
	int					ending;
	t_room				*head;
	t_room				*tail;
	t_room				*start;
	t_room				*end;
}				t_farm;

/*
** >-------------------------------- FUNCTIONS -------------------------------<
*/

void			release(t_farm *f);
void			leave(t_farm *f, char *s);
int				is_com(t_farm *f, char *buf);
t_room			*is_saved_name(t_farm *f, char *buf, size_t n);
int				get_map(t_farm *f, char *buf);
int				get_rooms(t_farm *f, char *buf);
void			get_farm(t_farm *f);
void			leveling(t_farm *f, t_room *room, int lv);
int				get_paths(t_farm *f);
void			set_ants(t_farm *f);
void			lem_in(t_farm *f, int n);

#endif
