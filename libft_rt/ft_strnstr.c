/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:50:47 by jwoo              #+#    #+#             */
/*   Updated: 2020/12/30 19:23:52 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	point;
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)&haystack[0]);
	point = 0;
	while (haystack[point])
	{
		i = point;
		j = 0;
		while (haystack[i] && (haystack[i] == needle[j]) && (i < len))
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[point]);
		if (i == len)
			break ;
		point++;
	}
	return (NULL);
}
