/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_expend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:55:02 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 12:05:59 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipe(t_minishell *ms)
{
	t_tok	*temp;

	temp = ms->list;
	if (ms->list)
	{
		while (ms->list != NULL)
		{
			if (ms->list->type == PIPE_LEX)
				ms->nbr_cmd++;
			ms->list = ms->list->next;
		}
	}
	ms->list = temp;
}

int	pipe_lexer(int i, t_minishell *minishell)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char), 2);
	if (new_str == NULL)
		return (perror("malloc"), -1);
	new_str[0] = '|';
	ft_lstadd_back_tok(&minishell->list, ft_lstnew_tok(new_str, PIPE_LEX, 0));
	if (ft_lstlast_tok(minishell->list) == NULL)
		return (free (new_str), -1);
	return ((i + 1));
}

int	lexer_and_expend(char *p, t_minishell *minishell)
{
	if (lexer(p, minishell) == 1)
		return (1);
	check_heredoc_bullshit(minishell);
	if (expender_and_cut(minishell) == 1)
		return (1);
	count_pipe(minishell);
	return (0);
}
