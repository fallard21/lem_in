
#include "struct.h"
#include "lem_parser.h"

/*
**		JUST FOR TESTING**********************
*/ 

void		print_input(t_input *input)
{
	t_input		*copy;

	copy = input;

	printf("\n---PRINT INPUT---\n");
	while (copy)
	{
		printf("%s\n", copy->line);
		copy = copy ? copy->next : NULL;
	}
	// printf("CMD = %s\n", stor->cmd ? (stor->cmd == 1 ? "START_SIG" : "END_SIG") : "NO_SIG");
	// char *str = "##end";
	// if (str == "##ende")
	// 	printf("\nYES\n");
}

void		print_room(t_room *room)
{
	if (!room)
		return;
	printf("\n---PRINT ROOM---\n");
	printf("name = %s\n", room->name);
	printf("x = %d\n", room->coord[0]);
	printf("y = %d\n", room->coord[1]);
	printf("level = %d\n", room->level);
	printf("num_links = %d\n", room->num_links);
	printf("input links = %d\n", room->input_links);
	printf("output links = %d\n", room->output_links);
	printf("visit = %d\n", room->visit);
	printf("is_link = %s\n", room->links ? "YES" : "NO");
	
	t_link	*lcopy;
	if (room->links)
	{
		lcopy = room->links;
		while (lcopy)
		{
			printf("room->links->name = %s\n", lcopy->room->name);
			lcopy = lcopy->next;
		}
	}

}

void	print_room_list(t_frame *stor, t_room *room)
{
	t_room	*copy;

	if (!room)
		return;
	copy = room;
	while (copy)
	{
		print_room(copy);
		copy = copy ? copy->next : NULL;
	}
	if (stor)
	{
		printf("\n---PRINT STOR---\n");
		printf("\nnum_rooms = %d\n", stor->num_rooms);
		printf("start = %s  num_links = %d\n", stor->start->name, stor->start->num_links);
		printf("end = %s  num_links = %d\n", stor->end->name, stor->end->num_links);
	}
}

void		print_path(t_path *path, int ct)
{
	t_link		*copy;
	int			i;

	i = 0;
	copy = path->start;
	if (!path)
		return;
	printf("\n----- PRINT PATH #%d | len = %d -----\n", ct, path->len);
	while (copy)
	{
		printf("room_%d = %s\tants = %d\n", i, copy->room->name, copy->room->ants);
		copy = copy->next;
		i++;
	}
}

void		printf_path_rev(t_path * path, int ct)
{
	t_link		*copy;
	int			i;

	i = 0;
	copy = path->end;
	if (!path)
		return;
	printf("\n----- PRINT PATH REV #%d | len = %d -----\n", ct, path->len);
	while (copy)
	{
		printf("room_%d = %s\tants = %d\n", i, copy->room->name, copy->room->ants);
		copy = copy->prev;
		i++;	
	}
}

void		print_path_list(t_frame *stor)
{
	t_path		*copy;
	int 		ct;

	ct = 1;
	copy = stor->paths;
	if (!copy)
		return;
	while (copy)
	{
		print_path(copy, ct);
		// printf_path_rev(copy, ct);
		printf("----- ants_togo = %d -----\n", copy->ants_togo);
		copy = copy->next;
		ct++;
	}
}

/*
**	Funcs to emulate bsf levels
**	Work only with correct map with no forks and unuseless links
*/

void		set_levels(t_frame *stor)
{
	t_room		*room;
	t_link		*link;
	int			i;

	link = stor->start->links;
	while (link)
	{
		i = 1;
		room = link->room;
		// printf("out | room->name = %s\n", room ? room->name : NULL);
		while (room && ft_strcmp(room->name, stor->end->name))
		{
			// printf("room->name = %s\n", room->name);
			// printf("room->next = %s\n", room->links->next->room->name);
			room->level = i++;
			room = room->links->next->room;
		}
		link = link->next;
	}

	// printf("\n***** IN SET LEVELS*****\n");
	// print_room_list(stor, stor->map);
}
