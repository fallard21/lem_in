/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 21:41:24 by fallard           #+#    #+#             */
/*   Updated: 2020/09/12 00:40:19 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>

typedef struct s_room	t_room;
typedef struct s_link	t_link;
typedef struct s_frame	t_frame;

struct	s_link
{
	t_room	*room;
	t_link	*next;
};

struct	s_room
{
	char	*name;
	int		coord[2];
	int		ant;
	int		level;
	int		visit;
	int		output_links;
	int		input_links;
	t_room	*next;
	t_link	*links;
};

struct s_frame
{
	int		ants;
	t_room	*all;
};

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
