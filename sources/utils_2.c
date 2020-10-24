/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:36:04 by user              #+#    #+#             */
/*   Updated: 2020/10/24 22:37:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct.h"

void		input_print_and_free(t_frame *stor)
{
	t_input		*input;
	char		*rqrd;

	input = stor->input;
	while (input)
	{
		if (ft_strstr(input->line, "#Here is the number of lines required: "))
		{
			rqrd = input->line + 39;
			if (ft_isint_str(rqrd))
				stor->stat.steps_rqrd = ft_atoi(rqrd);
		}
		if (stor->stat.key_map)
			ft_putendl_fd(input->line, 1);
		if (!stor->stat.key_map && stor->stat.steps_rqrd)
			break ;
		input = input->next;
	}
	if (stor->stat.key_map && !stor->stat.key_stat)
		ft_putchar_fd('\n', 1);
	free_input(stor->input);
	stor->input = NULL;
}

int			is_lead_zero(char *str)
{
	if (str)
		return ((ft_strlen(str) > 1 && str[0] == '0') ||
			(str[0] == '-' && ft_strlen(str) > 2 && str[1] == '0'));
	else
		return (1);
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
