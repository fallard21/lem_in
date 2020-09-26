/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:02:05 by fallard           #+#    #+#             */
/*   Updated: 2020/09/27 02:43:44 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

#define N 17
#define M 7

/* 14 7
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
*/

static int graf[N][M] = {{0, 1, 2, 3, 4, -1, -1},
						{1, 6, -1, -1, -1, -1, -1},
						{2, 5, -1, -1, -1, -1, -1},
						{3, 6, 13, -1, -1, -1, -1},
						{4, 7, -1, -1, -1, -1, -1},
						{5, 2, 8, -1, -1, -1, -1},
						{6, 1, 3, 9, 10, -1, -1},
						{7, 4, 9, -1, -1, -1, -1},
						{8, 5, 12, -1, -1, -1, -1},
						{9, 6, 7, 11, 12, -1, -1},
						{10, 6, 15, -1, -1, -1, -1},
						{11, 9, 99, -1, -1, -1, -1},
						{12, 8, 9, 13, 99, -1, -1},
						{13, 3, 12, 14, -1, -1, -1},
						{14, 13, 99, -1, -1, -1, -1},
						{15, 10, 99, -1, -1, -1, -1},
						{99, -1, -1, -1, -1, -1, -1}};


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
	t_room	*prev;
	int		j;

	prev = NULL;
	start->output = get_links(map, 0);
	tmp = map;
	j = 1;
	while (map)
	{
		if (!ft_strcmp(map->name, "0") || !ft_strcmp(map->name, "99"))
		{
			prev = map;
			map = map->next;
			continue;
		}
		if (map->in)
		{
			map->output = ft_calloc(1, sizeof(t_link));
			map->output->room = map->next;
			map->output->edge_size = 0;

			//map->input = get_links(tmp, j++);
		}
		else
		{
			//map->input = ft_calloc(1, sizeof(t_link));
			//map->input->room = prev;
			//map->input->edge_size = 0;

			map->output = get_links(tmp, j++);
		}
		prev = map;
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

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void	insert_p(t_prev **head, t_room *room)
{
	t_prev	*tmp;

	if (*head == NULL)
	{
		*head = ft_calloc(1, sizeof(t_prev));
		(*head)->room = room;
	}
	else
	{
		tmp = ft_calloc(1, sizeof(t_prev));
		tmp->room = room;
		tmp->next = *head;
		*head = tmp;
	}
}

t_prev	*restore_path(t_room *end)
{
	t_room *tmp;
	t_prev *p;
	
	p = NULL;
	tmp = end;
	while (tmp)
	{
		insert_p(&p, tmp);
		tmp = tmp->prev;
	}

	//////////////////////
	t_prev *tmp_p = p;
	ft_printf("\npath: ");
	while (tmp_p)
	{
		if (tmp_p->room->in)
			ft_printf("{3}%s -> {0}", tmp_p->room->name);
		else
			ft_printf("{3}%s' -> {0}", tmp_p->room->name);
		tmp_p = tmp_p->next;
	}
	ft_printf("\n\n");
	////////////////////////
	return (p);
}

void	add_rev_edge(t_room *from, t_room *to, int size)
{
	t_link	*tmp;

	if (!from->output)
	{
		from->output = ft_calloc(1,sizeof(t_link));
		from->output->room = to;
		from->output->edge_size = size * -1;;
		from->output->status = 1;
	}
	else
	{
		tmp = from->output;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ft_calloc(1,sizeof(t_link));
		tmp->next->room = to;
		tmp->next->edge_size = size * -1;
		tmp->next->status = 1;
	}
}

void	reverse_path(t_prev *p, t_room *current) // 642 680
{
	t_link *tmp;
	t_room *next;

	while (p)
	{
		tmp = current->output;
		while (tmp)
		{
			if (!ft_strcmp(tmp->room->name, p->room->name))
				break ;
			tmp = tmp->next;
		}
		add_rev_edge(p->room, current, tmp->edge_size);
		delete_link(current, p->room->name);
		
		current = p->room;
		p = p->next;
	}
}

int		bellman_ford(t_frame *frame, t_room *start)
{
	t_room	*current;
	t_link	*tmp;
	int		i;
	int		flag;

	i = 0;
	current = start;
	while (i++ < (frame->num_rooms - 1))
	{
		//ft_printf("%d\n", i);
		flag = 0;
		current = start;
		while (current)
		{
			tmp = current->output;
			while (tmp)
			{
				if (current->vertex_size == INT_MAX)
					break ;
				if (current->vertex_size + tmp->edge_size < tmp->room->vertex_size)
				{
					tmp->room->vertex_size = current->vertex_size + tmp->edge_size;
					tmp->room->prev = current;
					flag = 1;
				}
				tmp = tmp->next;
			}
			current = current->next;
		}
		if (!flag)
			break ;
	}
	if (frame->end->vertex_size == INT_MAX)
		return (1);
	return (0);
}

void	reinit_sizes(t_room *start)
{
	t_room *tmp;

	tmp = start;
	while (tmp)
	{
		tmp->vertex_size = INT_MAX;
		tmp->prev = NULL;
		tmp = tmp->next;
	}
	start->vertex_size = 0;
}

void	suurballe(t_frame *frame)
{
	frame->num_rooms = N * 2 - 2;
	create_graf(frame);
	frame->start->vertex_size = 0;
	frame->start->level = 0;
	frame->end->level = INT_MAX;
	glue_list(frame);
	add_links(frame->map, frame->start, frame->end);
	//////////////////////////////////////////////////////////////////////////
	
	t_prev *p;
	//bfs_queue(frame->start);
	//print_all_info(frame->start);

	bellman_ford(frame, frame->start);
		print_suurb(frame->start);

	p = restore_path(frame->end);
	//reverse_path(p, frame->start);

	return ;
}


// 1) Цикл Беллмана-Форда, пока есть пути // DONE ?
	// 1.1) Восстановление пути после Б-Ф // DONE ?
	// 1.2) Реверс ребер (отрицательная стоимость + status link = 1) // DONE ??
	// 1.3) Обновление prev и vertex_size // DONE ??
// 2) Поиск и удаление встречных ребер // NOT
// 3) Восстановление всех путей по status = 1 линкам. // NOT
