/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:53:51 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 18:05:14 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_lexer_leght(char *str, int i)
{
	int		trigger;
	char	c;

	c = 0;
	trigger = 0;
	while (str[i] != 0 && char_is_token_with_trigg(str[i], trigger) == 0)
	{
		if (char_is_quote(str[i]) == 0
			&& check_quote(str, i) == 0 && trigger == 0)
		{
			trigger = 1;
			c = str[i];
			i++;
			continue ;
		}
		if (c == str[i])
			trigger = 0;
		i++;
	}
	return (i);
}

int	check_infos_one(char *str)
{
	if (str[0] == 34 && str[ft_strlen(str) - 1] == 34)
		return (1);
	if (str[0] == 39 && str[ft_strlen(str) - 1] == 39)
		return (0);
	return (0);
}

int	cmd_lexer(char *str, int i, t_minishell *minishell)
{
	char	*new_str;
	int		j;
	int		infos;

	infos = 0;
	j = i;
	i = cmd_lexer_leght(str, i);
	new_str = ft_calloc(sizeof(char), (i + 1));
	if (new_str == NULL)
		return (-1);
	ft_strlcpy(new_str, str + j, ((i - j) + 1));
	if (ft_strlen(new_str) == 0)
		free (new_str);
	else
	{
		infos = check_infos_one(new_str);
		ft_lstadd_back_tok(&minishell->list,
			ft_lstnew_tok(new_str, CMD_LEX, infos));
		if (ft_lstlast_tok(minishell->list) == NULL)
			return (free (new_str), -1);
	}
	return (i);
}
