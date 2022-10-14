/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:50:14 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/14 01:34:20 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 199309L
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
# include <linux/limits.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include "colors.h"

/* define macros */

# define SA_RESTART	0x10000000
# define SUCCESS 0
# define FAIL 1
# define TRUE 1
# define FALSE 0
# define MAX_PIPE 1024
# define MAX_FILE_NAME 255
# define NBR_BI 7

/* macros lexer type */

# define END_LEX 0
# define STDIN_LEX 1
# define STDOUT_LEX 2
# define HEREDOC_LEX 3
# define APPEND_LEX 4
# define CMD_LEX 5
# define PIPE_LEX 6
# define NOTFOUND " command not found"

/* Structure lexer */

typedef struct s_tok
{
	char			*data;
	int				type;
	int				infos;
	struct s_tok	*next;
}	t_tok;

typedef struct s_int
{
	int	i;
	int	j;
	int	k;
	int	l;
}	t_int;

typedef struct s_commands
{
	char			**cmd;
	t_list			*cmdlst;
	char			*inf;
	char			*o;
	char			**env;
	int				fd[2];
	int				fdhd;
	char			*hdpath;
	int				here_doc;
	char			*limiter;
	unsigned int	lim_len;
	int				exec_ret;
	short			sigint;
}	t_command;

typedef struct s_minishell
{
	t_command	**cm;
	int			nbr_cmd;
	char		**cmd_array;
	int			exec_ret;
	short		parse_status;
	t_list		*gb;
	t_list		*env;
	char		**env_array;
	t_tok		*list;
	t_int		i;
	short		sigint;
	pid_t		pid;
	pid_t		*pids;
	int			*end;
	int			hd_quote;
}	t_minishell;

/* struct for builtin utilities */

typedef struct s_builtin
{
	char	name[10];
	int		(*func)(t_minishell *ms, int argc, char **argv);
}	t_builtin;

/* Protos */

	/* --- lexer --- */

int			lexer_and_expend(char *p, t_minishell *minishell);
void		count_pipe(t_minishell *ms);
int			pipe_lexer(int i, t_minishell *minishell);	

int			lexer(char *str, t_minishell *minishell);
int			chevron_lexer(char *str, int i, t_minishell *minishell);
int			chevron(char *str, int i, t_minishell *minishell, int type);
int			ft_copy_chevron(char *str, char *new_str, int j, int type);
int			token_lenght(char *str, int i, char c);

int			cmd_lexer(char *str, int i, t_minishell *minishell);
int			cmd_lexer_leght(char *str, int i);

void		cmd_argv(char **argv, t_minishell *minishell);

	/* --- expender --- */

char		*init_expender(char *str, int len, t_minishell *minishell);
char		*copy_expend(char *s, char *new_s, t_minishell *ms);
int			trigg_alias(char *s, t_minishell *ms, int trigger);
void		copy_str(char *str, char *new_str, t_minishell *ms);

int			expender_and_cut(t_minishell *minishell);
char		*expender(char *str, t_minishell *ms);

int			count_expender(struct s_int i, char *str, t_minishell *minishell);
int			count_dollar(char *str, t_minishell *minishell, int i);
int			count_ret(char *str, t_minishell *minishell, int i);
int			count_alias(char *str, t_minishell *ms, int i);
int			break_point_alias(char *str, int i);

int			ft_unset_tok(t_minishell *ms);
char		**list_to_export_tok(t_minishell *ms);

int			cut_quote(t_minishell *minishell);
char		*dup_without_quote_init(char *str);
int			dup_without_quote(char *str, char *new_str, int i, int j);

int			copy_dollar(char *s, char *new_s, t_minishell *ms);
void		search_alias(char *str, char *new_s, t_minishell *ms);
void		copy_alias(char *env, char *new_s, t_minishell *ms);
int			copy_ret(char *new_s, t_minishell *ms);

char		*add_double_quote(char *str);
char		*suppr_double_quote(char *str);

	/* --- parser --- */

int			parse(t_minishell *ms);
int			ttok4(t_tok *tmp, t_command **pa, int i);
t_command	**malloc_pa(t_minishell *ms, int *j, t_tok **tmp);
int			ttok0(t_command **pa, int *i);
int			ttok1(t_tok *tmp, t_command **pa, int i);
int			ttok2(t_tok *tmp, t_command **pa, int i);
int			ttok356(t_tok *tmp, t_command **pa, int *i, t_minishell *ms);
void		check_hd(t_command **pa, int i, t_minishell *ms, int check_hdq);
int			list_to_cmd(t_command **cm, int i);
int			checkforenvvar(char *content, t_command **pa, int *i);

	/* --- core --- */

char		*prompt_line(t_minishell *ms);
int			exec(t_minishell *ms, char **cmds, char **envp);
int			pipex(t_minishell *minishell);
void		build_env(t_minishell *ms, char **envp);
int			is_built_in(t_minishell *ms, int argc, char **argv);

	/* --- utilities --- */

int			check_heredoc_bullshit(t_minishell *ms);
int			shitty_char(char c);
void		print_welcome_msg(char **envp);
int			gb_c(t_list **gb, void *content, void **content2);
void		init_minishell(t_minishell *minishell, int argc, char **envp);
void		mini_init(t_minishell *ms);
void		clean_up(t_list *lst, char **env_array, t_list *env);
void		clean_iteration(t_minishell *ms);
void		init_struct(t_minishell *ms, t_command *cm);
void		init_builtin(t_builtin *built);
int			close_pipes(int cmd_nbr, int *end, t_command *cm);
int			close_pipes_parent(int cmd_nbr, int *end, t_minishell *ms);
void		close_std_in_child(t_minishell *ms);
int			open_pipes(int cmd_nbr, int *end);
void		dupper(int input, int output, t_minishell *ms, int i);
int			char_is_token(char c);
int			char_is_quote(char c);
int			char_is_whitespace(char c);
int			check_quote(char *str, int i);
int			char_is_token_with_trigg(char c, int trigger);
void		error_clean_up(t_minishell *ms);
void		list_to_array(t_minishell *ms);
void		list_to_export(t_minishell *ms);
int			nb_cmd(char **argv);
void		printlist(t_tok *list);
void		free_param(t_command **param);
void		ft_lstclear_tok(t_tok *lst);
int			ft_lstsize_tok(t_tok *lst);
t_tok		*ft_lstnew_tok(char *content, int content2, int content3);
t_tok		*ft_lstlast_tok(t_tok *lst);
void		ft_lstadd_back_tok(t_tok **lst, t_tok *new);
void		ft_printab(char **str);
char		*ias(char *str);
void		get_fd_in(t_command *cm);
void		exit_fd(void);
void		bubblesortlist(t_list *start);
char		*genv(t_minishell *ms, char *p);
void		child_exit(t_minishell *ms);
char		*str_join_tab(char **argv);
int			ft_count_tab(char **str);
int			copy_tab_with_space(char **argv, char *str);
void		freer(char **ptr);
void		init_int(t_minishell *ms, t_int *i);

	/* --- build-in --- */

int			ft_echo(t_minishell *minishell, int argc, char **argv);
int			ft_pwd(t_minishell *minishell, int argc, char **argv);
int			ft_env(t_minishell *minishell, int argc, char **argv);
int			ft_exit(t_minishell *minishell, int argc, char **argv);
int			ft_export(t_minishell *minishell, int argc, char **argv);
int			ft_unset(t_minishell *ms, int argc, char **argv);
int			ft_cd(t_minishell *ms, int argc, char **argv);

	/* --- signals --- */
void		tmp_handler(int sig, siginfo_t *info, void *context);
void		signal_handling(void);

/* Unique local variable to manage signals with sigaction() */

extern t_minishell	*g_ms;

/* This is a minimal set of ANSI/VT100 color codes */

# define END "\033[0m"
# define GREY "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define BLUE "\033[0;34m"
# define IRED "\033[0;41m"
# define BOLD "\033[1m"
# define UNDER "\033[4m"
# define REV "\033[7m"

#endif
