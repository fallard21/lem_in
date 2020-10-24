/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:43:44 by fallard           #+#    #+#             */
/*   Updated: 2020/10/24 18:27:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

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
	{
		stat->key_move = 1;
		stat->key_map = 1;
		return ;
	}
	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "--help"))
			put_usage(NULL);
		if (!ft_strcmp(av[i], "--map") || !ft_strcmp(av[i], "--all"))
			stat->key_map = 1;
		else if (!ft_strcmp(av[i], "--stat") || !ft_strcmp(av[i], "--all"))
			stat->key_stat = 1;
		else if (!ft_strcmp(av[i], "--move") || !ft_strcmp(av[i], "--all"))
			stat->key_move = 1;
		else
			put_usage(av[i]);
		i++;
	}
}

void	put_stat(t_frame *frame)
{
	float	dead_per;
	float	all_per;
	float	used_per;

	ft_print_path(frame, frame->paths, 1);
	dead_per = frame->stat.dead_ends / (float)frame->stat.vrtx_orig * 100;
	all_per = frame->stat.vrtx_in_all / (float)frame->stat.vrtx_orig * 100;
	used_per = frame->stat.vrtx_in_used / (float)frame->stat.vrtx_orig * 100;
	ft_printf("\n------------- Graph Statistic -------------\n\n");	
	ft_printf("Total vertices\t\t%4d\n", frame->stat.vrtx_orig);
	ft_printf("Dead ends\t\t%4d (%.2f%% of all)\n",
	frame->stat.dead_ends, dead_per);
	ft_printf("Vertices in all paths\t%4d (%.2f%% of all)\n",
	frame->stat.vrtx_in_all, all_per);
	ft_printf("Vertices in used paths\t%4d (%.2f%% of all)\n\n",
	frame->stat.vrtx_in_used, used_per);
	ft_printf("Ants count\t\t%4d\n", frame->num_ants);
	ft_printf("All paths\t\t%4d\n", frame->stat.all_paths);
	ft_printf("Used paths\t\t%4d\n", frame->stat.used_paths);
	ft_printf("Required steps\t\t%4d\n", frame->stat.steps_rqrd);
	ft_printf("Actual steps\t\t%4d\n", frame->current_steps);
	ft_printf("\n-------------------------------------------\n\n");
}

void	ft_print_path(t_frame *frame, t_path *p, int i)
{
	t_link	*tmp;

	ft_printf("\n------------- Paths Details -------------\n\n");
	while (p)
	{
		ft_printf("%d) Path size: %d | %s | ants on path: %d\n\t", i++,
		p->len, (p->ants_togo) ? "USED" : "UNUSED", p->ants_togo);
		tmp = p->start;
		while (tmp)
		{
			!tmp->next ? ft_printf("%s", tmp->room->name) :
			ft_printf("%s -> ", tmp->room->name);
			tmp = tmp->next;
		}
		frame->stat.vrtx_in_all += p->len;
		frame->stat.all_paths++;
		frame->stat.vrtx_in_used += p->ants_togo ? p->len : 0;
		frame->stat.used_paths += p->ants_togo ? 1 : 0;
		p = p->next;
		ft_printf("\n");
	}
}
