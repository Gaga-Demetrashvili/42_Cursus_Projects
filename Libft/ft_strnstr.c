/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:31 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/10 18:14:48 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j] && little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char *largestring = "aaabcabcd";
// 	const char *smallstring = "aabc";
// 	const char *ptr1;
// 	// char *ptr2;

// 	ptr1 = ft_strnstr(largestring, smallstring, -1);
// 	// ptr2 = strnstr(largestring, smallstring);
// 	printf("%s\n", ptr1); // lorem ipsum dolor sit amet
// 	// printf("%s", strnstr(largestring, smallstring, 3));
// 	return (0);
// }