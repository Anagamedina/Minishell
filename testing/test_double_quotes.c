//
// Created by daruuu on 12/30/24.
//
# include "testing.h"

/**
 * @brief Prueba la detección del patron: [" hello "abcd" "]
 *
 * @see check_double_quotes
 * @return TRUE or FALSE
 */

void	test01_double_quotes_keyboard_basic(void)
{
	int		i;
	int		len;
	t_tokens	*token;
	char 	message[256];

	struct s_test_int	keyboard_basic[] = {
			{"\"\"", 1},
			{"\"     \"", 1},

			{"\"1234567890\"", 1},
			{"\"qwert  ypoiu \"", 1},
			{"\"asdfghjkl\"", 1},
			{"\"zxcvbnm\"", 1},
			{"\"1234abcd5678\"", 1},

			{"\"@#$%^&*()\"", 1},
			{"\"{}[]|\\:;'\"", 1},
			{"\"escaped\\\"quote\"", 1},

			{"\"line\nbreak\"", 1},
			{"\"tab\tcharacter\"", 1},

			{"\"missing-end-quote", 0},
			{"missing-start-quote\"", 0},
			{"\"nested \"quote\" inside\"", 1},
			{" before \"inside\" after ", 0},
	};


	i = 0;
	len = sizeof(keyboard_basic) / sizeof(keyboard_basic[0]);

	while (i < len)
	{
		token = init_token(keyboard_basic[i].input, set_token_type(keyboard_basic[i].input));

		int result = handle_double_quotes(token);

		snprintf((char *) message, sizeof(message),
		"FAILED ON CASE (%d):" " INPUT=[%s] "
		"EXPECTED=[%d]" " | "
		"ACTUAL=[%d]",
		i + 1,
		keyboard_basic[i].input,
		keyboard_basic[i].expected,
		result);

		TEST_ASSERT_EQUAL_MESSAGE(keyboard_basic[i].expected, result, message);
		token->str = NULL;
		i++;
	}
}

void	test01_check_double_simple_dollar_case_int(void)
{
	int		i;
	int		len;
	t_tokens	*token;
	char 	message[256];

	struct s_test_int	keyboard_basic[] = {
			{"\"\'$HOME\'\"", 1},                          // Caso 1: vacío
			{"\" \'$HOME\'\"", 1},                          // Caso 1: vacío
			{"\" \' $HOME\'\"", 1},                // Caso 2: espacios
			{"\" \' $HOME \'\"", 1},                // Caso 2: espacios
			{"\" \' $HOME \' \"", 1},                // Caso 2: espacios
	};

	i = 0;
	len = sizeof(keyboard_basic) / sizeof(keyboard_basic[0]);

	while (i < len)
	{
		token = init_token(keyboard_basic[i].input, set_token_type(keyboard_basic[i].input));

		int result = check_double_simple_dollar_case(token->str);

		snprintf((char *) message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%d]" " | "
				 "ACTUAL=[%d]",
				 i,
				 keyboard_basic[i].input,
				 keyboard_basic[i].expected,
				 result);

		TEST_ASSERT_EQUAL_MESSAGE(keyboard_basic[i].expected, result, message);
		token->str = NULL;
		i++;
	}
}

/**
 * @brief Test cases for handling double quotes in the minishell project.
 *
 * This file contains various test cases to ensure that the minishell
 * correctly handles inputs with double quotes. The tests cover different
 * scenarios such as nested quotes, escaped quotes, and quotes within
 * commands.
 *
 * @author dasalaza
 * @date 2023-10-05
 */

void	test02_remove_quotes_str_valid_basic(void)
{
	int			i;
	int			len;
	char		message[256];
	char		*result;
	t_tokens	*curr_token;

	struct s_test_str valid_input[] = {
		{"\"\'abc hello\'\"", "'abc hello'"},
		{"\"\'1234567890\'\"", "'1234567890'"},
		{"\"qwert  ypoiu \"", "qwert  ypoiu "},
		{"\"asdfghjkl\"", "asdfghjkl"},
		{"\"zxcvbnm\"", "zxcvbnm"},
		{"\"1234abcd5678\"", "1234abcd5678"},
	};

	i = 0;
	len = sizeof(valid_input) / sizeof(valid_input[0]);

	while (i < len)
	{
		curr_token = init_token(valid_input[i].input, set_token_type(valid_input[i].input));

		// call to test function
		result = remove_quotes_str(curr_token->str, D_QUOTE);

		TEST_ASSERT_EQUAL_STRING(valid_input[i].expected, result);
		i ++;
	}
}

void	test02_remove_quotes_str_valid_special_chars(void)
{
	int			i;
	int			len;
	char		message[256];
	char		*result;
	t_tokens	*curr_token;

	struct s_test_str valid_special_chars[] = {
		{"\"\'@#$%^&*()\'\"", "\'@#$%^&*()\'"},
		{"\"\''{}[]|\\:';\'\"", "\''{}[]|\\:';\'"},
		{"\"  \'  escaped_quote\'\"", "  \'  escaped_quote\'"},
	};

	i = 0;
	len = sizeof(valid_special_chars) / sizeof(valid_special_chars[0]);

	while (i < len)
	{
		curr_token = init_token(valid_special_chars[i].input, set_token_type(valid_special_chars[i].input));

		result = remove_quotes_str(curr_token->str, D_QUOTE);

		TEST_ASSERT_EQUAL_STRING(valid_special_chars[i].expected, result);
		i ++;
	}
}

//posible caso de error: echo "'line\nbreak'"
void	test02_remove_quotes_str_valid_format(void)
{
	int			i;
	int			len;
	char		message[256];
	char		*result;
	t_tokens	*curr_token;

	struct s_test_str valid_format[] = {
		{"\"  \'line_%_break  \'  \"", "  \'line_%_break  \'  "},
		{"\"\'tab\\tcharacter\'\"", "\'tab\\tcharacter\'"},
	};

	i = 0;
	len = sizeof(valid_format) / sizeof(valid_format[0]);

	while (i < len)
	{
		curr_token = init_token(valid_format[i].input, set_token_type(valid_format[i].input));

		result = remove_quotes_str(curr_token->str, D_QUOTE);

		snprintf(message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%s]" " | "
				 "ACTUAL=[%s]",
				 i + 1,
				 valid_format[i].input,
				 valid_format[i].expected,
				 result);
		TEST_ASSERT_EQUAL_STRING_MESSAGE(valid_format[i].expected, result, message);
		curr_token->str = NULL;
		i ++;
	}
}

void	test02_remove_quotes_str_invalid_quotes(void)
{
	int			i;
	int			len;
	char		message[256];
	char		*result;
	t_tokens	*curr_token;

	struct s_test_str invalid_quotes[] = {
    {"\"\'missing-end-quote\"\'", 0},
    {"missing-start-quote\"", 0},                
    {"\"nested \"quote\" inside\"", 0},          
    {" before \"inside\" after ", 0},           
	};

	i = 0;
	len = sizeof(invalid_quotes) / sizeof(invalid_quotes[0]);

	while (i < len)
	{
		curr_token = init_token(invalid_quotes[i].input, set_token_type(invalid_quotes[i].input));

		result = remove_quotes_str(curr_token->str, D_QUOTE);

		snprintf(message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%s]" " | "
				 "ACTUAL=[%s]",
				 i + 1,
				 invalid_quotes[i].input,
				 invalid_quotes[i].expected,
				 result);
		TEST_ASSERT_EQUAL_STRING_MESSAGE(invalid_quotes[i].expected, result, message);
		curr_token->str = NULL;
		i ++;
	}
}




















/*
void	test01_handle_dollar_case_with_double_quotes(void)
{
	int		i;
	int		len;
	t_tokens	*token;
	char 	*message[256];

	struct s_test_char keyboard_basic[] = {
			{"\"\"", ""},                          // Caso 1: vacío
			{"\"     \"", "     "},                // Caso 2: espacios

			{"\"1234567890\"", "1234567890"},      // Números
			{"\"qwert  ypoiu \"", "qwert  ypoiu "}, // Texto con espacios
			{"\"asdfghjkl\"", "asdfghjkl"},        // Letras
			{"\"zxcvbnm\"", "zxcvbnm"},            // Letras
			{"\"1234abcd5678\"", "1234abcd5678"},  // Mixto

			{"\"@#$%^&*()\"", "@#$%^&*()"},        // Caracteres especiales
			{"\"{}[]|\\:;'\"", "{}[]|\\:;'"},
			{"\"escaped\\\"quote\"", "escaped\\\"quote"},

			{"\"line\nbreak\"", "line\nbreak"},    // Salto de línea
			{"\"tab\tcharacter\"", "tab\tcharacter"}, // Tabulaciones

			{"\"missing-end-quote", 0},            // Error: faltan comillas finales
			{"missing-start-quote\"", 0},          // Error: faltan comillas iniciales
			{"\"nested \"quote\" inside\"", 0},    // Error: comillas internas
			{" before \"inside\" after ", 0},      // Error: contenido externo
	};

	i = 0;
	len = sizeof(keyboard_basic) / sizeof(keyboard_basic[0]);

	while (i < len)
	{
		token = init_token(keyboard_basic[i].input, set_token_type(keyboard_basic[i].input));

		int result = handle_double_quotes(token);

		snprintf((char *) message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%d]" " | "
				 "ACTUAL=[%d]",
				 i + 1,
				 keyboard_basic[i].input,
				 keyboard_basic[i].expected,
				 result);

		TEST_ASSERT_EQUAL_MESSAGE(keyboard_basic[i].expected, result, message);
		token->str = NULL;
		i++;
	}
}
*/

void	test_check_dollar_with_space_in_s_quotes(void)
{
	int			i;
	int			len;
	t_tokens	*token;
	char 		*message[256];

	struct s_test_int	basic_cases[] = {
	{"\"$\'USER\'\"", 1},		// Caso 1: vacío
	};

	i = 0;
	len = sizeof(basic_cases) / sizeof(basic_cases[0]);

	while (i < len)
	{
		token = init_token(basic_cases[i].input, set_token_type(basic_cases[i].input));

		int result = check_dollar_with_space_single(token->str);

		snprintf((char *) message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%d]" " | "
				 "ACTUAL=[%d]",
				 i,
				 basic_cases[i].input,
				 basic_cases[i].expected,
				 result);

		TEST_ASSERT_EQUAL_MESSAGE(basic_cases[i].expected, result, message);
		token->str = NULL;
		i++;
	}

}

/*
void	test_d_quotes_quantity_of_d_quotes(void)
{
}
*/
