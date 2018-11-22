/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/10/27 18:55:05 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_check(char *s, int par)
{
	//t_stack	*tmp;
	int		i;
	long	res;
	long	count;

	//tmp = head;
	//(s[0] == '-') ? i = 0 : i = -1;
	i = ft_strlen(s);
	//(s[0] == '-') ? count = -1 : count = 1;
	res = 0;
	count = 1;
	// if (s[0] == '-')
	// {
	// 	count = -1;
	// 	i++
	// }
	while (--i >= 0 && s[i] > 47 && s[i] < 58)
	{
		res = res + count * (s[i] - 48);
		count = count * 10;
	}
	if (i > -1 && !(i = 0 && s[i] == '-'))
	{
		ft_printf("Error. %d element contains a non digital value.", par);
		exit (1);
	}
	if (i = 0 && s[i] == '-')
		res = -1 * res;
	if (res > 2147483647 || res < -2147483648)
	{
		ft_printf("Error. %d element isn't integer.", par);
		exit (1);
	}
	return (int(res));
}

int		ft_find_pivot(t_stack *head, int num)
{
	t_stack	*tmp;
	int		cur;
	int		less;
	int		res;
	int		i;

	cur = -1;
	while(++cur < num)
	{
		i = -1;
		tmp = head;
		while (++i < cur)
			tmp = tmp->next;
		res = tmp->value;
		i = -1;
		tmp = head;
		less = 0;
		while (tmp->next->value != head->value && ++i < num)
		{
			if (tmp->value <= res)
				less++;
			tmp = tmp->next;
		}
		if (num - 2 * less <= 0 && num - 2 * less >= -1)
			return (res);
	}
}

void	ft_addelement(int to_add, t_stack *head, int par)
{
	t_stack	*tmp;

	tmp = head;
	if (head == NULL)
	{
		head = (t_stack *)malloc(sizeof(t_stack));
		head->next = head;
		head->prev = head;
		head->value = to_add;
		return ;
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
}

void	ft_swap(t_stack *head, char mark, t_list *list)
{
	int	tmp;

	if (head == NULL || head->next == head)
		return ;
	tmp = head->value;
	head->value = head->next->value;
	head->next->value = tmp;
	if (list == NULL)
		list = ft_memalloc(sizeof(t_list));
	else
	{
		list->next=ft_memalloc(sizeof(t_list));
		list =list->next;
	}
	if (mark == 'a')
		list->com = ft_strdup("sa");
	else
		list->com = ft_strdup("sb");	
}

void	ft_push(t_stack *from, t_stack *to)//ссылка на ссылку или нет
{
	t_stack	*tmp;

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
		return ;
	}
	to = tmp;
	to->next = to;
	to->prev = to;
}

int		*to_stack_B(t_stack *head_a, t_stack *head_b)
{
	int		*elem_num;
	size_t	i;
	int		piv;
	int		tmp;

	i = -1;
	elem_num = ft_get_stack_size(head_a);
	while (elem_num[++i] > 3)
	{
		tmp = head_a->value;
		piv = ft_find_pivot(head_a);
		while (head_a->next->value != tmp)
		{
			if (head_a->value <= piv)
				ft_push(head_a, head_b);
			else
			{
				head_a = head_a->next;
				elem_num[i + 1]++;
			}
			head_a = head_a->next;
			elem_num[i] = elem_num[i] - elem_num[i + 1];
		}
	}
	return (elem_num);
}

t_list	*ft_sort(t_stack *head_a)
{
	t_stack	*head_b;
	t_list	*res;

	head_b = NULL;
	res = NULL;
	
}

int		main(int ac, char **av)
{
	int		i;
	t_stack	*a;
	t_list	*coms;
	
	i = 0;
	a = NULL;
	if (ac == 1)
	{
		ft_printf("Error. No elements to sort.");
		exit (1);
	}
	while (++i < ac)
	{
		// if (ft_check(av[i], i))
		ft_addelement(ft_check(av[i], i), a, i);
		// else
		// {
		// 	ft_printf("Error")
		// 	exit;//f;lsdkf
		// }
	}
	coms = ft_sort(a);
	while (coms)
	{
		ft_printf("%s\n", coms->data);
		coms = coms->next;
	}
	return (0);
}
