/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:53:06 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/04 14:53:01 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	length;
	size_t	index;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL || s == NULL)
		return (NULL);
	length = ft_strlen(s);
	i = 0;
	index = start;
	while (i < len && index < length)
		str[i++] = s[index++];
	str[i] = '\0';
	return (str);
}
