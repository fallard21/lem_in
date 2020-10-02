/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 20:49:12 by user              #+#    #+#             */
/*   Updated: 2020/10/02 07:01:10 by fallard          ###   ########.fr       */
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
# define MEM_FREE_ERR	"ERROR: No memory to free on passed pointer"
# define PATH_ERR		"ERROR: Path creation error"
# define NO_PATHS_ERR	"ERROR: No paths constructed"
# define ANTS_MOVE_ERR	"ERROR: Ants moving error"
# define MOVE_RES_ERR	"ERROR: Not all ants have reached the end"

# define IN 1
# define OUT 2

/*
**	Structures
*/

typedef struct s_link		t_link;
typedef struct s_room		t_room;
typedef struct s_frame		t_frame;
typedef struct s_input		t_input;
typedef struct s_path		t_path;
typedef struct s_recovery	t_recovery;

struct				s_input
{
	char			*line;
	t_input			*next;
};

struct				s_link
{
	t_room			*room;
	t_link			*next;
	t_link			*prev;
	int				edge_size;
	int				status;
};

struct				s_room
{
	char			*name;
	int				coord[2];
	int				ants;
	int				ant_name;
	int				level;
	int				vertex_size;
	int				num_links;
	int				output_links;
	int				input_links;
	int				visit;
	int				suur_type;
	t_room			*prev;
	t_link			*links;
	t_link			*output;
	t_link			*input;
	t_room			*next;
};

struct				s_path
{
	t_link			*start;
	t_link			*end;
	t_path			*next;
	int				on_work;
	int				len;
	int				ants_togo;
	int				ants_pass;
};

struct				s_frame
{
	t_room			*start;
	t_room			*end;
	int				cmd;
	int				num_ants;
	int				ant_name;
	int				num_rooms;
	t_input			*input;
	t_room			*map;
	t_room			*map_copy;	// static pointer to use in case of EXIT and clear all data
	t_path			*paths;
};

struct				s_recovery
{
	t_room			*room;
	t_recovery		*next;
};


#endif
