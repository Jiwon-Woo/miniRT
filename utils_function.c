/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:20 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:27 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		is_space(char s)
{
	if (s == 32 || (9 <= s && s <= 13))
		return (1);
	return (0);
}

int		word_num(char *s)
{
	int	num;
	int	index;

	if (*s == 0)
		return (0);
	num = 0;
	if (is_space(s[0]) == 0)
		num++;
	index = 0;
	while (++index < ft_strlen(s))
	{
		if (is_space(s[index - 1]) == 1 && is_space(s[index]) == 0)
			num++;
	}
	return (num);
}
