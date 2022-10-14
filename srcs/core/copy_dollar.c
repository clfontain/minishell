/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:57:51 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 17:34:19 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_ret(char *new_s, t_minishell *ms)
{
	int		i;
	char	*temp;

	i = 0;
	ms->i.i++;
	temp = NULL;
	temp = ft_itoa(ms->exec_ret);
	if (temp == NULL)
		return (perror("malloc"), (1));
	while (temp[i] != 0)
	{
		new_s[ms->i.j] = temp[i];
		i++;
		ms->i.j++;
	}
	free (temp);
	return (0);
}	

void	copy_alias(char *env, char *new_s, t_minishell *ms)
{
	int	i;

	i = 0;
	while (env[i] != 0)
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	i++;
	while (env[i] != 0)
	{
		new_s[ms->i.j] = env[i];
		i++;
		ms->i.j++;
	}
	if (ms->list->type == 5 && ms->list->infos != 1)
		ms->list->infos = 2;
}

void	search_alias(char *str, char *new_s, t_minishell *ms)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	j = break_point_alias(str, ms->i.i) - ms->i.i;
	while (ms->env_array[k] != NULL)
	{
		if (ft_strncmp(ms->env_array[k], str + ms->i.i, j) == 0
			&& ms->env_array[k][j] == '=')
			copy_alias(ms->env_array[k], new_s, ms);
		k++;
	}
	ms->i.i += (j);
}

int	copy_dollar(char *s, char *new_s, t_minishell *ms)
{
	ms->i.i++;
	if (s[ms->i.i] == '?')
	{
		if (copy_ret(new_s, ms) == 1)
			return (1);
	}	
	else if (char_is_whitespace(s[ms->i.i]) != 1
		&& char_is_token(s[ms->i.i]) != 1 && char_is_quote(s[ms->i.i]) != 0)
		search_alias(s, new_s, ms);
	return (0);
}
