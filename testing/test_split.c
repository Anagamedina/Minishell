/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:04:14 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/25 22:58:08 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by daruuu on 1/14/25.
//
# include "testing.h"

/**
 * @see count_words
 */
void	test_count_words(void)
{
	struct s_test_int	t_matrix_cases[] =
			{
					{"echo '$'USER' '", 4},
					{"echo '$' USER ' '", 4},
					{"echo '$HOME' 'hi'", 3},
			};

	int		i = 0;
	int 	result;
	char	message[256];
	int		len = sizeof(t_matrix_cases) / sizeof(t_matrix_cases[0]);

	while (i < len)
	{
		result = count_words_split(t_matrix_cases[i].input);

		snprintf(message, sizeof(message), "Failed on case %d: input='%s'", i + 1, t_matrix_cases[i].input);
		TEST_ASSERT_EQUAL_INT(t_matrix_cases[i].expected, result);
		i ++;
	}
}

/**
 * @see find_matching_quote
 */
/*void	test_find_matching_quote(void)
{
	struct s_test_int	t_matrix_cases[] =
			{
					{"echo '$'USER' '", 5},
					{"echo  '$' USER ' '", 6},
					{"echo $HOME 'hi'", 11},
					{"echo $HOME hi", -1},
			};

	int		i = 0;
	int 	result;
	char	message[256];
	int		len = sizeof(t_matrix_cases) / sizeof(t_matrix_cases[0]);

	while (i < len)
	{
		result = find_matching_quote(t_matrix_cases[i].input, 0, S_QUOTE);

		snprintf(message, sizeof(message), "Failed on case %d: input='%s'", i + 1, t_matrix_cases[i].input);
		TEST_ASSERT_EQUAL_INT(t_matrix_cases[i].expected, result);
		i ++;
	}
}*/