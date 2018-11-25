/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:10:26 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/24 22:17:18 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_b(t_head *head, int *blocks, int j, int piv)
{
	size_t	i;

	i = 0;
	while (blocks[i] != 0)
		i++;
	while (i-- > 0)
	{
		j = -1;
		piv = ft_find_pivot(head->b, blocks[i]);
		if (blocks[i] > 0 && blocks[i] > 4)
			while (++j < blocks[i])
				(head->b->value > piv) ? ft_push(head, 'a')
				: (head->b = ft_rotating(head->b, 'b', 0, head->lst));
		else if (blocks[i] < 0 && blocks[i] < -4)
			while (++j < -1 * blocks[i])
			{
				head->b = ft_rotating(head->b, 'b', 1, head->lst);
				(head->b->value > piv) ? ft_push(head, 'a') : 0;
			}
		blocks[i + 1] = (blocks[i] < 0) ? blocks[i] / (-2) : blocks[i] / 2;
		blocks[i] = (blocks[i] < -4 || blocks[i] > 4) ?
		blocks[i] / (-2) - blocks[i] % 2 : blocks[i];
		ft_make_b(head, blocks, i, j);
	}
}

void	ft_sort_a(t_head *head, int *block, int fl)
{
	size_t	i;
	int		j;
	int		k;
	int		piv;

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
		i = ft_backtrack(head, block, fl, k);
	}
	(i > 0) ? ft_make_sort(head, block[i], block[i - 1]) : 0;
	block[i] = (i > 0) ? 0 : block[i];
	block[i - 1] = (i > 0) ? 0 : block[i - 1];
}

void	ft_sort(t_head *head, int i)
{
	int		*blocks;
	int		fl;
	int		*tmp;

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
		ft_sort_b(head, tmp, i, fl);
	}
	ft_memdel((void **)(&blocks));
	ft_memdel((void **)(&tmp));
}

int		main(int ac, char **av)
{
	t_head	head;
	t_lists	*tmp;

	ft_bzero((void *)(&head), sizeof(t_head));
	head.lst = ft_memalloc(sizeof(t_lists));
	head.lst->com = ft_strdup("start");
	if (ac == 1 && (ft_printf("Error. No elements to sort.")))
		exit(1);
	while (--ac > 0)
		ft_check(av[ac], ac, &head, ac);
	ac = ft_get_stack_size(head.a);
	if (ac < 3 && head.a->value > head.a->next->value)
		ft_swap(head.a, 'a', head.lst);
	else if (ac > 3)
		ft_sort(&head, ac);
	else
		ft_a_bot_3(&head, 3);
	tmp = head.lst->next;
	ft_optimize(tmp);
	while (tmp)
	{
		ft_printf("%s\n", tmp->com);
		tmp = tmp->next;
	}
	return (0);
}
