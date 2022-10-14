/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:11:25 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 12:05:52 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_without_quote(char *str, char *new_str, int i, int j)
{
	char	c;
	int		trigger;

	trigger = 0;
	c = 0;
	while (str[i] != 0)
	{
		if (char_is_quote(str[i]) == 0 && check_quote(str, i) == 0
			&& trigger == 0)
		{
			c = str[i];
			trigger++;
			i++;
		}
		if (str[i] == c)
		{
			i++;
			trigger = 0;
			continue ;
		}	
		new_str[j] = str[i];
		j++;
		i++;
	}
	return (0);
}

char	*dup_without_quote_init(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_str = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (new_str == NULL)
		return (NULL);
	dup_without_quote(str, new_str, i, j);
	return (new_str);
}

int	cut_quote(t_minishell *minishell)
{
	char	*str2;
	t_tok	*temp;

	temp = minishell->list;
	while (minishell->list)
	{
		str2 = dup_without_quote_init(minishell->list->data);
		if (str2 == NULL)
			return (1);
		free (minishell->list->data);
		minishell->list->data = str2;
		minishell->list = minishell->list->next;
	}
	minishell->list = temp;
	ft_lstadd_back_tok(&minishell->list, ft_lstnew_tok(NULL, END_LEX, 0));
	if (ft_lstlast_tok(minishell->list) == NULL)
		return (1);
	return (0);
}	
