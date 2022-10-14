/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bullshit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:54:49 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 18:04:29 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc_quote2(char *str, int i, t_minishell *ms)
{
	int	quote;
	int	single;

	quote = 0;
	single = 0;
	while (str[i] != 0 && char_is_whitespace(str[i]) == 0)
	{
		if (str[i] == 34)
			quote++;
		if (str[i] == 39)
			single++;
		i++;
	}	
	if (quote >= 2 || single >= 2)
		ms->list->infos = 1;
	return (0);
}

int	check_heredoc_quote(char *str, t_minishell *ms)
{
	int	i;

	i = 2;
	ms->list->infos = 0;
	while (char_is_whitespace(str[i]) == 1)
		i++;
	check_heredoc_quote2(str, i, ms);
	return (0);
}

int	check_heredoc_bullshit(t_minishell *ms)
{
	t_tok	*tmp;

	tmp = ms->list;
	if (ms->list)
	{
		while (ms->list)
		{
			if (ms->list->type == 3)
				check_heredoc_quote(ms->list->data, ms);
			ms->list = ms->list->next;
		}
	}
	ms->list = tmp;
	return (0);
}

char	*suppr_double_quote(char *str)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char), ft_strlen(str));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + 1, (ft_strlen(str) - 1));
	free (str);
	return (new_str);
}

char	*add_double_quote(char *str)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char), (ft_strlen(str) + 3));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str + 1, str, (ft_strlen(str) + 1));
	new_str[0] = 34;
	new_str[ft_strlen(new_str)] = 34;
	free (str);
	return (new_str);
}
