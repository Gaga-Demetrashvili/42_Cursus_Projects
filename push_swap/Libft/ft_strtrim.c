/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:44:10 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/11 21:16:13 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*a;

	a = NULL;
	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j - 1]))
		j--;
	a = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!a)
		return (NULL);
	ft_strlcpy(a, &s1[i], j - i + 1);
	return (a);
}

// int	main(void)
// {
// 	char *strtrim;
// 	char s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
// 	if (!(strtrim = ft_strtrim(s1, " ")))
// 		ft_printf("%s", "NULL");
// 	else
// 		ft_printf("%s", strtrim);
// 	if (strtrim == s1)
// 		ft_printf("\nA new string was not returned");
// 	return (0);
// }