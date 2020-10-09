/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:56:58 by fallard           #+#    #+#             */
/*   Updated: 2020/10/09 18:10:35 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	bubble_sort(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
			if (arr[j] >  arr[j + 1])
				ft_swap(&arr[j], &arr[j + 1]);
	}
}

int		find_max(int *arr, int size)
{
	int i = 0;
	int max  = arr[0];
	while (i < size)
	{
		if (arr[i] > max)
			max = arr[i];
		i++;
	}
	return (max);	
}

int		flow_2(t_frame *frame, int *path, int size)
{
	int *ants;
	int *diff;
	int num_ants;
	int i;

    ants = calloc(size, sizeof(int));
    diff = calloc(size, sizeof(int));
    
	num_ants = frame->num_ants;
    while (num_ants != 0)
    {
        i = 0;
        while (i < size)
        {
            if (i + 1 == size)
                break;
            if (path[i + 1] + ants[i + 1] > path[i] + ants[i])
                break;
            i++;
        }
        ants[i] = ants[i] + 1;
        diff[i] = path[i] + ants[i];
        num_ants--;
    }
	int n = find_max(diff, size);
		//ft_printf("Max steps: %d\n", n);
	free(path);
    free(ants);
    free(diff);
		//ft_printf("|----------------------------------------------------|\n");
	if (n > frame->current_steps)
		return (1);
	frame->current_steps = n;
	return (0);
}


int	calculate_flow(t_frame *frame)
{
	t_link	*tmp;
	t_room	*current;
	t_link	*tmp_2;
	int		size;
	int		i;
	int		j;
	int		*arr;

	tmp = frame->end->output;
	size = 0;
	while (tmp)
	{
		size = (tmp->status) ? size + 1 : size;
		tmp = tmp->next;
	}

		//ft_printf("Numbers of path: %d\n", size);

	arr = ft_calloc(size , sizeof(int));
	tmp = frame->end->output;
	i = 0;
	while (tmp)
	{
		j = 0;
		if (tmp->status)
		{
			current = tmp->room;
			while (1)
			{
				if (!(tmp_2 = get_status_link(current->output)))
					break;
				current = tmp_2->room;
				j++;
			}
				//ft_printf("Path size: %d\n", j / 2);
			arr[i] = j / 2;
			i++;
		}
		tmp = tmp->next;
	}
	bubble_sort(arr, size);
	// i = 0;
	// while (i < size)
	// {
	// 	ft_printf("%d ", arr[i]);
	// 	i++;
	// }
	// ft_printf("\n");
	
	return (flow_2(frame, arr, size));
}
