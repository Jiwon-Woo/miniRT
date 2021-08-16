/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:00:33 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/18 00:05:19 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fs;
	unsigned int	index;

	if (s == NULL || f == NULL)
		return (NULL);
	fs = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (fs == NULL)
		return (NULL);
	index = 0;
	while (index < (unsigned int)ft_strlen(s))
	{
		fs[index] = f(index, s[index]);
		index++;
	}
	fs[index] = '\0';
	return (fs);
}
