/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 22:44:30 by user              #+#    #+#             */
/*   Updated: 2020/09/14 17:42:03 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

/*
**	TODO:	1. Прочекать какие специфические библиотечные функции использую. Составить список.
**			2. Разделить хедеры
**			3. Добавить флаг is_link в парсер
**			4. Добавить печать и очистку input в конец create_map()
*/


t_frame		*create_map()
{
	t_room		*map;
	t_input		*input;
	t_frame		*stor;

	if (!(input = read_input()))
	{
		free_input(input);
		lem_error(READ_ERR, NULL);
	}
	stor = init_storage(&input);
	if (!(map = parse_input(input, stor)) || !is_valid_map(stor))
		lem_error(NOT_ENOUGH_ERR, stor);
	// lem_free(stor);
	// print_input();
	return (stor);
}

int			main(int ac, char **av)
{
	t_frame		*stor;
	t_path		*path;

	errno = 0;
	// if (ac >= 2) 	// Here is to handle possible bonus-flags
	// {				// --help, --verbose, --debug, etc
	// }
	if (ac == 1)
	{
		stor = create_map();
		bfs_list(stor);
		// path = create_path(stor);
	}
	// else
	// 	lem_error(SMTH_HERE)
	
	return(0);
}
