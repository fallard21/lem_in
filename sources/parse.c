/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:01:22 by user              #+#    #+#             */
/*   Updated: 2020/09/28 21:45:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void		parse_start_end(char *line, t_frame *stor)
{
	if (!line)
		lem_error(READ_ERR, stor);
	if (line && !ft_strcmp(line, "##start"))
	{
		if (stor->start)
			lem_error(CMD_ST_ERR, stor);
		stor->cmd = START_SIG;
	}
	if (line && !ft_strcmp(line, "##end"))
	{
		if (stor->end)
			lem_error(CMD_END_ERR, stor);
		stor->cmd = END_SIG;
	}
}

static void	set_stor_params(t_frame *stor)
{
	stor->map = NULL;
	stor->map_copy = NULL;
	stor->num_rooms = 0;
	stor->ant_name = 1;
	stor->cmd = NO_SIG;
	stor->end = NULL;
	stor->start = NULL;
	stor->paths = NULL;
}

t_frame		*init_storage(t_input **input)
{
	t_frame		*stor;

	if (!(stor = ft_calloc(1, sizeof(t_frame))))
		return (NULL);
	stor->input = (*input);
	set_stor_params(stor);
	while (*input && is_hash((*input)->line, stor))
		(*input) = (*input)->next;
	if (*input &&
	(ft_isdigit((*input)->line[0]) || (*input)->line[0] == '-') &&
	is_valid_ants((*input)->line, stor))
		stor->num_ants = ft_atoi((*input)->line);
	else
		lem_error(NOT_ENOUGH_ERR, stor);
	(*input) = (*input)->next;
	return (stor);
}

t_room		*parse_input(t_input *input, t_frame *stor)
{
	int		link_flag;

	link_flag = 0;
	if (!input)
		return (NULL);
	while (input)
	{
		if (is_hash(input->line, stor))
			parse_start_end(input->line, stor);
		else
		{
			if (is_room(input->line, stor))
				link_flag ? lem_error(INPUT_ERR, stor) :
				(stor->map = add_room(stor->map,
				create_room(stor, input->line), stor));
			else if (is_link(input->line, stor))
				link_flag = handle_links(stor->map, input->line, stor);
			else
				lem_error(INPUT_ERR, stor);
		}
		input = input->next;
	}
	return (stor->map_copy = stor->map);
}

t_frame		*create_map(void)
{
	t_room		*map;
	t_input		*input;
	t_frame		*stor;

	if (!(input = read_input()))
	{
		free_input(input);
		lem_error(READ_ERR, NULL);
	}
	stor = init_storage(&input);
	if (!(map = parse_input(input, stor)) || !is_valid_map(stor) ||
	!bfs_queue(stor->start))
		lem_error(NOT_ENOUGH_ERR, stor);
	// input_print_and_free(stor);
	// print_room_list(stor, stor->map);
	return (stor);
}
