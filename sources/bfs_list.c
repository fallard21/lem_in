/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:07:49 by fallard           #+#    #+#             */
/*   Updated: 2020/09/20 17:00:54 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

static int	bool_list(t_room *room, t_link *link)
{
	
	if (room->level > link->room->level) // >=
		return (1);
	if (link->room->level < 0)
		return (1);
	return (0);
}

static void	del_links_v2(t_room *room, t_link **head)
{
	t_link	*tmp;
	t_link	*prev;
	t_link	*del;

	tmp = *head;
	prev = tmp;
	while (tmp)
	{
		if (bool_list(room, *head))
			del_head(head, &tmp);
		else if (bool_list(room, tmp))
			del_middle(prev, &tmp);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	del_unused_links_v2(t_room *start)
{
	t_link	*l_tmp;

	while (start)
	{
		if (start->level == -1)
			del_all_links(&start->links);
		else
			del_links_v2(start, &start->links);
		start = start->next;
	}
}

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
			if (tmp->room->level < start->level)
				start->input_links++;
			if (tmp->room->level > start->level)
				start->output_links++;
			tmp = tmp->next;
		}
		start = start->next;
	}
}

t_link	*del_list(t_link *prev, t_link **head, int *inout)
{
	t_link *del;

	if (!(*head))
		return (NULL);
	if (!prev)
	{
		del = *head;
		*head = (*head) ->next;
		free(del);
		(*inout)--;
		return (*head);
	}
	else
	{
		del = prev->next;
		prev->next = del->next;
		free(del);
		(*inout)--;
		return (prev);
	}
}

void	delete_link(t_room *head, char *name, int *inout)
{
	t_link *tmp;
	t_link *prev;

	tmp = head->links;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->room->name, name))
			tmp = del_list(prev, &head->links, inout);
		if (!tmp)
			break;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	del_dead_end(t_room *del)
{
	t_link *tmp;

	tmp = del->links;
	while (tmp)
	{
			//ft_printf("\n1. room: %s, in: %d, out: %d\n", tmp->room->name, tmp->room->input_links, tmp->room->output_links);
		delete_link(tmp->room, del->name, &tmp->room->output_links);
			//ft_printf("2. room: %s, in: %d, out: %d\n", tmp->room->name, tmp->room->input_links, tmp->room->output_links);
		
		if (!tmp->room->output_links)
			del_dead_end(tmp->room);
		tmp = tmp->next;
	}
}

void	find_dead_end(t_room *start)
{
	t_link *tmp;
	//t_link *prev;

	//prev = NULL;
	//start->visit = 1;
	//ft_printf(" {1}%s{0} - ", start->name);
	while (start)
	{
		if (!(start->level == 0 || start->level == INT_MAX))
		{
			if (start->output_links == 0)
			{
				del_dead_end(start);
			}
		}
		start = start->next;
	}
	
}

void	find_input_forks(t_room *start)
{
	t_link	*queue;
	t_link	*tmp;
	t_room	*current;
	t_link	*del;
	int		count;

	queue = NULL;
	count = 0;
	queue_push(&queue, start);
	start->visit = 1;
	while (!is_empty(queue))
	{
		current = queue_pop(&queue);
			//ft_printf("current: %s\n\n", current->name);
		tmp = current->links;
		while (tmp)
		{
			if (tmp->room->visit == 0)
			{
				tmp->room->visit = 1;
				queue_push(&queue, tmp->room);
			}
			tmp = tmp->next;
		}
		if (!(current->level && current->level == INT_MAX))
		{
			while (current->input_links > 1)
			{
				del = check_path(current);
				if (del)
				{
						//ft_printf("{2}del: %s{0}\n", del->room->name);	// DEL
					delete_link(del->room, current->name, &del->room->output_links);
					delete_link(current, del->room->name, &current->input_links);
					
				}
				else
				{
						//ft_printf("{1}OTHER!{0}\n");	// DEL
					delete_link(del->room, current->name, &del->room->output_links);
					delete_link(current, current->links->room->name, &current->links->room->input_links);
					
				}
			}
		}
	}
		//ft_printf("\n");
}

t_link *check_path(t_room *current)
{
	t_room *tmp;
	t_link *kek;
	t_link *lol;
	//int i;

	//i = 0;
	
	kek = current->links;
	while (kek)
	{
		if (kek->room->level > current->level)
		{
			kek = kek->next;
			continue;
		}
		//ft_printf("{1}%s -> ", current->name);
		tmp = kek->room;
		
		while (tmp->level != 0)
		{
			//ft_printf("%s -> ", tmp->name);
			if (tmp->output_links > 1)
				return (kek);
			lol = tmp->links;
			while (lol)
			{
				if (lol->room->level < tmp->level)
					break;
				lol = lol->next;
			}
			tmp = lol->room;
		}
		kek = kek->next; //ft_printf("\n");
	}
		//ft_printf("\n");
	return (NULL);
}

void	find_output_forks(t_room *end)
{
	t_link	*queue;
	t_link	*tmp;
	t_room	*current;
	t_link	*del;
	int		count;

		//ft_printf("OUTPUTS QUEUE\n");
	queue = NULL;
	count = 0;
	queue_push(&queue, end);
	while (!is_empty(queue))
	{
		current = queue_pop(&queue);
			//ft_printf("current: %s\n\n", current->name);
		tmp = current->links;
		while (tmp)
		{
			if (tmp->room->visit == 0)
			{
				tmp->room->visit = 1;
				queue_push(&queue, tmp->room);
			}
			tmp = tmp->next;
		}
		if (!(current->level && current->level == INT_MAX))
		{
			while (current->output_links > 1)
			{
				del = get_out_path(current); 
					//ft_printf("{2}del: %s{0}\n", del->room->name);	// DEL
				delete_link(del->room, current->name, &current->output_links);
				delete_link(current, del->room->name, &del->room->input_links);
			}
		}
	}
		//ft_printf("\n");
}

t_link	*get_out_path(t_room *current)
{
	t_room *tmp;
	t_link *kek;
	t_link *lol;
	t_link *res;
	int		count_res = 0;

	int count;
	
	kek = current->links;

	while (kek)
	{
		if (kek->room->level < current->level)
		{
			kek = kek->next;
			continue;
		}
			//ft_printf("{1}%s -> ", current->name);
		count = 0;
		tmp = kek->room;
		while (tmp->level != INT_MAX)
		{
			if (tmp->output_links == 0)
				return (kek);
				//ft_printf("%s -> ", tmp->name);
			lol = tmp->links;
			while (lol)
			{
				if (lol->room->level > tmp->level)
					break;
				lol = lol->next;
			}
			tmp = lol->room;
			count++;
		}
		if (count > count_res)
		{
			count_res  = count;
			res = kek;
		}
		kek = kek->next; //ft_printf("\n");
		
	}
	return (res);
}

void	reset_visits(t_room *start)
{
	while (start)
	{
		if (!(start->level == 0 || start->level == INT_MAX))
			start->visit = 0;
		start = start->next;
	}
}

void	bfs_list(t_frame *frame)
{
	//frame->ants = ANT;
	//rooms_to_list(frame);
	
	//add_links(frame->map);

		//print_rooms(frame->map);
	//print_all_info(frame->all);
	//ft_printf("{1}%s{0}\n", frame->start->name);

	bfs_queue(frame->start);
		//ft_printf("{4} ---- BFS INIT LEVELS ----{0}\n"); print_all_info(frame->map);

	del_unused_links(frame->map);
		//ft_printf("{4} ---- DEL UNUSED LINKS ----{0}\n"); print_all_info(frame->map);

	counted_links(frame->map);
		//ft_printf("{4} ---- CALCULATE IN/OUT LINKS ----{0}\n"); print_all_info(frame->map);
		//ft_printf("HERE2\n");
	find_dead_end(frame->map);
		
		//printf("\n"); print_all_info(frame->map);
	
	find_input_forks(frame->map);
		//printf("\n"); print_all_info(frame->map);
	
	reset_visits(frame->map);
	
	find_output_forks(frame->end);
	//printf("\n"); print_all_info(frame->map);
	
	//del_unused_links_v2(frame->map);
	//printf("\n"); print_all_info(frame->map);

		
	//free_all(frame->map);
}
