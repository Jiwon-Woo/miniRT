/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_comma.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:23 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		factor_num(char *s)
{
	int	num;
	int	index;

	if (*s == 0)
		return (0);
	num = 0;
	if (s[0] != ',')
		num++;
	index = 0;
	while (++index < ft_strlen(s))
	{
		if (s[index] == ',')
			num++;
	}
	return (num);
}

static char		**free_split(char **words, int num)
{
	int	n;

	n = -1;
	while (++n <= num)
	{
		free(words[n]);
		words[n] = 0;
	}
	free(words);
	words = 0;
	return (words);
}

static char		**factor_len(char **factor, char *s, int factor_num)
{
	int	len;
	int	index;
	int	num;

	index = 0;
	num = 0;
	while (num < factor_num && index < ft_strlen(s))
	{
		while (s[index] == ',' && index < ft_strlen(s))
			index++;
		len = 0;
		while (s[index] != ',' && index < ft_strlen(s))
		{
			len++;
			index++;
		}
		if (len != 0)
		{
			factor[num] = (char *)malloc(sizeof(char) * (len + 1));
			if (factor[num] == 0)
				return (free_split(factor, num));
			num++;
		}
	}
	return (factor);
}

static void		factor_split(char **factor, char *s, int factor_num)
{
	int	len;
	int	index;
	int	num;

	index = 0;
	num = 0;
	len = 0;
	while (num < factor_num && index < ft_strlen(s))
	{
		if (s[index] == ',')
		{
			index++;
			continue ;
		}
		len = 0;
		while (s[index] != ',' && index < ft_strlen(s))
		{
			factor[num][len] = s[index];
			len++;
			index++;
		}
		factor[num][len] = '\0';
		num++;
	}
	factor[num] = 0;
}

char			**split_comma(char *s)
{
	char	**words;
	int		num;

	if (s == 0)
		return (0);
	num = factor_num(s);
	if (num != 3)
		return (0);
	words = (char **)malloc(sizeof(char *) * (num + 1));
	if (words == 0)
		return (0);
	if (factor_len(words, s, num) == 0)
		return (0);
	factor_split(words, s, num);
	return (words);
}
