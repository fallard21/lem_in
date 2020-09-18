/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 18:07:20 by fallard           #+#    #+#             */
/*   Updated: 2020/09/19 02:43:10 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	del_head(t_link **head, t_link **tmp)
{
	t_link *del;

	del = *head;
	(*head) = (*head)->next;
	free(del);
	*tmp = *head;
}
void	del_middle(t_link *prev, t_link **tmp)
{
	t_link *del;

	del = prev->next;
	*tmp = (*tmp)->next;
	prev->next = del->next;
	free(del);
}

static int	bool_list(t_room *room, t_link *link)
{
	if (room->level == link->room->level) // >=
		return (1);
	if (link->room->level < 0)
		return (1);
	return (0);
}

void	del_links(t_room *room, t_link **head)
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

void	del_all_links(t_link **link)
{
	t_link	*next;

	while (*link)
	{
		next = (*link)->next;
		free(*link);
		*link = next;
	}
}

void	free_all(t_room *start)
{
	t_room *next;

	while (start)
	{
		next = start->next;
		del_all_links(&start->links);
		free(start->name);
		free(start);
		start = next;
	}
}

void	del_withname()
{
	return ;
}
