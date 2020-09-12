/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 20:49:12 by user              #+#    #+#             */
/*   Updated: 2020/09/11 20:53:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
**	Error messages
*/

# define NOT_ENOUGH_ERR	"ERROR"
# define READ_ERR		"ERROR: Reading error occured"
# define INPUT_ERR		"ERROR: Incorrect input"
# define ROOM_DUPL_ERR	"ERROR: Room name or coords duplicate"
# define NO_ANTS_ERR	"ERROR: Incorrect number of ants on input"
# define ROOM_ADD_ERR	"ERROR: Room creation failed"
# define ALLOC_ERR		"ERROR: Allocation error"
# define LINKS_ERR		"ERROR: Links creation failed"
# define LINKS_DUPL_ERR "ERROR: Duplicate links"
# define CMD_ST_ERR		"ERROR: More than one ##start cmd"
# define CMD_END_ERR	"ERROR: More than one ##end cmd"

/*
**	Structures
*/

typedef struct s_link		t_link;
typedef struct s_room		t_room;
typedef struct s_frame		t_frame;
typedef struct s_input		t_input;
typedef struct s_path		t_path;

struct				s_input
{
	char			*line;
	t_input			*next;
};

struct				s_link
{
	t_room			*room;
	t_link			*next;
};

struct				s_room
{
	char			*name;
	int				coord[2];
	int				level;
	int				num_links;
	int				output_links;
	int				input_links;
	int				visit;
	t_room			*next;
	t_link			*links;
};

struct				s_path
{
	t_room			*start;
	t_path			*next;
	int				len;
};

struct				s_frame
{
	t_room			*start;
	t_room			*end;
	int				cmd;
	int				num_ants;
	int				num_rooms;
	t_input			*input;
	t_room			*map;
	t_room			*map_copy;	// static pointer to use in case of EXIT and clear all data
};

#endif