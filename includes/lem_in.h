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
# define COMMENT 2
# include "libft.h"

/*
** >---------------------------- LEM_IN STRUCTURES ---------------------------<
*/

typedef struct	s_room					//malloc
{
	char				*name;			//malloc
	int					x;
	int					y;
	int					level;			//set à 0
	int					n_links;
	int					len;
	int					ants;
	struct s_room		**links;		//malloc
	struct s_room		*epath;
	struct s_room		*spath;
	struct s_room		*next;
}				t_room;

typedef struct	s_farm
{
	char				*buf;			//malloc
	int					n_ants;
	int					n_rooms;	//taille des room->links[]
	int					starting;	//utilisé que dans le parsing, peut être recyclé
	int					ending;		//devient le nombre de paths trouvés
	t_room				*head;  	//start of the list
	t_room				*tail; 		//last of the list peut être recyclé
	t_room				*start;     //starting room
	t_room				*end;     	//ending room 
}				t_farm;

/*
** >-------------------------------- FUNCTIONS -------------------------------<
*/

void	release(t_farm *f);
void	leave(t_farm *f, char *s);
int		is_com(t_farm *f, char *buf);
t_room	*is_saved_name(t_farm *f, char *buf, size_t n);
int		get_rooms(t_farm *f, char *buf);
void	get_farm(t_farm *f);
void	leveling(t_farm *f, t_room *room, int lv);
int		get_paths(t_farm *f);

void	print_rooms(t_farm *f, char *s);
void	pf_room_name(t_farm *f, char *s);
void	print_paths(t_farm *f);
void	show_farm(t_farm *f);
void	show_links(t_room *r);
#endif