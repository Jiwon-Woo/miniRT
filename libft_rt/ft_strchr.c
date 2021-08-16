/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:50:04 by jwoo              #+#    #+#             */
/*   Updated: 2020/12/30 20:52:19 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	pos;

	pos = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == (char)c)
			return ((char *)&s[pos]);
		pos++;
	}
	if ((s[pos] == '\0') && ((char)c == '\0'))
		return ((char *)&s[pos]);
	return (NULL);
}
