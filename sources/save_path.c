/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 08:44:09 by fallard           #+#    #+#             */
/*   Updated: 2020/10/05 13:25:06 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	ft_print_path(t_path *p)
{
	t_link *tmp;

	while (p)
	{
		ft_printf("len: %d\n", p->len);
		tmp = NULL; 
		//tmp = p->start;
		print_links(p->start);
		while (tmp)
		{
			ft_printf("link: %-10s ", tmp->room->name);

			if (tmp->prev)
				ft_printf("prev: %-10s ", tmp->prev->room->name);
			else
				ft_printf("prev: %-10s ", NULL);

			if (tmp->next)
				ft_printf("next: %-10s ", tmp->next->room->name);
			else
				ft_printf("next: %-10s ", NULL);
	
			tmp = tmp->next;
			ft_printf("\n");
		}
		p = p->next;
		ft_printf("\n\n");
	}
}

t_path	*sort_path(t_path *head)
{
	t_path *new_head;
	t_path *tmp;
	t_path *current;

	new_head = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (!new_head || tmp->len < new_head->len)
		{
			tmp->next = new_head;
			new_head = tmp;
		}
		else
		{
			current = new_head;
			while (current->next && !(tmp->len < current->next->len))
				current = current->next;
			tmp->next = current->next;
			current->next = tmp;
		}
	}
	return (new_head);
}

t_link	*get_status_link(t_link *link)
{
	t_link	*res;

	res = NULL;
	while (link)
	{
		if (link->status == 1)
			res = link;
		link = link ->next;
	}
	return (res);
}

int		insert_link(t_link **head, t_room *room)
{
	t_link	*tmp;

	if (*head == NULL)
	{
		if (!(*head = ft_calloc(1, sizeof(t_link))))
			return (1);
		(*head)->room = room;
	}
	else
	{
		if (!(tmp = ft_calloc(1, sizeof(t_link))))
			return (1);
		tmp->room = room;
		tmp->next = *head;
		*head = tmp;
	}
	return (0);
}

int		init_link_list(t_link *link, t_link **path, int *len)
{
	t_room *current;
	t_link *tmp;
	t_link *prev;

	prev = *path;
	current = link->room;
	while (1)
	{
		if (!(tmp = get_status_link(current->output)))
			break ;
		if (ft_strcmp(tmp->room->name, (*path)->room->name) == 0)
		{
			current = tmp->room;
			continue ;
		}
		if (insert_link(path, tmp->room))
			return (free_link(path));
		(*len)++;
		prev->prev = *path;
		prev = *path;
		current = tmp->room;
	}
	return (0);
}

void	get_path(t_frame *frame)
{
	t_path **tmp;
	t_link	*links;
	t_link *next;

	tmp = &frame->paths;
	links = frame->end->output;
	while (links)
	{
		next = links->next;
		if (!(*tmp = ft_calloc(1, sizeof(t_path))))
			lem_error(ALLOC_ERR, frame);
		if (!(links->next = ft_calloc(1, sizeof(t_link))))
			lem_error(ALLOC_ERR, frame);
		links->next->room = frame->end;
		(*tmp)->end = links;
		(*tmp)->start = links;
		if (init_link_list(links, &(*tmp)->start, &(*tmp)->len))
			lem_error(ALLOC_ERR, frame);
		tmp = &(*tmp)->next;
		links = next;
	}
	frame->paths = sort_path(frame->paths);
		//ft_print_path(frame->paths);	// DELETE
}

//////////////////////////////////////////////////////////////////////////

void	print_arr(int *arr, int size)
{
	int i = 0;

	while (i < size)
	{
		ft_printf("%3d ", arr[i]);
		i++;
	}
	ft_printf("\n");
}

void	ft_moving(t_frame *frame)
{
	t_path *path;
	int i = 0;

	while (frame->start->ants != 0)
	{
		path = frame->paths;
		while (path)
		{
			i = path->len + 2 - 1;
			if (path->arr[i])
			path = path->next;
		}
	}
}

void	calcul_ants(t_frame *frame, int size)
{
	int		*sizes;
	int		*ants;
	t_path	*tmp;
	int		count;
	int		i;

	count = frame->num_ants;
	tmp = frame->paths;
	sizes = ft_calloc(size, sizeof(int));
	ants = ft_calloc(size, sizeof(int));
	i = 0;
	while (tmp)
	{
		sizes[i] = tmp->len;
		tmp = tmp->next;
		i++;
	}
	
	while (count != 0)
	{
		i = 0;
		while (i < size)
		{
			if ((i + 1) == size)
				break ;
			if (sizes[i + 1] + ants[i + 1] > sizes[i] + ants[i])
				break;
			i++;
		}
		ants[i] = ants[i] + 1;
		
		count--;
	}
	print_arr(sizes, size);
	print_arr(ants, size);

	// tmp = frame->paths;
	// i = 0;
	// while (tmp)
	// {
	// 	tmp->ants_togo = ants[i++];
	// 	tmp = tmp->next;
	// }
	// ft_moving(frame);
}

void	test_move_ants(t_frame *frame, int size)
{
	t_path *tmp;
	t_link *link;
	int i;

	
	while (tmp)
	{
		i = 0;
		link = tmp->start;
		tmp->arr = ft_calloc(tmp->len + 2, sizeof(t_room*));
		while (link)
		{
			tmp->arr[i++] = link;
			link = link->next;
		}
		tmp = tmp->next;
	}
	calcul_ants(frame, size);
}
