/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/25 20:50:27 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_make_to_check(t_stack *tmp, t_stack *to)
{
	if (to != NULL)
	{
		tmp->prev = to->prev;
		tmp->next = to;
		to->prev->next = tmp;
		to->prev = tmp;
		to = tmp;
	}
	else
	{
		to = tmp;
		to->next = to;
		to->prev = to;
	}
	return (to);
}

void	ft_push_check(t_head *head, char *com, char fl)
{
	t_stack	*tmp;
	t_stack	*from;
	t_stack	*to;

	if (!(ft_strequ(com, "pa") || ft_strequ(com, "pb")) &&
	(ft_printf("Error. No such command - %s.\n", com)))
		exit(1);
	(fl != 0) ? ft_printf("%s\n", com) : 0;
	from = (com[1] == 'a') ? head->b : head->a;
	to = (com[1] == 'a') ? head->a : head->b;
	if (from == NULL)
		return ;
	tmp = from;
	from = (from->next == from) ? NULL : from;
	if (from)
	{
		from->prev->next = from->next;
		from->next->prev = from->prev;
		from = from->next;
	}
	head->a = (com[1] == 'a') ? ft_make_to_check(tmp, to) : from;
	head->b = (com[1] == 'b') ? ft_make_to_check(tmp, to) : from;
	(fl == 'c') ? ft_debug_a(head->a, com, ft_get_stack_size(head->a) - 1) : 0;
	(fl == 'c') ? ft_debug_b(head->b, com, ft_get_stack_size(head->b) - 1) : 0;
	(fl == 'v' && (head->a)) ? ft_debug(head) : 0;
}

void	ft_swap_check(t_head *head, char *com, char fl)
{
	int		tmp;

	if (!(ft_strequ(com, "sa") || ft_strequ(com, "sb") || ft_strequ(com, "ss"))
	&& (ft_printf("Error. No such command - %s.\n", com)))
		exit(1);
	(fl != 0) ? ft_printf("%s\n", com) : 0;
	if ((com[1] == 'a' || com[1] == 's') && (head->a))
	{
		tmp = head->a->value;
		head->a->value = head->a->next->value;
		head->a->next->value = tmp;
		if (fl == 'c')
			ft_debug_a(head->a, com, ft_get_stack_size(head->a) - 1);
	}
	if ((com[1] == 'b' || com[1] == 's') && (head->b))
	{
		tmp = head->b->value;
		head->b->value = head->b->next->value;
		head->b->next->value = tmp;
		if (fl == 'c')
			ft_debug_b(head->b, com, ft_get_stack_size(head->b) - 1);
	}
	if (fl == 'v' && (head->a))
		ft_debug(head);
}

void	ft_rotate_check(t_head *head, char *com, char fl)
{
	if (!(ft_strequ(com, "ra") || ft_strequ(com, "rb") || ft_strequ(com, "rr")
	|| ft_strequ(com, "rra") || ft_strequ(com, "rrb") || ft_strequ(com, "rrr"))
	&& (ft_printf("Error. No such command - %s.\n", com)))
		exit(1);
	(fl != 0) ? ft_printf("%s\n", com) : 0;
	if ((com[1] == 'a' || (com[1] == 'r' && com[2] != 'b')) && head->a)
	{
		if (com[2] == '\0')
			head->a = head->a->next;
		else
			head->a = head->a->prev;
		if (fl == 'c')
			ft_debug_a(head->a, com, ft_get_stack_size(head->a) - 1);
	}
	if ((com[1] == 'b' || (com[1] == 'r' && com[2] != 'a')) && head->b)
	{
		if (com[2] == '\0')
			head->b = head->b->next;
		else
			head->b = head->b->prev;
		if (fl == 'c')
			ft_debug_b(head->b, com, ft_get_stack_size(head->b) - 1);
	}
	if (fl == 'v')
		ft_debug(head);
}
