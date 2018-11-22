/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/22 21:14:03 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_check(char *s, int par, t_head *head)
{
	int		i;
	long	res;
	long	count;
	char	**tmp;
	int		j;

	tmp = ft_strsplit(s, ' ');
	j = -1;
	while (tmp[++j] != NULL)
	{
		i = ft_strlen(tmp[j]);
		res = 0;
		count = 1;
		while (--i >= 0 && tmp[j][i] > 47 && tmp[j][i] < 58)
		{
			res = res + count * (tmp[j][i] - 48);
			count = count * 10;
		}
		if (i > -1 && !(i == 0 && tmp[j][i] == '-') &&
		ft_printf("Error. %d element contains a non digital value.", par))
			exit (1);
		if (i == 0 && tmp[j][i] == '-')
			res = -1 * res;
		if ((res > 2147483647 || res < -2147483648) &&
		ft_printf("Error. %d element isn't integer.", par + j))
			exit (1);
		head->a = ft_addelement((int)(res), head->a, par + j);
	}
	// i = ft_strlen(s);
	// res = 0;
	// count = 1;
	// while (--i >= 0 && s[i] > 47 && s[i] < 58)
	// {
	// 	res = res + count * (s[i] - 48);
	// 	count = count * 10;
	// }
	// if (i > -1 && !(i == 0 && s[i] == '-'))
	// {
	// 	ft_printf("Error. %d element contains a non digital value.", par);
	// 	exit (1);
	// }
	// if (i == 0 && s[i] == '-')
	// 	res = -1 * res;
	// if (res > 2147483647 || res < -2147483648)
	// {
	// 	ft_printf("Error. %d element isn't integer.", par);
	// 	exit (1);
	// }
	// return ((int)(res));
}

int		ft_get_stack_size(t_stack *head)
{
	int		res;
	t_stack	*tmp;

	if (head == NULL)
		return (0);
	res = 1;
	tmp = head->next;
	while (tmp->value != head->value)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int		ft_find_pivot(t_stack *head, int num)
{
	t_stack	*tmp;
	int		cur;
	int		less;
	int		res;
	int		i;

	cur = -1;
	while(++cur < num || cur < -1 * num)
	{
		i = (num > 0) ? -1 : 1;
		tmp = head;
		while (num > 0 && ++i < cur)
			tmp = tmp->next;
		while (num < 0 && --i > cur + num)
			tmp = tmp->prev;
		res = tmp->value;
		if (num > 0)
			tmp = head;
		while (i-- > num)
			tmp = tmp->prev;
		i = -1;
		less = 0;
		while (i++ == -1 || (tmp->value != head->value && (i < num || i < -1 * num)))
		{
			if (tmp->value <= res)
				less++;
			tmp = tmp->next;
		}
		if ((num - 2 * less <= 0 && num - 2 * less >= -1) || (num + 2 * less >= 0 && num + 2 * less <= 1))
			return (res);
	}
	return (res);
}

t_stack	*ft_addelement(int to_add, t_stack *head, int par)
{
	t_stack	*tmp;

	tmp = head;
	if (head == NULL)
	{
		head = (t_stack *)malloc(sizeof(t_stack));
		head->next = head;
		head->prev = head;
		head->value = to_add;
		return (head);
	}
	while (tmp->next != head && tmp->value != to_add)
	//{
		// if (tmp->value == to_add)
		// {
		// 	ft_printf("Error. %d element is duplicated.", par);
		// 	exit (1);
		// }
		tmp = tmp->next;
	//}
	if (tmp->value == to_add)
	{
		ft_printf("Error. %d element is duplicated.", par);
		exit (1);
	}
	tmp->next = (t_stack *)malloc(sizeof(t_stack));
	(tmp->next)->prev = tmp;
	tmp = tmp->next;
	tmp->value = to_add;
	tmp->next = head;
	head->prev = tmp;
	return (tmp);
}

void	ft_swap(t_stack *head, char mark, t_lists *lst)
{
	int	tmp;

	if (head == NULL || head->next == head)
		return ;
	tmp = head->value;
	head->value = head->next->value;
	head->next->value = tmp;
	// if (list == NULL)
	// 	list = ft_memalloc(sizeof(t_lists));
	// else
	// {
	// 	list->next=ft_memalloc(sizeof(t_lists));
	// 	list = list->next;
	// }
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = ft_memalloc(sizeof(t_lists));
	if (mark == 'a')
		lst->next->com = ft_strdup("sa");
	else
		lst->next->com = ft_strdup("sb");	
}

void	ft_push(t_head *head, char mark)//ссылка на ссылку или нет
{
	t_stack	*tmp;
	t_stack	*from;
	t_stack	*to;
	t_lists	*tmpl;

	from = (mark == 'a') ? head->b : head->a;
	to = (mark == 'a') ? head->a : head->b;
	if (from == NULL)
		return ;
	tmp = from;
	if (from->next == from)
		from = NULL;
	else
	{
		from->prev->next = from->next;
		from->next->prev = from->prev;
		from = from->next;
	}
	if (to != NULL)
	{
		tmp->prev = to->prev;
		tmp->next = to;
		to->prev->next = tmp;
		to->prev = tmp;
		to = tmp;
		// return ;
	}
	else
	{
		to = tmp;
		to->next = to;
		to->prev = to;
	}
	tmpl = head->lst;
	while (tmpl->next != NULL)
		tmpl = tmpl->next;
	tmpl->next = ft_memalloc(sizeof(t_lists));
	if (mark == 'a')
	{
		tmpl->next->com = ft_strdup("pa");
		head->a = to;
		head->b = from;
	}
	else if (mark == 'b')
	{
		tmpl->next->com = ft_strdup("pb");
		head->a = from;
		head->b = to;
	}
	// if (tmpl != NULL)
	// 	head->lst = tmpl;
	// if (mark == 'a')
	// 	head->a = to;
	// else if (mark == 'b')
	// 	head->a = from;
	// if (mark == 'a')
	// 	head->b = from;
	// else if (mark == 'b')
	// 	head->b = to;
}

t_stack	*ft_rotating(t_stack *head, char mark, char rmark, t_lists *lst)
{
	if (head == NULL)
		return (head);
	// if (list == NULL)
	// 	list = ft_memalloc(sizeof(t_lists));
	// else
	// {
	// 	list->next=ft_memalloc(sizeof(t_lists));
	// 	list = list->next;
	// }
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = ft_memalloc(sizeof(t_lists));
	if (rmark == 1)
	{
		// head = head->prev;
		if (mark == 'a')
			lst->next->com = ft_strdup("rra");
		else
			lst->next->com = ft_strdup("rrb");
		return (head->prev);
	}
	else if (rmark == 0)
	{
		// head = head->next;
		if (mark == 'a')
			lst->next->com = ft_strdup("ra");
		else
			lst->next->com = ft_strdup("rb");
		return (head->next);
	}
	return (head);
}

// t_lists	*ft_make_sort(t_stack *head_a, t_stack *head_b, char mark, int *num)
// {
// 	t_lists	*res;
// 	// int		piv;
// 	// int		i;

// 	res = NULL;
// 	// piv = ft_find_pivot(from, num);
// 	// i = -1;
// 	// if (mark == 'a')
// 	// 	while (++i < num)
// 	// 	{
// 	// 		if (from->value <= piv)
// 	// 			ft_push(from, to);
// 	// 		else
// 	// 			ft_rotating(from, 'a', 0, res);
// 	// 	}

// }

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
	// if (head->b->value < head->b->prev->value)
	// {
	// 	ft_rotating(head->b, 'b', 1, head->lst);
	// 	num--;
	// }
	(head->b->value < head->b->prev->value) ? num-- : num;
	head->b = (head->b->value < head->b->prev->value) ? ft_rotating(head->b, 'b', 1, head->lst) : head->b;
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
	//return (res);
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
	//return (res);
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
	// if (head->a->value > head->a->next->value && head->a->value <
	// head->a->next->next->value)
	// 	ft_swap(head->a, 'a', head->lst);
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
	//return (res);
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
	// return (res);
}

void	ft_omg_sort(t_head *head, int num_a, int num_b, int b_size)
{
	// t_lists	*res;
	int		pshs;

	// res = NULL;
	if (/*num_a == 3 || num_a == 0*/num_b == 4 || num_b == -4)
	{
		(num_a == 3 || num_a == 0) ? ft_a_bot_3(head, num_a) : 0;
		num_b = (b_size == 4 && num_b < 0) ? -1 * num_b : num_b;
		num_a = ft_find_pivot(head->b, num_b);
	
		// while (num_b > -8 && num_b < 8)
		// {
		// 	(num_b > 0) ? num_b++ : num_b--;
		// 	if (num_b < 0)
		// 		head->b = ft_rotating(head->b, 'b', 1, head->lst);
		// 	if (head->b->value <= num_a && num_b > 0)
		// 		head->b = ft_rotating(head->b, 'b', 0, head->lst);
		// 	else if (head->b->value > num_a)
		// 		ft_push(head, 'a');
		// }
		// while (b_size > 4 && num_b-- > 6)
		// 	head->b = ft_rotating(head->b, 'b', 1, head->lst);

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
			if (num_b > 0 && head->b->value <= num_a && head->b->next->value > num_a)
				ft_swap(head->b, 'b', head->lst);
		}
		if (num_b > 0 && pshs < 2 && head->b->next->value > num_a)
			ft_swap(head->b, 'b', head->lst);
		if (num_b > 0 && pshs < 2 && head->b->value > num_a)
			ft_push(head, 'a');
		while (b_size > 4 && num_b > 0 && pshs++ < 2)
			head->b = ft_rotating(head->b, 'b', 1, head->lst);
	}
	if (head->a->value > head->a->next->value)
		ft_swap(head->a, 'a', head->lst);
	if (head->b->value < head->b->next->value)
		ft_swap(head->b, 'b', head->lst);
	// return (res);
}

void	ft_make_sort(t_head *head, int num_a, int num_b)
{

	if (num_b == -3)
		ft_b_bottom_3(head, num_a);
	if (num_a == -3)
	{
		while (++num_a < 0)
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
		if (!(head->a->value > head->a->next->value && head->a->value > head->a->prev->value))
			num_a = 3;
		if (num_a == 3)
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
	}
	// if (num_b == -3)
	// 	ft_b_bottom_3(head, num_a);
	if (num_b == 3)
		ft_ab_top(head, num_a);
	if (num_b == 2 || num_b == -4 || num_b == 4)
	{
		ft_omg_sort(head, num_a, num_b, ft_get_stack_size(head->b));
		// if (num_a == 3 || num_a == 0)
		// {
			
		// 	// if (head_a->value > head_a->next->value)
		// 	// 	ft_swap(head_a, 'a', res);
		// 	// if (head_a->next->value > head_a->next->next->value)
		// 	// {
		// 	// 	ft_rotating(head_a, 'a', 0, res);
		// 	// 	num_a--;
		// 	// }
		// 	// if (head_a->value > head_a->next->value)
		// 	// 	ft_swap(head_a, 'a', res);
		// 	// if (num_a == 2)
		// 	// 	ft_rotating(head_a, 'a', 1, res);
		// 	// if (head_a->value > head_a->next->value)
		// 	// 	ft_swap(head_a, 'a', res);
			
		// 	// if (head_b->value >= num_a && head_b->next->value >= num_a)
		// 	// {
		// 	// 	ft_push(head_b, head_a, 'a', res);
		// 	// 	ft_push(head_b, head_a, 'a', res);
		// 	// 	num_b = num_b - 2;
		// 	// }

		// 	res = ft_a_bot_3(head_a, res, num_a);
		// 	num_a = ft_find_pivot(head_b, num_b);
		// 	while (num_b > -8 && num_b < 8)
		// 	{
		// 		num_b = (num_b > 0) ? num++ : num--;
		// 		if (num_b < 0)
		// 			ft_rotating(head_b, 'b', 1, res);
		// 		if (head_b->value <= num_a && num_b > 0)
		// 			ft_rotating(head_b, 'b', 0, res);
		// 		else if (head_b->value > num_a)
		// 			ft_push(head_b, head_a, 'a', res);
		// 	}
		// 	while (num_b-- > 6)
		// 		ft_rotating(head_b, 'b', 1, res);
		// }
		// if (head_a->value > head_a->next->value)
		// 	ft_swap(head_a, 'a', res);
		// if (head_b->value < head_b->next->value)
		// 	ft_swap(head_b, 'b', res);
		ft_push(head, 'a');
		ft_push(head, 'a');
	}
	// if (num_a == 2 && num_b == 3)
	// {
	// 	if (head_b->value < head_b->next->next->value)
	// 	{
	// 		ft_rotating(head_b, 'b', 0, res);
	// 		if (head_a->value > head_a->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		if (head_b->value < head_b->next->value)
	// 			ft_swap(head_b, 'b', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		if (head_b->value > head_b->prev->value)
	// 		{	
	// 			ft_push(head_b, head_a, 'a', res);
	// 			num_b--;
	// 		}
	// 		ft_rotating(head_b, 'b', 1, res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		if (num_b == 3)
	// 			ft_push(head_b, head_a, 'a', res);
	// 	}
	// 	else
	// 	{
	// 		if (head_b->value < head_b->next->value)
	// 			ft_swap(head_b, 'b', res);
	// 		if (head_a->value > head_a->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		if (head_b->value < head_b->next->value)
	// 			ft_swap(head_b, 'b', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 	}
	// }

	// if (num_a == 3 && num_b == 3)
	// {
	// 	if (head_b->value < head_b->next->next->value)
	// 	{
	// 		if (head_a->value > head_a->next->value && head_a->value < head_a->next->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		if (head_a->next->value > head_a->next->next->value)
	// 		{	
	// 			ft_rotating(head_a, 'a', 0, res);
	// 			num_a--;
	// 		}
	// 		ft_rotating(head_b, 'b', 0, res);
	// 		if (head_a->value > head_a->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		if (head_b->value < head_b->next->value)
	// 			ft_swap(head_b, 'b', res);
	// 		if (num_a == 2)
	// 			ft_rotating(head_a, 'a', 1, res);
	// 		if (head_a->value > head_a->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		if (head_b->value > head_b->prev->value)
	// 		{	
	// 			ft_push(head_b, head_a, 'a', res);
	// 			num_b--;
	// 		}
	// 		ft_rotating(head_b, 'b', 1, res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		if (num_b == 3)
	// 			ft_push(head_b, head_a, 'a', res);
	// 	}
	// 	else
	// 	{
	// 		if (head_a->value > head_a->next->value && head_a->value < head_a->next->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		if (head_a->next->value > head_a->next->next->value)
	// 		{
	// 			ft_rotating(head_a, 'a', 0, res);
	// 			num_a--;
	// 		}
	// 		if (head_a->value > head_a->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		if (head_b->value < head_b->next->value)
	// 			ft_swap(head_b, 'b', res);
	// 		if (num_a == 2)
	// 			ft_rotating(head_a, 'a', 1, res);
	// 		if (head_a->value > head_a->next->value)
	// 			ft_swap(head_a, 'a', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		if (head_b->value < head_b->next->value)
	// 			ft_swap(head_b, 'b', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 		ft_push(head_b, head_a, 'a', res);
	// 	}
	// }

	// if (num_a = 3 && num_b == -3)
	// {
	// 	if (head_a->value > head_a->next->value && head_a->value <
	// 	head_a->next->next->value)
	// 		ft_swap(head_a, 'a', res);
	// 	if (head_a->next->value > head_a->next->next->value)
	// 	{	
	// 		ft_rotating(head_a, 'a', 0, res);
	// 		num_a--;
	// 	}
	// 	if (head_a->value > head_a->next->value)
	// 		ft_swap(head_a, 'a', res);
	// 	if (num_a == 2)
	// 		ft_rotating(head_a, 'a', 1, res);
	// 	ft_rotating(head_b, 'b', 1, res);
	// 	if (head_a->value > head_a->next->value)
	// 		ft_swap(head_a, 'a', res);
	// 	res = ft_sort_b_bottom_3(head_b, res, 3, 0)
	// }


	//return (res);
}

void	ft_sort_b(t_head *head, int *blocks)
{
	size_t	i;
	int		piv;
	int		j;

	i = 0;
	while (blocks[i] != 0)
		i++;
	while (i-- > 0)
	{
		j = -1;
		piv = (blocks[i] > 4 || blocks[i] < -4) ? ft_find_pivot(head->b, blocks[i]) : piv;
		if (blocks[i] > 0 && blocks[i] > 4)
			while (++j < blocks[i])
			{
				if (head->b->value > piv)
					ft_push(head, 'a');
				else
					head->b = ft_rotating(head->b, 'b', 0, head->lst);			
			}
		else if (blocks[i] < 0 && blocks[i] < -4)
			while (++j < -1 * blocks[i])
			{
				head->b = ft_rotating(head->b, 'b', 1, head->lst);
				if (head->b->value > piv)
					ft_push(head, 'a');
			}
		blocks[i + 1] = (blocks[i] < 0) ? blocks[i] / (-2) : blocks[i] / 2;
		blocks[i] = (blocks[i] < -4 || blocks[i] > 4) ? blocks[i] / (-2) - blocks[i] % 2 : blocks[i];
		if (blocks[i + 1] > 3)
		{
			ft_sort_a(head, &(blocks[i + 1]), j);
			ft_sort_b(head, blocks);			
		}
		else
		{
			ft_make_sort(head, blocks[i + 1], blocks[i]);
			blocks[i] = 0;
			blocks[i + 1] = 0;
		}
		// if (blocks[i] > 7 || blocks[i] < -7)
		// {
		// 	if (blocks[i] > 0)
		// 	{
		// 		while (++j < blocks[i])
		// 		{
		// 			if (head_b->value > piv)
		// 				ft_push(head_b, head_a, 'a', list);
		// 			else
		// 				ft_rotating(head_a, 'a', 0, list);			
		// 		}
		// 		blocks[i + 1] = blocks[i] / 2;
		// 	}
		// 	else
		// 	{
		// 		while (++j < blocks[i])
		// 		{
		// 			ft_rotating(head_b, 'b', 1, list);
		// 			if (head_b->value > piv)
		// 				ft_push(head_b, head_a, 'a', list);
		// 		}
		// 		blocks[i + 1] = blocks[i] / (-2);
		// 	}
		// 	blocks[i] = blocks[i] / (-2) - blocks[i] % 2;
		// 	ft_sort_a(head_a, head_b, list, &(blocks[i + 1]));
		// 	ft_sort_b(head_a, head_b, list, blocks);
		// }
		// else
		// {
		// 	if (blocks[i] > 0)
		// 	{
		// 		while (++j < blocks[i])
		// 		{
		// 			if (head_b->value > piv)
		// 				ft_push(head_b, head_a, 'a', list);
		// 			else
		// 				ft_rotating(head_a, 'a', 0, list);			
		// 		}
		// 		piv = blocks[i] / (-2);
		// 	}
		// 	else
		// 	{
		// 		while (++j < blocks[i])
		// 		{
		// 			ft_rotating(head_b, 'b', 1, list);
		// 			if (head_b->value > piv)
		// 				ft_push(head_b, head_a, 'a', list);
		// 		}
		// 		piv = blocks[i] / (-2);
		// 	}
		// 	list = ft_make_sort(head_a, head_b, piv,blocks[i] / (-2) - blocks[i] % 2);
		// 	blocks[i] = 0;			
		// }
	}
}

// void	in_stack_B(t_stack *head_a, t_stack *head_b, int *elem_num, t_lists *list)
// {
// 	int		*belem_num;
// 	size_t	j;
// 	int		piv;
// 	size_t	k;
// 	size_t	i;
	
// 	i = 0;
// 	while (elem_num[i] > 0)
// 		i++;
// 	belem_num = ft_memalloc(4 * (elem_num[i] + 1));
// 	while(--i >= 0)
// 	{
// 		j = -1;
// 		belem_num[0] = elem_num[i];
// 		while (belem_num[++j] > 4)
// 		{
// 			piv = ft_find_pivot(head_b, belem_num[j]);
// 			k = -1;
// 			while (++k < belem_num[j])
// 			{
// 				if (head_b->value <= piv)
// 					ft_rotating(head_b, 'b', 0, list);
// 				else
// 					ft_push(head_b, head_a);
// 			}
// 			belem_num[j] = belem_num[j] / 2 + belem_num[j] % 2;
// 			while (++belem_num[j + 1] + belem_num[j] <= k)
// 				ft_push(head_a, head_b);
// 		}
// 		ft_mak
// 		ft_bzero(belem_num, j);
// 	}
// }

int		ft_backtrack(t_head *head, int *nums, int fl, int k)
{
	size_t	i;
	//int		piv;
	//int		j;

	i = 0;
	while(nums[i] > 0)
		i++;
	nums[i] = nums[i - 1] / 2;
	nums[i - 1] = nums[i - 1] - nums[i];
	// if (fl == 0)
	// 	return (i);
	if (fl != 0 && (nums[i] - k > nums[i] / 3 + nums[i] % 3 || nums[i] < 4))
		while (k-- > 0)
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
	else if (fl != 0)
	{
		while (k++ < nums[i])
			head->a = ft_rotating(head->a, 'a', 0, head->lst);
		k = ft_find_pivot(head->a, -1 * nums[i]);
		fl = nums[i];
		while (fl-- > 0)
		{
			head->a = ft_rotating(head->a, 'a', 1, head->lst);
			// if (nums[i] > 3 && head->a->value <= k)
			// 	ft_push(head, 'b');
			(nums[i] > 3 && head->a->value <= k) ? ft_push(head, 'b') : 0;
		}
		nums[i + i] = nums[i] / 2;
		nums[i] = nums[i] - nums[i + 1];
		i++;
		// nums[++i] = nums[i - 1] / 2;
		// nums[i - 1] = nums[i - 1] - nums[i];
	}
	// if (nums[i] > 3)
	// 	nums[i + i] = nums[i] / 2;
	// nums[i] = nums[i] - nums[i + 1];
	return(i - 1);
}

void	ft_sort_a(t_head *head, int *block, int fl)
{
	//int		*block;
	// int		fl;
	size_t	i;
	int		j;
	int		k;
	int		piv;

	//block = ft_memalloc(4 * size);
	//block[0] = size;
	i = -1;
	fl = (block[0] == ft_get_stack_size(head->a)) ? 0 : 1;
	while (block[++i] > 3)
	{
		j = 0;
		k = 0;
		piv = ft_find_pivot(head->a, block[i]);
		while (j < block[i] / 2 + block[i] % 2)
		{
			(head->a->value <= piv) ? j++ : k++;
			if (head->a->value <= piv)
				ft_push(head, 'b');
			else
				head->a = ft_rotating(head->a, 'a', 0, head->lst);			
		}
		// i = (fl == 0) ? i : ft_backtrack(head, block);
		i = ft_backtrack(head, block, fl, k);
		// block[i + 1] = (size == 0) ? block[i] / 2 : ft_backtrack(head_a, head_b, lst, block);

		// block[i + 1] = (block[i] > 3) ? block[i] / 2 : block[i + 1];
		// block[i] = block[i] - block[i + 1];
	}
	//return (block);
	(i > 0) ? ft_make_sort(head, block[i], block[i - 1]) : 0;
	block[i] = (i > 0) ? 0 : block[i];
	block[i - 1] = (i > 0) ? 0 : block[i - 1];
}

// int		*to_stack_B(t_stack *head_a, t_stack *head_b, t_lists *list)
// {
// 	int		*elem_num;
// 	size_t	i;
// 	int		piv;
// 	int		tmp;

// 	tmp = ft_get_stack_size(head_a);
// 	elem_num = ft_memalloc(4 * tmp);
// 	elem_num[0] = tmp;
// 	i = -1;
// 	while (elem_num[++i] > 3)
// 	{
// 		tmp = -1;
// 		piv = ft_find_pivot(head_a, elem_num[i]);
// 		while (++tmp < elem_num[i])
// 		{
// 			if (head_a->value <= piv)
// 				ft_push(head_a, head_b);
// 			else
// 				ft_rotating(head_a, 'a', 0, list);
// 			//head_a = head_a->next;
// 		}
// 		elem_num[i + 1] = elem_num[i] / 2;
// 		elem_num[i] = elem_num[i] - elem_num[i + 1];
// 	}
// 	return (elem_num);
// }

void	ft_sort(t_head *head, int i)
{
	// t_stack	*head_b;
	// t_lists	*res;
	int		*blocks;
	int		fl;
	int		*tmp;

	//head_b = NULL;
	// res = NULL;
	//res = ft_memalloc(sizeof(t_lists));
	//res->com = ft_strdup("start");
	//i = ft_get_stack_size(head_a);
	fl = 0;
	blocks = ft_memalloc(4 * i);
	tmp = ft_memalloc(4 * i);
	blocks[0] = i;
	i = 0;
	ft_sort_a(head, blocks, fl);
	while (blocks[i] != 0)
		i++;
	while (--i >= 0)
	{
		tmp[0] = blocks[i];
		ft_sort_b(head, tmp);
	}
	//return (res);
	ft_memdel((void **)(&blocks));
	ft_memdel((void **)(&tmp));
}

void	ft_optimize(t_lists *lst)
{
	t_lists	*tmpl;
	char	*tmpc;

	tmpl = NULL;
	tmpc = NULL;
	while (lst != NULL && lst->next != NULL)
	{
		//tmp = ft_memalloc(sizeof(t_lsts));
		if (lst->com[0] != 'p' && lst->com[0] == lst->next->com[0] &&
		(lst->com[1] != lst->next->com[1] || 
		(lst->com[1] == 'r' && lst->com[2] != lst->next->com[2])))
		{
			tmpl = lst->next;
			tmpc = lst->com;
			//ft_memdel((void**)(&(lst->com)));
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
		//else
			// tmp->com = ft_strdup(lst->com);
			lst = lst->next;
		// tmp = tmp->next;
	}
	//ft_memdel((void**)(&list));
	//return (tmp);
}

int		main(int ac, char **av)
{
	int		i;
	// t_stack	*a;
	//t_lists	*coms;
	t_head	head;

	i = 0;
	//a = NULL;
	ft_bzero((void *)(&head), sizeof(t_head));
	head.lst = ft_memalloc(sizeof(t_lists));
	head.lst->com = ft_strdup("start");
	if (ac == 1 && (ft_printf("Error. No elements to sort.")))
		exit (1);
	while (++i < ac)
		// head.a = ft_addelement(ft_check(av[i], i), head.a, i);
		ft_check(av[i], i, &head);
	//coms = NULL;
	i = ft_get_stack_size(head.a);
	if (i < 3 && head.a->value > head.a->next->value)
		ft_swap(head.a, 'a', head.lst);
	else if (i > 3)
		// coms = (i - 1 > 3) ? ft_sort(a, i - 1) : ft_a_bot_3(head, 3);
		ft_sort(&head, i);
	else
		ft_a_bot_3(&head, 3);
	head.lst = head.lst->next;
	ft_optimize(head.lst);
	while (i-- > 0/* && head.lst->com*/)
	{
		ft_printf("%d ", head.a->value);
		if (i > 0 && head.a->value > head.a->next->value)
			ft_printf("((((((((((((((((((\n");
		head.a = head.a->next;
	}
	while (head.lst/* && head.lst->com*/)
	{
		ft_printf("%s\n", head.lst->com);
		head.lst = head.lst->next;
	}
	return (0);
}
