/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:39:09 by user              #+#    #+#             */
/*   Updated: 2020/10/12 16:27:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void		input_print_and_free(t_frame *stor)
{
	t_input		*input;

	input = stor->input;
	while (input)
	{
		ft_putendl_fd(input->line, 1);
		input = input->next;
	}
	ft_putchar_fd('\n', 1);
	free_input(stor->input);
	stor->input = NULL;
}

int			is_valid_map(t_frame *stor)
{
	if (!stor)
		return (0);
	if (!stor->start || !stor->end || stor->start->num_links == 0 ||
	stor->end->num_links == 0 || !stor->map || stor->num_rooms == 1 ||
	stor->num_ants == 0)
		return (0);
	return (1);
}

int			is_valid_ants(char *str, t_frame *stor)
{
	if (!str)
		return (0);
	if (str[0] == '0' || !ft_isposint_str(str))
		lem_error(NO_ANTS_ERR, stor);
	return (1);
}

int			is_link(char *line, t_frame *stor)
{
	char	**split;
	int		res;

	res = 1;
	if (!line)
		lem_error(READ_ERR, stor);
	if (!(split = ft_strsplit(line, '-')))
	{
		ft_free_splited(split);
		lem_error(ALLOC_ERR, stor);
	}
	if (ft_len_splited(split) != 2 || !is_room_name(split[0]) ||
	!is_room_name(split[1]))
		res = 0;
	ft_free_splited(split);
	return (res);
}

int			is_hash(char *line, t_frame *stor)
{
	if (!line)
		lem_error(READ_ERR, stor);
	return (line[0] == '#');
}

int			is_room_name(char *line)
{
	if (!line)
		return (0);
	if (line[0] == 'L' || line[0] == '#')
		return (0);
	return (1);
}

int			is_room(char *line, t_frame *stor)
{
	char	**split;
	int		res;

	res = 1;
	if (!line)
		lem_error(READ_ERR, stor);
	if (!(split = ft_strsplit(line, ' ')))
	{
		ft_free_splited(split);
		lem_error(ALLOC_ERR, stor);
	}
	if (ft_len_splited(split) != 3 || !is_room_name(split[0]) ||
	!ft_isint_str(split[1]) || !ft_isint_str(split[2]))
		res = 0;
	ft_free_splited(split);
	return (res);
}
