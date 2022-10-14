/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:51:12 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/12 17:44:12 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shitty_char(char c)
{
	if (c == '@' || c == '!' || c == '#' || c == '$' || c == '-'
		|| c == 34 || c == 39 || c == '&' || c == '*')
		return (1);
	return (0);
}

int	check_single_quote(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != 0 && str[(*i)] != 39)
		(*i)++;
	if (str[(*i)] != 39)
		return (1);
	return (0);
}

int	check_double_quote(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != 0 && str[(*i)] != 34)
		(*i)++;
	if (str[(*i)] != 34)
		return (1);
	return (0);
}
