/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:09:09 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/05 16:29:51 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getfilename(char *str, int type)
{
	char	*p;

	if (type == 2 || type == 1)
	{
		if (ft_strlen(str) <= 1 || ias(str + 1) == NULL)
			return (ft_putstr_fd("redirection : bad name\n", 2), NULL);
		p = ft_strdup(str + 1);
		if (!p)
			error_clean_up(g_ms);
		return (p);
	}
	else
	{
		if (ft_strlen(str) <= 2 || ias(str + 2) == NULL)
			return (ft_putstr_fd("redirection : bad name\n", 2), NULL);
		p = ft_strdup(str + 2);
		if (!p)
			error_clean_up(g_ms);
		return (p);
	}
}

int	ttok4(t_tok *tmp, t_command **pa, int i)
{
	if (pa[i]->fd[1] <= 1)
	{
		pa[i]->o = getfilename(tmp->data, 4);
		if (pa[i]->o == NULL)
			return (1);
		pa[i]->fd[1] = open(pa[i]->o, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (pa[i]->fd[1] <= -1 || pa[i]->fd[1] > FOPEN_MAX)
			return (perror("parse fd out append open"), 1);
	}
	else
	{
		if (close(pa[i]->fd[1]) == -1)
			return (perror("parse fd out append close"), 1);
		if (pa[i]->o)
			free(pa[i]->o);
		pa[i]->o = getfilename(tmp->data, 4);
		if (pa[i]->o == NULL)
			return (1);
		pa[i]->fd[1] = open(pa[i]->o, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (pa[i]->fd[1] <= -1 || pa[i]->fd[1] > FOPEN_MAX)
			return (perror("parse fd out append open"), 1);
	}
	return (0);
}

int	ttok1(t_tok *tmp, t_command **pa, int i)
{
	if (pa[i]->fd[0] <= 0)
	{
		pa[i]->inf = getfilename(tmp->data, 1);
		if (pa[i]->inf == NULL)
			return (1);
		pa[i]->fd[0] = open(pa[i]->inf, O_RDONLY);
		if (pa[i]->fd[0] <= -1 || pa[i]->fd[0] > FOPEN_MAX)
			return (perror("parse fd in open"), 1);
	}
	else
	{
		if (close(pa[i]->fd[0]) == -1)
			perror("parse fd in close");
		if (pa[i]->inf)
			free(pa[i]->inf);
		pa[i]->here_doc = FALSE;
		pa[i]->inf = getfilename(tmp->data, 1);
		if (pa[i]->inf == NULL)
			return (1);
		pa[i]->fd[0] = open(pa[i]->inf, O_RDONLY);
		if (pa[i]->fd[0] <= -1 || pa[i]->fd[0] > FOPEN_MAX)
			return (perror("parse fd in open"), 1);
	}
	return (0);
}

int	ttok2(t_tok *tmp, t_command **pa, int i)
{
	if (pa[i]->fd[1] <= 1)
	{
		pa[i]->o = getfilename(tmp->data, 2);
		if (pa[i]->o == NULL)
			return (1);
		pa[i]->fd[1] = open(pa[i]->o, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pa[i]->fd[1] <= -1 || pa[i]->fd[1] > FOPEN_MAX)
			return (perror("parse fd out open"), 1);
	}
	else
	{
		if (close(pa[i]->fd[1]) == -1)
			return (perror("parse fd out close"), 1);
		if (pa[i]->o)
			free(pa[i]->o);
		pa[i]->o = getfilename(tmp->data, 2);
		if (pa[i]->o == NULL)
			return (1);
		pa[i]->fd[1] = open(pa[i]->o, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pa[i]->fd[1] <= -1 || pa[i]->fd[1] > FOPEN_MAX)
			return (perror("parse fd out open"), 1);
	}
	return (0);
}
