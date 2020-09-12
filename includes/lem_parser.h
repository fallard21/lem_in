/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 09:23:10 by user              #+#    #+#             */
/*   Updated: 2020/09/12 00:33:06 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_PARSER_H
# define LEM_PARSER_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# include "libft.h"
# include "struct.h"


# define START_SIG	1
# define END_SIG	2
# define NO_SIG		0


/*
**	Functions to parse input and create map
*/

t_frame		*create_map();
t_input		*read_input();
t_input		*create_input_item(char *line);

t_room		*parse_input(t_input *input, t_frame *stor);
t_frame		*init_storage(t_input **input);
void		parse_start_end(char *line, t_frame *stor);

t_room		*create_room(t_frame *stor, char *line);
t_room		*add_room(t_room *room, t_room *new_room, t_frame *stor);

int			is_valid_ants(char *str, t_frame *stor);
int			is_room(char *line, t_frame *stor);
int			is_hash(char *line, t_frame *stor);
int			is_room_name(char *line);
int			is_link(char *line, t_frame *stor);
int			is_valid_map(t_frame *stor);

void		handle_links(t_room *room, char *line, t_frame *stor);
void		find_rooms(t_room *room, const char *r1, const char *r2, t_frame *stor);
void		set_links(t_room *room1, t_room *room2, t_frame *stor);
t_link		*create_link(t_room *room, t_frame *stor);


void		lem_error(char *str, t_frame *stor);
void		lem_free(t_frame *stor);
void		free_input(t_input *input);
void		free_stor(t_frame *stor);
void		free_map(t_room *room);


/*
**	Functions to handle paths
*/

t_path		*create_path(t_frame *stor);


/*
**	JUST FOR TESTING ********************** DELETE
*/ 

void		print_input(t_input *input);
void		print_room(t_room *room);
void		print_room_list(t_frame *stor, t_room *room);


////

void	print_graf(t_frame *frame);
void	print_rooms(t_room *room);
void	print_links(t_link *links);
void	print_all_info(t_room *room);


void	bfs_list(t_frame *frame);
void	del_links(t_room *room, t_link **head);
void	del_all_links(t_link **link);

void	ft_exit(char *error);
void	free_link(t_link **link);
void	free_room(t_room **room);

void	bfs_queue(t_room *start);

void	free_all(t_room *start);
#endif
