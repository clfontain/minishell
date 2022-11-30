/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:09:29 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/17 12:59:23 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ias(char *str)
{
	char	*p;

	if (str == NULL)
		return (NULL);
	p = str;
	while (*p)
	{
		if (!ft_isspace(*p))
			return (p);
		p++;
	}
	return (NULL);
}

char	*expd(char *str, t_minishell *ms)
{
	char			*new_str;
	int				len;
	t_int			i;

	init_int(ms, &i);
	len = 0;
	if (str == NULL)
		return (NULL);
	str = add_double_quote(str);
	if (str == NULL)
		return (ft_lstclear_tok(ms->list),
			clean_up(ms->gb, ms->env_array, ms->env),
			perror("malloc"), exit(errno), NULL);
	len = count_expender(i, str, ms);
	len += ft_strlen(str);
	new_str = init_expender(str, len, ms);
	if (new_str == NULL)
		return (NULL);
	free(str);
	new_str = suppr_double_quote(new_str);
	if (new_str == NULL)
		return (ft_lstclear_tok(ms->list),
			clean_up(ms->gb, ms->env_array, ms->env),
			perror("malloc"), exit(errno), NULL);
	return (new_str);
}

static void	ex_and_put(int check_hdq, char *p, t_minishell *ms, int tmp_fd)
{
	if (check_hdq != 1)
		p = expd(p, ms);
	ft_putstr_fd(p, tmp_fd);
	free(p);
}

void	check_hd(t_command **pa, int i, t_minishell *ms, int check_hdq)
{
	char	*p;
	int		tmp_fd;

	tmp_fd = open(".here_doc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1 || tmp_fd > FOPEN_MAX)
		return (perror("check_heredoc open"), (void)0);
	pa[i]->fdhd = dup(STDIN_FILENO);
	ms->i.l = i;
	while (1 && g_ms->sigint == FALSE)
	{
		write(STDIN_FILENO, "heredoc> ", 9);
		p = get_next_line(pa[i]->fdhd);
		if (p == NULL || cmpheredoc(p, pa[i]->limiter, '\n') == 0)
		{
			close(pa[i]->fdhd);
			if (p == NULL)
				ft_fprintf(2, "\nwarning: expected %s\n", pa[i]->limiter);
			free(p);
			break ;
		}
		ex_and_put(check_hdq, p, ms, tmp_fd);
	}
	close(tmp_fd);
}

int	parse(t_minishell *ms)
{
	t_tok		*tmp;
	int			f;
	int			i;

	ms->cm = malloc_pa(ms, &i, &tmp);
	while (tmp)
	{
		if (tmp->type == 0)
			ttok0(ms->cm, &i);
		else if ((tmp->type == 1 && ttok1(tmp, ms->cm, i) == 1)
			|| (tmp->type == 2 && ttok2(tmp, ms->cm, i) == 1)
			|| (tmp->type == 4 && ttok4(tmp, ms->cm, i) == 1))
			return (1);
		else
		{
			f = ttok356(tmp, ms->cm, &i, ms);
			if (f == -1)
				return (free_param(ms->cm), error_clean_up(ms), 1);
			if (f == -2 || f != 0)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
