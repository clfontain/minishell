/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:44:09 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/14 00:20:59 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_clean_up(t_minishell *ms)
{
	int	error;

	error = errno;
	ft_printf("%s\n", strerror(error));
	ft_lstclear(ms->gb);
	ft_lstclear(ms->env);
	ft_lstclear_tok(ms->list);
	free(ms->env_array);
	exit(error);
}

void	free_param(t_command **param)
{
	int	i;

	i = 0;
	if (param != NULL)
	{
		while (param[i] != NULL)
		{
			free(param[i]->cmd);
			ft_lstclear(param[i]->cmdlst);
			free(param[i]->inf);
			free(param[i]->o);
			free(param[i]->limiter);
			free(param[i]->hdpath);
			free(param[i]);
			i++;
		}
	}
	free(param);
}

void	clean_iteration(t_minishell *ms)
{
	ft_lstclear(ms->gb);
	ft_lstclear_tok(ms->list);
	free_param(ms->cm);
}

void	clean_up(t_list *lst, char **env_array, t_list *env)
{
	ft_lstclear(lst);
	ft_lstclear(env);
	free(env_array);
	return ;
}

void	freer(char **ptr)
{
	free(ptr[1]);
	free(ptr);
}
