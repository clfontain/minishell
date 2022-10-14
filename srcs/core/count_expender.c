/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_expender.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:52:09 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/12 14:22:36 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	break_point_alias(char *str, int i)
{
	if (ft_isdigit(str[i]) == 1 || shitty_char(str[i]) == 1)
		return (i += 1);
	while (str[i] != 0 && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i);
}

int	count_alias(char *str, t_minishell *ms, int i)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	j = break_point_alias(str, i) - i;
	while (ms->env_array[k] != NULL)
	{
		if (ft_strncmp(ms->env_array[k], str + i, (j)) == 0
			&& ms->env_array[k][j] == '=')
			ms->i.k += (ft_strlen(ms->env_array[k])) - j;
		k++;
	}
	i += (j);
	return (i);
}

int	count_ret(char *str, t_minishell *minishell, int i)
{
	char	*temp;

	(void)str;
	i++;
	temp = NULL;
	temp = ft_itoa(minishell->exec_ret);
	if (temp == NULL)
		return (perror("malloc"), (-1));
	minishell->i.k += ft_strlen(temp);
	free (temp);
	return (i);
}	

int	count_dollar(char *str, t_minishell *minishell, int i)
{
	i++;
	if (str[i] == '?')
		i = count_ret(str, minishell, i);
	else if (char_is_whitespace(str[i]) != 1
		&& char_is_token(str[i]) != 1 && char_is_quote(str[i]) != 0)
		i = count_alias(str, minishell, i);
	return (i);
}

int	count_expender(struct s_int i, char *str, t_minishell *minishell)
{
	while (str[i.i] != 0)
	{
		if (str[i.i] == '$' && i.k == 0)
		{
			i.i = count_dollar(str, minishell, i.i);
			if (i.i == -1)
				return (1);
			continue ;
		}
		if (str[i.i] == 34 && i.j == 0)
			i.j = 1;
		else if (str[i.i] == 34 && i.j == 1)
			i.j = 0;
		if (str[i.i] == 39 && i.k == 0
			&& check_quote(str, i.i) == 0 && i.j == 0)
			i.k = 1;
		else if (str[i.i] == 39 && i.k == 1)
			i.k = 0;
		i.i++;
		minishell->i.j++;
	}
	return (minishell->i.k += minishell->i.j);
}
