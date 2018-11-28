/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/27 21:57:28 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_debug_a(t_stack *head, char *com, int i)
{
	(ft_printf("Stack A -") && com[0] == 's') ? ft_putstr(GREEN) : 0;
	(com[0] == 'r') ? ft_putstr(BLUE) : 0;
	(ft_strequ(com, "pa")) ? ft_putstr(B_CYAN) : 0;
	(ft_strequ(com, "pb")) ? ft_putstr(B_YELLOW) : 0;
	(i >= 0) ? ft_printf(" %d", head->value) : 0;
	(i >= 0) ? head = head->next : 0;
	if (com[0] == 's')
		ft_putstr(RED);
	else if (com[2] == 'r' || com[2] == 'a' || (i == 1 && (ft_strequ(com, "ra")
	|| ft_strequ(com, "rr"))))
		ft_putstr(YELLOW);
	else
		ft_putstr(RESET);
	(i > 0) ? ft_printf(" %d", head->value) : 0;
	(i >= 0) ? head = head->next : 0;
	ft_putstr(RESET);
	while (--i > 1)
	{
		ft_printf(" %d", head->value);
		head = head->next;
	}
	(ft_strequ(com, "ra") || ft_strequ(com, "rr")) ? ft_putstr(YELLOW) : 0;
	(i > 0) ? ft_printf(" %d", head->value) : 0;
	ft_putstr(RESET);
	ft_printf("\n");
}

void	ft_debug_b(t_stack *head, char *com, int i)
{
	(ft_printf("Stack B -") && com[0] == 's') ? ft_putstr(GREEN) : 0;
	(com[0] == 'r') ? ft_putstr(BLUE) : 0;
	(ft_strequ(com, "pb")) ? ft_putstr(B_CYAN) : 0;
	(ft_strequ(com, "pa")) ? ft_putstr(B_YELLOW) : 0;
	(i >= 0) ? ft_printf(" %d", head->value) : 0;
	(i >= 0) ? head = head->next : 0;
	if (com[0] == 's')
		ft_putstr(RED);
	else if (com[2] == 'r' || com[2] == 'b' ||
	(i == 1 && (ft_strequ(com, "rb") || ft_strequ(com, "rr"))))
		ft_putstr(YELLOW);
	else
		ft_putstr(RESET);
	(i > 0) ? ft_printf(" %d", head->value) : 0;
	(i >= 0) ? head = head->next : 0;
	ft_putstr(RESET);
	while (--i > 1)
	{
		ft_printf(" %d", head->value);
		head = head->next;
	}
	(ft_strequ(com, "rb") || ft_strequ(com, "rr")) ? ft_putstr(YELLOW) : 0;
	(i > 0) ? ft_printf(" %d", head->value) : 0;
	ft_putstr(RESET);
	ft_printf("\n");
}

void	ft_debug(t_head *head)
{
	int		i;

	ft_printf("Stack A -");
	i = ft_get_stack_size(head->a);
	while (i-- > 0)
	{
		ft_printf(" %d", head->a->value);
		head->a = head->a->next;
	}
	ft_printf("\nStack B -");
	i = ft_get_stack_size(head->b);
	while (i-- > 0)
	{
		ft_printf(" %d", head->b->value);
		head->b = head->b->next;
	}
	ft_printf("\n");
}

void	ft_sort_stack(t_head *head, char fl)
{
	t_lists	*tmp;
	int		i;

	tmp = head->lst;
	while (tmp->com != NULL)
	{
		if (tmp->com[0] == 'p' && tmp->com[2] == 0)
			ft_push_check(head, tmp->com, fl);
		else if (tmp->com[0] == 's' && tmp->com[2] == 0)
			ft_swap_check(head, tmp->com, fl);
		else if (tmp->com[0] == 'r')
			ft_rotate_check(head, tmp->com, fl);
		else if (ft_printf("Error. No such command - %s.\n", tmp->com))
			exit(1);
		tmp = tmp->next;
	}
	i = ft_get_stack_size(head->a);
	while (--i > 0)
	{
		if ((head->b != NULL || head->a->value > head->a->next->value) &&
		(ft_printf("KO\n")))
			return ;
		head->a = head->a->next;
	}
	ft_printf("OK\n");
}

int		main(int ac, char **av)
{
	t_head	head;
	char	fl;
	int		gnl;
	t_lists	*tmp;

	ft_bzero((void *)(&head), sizeof(t_head));
	head.lst = ft_memalloc(sizeof(t_lists));
	if (ac == 1 && (ft_printf("Error. No elements to sort.")))
		exit(1);
	while (--ac > 1)
		ft_check(av[ac], ac, &head, ac);
	fl = (ft_strequ(av[1], "-v")) ? 'v' : 0;
	fl = (ft_strequ(av[1], "-c")) ? 'c' : fl;
	(fl == 0) ? ft_check(av[ac], ac, &head, ac) : 0;
	tmp = head.lst;
	while ((gnl = get_next_line(0, &(tmp->com))) > 0)
	{
		tmp->next = ft_memalloc(sizeof(t_lists));
		tmp = tmp->next;
	}
	if (gnl < 0 && (ft_printf("Error. Can't read command.")))
		exit(1);
	ft_sort_stack(&head, fl);
	return (0);
}
