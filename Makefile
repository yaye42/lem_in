# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 11:17:35 by yaye              #+#    #+#              #
#    Updated: 2019/11/28 11:17:37 by yaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC	 = clang
CFLAGS = -Wall -Wextra -Werror -Wpadded
CFLAGS += -fsanitize=address,undefined -g3
INCL = -Iincludes -Ilibft/includes

LBFT = libft/libft.a

LM_S =  get_paths.c get_farm.c get_rooms.c lem_in.c tools.c
CM_S = 
ODIR = ./objects/
LM_O = $(patsubst %.c, $(ODIR)%.o, $(LM_S))
CM_O = $(patsubst %.c, $(ODIR)%.o, $(CM_S))

HEAD = includes/lem_in.h

vpath %.c ./sources/

all : $(ODIR) $(NAME)

$(NAME) : $(LBFT) $(CM_O) $(LM_O)
	$(CC) $(CFLAGS) -o $@ $(LM_O) $(CM_O) $(INCL) -Llibft/ -lft
	@printf "\033[1;32m%35s	COMPILED\033[0m\n" "$(NAME)"

$(LBFT) : FORCE
	@$(MAKE) -C libft

$(CM_O) : $(ODIR)%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(LM_O) : $(ODIR)%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(PS_O) : $(ODIR)%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(ODIR) :
	mkdir $@

FORCE :

clean :
	$(RM) $(CM_O)
	$(RM) $(LM_O)
	$(RM) $(PS_O)
	$(RM) $(ARG)
	$(RM) -R $(ODIR)
	$(MAKE) clean -C libft

fclean : clean
	$(RM) $(NAME)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(NAME)"
	$(RM) $(LBFT)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(LBFT)"

re : fclean
	@$(MAKE)

#.SILENT:
.PHONY: all FORCE clean fclean re
