/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 21:45:03 by fallard           #+#    #+#             */
/*   Updated: 2020/09/10 00:56:55 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	t_frame	frame;
	int		fd;
	
	ft_memset(&frame, 0, sizeof(t_frame));
	/*
	if (argc != 2)
		exit (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		ft_exit("open");
	*/
	bfs_list(&frame);
	
	close(fd);
	return (0);
}
