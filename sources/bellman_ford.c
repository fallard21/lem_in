/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:02:05 by fallard           #+#    #+#             */
/*   Updated: 2020/09/23 07:53:46 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

#define N 14
#define M 7
static int graf[N][M] = {{0, 1, 2, 3, -1, -1, -1},		// out
						{1, 4, 5, -1, -1, -1, -1},		// out
						{2, 4, 5, -1, -1, -1, -1},		// out
						{3, 5, 6, -1, -1, -1, -1},		// out
						{4, 1, 2, 7, -1, -1, -1},		// out
						{5, 1, 2, 3, 8, 9, -1},			// out
						{6, 3, 9, -1, -1, -1, -1},		// out
						{7, 4, 10, -1, -1, -1, -1},		// out
						{8, 5, 11, -1, -1, -1, -1},		// out
						{9, 5, 6, 12, -1, -1, -1},		// out
						{10, 7, 99, -1, -1, -1, -1},	// out
						{11, 7, 8, 9, -1, -1, -1},		// out
						{12, 8, 9, 99, -1, -1, -1},		// out
						{99, -1, -1, -1, -1, -1, -1}};	// in

//static int in[12][12] = {1};

//static int	out[24][24] = {0};

t_room	*new_room(int name, int flag)
{
	t_room	*res;

	res = ft_calloc(1, sizeof(t_room));
	res->in = (flag) ? 0 : 1;
	res->out = (flag) ? 1 : 0;
	res->name = ft_itoa(name);
	res->vertex_size = INT_MAX;
	res->level = -1;
	return (res);
}

void	create_graf(t_frame *frame)
{
	t_room	**tmp;
	int i;
	int j;

	tmp = &frame->map;
	for (i = 0; i < N; i++)
	{
			//ft_printf("%d ", i);
		if (graf[i][0] == 0)
		{
			frame->start = new_room(0, 1);

		}
		else if (graf[i][0] == 99)
		{
			frame->end = new_room(99, 0);
		}
		else
		{
			*tmp = new_room(graf[i][0], 0);
			tmp = &(*tmp)->next;
			*tmp = new_room(graf[i][0], 1);
			tmp = &(*tmp)->next;
		}
	}
	
}

t_room	*get_room(t_room *start, int name)
{
	char *sname;

	sname = ft_itoa(name);

	while (start)
	{
		if (ft_strcmp(start->name, sname) == 0 && start->in)
			break;
		start = start->next;
	}
	free (sname);
	return (start);
}

t_link	*get_links(t_room *map, int j)
{
	t_link	*res;
	t_link	**tmp;
	int		i;

	i = 1;
	res = NULL;
	tmp = &res;

	while (graf[j][i] != -1)
	{
		*tmp = ft_calloc(1, sizeof(t_link));
		(*tmp)->room = get_room(map, graf[j][i]);
		(*tmp)->edge_size = 1;
		tmp = &(*tmp)->next;
		i++;
	}
	return (res);
}

void	add_links(t_room *map, t_room *start, t_room *end)
{
	t_room	*tmp;
	int		j;

	start->links = get_links(map, 0);
	tmp = map;
	j = 1;
	while (map)
	{
		if (!ft_strcmp(map->name, "0") || !ft_strcmp(map->name, "99"))
		{
			map = map->next;
			continue;
		}
		if (map->in)
		{
			map->links = ft_calloc(1, sizeof(t_link));
			map->links->room = map->next;
			map->links->edge_size = 0;
		}
		else
		{
			map->links = get_links(tmp, j++);
		}
		map = map->next;
	}
	
}

void	glue_list(t_frame *frame)
{
	t_room	*kek;

	frame->start->next = frame->map;

	kek = frame->map;
	while (kek && kek->next)
		kek = kek->next;
	kek->next = frame->end;

	frame->map = frame->start;
	
}

int		bellman_ford(t_frame *frame, t_room *start)
{
	t_room	*current;
	t_link	*tmp;

	int		i;
	int		n, m;
	int		flag;

	i = 0;
	n = 0;
	m = 0;
	current = start;
	while (i++ < (frame->num_rooms - 1))
	{
		current = start;
		while (current)
		{
			tmp = current->links;
			while (tmp)
			{
				n = current->vertex_size + tmp->edge_size;
				if (n < tmp->room->vertex_size)
					tmp->room->vertex_size = n;
				tmp = tmp->next;
			}
			current = current->next;
		}
	}
	return (0);
}

void	suurballe(t_frame *frame)
{
	frame->num_rooms = 26;
	
	create_graf(frame);
	frame->start->vertex_size = 0;
	glue_list(frame);
	add_links(frame->map, frame->start, frame->end);
	//print_suurb(frame->map);
	
	bellman_ford(frame, frame->start);
	print_suurb(frame->map);
	//frame->start->level = 0;
	//frame->end->level= INT_MAX;
	//bfs_queue(frame->start); print_all_info(frame->start);
	return ;
}
