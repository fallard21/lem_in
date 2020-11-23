/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 06:16:10 by fallard           #+#    #+#             */
/*   Updated: 2020/09/12 00:36:27 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

static int arr[8][8] = {-1, 1, 1, 0, 0, 0, 0, 0,
						1, -1, 0, 1, 1, 0, 1, 0,
						1, 0, -1, 1, 1, 0, 0, 0,
						0, 1, 1, -1, 0, 0, 1, 1,
						0, 1, 1, 0, -1, 1, 0, 0,
						0, 0, 0, 0, 1, -1, 1, 1,
						0, 1, 0, 1, 0, 1, -1, 0,
						0, 0, 0, 1, 0, 1, 0, 99,};

static void	print_arr()
{
	for (int i = 0; i < 8; i++)
	{
		int width = 3;
		for (int j = 0; j < 8; j++)
		{
			if (i == j)
				ft_printf("{1}%*d{0}", width, arr[i][j]);
			else if (arr[i][j] == 0)
				ft_printf("{2}%*d{0}", width, arr[i][j]);
			else
				ft_printf("{3}%*d{0}", width, arr[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

static void	set_level(int level, int mid)
{
	for (int i = 0; i < 8; i++)
	{
		if (i > mid && arr[mid][i] == 1)
		{
			if (arr[mid][mid] != -1)
				arr[mid][mid] = level;
		}
	}
}

static void	ft_bfs(int level, int mid)
{
	//if (mid == 8)
	//	return ;
	for (int i = mid + 1; i < 8; i++)
	{
		if (arr[mid][i] == 1 && arr[i][i] == -1)
		{
			arr[i][i] = level;
		}
	}
	for (int i = mid + 1; i < 8; i++)
	{
		ft_printf("%d\n", i);
		if (arr[mid][i] == 1)
		{
			ft_bfs(level + 1, i);
		}
	}
}

void	bfs_main()
{
	int level;
	int mid;

	level = 0;
	mid = 0;
	arr[mid][mid] = level;
	ft_bfs(level + 1, mid);
	print_arr();
}
