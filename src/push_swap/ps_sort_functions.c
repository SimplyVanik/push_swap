/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/23 22:24:03 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_b_bottom(t_head *head, int num)
{
	int		pshs;

	pshs = 0;
	if (head->b->value > head->b->prev->value && head->b->value >
	head->b->prev->prev->value)
	{
		ft_push(head, 'a');
		pshs++;
	}
	head->b = ft_rotating(head->b, 'b', 1, head->lst);
	(head->b->value < head->b->prev->value) ? num-- : num;
	head->b = (head->b->value < head->b->prev->value) ?
	ft_rotating(head->b, 'b', 1, head->lst) : head->b;
	ft_push(head, 'a');
	if (num == 3 && (pshs == 1 || head->b->value < head->b->prev->value))
	{
		head->b = ft_rotating(head->b, 'b', 1, head->lst);
		num--;
	}
	else if (num == 2 && pshs == 0 && head->b->value < head->b->next->value)
		ft_swap(head->b, 'b', head->lst);
	ft_push(head, 'a');
	head->b = (num == 3) ? ft_rotating(head->b, 'b', 1, head->lst) : head->b;
	(pshs == 0) ? ft_push(head, 'a') : pshs;
}

void	ft_sort_b_top(t_head *head, int num)
{
	int		fl;

	fl = 0;
	ft_push(head, 'a');
	if ((num == 1 && head->b->value > head->b->prev->value) ||
	(num == 0 && head->b->value > head->b->next->value))
	{
		ft_push(head, 'a');
		fl++;
	}
	else if (num == 0)
		ft_swap(head->b, 'b', head->lst);
	if (num == 1)
		head->b = ft_rotating(head->b, 'b', 1, head->lst);
	ft_push(head, 'a');
	if (fl == 0)
		ft_push(head, 'a');
}

void	ft_ab_top(t_head *head, int num_a)
{
	int		fl_a;
	int		fl_b;

	fl_a = 0;
	if (num_a == 3)
	{
		if (head->a->value > head->a->next->value && head->a->value >
		head->a->next->next->value)
			ft_swap(head->a, 'a', head->lst);
		fl_a = (head->a->next->value > head->a->next->next->value) ? 1 : fl_a;
		if (head->a->next->value > head->a->next->next->value)
			head->a = ft_rotating(head->a, 'a', 0, head->lst);
	}
	fl_b = (head->b->value < head->b->next->next->value) ? 1 : 0;
	if (head->b->value < head->b->next->next->value)
		head->b = ft_rotating(head->b, 'b', 0, head->lst);
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	if (head->b->value < head->b->next->value)
		ft_swap(head->b, 'b', head->lst);
	if (fl_a == 1 || num_a == 0)
		head->a = ft_rotating(head->a, 'a', 1, head->lst);
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	ft_sort_b_top(head, fl_b);
}

void	ft_b_bottom_3(t_head *head, int num)
{
	if (num == 2)
	{
		if (head->a->value > head->a->next->value)
			ft_swap(head->a, 'a', head->lst);
		head->b = ft_rotating(head->b, 'b', 1, head->lst);
		ft_sort_b_bottom(head, 3);
		return ;
	}
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	if (head->a->next->value > head->a->next->next->value)
	{
		head->a = ft_rotating(head->a, 'a', 0, head->lst);
		num--;
	}
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	if (num == 2)
		head->a = ft_rotating(head->a, 'a', 1, head->lst);
	head->b = ft_rotating(head->b, 'b', 1, head->lst);
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	ft_sort_b_bottom(head, 3);
}

void	ft_a_bot_3(t_head *head, int num_a)
{
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	if (head->a->next->value > head->a->next->next->value)
	{
		head->a = ft_rotating(head->a, 'a', 0, head->lst);
		num_a++;
	}
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	if (num_a == 4 || num_a == 0)
		head->a = ft_rotating(head->a, 'a', 1, head->lst);
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
}
