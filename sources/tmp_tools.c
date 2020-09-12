
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
