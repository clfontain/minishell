/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:07:44 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/14 01:53:26 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gethdname(char *str)
{
	int		len;
	char	*p;

	len = ft_strlen(str);
	if (len <= 2 || ias(str + 2) == NULL)
		return (ft_putstr_fd("heredoc : bad name\n", 2), NULL);
	else
	{
		p = ft_strdup(str + 2);
		if (!p)
			error_clean_up(g_ms);
		return (p);
	}
}

t_command	**malloc_pa(t_minishell *ms, int *j, t_tok **tmp)
{
	int			i;
	t_command	**pa;

	i = 0;
	*j = 0;
	*tmp = ms->list;
	ms->i.l = -1;
	pa = (t_command **)ft_calloc(sizeof(t_command *), ms->nbr_cmd + 1);
	if (pa == NULL)
		error_clean_up(ms);
	while (i < ms->nbr_cmd)
	{
		pa[i] = (t_command *)malloc(sizeof(t_command));
		if (pa[i] == NULL)
		{
			free_param(pa);
			error_clean_up(ms);
		}
		init_struct(ms, pa[i]);
		i++;
	}
	return (pa);
}

int	ttok0(t_command **pa, int *i)
{
	if (list_to_cmd(pa, *i) == -1)
		return (-1);
	if (pa[*i]->cmd == NULL)
	{
		free_param(pa);
		error_clean_up(g_ms);
	}
	pa[++*i] = NULL;
	return (0);
}

int	ttok3(t_tok *tmp, t_command **pa, int *i, t_minishell *ms)
{
	char	wd[PATH_MAX];

	if (pa[*i]->here_doc++ > 0)
	{
		free(pa[*i]->limiter);
		free(pa[*i]->hdpath);
	}
	pa[*i]->limiter = gethdname(tmp->data);
	if (pa[*i]->limiter != NULL)
	{
		pa[*i]->lim_len = ft_strlen(pa[*i]->limiter);
		if (getcwd(wd, PATH_MAX))
			pa[*i]->hdpath = ft_strjoin(wd, "/.here_doc.tmp");
		else
			return (perror("get hd path ttok3"), errno);
		check_hd(pa, *i, ms, tmp->infos);
	}
	else
		return (-2);
	ms->i.l = -1;
	return (0);
}

int	ttok356(t_tok *tmp, t_command **pa, int *i, t_minishell *ms)
{
	if (tmp->type == 3 && g_ms->sigint == FALSE)
	{
		if (ttok3(tmp, pa, i, ms) == -2)
			return (-2);
	}
	else if (tmp->type == 5 && (tmp->infos == 0 || tmp->infos == 1))
	{
		ft_lstadd_back(&pa[*i]->cmdlst, ft_lstnew(ft_strdup(tmp->data), NULL));
		if (ft_lstlast(pa[*i]->cmdlst)->content == NULL)
			return (-1);
	}
	else if (tmp->type == 5 && tmp->infos == 2)
		return (checkforenvvar(tmp->data, pa, i));
	else if (tmp->type == 6)
	{
		if (list_to_cmd(pa, *i) == -1)
			return (-1);
		++*i;
		return (0);
	}
	return (0);
}
