/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:27:31 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/03 14:53:53 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str, int i)
{
	if (str[i] == 39)
	{
		i++;
		while (str[i] != 0 && str[i] != 39)
			i++;
		if (str[i] != 39)
			return (1);
	}
	if (str[i] == 34)
	{
		i++;
		while (str[i] != 0 && str[i] != 34)
			i++;
		if (str[i] != 34)
			return (1);
	}
	return (0);
}

int	char_is_token_with_trigg(char c, int trigger)
{
	if (trigger == 0)
	{
		if (c == '<' || c == '>' || c == '|' || char_is_whitespace(c) == 1)
			return (1);
	}	
	return (0);
}

int	char_is_quote(char c)
{
	if (c == 34 || c == 39)
		return (0);
	else
		return (1);
}

int	char_is_whitespace(char c)
{
	if (c >= 9 && c <= 11)
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	char_is_token(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}
