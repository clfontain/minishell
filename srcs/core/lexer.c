/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:41:46 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 12:06:14 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_lenght(char *str, int i, char c)
{
	while (str[i] != 0 && char_is_whitespace(str[i]) == 1)
		i++;
	while (str[i] != 0 && char_is_whitespace(str[i]) == 0
		&& char_is_token(str[i]) == 0)
	{
		if (char_is_quote(str[i]) == 0 && check_quote(str, i) == 0)
		{
			c = str[i];
			i++;
			if (c == 34)
			{
				while (str[i] != 0 && str[i] != c && str[i] != '$')
					i++;
			}
			else
			{
				while (str[i] != 0 && str[i] != c)
				i++;
			}
		}
		i++;
	}
	return (i);
}

int	ft_copy_chevron(char *str, char *new_str, int j, int type)
{
	new_str[0] = str[j];
	j++;
	if (type == HEREDOC_LEX || type == APPEND_LEX)
	{
		new_str[1] = str[j];
		j++;
	}
	while (char_is_whitespace(str[j]) == 1)
		j++;
	return (j);
}

int	chevron(char *str, int i, t_minishell *minishell, int type)
{
	char	*new_str;
	int		j;
	char	c;

	c = 0;
	j = i;
	if (type == HEREDOC_LEX || type == APPEND_LEX)
		i += 2;
	if (type == 1 || type == 2)
		i += 1;
	i = token_lenght(str, i, c);
	new_str = ft_calloc(sizeof(char), (i + 1));
	if (new_str == NULL)
		return (perror("malloc"), -1);
	j = ft_copy_chevron(str, new_str, j, type);
	ft_strlcpy(new_str + (ft_strlen(new_str)), str + j, ((i - j) + 1));
	ft_lstadd_back_tok(&minishell->list, ft_lstnew_tok(new_str, type, 0));
	if (ft_lstlast_tok(minishell->list) == NULL)
		return (free (new_str), -1);
	return (i);
}

int	chevron_lexer(char *str, int i, t_minishell *minishell)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			i = chevron(str, i, minishell, HEREDOC_LEX);
		else
			i = chevron(str, i, minishell, STDIN_LEX);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			i = chevron(str, i, minishell, APPEND_LEX);
		else
			i = chevron(str, i, minishell, STDOUT_LEX);
	}
	if (i == -1)
		return (-1);
	return (i);
}

int	lexer(char *str, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		while (char_is_whitespace(str[i]) == 1)
			i++;
		if (str[i] == '>' || str[i] == '<')
			i = chevron_lexer(str, i, minishell);
		else if (str[i] == '|')
			i = pipe_lexer(i, minishell);
		else
			i = cmd_lexer(str, i, minishell);
		if (i == -1)
			return (1);
	}
	return (0);
}
