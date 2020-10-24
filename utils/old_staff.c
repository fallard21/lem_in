// void	ft_print_path(t_frame *frame, t_path *p)
// {
// 	t_link	*tmp;
// 	int		i;

// 	i = 0;
// 	while (p)
// 	{
// 		ft_printf("%d) Path size: %d | %s | ants on path: %d\n\t", i + 1,
// 		p->len, (p->ants_togo) ? "USED" : "UNUSED", p->ants_togo);
// 		tmp = p->start;
// 		while (tmp)
// 		{
// 			if (!tmp->next)
// 				ft_printf("%s", tmp->room->name);
// 			else
// 				ft_printf("%s -> ", tmp->room->name);
// 			tmp = tmp->next;
// 		}
// 		p = p->next;
// 		i++;
// 		ft_printf("\n");
// 	}
// 	ft_printf("Number of steps: %d\n\n", frame->current_steps);
// }