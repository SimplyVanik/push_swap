/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main_sort_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/24 21:54:10 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_omg_sort(t_head *head, int num_a, int num_b, int b_size)
{
	int		pshs;

	(num_a == 3 || num_a == 0) ? ft_a_bot_3(head, num_a) : 0;
	num_b = (b_size == 4 && num_b < 0) ? -1 * num_b : num_b;
	num_a = ft_find_pivot(head->b, num_b);
	pshs = 0;
	while (num_b > -8 && num_b < 6)
	{
		(num_b > 0) ? num_b++ : num_b--;
		if (num_b < 0)
			head->b = ft_rotating(head->b, 'b', 1, head->lst);
		(num_b > 0 && head->b->value > num_a) ? pshs++ : pshs;
		if (head->b->value <= num_a && num_b > 0)
			head->b = ft_rotating(head->b, 'b', 0, head->lst);
		else if (head->b->value > num_a)
			ft_push(head, 'a');
		(num_b > 0 && head->b->value <= num_a && head->b->next->value >
		num_a) ? ft_swap(head->b, 'b', head->lst) : 0;
	}
	if (num_b > 0 && pshs < 2 && head->b->next->value > num_a)
		ft_swap(head->b, 'b', head->lst);
	if (num_b > 0 && pshs < 2 && head->b->value > num_a)
		ft_push(head, 'a');
	while (b_size > 4 && num_b > 0 && pshs++ < 2)
		head->b = ft_rotating(head->b, 'b', 1, head->lst);
}

void	ft_make_sort(t_head *head, int num_a, int num_b)
{
	if (num_b == -3)
		ft_b_bottom_3(head, num_a);
	if (num_a == -3)
	{
		while (++num_a < 0)
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
		if (!(head->a->value > head->a->next->value && head->a->value >
		head->a->prev->value))
			num_a = 3;
		if (num_a == 3)
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
	}
	if (num_b == 3)
		ft_ab_top(head, num_a);
	if (num_b == 2 || num_b == -4 || num_b == 4)
	{
		if (num_b == 4 || num_b == -4)
			ft_omg_sort(head, num_a, num_b, ft_get_stack_size(head->b));
		if (head->a->value > head->a->next->value)
			ft_swap(head->a, 'a', head->lst);
		if (head->b->value < head->b->next->value)
			ft_swap(head->b, 'b', head->lst);
		ft_push(head, 'a');
		ft_push(head, 'a');
	}
}

void	ft_make_b(t_head *head, int *blocks, int i, int j)
{
	if (blocks[i + 1] > 3)
	{
		ft_sort_a(head, &(blocks[i + 1]), j);
		ft_sort_b(head, blocks, j, i);
	}
	else
	{
		ft_make_sort(head, blocks[i + 1], blocks[i]);
		blocks[i] = 0;
		blocks[i + 1] = 0;
	}
}

int		ft_backtrack(t_head *head, int *nums, int fl, int k)
{
	size_t	i;

	i = 0;
	while (nums[i] > 0)
		i++;
	nums[i] = nums[i - 1] / 2;
	nums[i - 1] = nums[i - 1] - nums[i];
	if (fl != 0 && (nums[i] - k > nums[i] / 3 + nums[i] % 3 || nums[i] < 4))
		while (k-- > 0)
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
	else if (fl != 0 && ++i > 0)
	{
		while (k++ < nums[i - 1])
			head->a = ft_rotating(head->a, 'a', 0, head->lst);
		k = ft_find_pivot(head->a, -1 * nums[i - 1]);
		fl = nums[i - 1];
		while (fl-- > 0)
		{
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
			(nums[i - 1] > 3 && head->a->value <= k) ? ft_push(head, 'b') : 0;
		}
		nums[i] = nums[i - 1] / 2;
		nums[i - 1] = nums[i - 1] - nums[i];
	}
	return (i - 1);
}

void	ft_optimize(t_lists *lst)
{
	t_lists	*tmpl;
	char	*tmpc;

	while (lst != NULL && lst->next != NULL)
	{
		if (lst->com[0] != 'p' && lst->com[0] == lst->next->com[0] &&
		((lst->com[1] != lst->next->com[1] && lst->com[1] != 'r' &&
		lst->next->com[1] != 'r') || (lst->com[1] == 'r' &&
		lst->next->com[1] == 'r' && lst->com[2] != lst->next->com[2])))
		{
			tmpl = lst->next;
			tmpc = lst->com;
			if (lst->com[0] == 's')
				lst->com = ft_strdup("ss");
			else if (lst->com[1] == 'r')
				lst->com = ft_strdup("rrr");
			else
				lst->com = ft_strdup("rr");
			ft_memdel((void**)(&(tmpc)));
			lst->next = lst->next->next;
			ft_memdel((void**)(&(tmpl->com)));
			ft_memdel((void**)(&tmpl));
		}
		lst = lst->next;
	}
}
