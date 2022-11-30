# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 14:32:38 by cfontain          #+#    #+#              #
#    Updated: 2022/10/20 18:15:06 by tnoulens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIB_DIR		=	./libft

LIBFT		=	./libft/libft.a

MAIN		=	./srcs/main.c

CORE		=	./srcs/core/prompt.c\
				./srcs/core/pipex.c\
				./srcs/core/execute.c\
				./srcs/core/signals.c\
				./srcs/core/signals_child.c\
				./srcs/core/cmd_lexer.c\
				./srcs/core/copy_dollar.c\
				./srcs/core/build_env.c\
				./srcs/core/lexer.c\
				./srcs/core/count_expender.c\
				./srcs/core/cut_quote.c\
				./srcs/core/list_token.c\
				./srcs/core/expender_and_cut.c\
				./srcs/core/init_expender.c\
				./srcs/core/lexer_and_expend.c\
				./srcs/core/unset_tok.c\
				./srcs/core/str_join_tab.c\
				./srcs/core/heredoc_bullshit.c\
				./srcs/core/cmd_argv.c

BUILTIN		=	./srcs/built-in/ft_echo.c\
				./srcs/built-in/ft_env.c\
				./srcs/built-in/ft_exit.c\
				./srcs/built-in/ft_pwd.c\
				./srcs/built-in/ft_export.c\
				./srcs/built-in/ft_unset.c\
				./srcs/built-in/ft_cd.c

UTILITIES	= 	./srcs/utilities/garbage_collector.c\
				./srcs/utilities/welcome_message.c\
				./srcs/utilities/pipes_mgmt.c\
				./srcs/utilities/init.c\
				./srcs/utilities/char_check.c\
				./srcs/utilities/check_quote.c\
				./srcs/utilities/clean_up.c\
				./srcs/utilities/utils1.c\
				./srcs/utilities/utils2.c\
				./srcs/utilities/utils3.c
				
PARSING		=	./srcs/parsing/parser.c\
				./srcs/parsing/parser_tools1.c\
				./srcs/parsing/parser_tools2.c

SRCS		=	${MAIN} ${CORE} ${BUILTIN} ${UTILITIES} ${PARSING}

OBJS		=	${SRCS:.c=.o} 

RM			=	rm -f

CC			=	cc

FLAGS		=	-Wall -Wextra -Werror -g -I includes/

SUPP		=	printf "{\n    leak readline\n    Memcheck:Leak\n    ...\n    fun:readline\n}\n{\n    leak add_history\n   Memcheck:Leak\n    ...\n    fun:add_history\n}" > ignore_leak.supp

all			: ${NAME}

%.o: %.c
		@${CC} ${FLAGS}  -c $< -o ${<:.c=.o}

${LIBFT}	:
		@echo "\033[35m----Building libft----"
		@make -sC ${LIB_DIR}
		@echo "OK\033[0m"

${NAME}		: ${OBJS}  ${LIBFT}
		@echo "\033[34m----Compiling----"
		@${CC} ${FLAGS} ${OBJS} -L/usr/include -lreadline -ltermcap -o ${NAME} ${LIBFT}
		@${SUPP}
		@echo "OK\033[0m"

clean		:
		@echo "\033[31m----Cleaning libft----"
		@make clean -sC ${LIB_DIR}
		@echo "OK"
		@echo "\033[31m----Cleaning objects----"
		@${RM} ${OBJS}
		@echo "OK\033[0m"

fclean		: clean
		@echo "\033[33m----Cleaning all----"
		@${RM} ${NAME}
		@${RM} ${LIBFT}
		@${RM} ignore_leak.supp
		@echo "OK\033[0m"

re			: fclean all

ms	: all
		valgrind --suppressions=ignore_leak.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./minishell

.PHONY		: all clean fclean re
