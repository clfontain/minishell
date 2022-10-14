/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:06:11 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/13 18:15:18 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkforenvvar(char *content, t_command **pa, int *i)
{
	char	**p;
	int		k;
	int		ix;

	p = NULL;
	ix = -1;
	if (ias(content))
	{
		p = ft_split(content, ' ');
		if (p == NULL)
			return (-1);
		k = nb_cmd(p);
		while (++ix, ix < k)
		{
			ft_lstadd_back(&pa[*i]->cmdlst, ft_lstnew(ft_strdup(p[ix]), NULL));
			if (pa[*i]->cmdlst->content == NULL || pa[*i]->cmdlst == NULL)
				return (ft_free_split(p), -1);
		}
	}
	return (ft_free_split(p), 0);
}

static void	swap(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	bubblesortlist(t_list *start)
{
	short	swapped;
	t_list	*ptr1;
	t_list	*lptr;

	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

char	*genv(t_minishell *ms, char *p)
{
	int	i;

	i = 0;
	while (ms->env_array[i])
	{
		if (!ft_cmpchr(ms->env_array[i], p, '='))
			return (ft_strchr(ms->env_array[i], '=') + 1);
		i++;
	}
	return (NULL);
}
