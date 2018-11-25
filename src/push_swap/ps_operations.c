/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/23 22:24:02 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_stack *head, char mark, t_lists *lst)
{
	int	tmp;

	if (head == NULL || head->next == head)
		return ;
	tmp = head->value;
	head->value = head->next->value;
	head->next->value = tmp;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = ft_memalloc(sizeof(t_lists));
	if (mark == 'a')
		lst->next->com = ft_strdup("sa");
	else
		lst->next->com = ft_strdup("sb");
}

t_stack	*ft_make_to(char mark, t_stack *tmp, t_stack *to, t_head *head)
{
	t_lists	*tmpl;

	tmpl = head->lst;
	while (tmpl->next != NULL)
		tmpl = tmpl->next;
	tmpl->next = ft_memalloc(sizeof(t_lists));
	if (mark == 'a')
		tmpl->next->com = ft_strdup("pa");
	else if (mark == 'b')
		tmpl->next->com = ft_strdup("pb");
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

void	ft_push(t_head *head, char mark)
{
	t_stack	*tmp;
	t_stack	*from;
	t_stack	*to;

	from = (mark == 'a') ? head->b : head->a;
	to = (mark == 'a') ? head->a : head->b;
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
	head->a = (mark == 'a') ? ft_make_to(mark, tmp, to, head) : from;
	head->b = (mark == 'b') ? ft_make_to(mark, tmp, to, head) : from;
}

t_stack	*ft_rotating(t_stack *head, char mark, char rmark, t_lists *lst)
{
	if (head == NULL)
		return (head);
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = ft_memalloc(sizeof(t_lists));
	if (rmark == 1)
	{
		if (mark == 'a')
			lst->next->com = ft_strdup("rra");
		else
			lst->next->com = ft_strdup("rrb");
		return (head->prev);
	}
	else if (rmark == 0)
	{
		if (mark == 'a')
			lst->next->com = ft_strdup("ra");
		else
			lst->next->com = ft_strdup("rb");
		return (head->next);
	}
	return (head);
}
