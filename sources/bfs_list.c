/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:07:49 by fallard           #+#    #+#             */
/*   Updated: 2020/09/12 00:38:26 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

#define ANT 4
#define N 11

/* 8 SUBJECT
static int larr[N][N] =	{1, 2, 3, -1, -1, -1, -1, -1,
						2, 5, 4, 7, 1, -1, -1, -1,
						3, 5, 4, 1, -1, -1, -1, -1,
						4, 2, 3, 7, 0, -1, -1, -1,
						5, 2, 3, 6, -1, -1, -1, -1,
						6, 5, 7, 0, -1, -1, -1, -1,
						7, 2, 4, 6, -1, -1, -1, -1,
						0, 4, 6, -1, -1, -1, -1, -1};
*/

/* 9 SUBJECT MODIF
static int larr[N][N] =	{1, 2, 3, -1, -1, -1, -1, -1, -1,
						2, 5, 4, 7, 1, -1, -1, -1, -1,
						3, 5, 4, 1, -1, -1, -1, -1, -1,
						4, 2, 3, 7, 0, -1, -1, -1, -1,
						5, 2, 3, 6, -1, -1, -1, -1, -1,
						6, 5, 7, 0, -1, -1, -1, -1, -1,
						7, 2, 4, 6, -1, -1, -1, -1, -1,
						8, 0, -1, -1, -1, -1, -1, -1, -1,
						0, 4, 6, 8, -1, -1, -1, -1, -1};
*/

// 11 VBRAZNIK
static int larr[N][N] =	{0, 1, 2, -1, -1, -1, -1, -1, -1, -1, -1,
						1, 0, 3, 4, -1, -1, -1, -1, -1, -1, -1,
						2, 0, 4, 5, -1, -1, -1, -1, -1, -1, -1,
						3, 1, 4, 6, 7, -1, -1, -1, -1, -1, -1,
						4, 1, 2, 3, 9, -1, -1, -1, -1, -1, -1,
						5, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1,
						6, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1,
						7, 3, 9, -1, -1, -1, -1, -1, -1, -1, -1,
						8, 6, 9, -1, -1, -1, -1, -1, -1, -1, -1,
						10, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1,
						9, 4, 7, 8, 10, -1, -1, -1, -1, -1, -1,};
//

/*
t_room	*new_room(int room)
{
	t_room *current;

	current = ft_calloc(1, sizeof(t_room));
	current->name = ft_itoa(room);
	return (current);
}
*/
/*
void	rooms_to_list(t_frame *frame)
{
	t_room **tmp;
	tmp = &frame->all;

	for (int i = 0; i < N; i++)
	{
		*tmp = ft_calloc(1, sizeof(t_room));
		(*tmp)->name = ft_itoa(larr[i][0]);
		if (i == 0)
			(*tmp)->level = 0;
		else if (i == N - 1)
			(*tmp)->level = 99;
		else
			(*tmp)->level = -1;
		tmp = &(*tmp)->next;
	}
}

t_room	*get_room(t_room *head, int	name)
{
	char *str;

	str = ft_itoa(name);
	while (head)
	{
		if (ft_strcmp(str, head->name) == 0)
		{
			free(str);
			return (head);
		}
		head = head->next;
	}
	free(str);
	return (NULL);
}

void	add_links(t_room *head)
{
	t_link	**tmp;
	t_room	*current;
	int		i;

	i = 0;
	current = head;
	while (current)
	{
		tmp = &current->links;
		for(int j = 1; larr[i][j] >= 0; j++)
		{
			*tmp = ft_calloc(1, sizeof(t_link));
			(*tmp)->room = get_room(head, larr[i][j]);
			tmp = &(*tmp)->next;
		}
		i++;
		current = current->next;
	}
}

void	bfs_set_level(t_link *link, int level)
{
	while (link)
	{
		if (link->room->level == -1)
			link->room->level = level;
		link = link->next;
	}
}

void	bfs(t_room *start, int level)
{
	t_room	*r_tmp;
	t_link	*l_tmp;

	start->visit = 1;
	ft_printf("{2}room:{0} %s\n", start->name);
	l_tmp = start->links;
	while (l_tmp)
	{
		if (l_tmp->room->level == -1)
			l_tmp->room->level = level;
		//bfs_set_level(l_tmp, level);
		l_tmp = l_tmp->next;
	}	
	l_tmp = start->links;
	while (l_tmp)
	{
		if (ft_strcmp("0", l_tmp->room->name) == 0)
			break;
		if (l_tmp->room->visit == 0)
			bfs(l_tmp->room, level + 1);
		l_tmp = l_tmp->next;
	}
}
*/

void	del_unused_links(t_room *start)
{
	t_link	*l_tmp;

	while (start)
	{
		if (start->level == -1)
			del_all_links(&start->links);
		else
			del_links(start, &start->links);
		start = start->next;
	}
}

void	counted_links(t_room *start)
{
	t_link *tmp;

	while (start)
	{
		tmp = start->links;
		while (tmp)
		{
			tmp->room->input_links++;
			start->output_links++;
			tmp = tmp->next;
		}
		start = start->next;
	}
}

void	find_fork()
{
	
}

void	bfs_list(t_frame *frame)
{
	//frame->ants = ANT;
	//rooms_to_list(frame);
	
	//add_links(frame->map);

	print_rooms(frame->map);
	//print_all_info(frame->all);
	
	bfs_queue(frame->map);
	//bfs(frame->all, level + 1);
	ft_printf("{4} ---- BFS INIT LEVELS ----{0}\n"); print_all_info(frame->map);

	del_unused_links(frame->map);
	ft_printf("{4} ---- DEL UNUSED LINKS ----{0}\n"); print_all_info(frame->map);

	counted_links(frame->map);
	ft_printf("{4} ---- CALCULATE IN/OUT LINKS ----{0}\n"); print_all_info(frame->map);
	free_all(frame->map);
}
