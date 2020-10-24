/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:43:44 by fallard           #+#    #+#             */
/*   Updated: 2020/10/24 16:14:23 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void	init_stat(t_stat *stat)
{
	stat->key_move = 1;
	stat->key_map = 1;
}

void	put_usage(char *av)
{
	if (av)
	{
		write(2, "lem-in: invalid key: '", 23);
		write(2, av, ft_strlen(av));
		write(2, "'\n", 3);
		write(2, "Usage:\n", 8);
		write(2, "\t./lem-in [--option]... < map\n", 31);
		write(2, "\t--help\t\t output manual\n", 25);
	}
	else
	{
		write(1, "options:\n", 10);
		write(1, "\t--help\t\toutput manual\n", 24);
		write(1, "\t--map\t\toutput graph map\n", 26);
		write(1, "\t--move\t\toutput ant's moving\n", 30);
		write(1, "\t--stat\t\toutput graph statistic\n", 33);
		write(1, "\t--all\t\tuse all options (except --help)\n", 41);
	}
	exit(EXIT_FAILURE);
}

void	ft_parse_flags(t_stat *stat, int ac, char **av)
{
	int i;

	if (ac == 1)
		return (init_stat(stat));
	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--help") == 0)
			put_usage(NULL);
		if (ft_strcmp(av[i], "--map") == 0)
			stat->key_map = 1;
		else if (ft_strcmp(av[i], "--stat") == 0)
			stat->key_stat = 1;
		else if (ft_strcmp(av[i], "--move") == 0)
			stat->key_move = 1;
		else if (ft_strcmp(av[i], "--all") == 0)
			stat->key_all = 1;
		else
			put_usage(av[i]);
		i++;
	}
}

void	ft_print_path(t_frame *frame, t_path *p)
{
	t_link	*tmp;
	int		i;

	i = 0;
	while (p)
	{
		ft_printf("%d) Path size: %d | %s | ants on path: %d\n\t", i + 1,
		p->len, (p->ants_togo) ? "USED" : "UNUSED", p->ants_togo);
		tmp = p->start;
		while (tmp)
		{
			if (!tmp->next)
				ft_printf("%s", tmp->room->name);
			else
				ft_printf("%s -> ", tmp->room->name);
			tmp = tmp->next;
		}
		p = p->next;
		i++;
		ft_printf("\n");
	}
	ft_printf("Number of steps: %d\n\n", frame->current_steps);
}
