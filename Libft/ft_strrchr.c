/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:58:32 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/08 20:04:52 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	int		i;

	ch = (char)c;
	i = ft_strlen(s);
	if (ch == '\0' && *(s + i) == '\0')
		return ((char *)(s + i));
	while (i-- >= 0)
		if (*(s + i) == ch)
			return ((char *)(s + i));
	return (NULL);
}

// int	main(void)
// {
// 	char	*str;

// 	str = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
// 	printf("%s\n", ft_strrchr(str, '\0'));
// 	printf("%s\n", strrchr(str, '\0'));
// }
