/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:17:15 by fallard           #+#    #+#             */
/*   Updated: 2020/10/09 17:52:50 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

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

t_find	*ft_reverse_list(t_find *head)
{
	t_find *prev;
	t_find *right;

	if (!head)
		return (head);
	prev = NULL;
	right = head->next;
	while (right)
	{
		head->next = prev;
		prev = head;
		head = right;
		right = right->next;
	}
	head->next = prev;
	return (head);
}
