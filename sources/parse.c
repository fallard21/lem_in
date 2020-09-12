/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:01:22 by user              #+#    #+#             */
/*   Updated: 2020/09/12 00:43:35 by fallard          ###   ########.fr       */
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

t_frame		*init_storage(t_input **input)
{
	t_frame		*stor;

	if (!(stor = ft_calloc(1, sizeof(t_frame))))
		return (NULL);
	stor->input = (*input);
	stor->map = NULL;
	stor->map_copy = NULL;
	while (*input && is_hash((*input)->line, stor))
		(*input) = (*input)->next;
	if (*input &&
	(ft_isdigit((*input)->line[0]) || (*input)->line[0] == '-') &&
	is_valid_ants((*input)->line, stor))
		stor->num_ants = ft_atoi((*input)->line);
	else
		lem_error(NOT_ENOUGH_ERR, stor);
	stor->num_rooms = 0;
	stor->cmd = NO_SIG;
	stor->end = NULL;
	stor->start = NULL;
	(*input) = (*input)->next;
	return (stor);
}

// добавить флаг is_link - когда начинается чтение комнат. Передаем его в проверку на комнаты - если флаг 1,
// значит, после ссылок пришла комната - это невалид. Lem_error()

t_room		*parse_input(t_input *input, t_frame *stor)
{
	if (!input)
		return (NULL);
	while (input)
	{
		if (is_hash(input->line, stor))
			parse_start_end(input->line, stor);
		else
		{
			if (is_room(input->line, stor))
				stor->map = add_room(stor->map, create_room(stor, input->line), stor);
			else if (is_link(input->line, stor))
				handle_links(stor->map, input->line, stor);
			else
				lem_error(INPUT_ERR, stor);
		}
		input = input->next;
	}
	stor->map_copy = stor->map;
	// JUST FOR TESTING ***** DELETE
	//print_room_list(stor, stor->map ? stor->map : NULL);
	return (stor->map);
}
