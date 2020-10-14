/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:39:09 by user              #+#    #+#             */
/*   Updated: 2020/10/15 01:17:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

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
	if (!line || line[0] == '\0')
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
	if (!line || line[0] == '\0')
		lem_error(READ_ERR, stor);
	return (line[0] == '#');
}

int			is_room_name(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	if (line[0] == 'L' || line[0] == '#')
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int			is_room(char *line, t_frame *stor)
{
	char	**split;
	int		res;

	res = 1;
	if (!line || line[0] == '\0')
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
