/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:27:55 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/10 16:27:55 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;
	size_t			i;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (st1[i] == st2[i])
		{
			i++;
			continue ;
		}
		if (st1[i] > st2[i])
			return (1);
		else
			return (-1);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char *str1 = "1434";
// 	const char *str2 = "1434";
// 	printf("%d\n", ft_memcmp(str1, str1 + 1, 3));
// 	printf("%d", memcmp(str2, str2 + 1, 3));
// 	return (0);
// }