/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 09:23:10 by user              #+#    #+#             */
/*   Updated: 2020/09/28 22:12:26 by user             ###   ########.fr       */
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

t_frame		*create_map(void);
t_input		*read_input(void);
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

int			handle_links(t_room *room, char *line, t_frame *stor);
void		find_rooms(t_room *room, char *r1, char *r2, t_frame *stor);
void		set_links(t_room *room1, t_room *room2, t_frame *stor);
t_link		*create_link(t_room *room, t_frame *stor, int weight);

void		lem_error(char *str, t_frame *stor);
void		lem_free(t_frame *stor);
void		free_input(t_input *input);
void		free_stor(t_frame *stor);
void		free_map(t_room *room);
void		del_room(t_room **room);
void		free_paths(t_path *paths);
void		input_print_and_free(t_frame *stor);

/*
**	Functions to handle paths
*/

t_path		*create_paths(t_frame *stor);
void		construct_path(t_path *path, t_link *lev1, t_frame *stor);
void		add_path(t_path *path, t_frame *stor);
t_path		*create_path_node(t_frame *stor);

/*
**	Functions to move ants
*/

void		handle_ants_move(t_frame *stor);
void		set_ants_on_paths(t_frame *stor);
int			move_through_path(t_path *path, t_frame *stor);
void		move_from_start(t_path * path, t_frame *stor);
void		move_by_mid(t_link *link);
void		move_to_end(t_link *link, t_path *path, t_frame *stor);
void		print_ant_action(int ant_name, char *room_name);	// USE printf - refactore to ft_printf
void		move_simple_path(t_path *path, t_frame *stor);

/*
**	Functions to set direct graph
*/

void		set_direct_graph(t_frame *stor);

/*
**	JUST FOR TESTING ********************** DELETE
*/

void		print_input(t_input *input);
void		print_room(t_room *room);
void		print_room_list(t_frame *stor, t_room *room);
void		print_path(t_path *path, int ct);
void		print_path_list(t_frame *stor);
void		set_levels(t_frame *stor);			// emulate bfs levels





void	print_graf(t_frame *frame);
void	print_rooms(t_room *room);
void	print_links(t_link *links);
void	print_all_info(t_room *room);


void	bfs_list(t_frame *frame);
void	delete_link(t_room *head, char *name);
void	del_links(t_room *room, t_link **head);
void	del_all_links(t_link **link);

void	ft_exit(char *error);
void	free_link(t_link **link);
void	free_room(t_room **room);

int		bfs_queue(t_room *start);
int		is_empty(t_link *queue);
void	queue_push(t_link **queue, t_room *room);
t_room	*queue_pop(t_link **queue);

void	free_all(t_room *start);

t_link	*check_path(t_room *current);
t_link	*get_out_path(t_room *current);

void	del_head(t_link **head, t_link **tmp);
void	del_middle(t_link *prev, t_link **tmp);
void	del_all_links(t_link **link);

void	print_patchs(t_room *start);


void	suurballe(t_frame *frame);
void	print_suurb(t_room *start);



#endif
