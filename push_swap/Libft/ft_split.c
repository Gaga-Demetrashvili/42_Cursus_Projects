/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:11:17 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/12 19:11:17 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// void	ft_writecharn(char c, size_t n)
// {
// 	while (n > 0)
// 	{
// 		write(1, &c, 1);
// 		n--;
// 	}
// 	write(1, "\n", 1);
// }

// void	ft_printtestres(char *funcname, char *ft_res, char *res)
// {
// 	static size_t	test_num = 1;
// 	char			*test;
// 	char			*emoji;

// 	test = "Test";
// 	if (test_num == 1)
// 	{
// 		ft_printf("%s %ss\n", funcname, test);
// 		fflush(stdout);
// 		ft_writecharn('-', 15);
// 	}
// 	ft_printf("%s %zu\t", test, test_num++);
// 	// ft_printf("Gaga Demetrashvili\n");
// 	// I use fflush(stdout) (stdout refers to terminal),
// 	// because ft_printf saves text to print in buffer,
// 	// then before program ends C runtime flushes,
// 	// which means shows output to terminal. That's why without
// 	// using fflush, first write method's output will be shown,
// 	//	because it writes directly to the file descriptor
// 	// (stdout for example - which stands for terminal) via the kernel,
// 	// immediately.It is said that if you put
// 	// "\n" (new line) in the end of the string of ft_printf,
// 	// it should automatically flush output like fflush(stdout),
// 	// but probably it doesn't always work like that so fflush(stdout)
//  // is go to method for that problem.
// 	ft_printf("ft_%s: %p | %s: %p\t", funcname, ft_res, funcname, res);
// 	emoji = (ft_res == res) ? "✅" : "❌";
// 	ft_printf("%s\n", emoji);
// }

// size_t	ft_strlen(const char *str)
// {
// 	int	len;

// 	len = 0;
// 	while (*str++)
// 		len++;
// 	return (len);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	i;
// 	size_t	s_len;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len || len == 0)
// 		len = 0;
// 	else if (len > s_len - start)
// 		len = s_len - start;
// 	substr = (char *)malloc(sizeof(char) * (len + 1));
// 	if (substr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && s[start + i])
// 	{
// 		substr[i] = s[start + i];
// 		i++;
// 	}
// 	substr[i] = '\0';
// 	return (substr);
// }

// void	ft_print_result(char **arr)
// {
// 	size_t	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		ft_printf("%s\n", arr[i]);
// 		i++;
// 	}
// }

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free_array(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

static char	**ft_alloc_array(const char *s, char c, size_t *word_count)
{
	char	**result;

	*word_count = ft_count_words(s, c);
	result = NULL;
	result = (char **)malloc(sizeof(char *) * (*word_count + 1));
	if (!result)
		return (NULL);
	return (result);
}

static char	**ft_fill_array(char **result, const char *s, char c,
		size_t word_count)
{
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	start = 0;
	while (i < word_count)
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != c)
			len++;
		result[i] = ft_substr(s, start, len);
		if (!result[i])
		{
			ft_free_array(result, i);
			return (NULL);
		}
		start += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	result = NULL;
	word_count = 0;
	result = ft_alloc_array(s, c, &word_count);
	if (!result)
		return (NULL);
	if (word_count == 0)
	{
		result[0] = NULL;
		return (result);
	}
	return (ft_fill_array(result, s, c, word_count));
}

// int	main(void)
// {
// 	char		**splitted_string;
// 	const char	*str_to_split;
// 	char		split_on;

// 	// str_to_split = "   lorem   ipsum dolor     sit amet,
// 	// 				consectetur adipiscing elit.Sed non risus.Suspendisse ";
// 	split_on = ' ';
// 	splitted_string = ft_split("   lorem   ipsum dolor     sit amet,"
// 			" consectetur adipiscing elit.Sed non risus.Suspendisse ",
// 								split_on);
// 	// splitted_string = ft_split("", split_on);
// 	ft_print_result(splitted_string);
// 	free(splitted_string);
// 	return (0);
// }

// ----- My old Implementation ----- //

// int	ft_strchr_for_split(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return (i);
// 		i++;
// 	}
// 	if ((char)c == '\0')
// 		return (i);
// 	return (-1);
// }

// size_t	ft_countwords(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	word_count;

// 	i = 1;
// 	word_count = 0;
// 	if (s[0] && s[0] != c)
// 		word_count++;
// 	while (s[i])
// 	{
// 		if (s[i] != c && s[i - 1] == c)
// 			word_count++;
// 		i++;
// 	}
// 	return (word_count);
// }

// void	ft_clear_memory(char **strarr, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		free(strarr[i]);
// 		i++;
// 	}
// }

// void	ft_initialize_arr(char **strarr, const char *src, char c,
// 		size_t word_count)
// {
// 	size_t	start_p;
// 	int		len;
// 	size_t	i;

// 	start_p = 0;
// 	i = 0;
// 	while (i < word_count)
// 	{
// 		while (src[start_p] == c)
// 			start_p++;
// 		len = ft_strchr_for_split(src + start_p, c);
// 		if (len < 0)
// 			len = ft_strlen(src + start_p);
// 		strarr[i] = ft_substr(src, start_p, len);
// 		if (!strarr[i])
// 		{
// 			ft_clear_memory(strarr, i);
// 			break ;
// 		}
// 		start_p += len;
// 		i++;
// 	}
// 	strarr[i] = NULL;
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr_of_strings;
// 	size_t	str_len;
// 	size_t	word_count;

// 	if (!s)
// 		return (NULL);
// 	str_len = ft_strlen(s);
// 	if (str_len == 0)
// 		word_count = 0;
// 	else
// 		word_count = ft_countwords(s, c);
// 	arr_of_strings = (char **)malloc(sizeof(char *) * (word_count + 1));
// 	if (!arr_of_strings)
// 		return (NULL);
// 	if (word_count == 0)
// 	{
// 		arr_of_strings[0] = NULL;
// 		return (arr_of_strings);
// 	}
// 	ft_initialize_arr(arr_of_strings, s, c, word_count);
// 	return (arr_of_strings);
// }

// -------------------------------- //

// int	main(void)
// {
// // Test for ft_split
// char **splitted_string;
// const char *str_to_split = "Gaga Temo leqso beqa";
// char split_on = ' ';
// char *ft_substr_res;

// splitted_string = ft_split(str_to_split, split_on);

// Test for ft_countwords
// char *str_to_test_for_count = "  a   a  a ";
// ft_printf("%zu\n", ft_countwords(str_to_test_for_count, ' '));

// Test for ft_substr
// const char *str_to_substr = "Gaga Temo leqso beqa";

// ft_printf("%s", ft_substr_res = ft_substr(str_to_split, 18, 4));
// free(ft_substr_res);

// Testing utility methods for ft_split
// char *funcname = "strchr";
// char *test_str = NULL;
// char test_chr = 0;
// char *ft_res = NULL;
// char *res = NULL;

// test_str = "Gaga";
// size_t i = 0;
// char *test_chr_arr = "g\0d";

// while(i < 3)
// {
//      ft_printtestres(funcname, ft_strchr_og(test_str, test_chr_arr[i]),
//      i++;
// }
// return (0);
// }