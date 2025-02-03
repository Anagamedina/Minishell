/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_double_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:41:22 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by daruuu on 12/30/24.
//
# include "testing.h"

/**
 * @brief Prueba la detección del patron: [" hello "abcd" "]
 *
 * @see has_even_double_quotes
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

		int result = has_even_double_quotes(token);

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

		int result = check_dquote_squote_dollar_case(token->str);

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


/**
 * @brief Test the detection of the pattern: [" hello '$USER' "]
 * @see handle_double_cases
 * In the first case we're testing the next function
 * @see replace_dollar_variable_skip_s_quote 
 */

/*
void	test_replace_dollar_variable_skip_s_quote_01(void)
{
	int			i;
	int			len;
	char		message[256];
	char		*result;

	struct s_test_str	test_cases[] =
	{
		{" \' $USER \' hei '2025' ", " ' dasalaza ' hei '2025' "}, 

		// Caso 1: Variable dentro de comillas simples
		{"   \'$USER\'  ", "   'dasalaza'  "}, 

		// Caso 2: Variable fuera de comillas simples
		{"   '$USER _ '  ", "   'dasalaza _ '  "},

		{"  \'  $USER  \'  ", "  \'  dasalaza  \'  "},

		// Caso 3: Combinación de texto, variable y comillas simples
		{"\'User: '$USER' is here\'", "\'User: 'dasalaza' is here\'"},

		{"  \'User: '$USER' is here  \'", "  \'User: 'dasalaza' is here  \'"},

		// Caso 4: Variable inexistente dentro de comillas simples
		{"\'$UNKNOWN\'", "\'\'"}, // Sin expansión por las comillas simples.

		// Caso 5: Variable inexistente fuera de comillas simples
		{"  \'$UNKNOWN\'  ", "  \'\'  "},

		{"  \'  $UNKNOWN  \'  ", "  \'    \'  "},

		// Caso 6: Variable parcialmente rodeada de comillas simples
		{"\'$USER and $HOME\'", "\'dasalaza and /home/dasalaza\'"}, // Solo $HOME se expande.

		// Caso 7: Texto mezclado con varias variables
		{"Path: '$PATH' and User: $USER", \
		"Path: '/home/dasalaza/bin:/home/dasalaza/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin' and User: dasalaza"},

		// Caso 8: Variable vacía fuera de comillas simples
		{"\'$EMPTY\'", "\'\'"}, // Variable definida pero vacía.

		{" $USER \'$HOME\':)  ", " dasalaza \'/home/dasalaza\':)  "},

	};

	i = 0;
	len = sizeof(test_cases) / sizeof(test_cases[0]);

	while (i < len)
	{
		result = replace_dollar_variable_skip_s_quote(test_cases[i].input, g_minishell->env);

		snprintf(message, sizeof(message),
				 "FAILED ON CASE (%d):" "                    INPUT=[%s] "
				 "EXPECTED=[%s]" " | "
				 "ACTUAL=[%s]",
				 i + 1,
				 test_cases[i].input,
				 test_cases[i].expected,
				 result);
		TEST_ASSERT_EQUAL_STRING_MESSAGE(test_cases[i].expected, result, message);
		i ++;
	}
}
*/


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

		int result = has_even_double_quotes(token);

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

/**
 * @brief Test the detection of the pattern: [" $ 'USER' "]
 * @see check_dquote_dollar_and_squotes
 */

void	test_check_dollar_with_space_in_s_quotes(void)
{
	int			i;
	int			len;
	t_tokens	*token;
	char 		*message[256];

	struct s_test_int	basic_cases[] = {

		// Caso 1: Patrón válido, comillas simples tras $ con espacios
		{"\"$ \'USER\'\"", 1},

		// Caso 2: Patrón válido, sin espacios entre $ y comillas simples
		{"\"$\'USER\'\"", 1},

		// Caso 3: Sin patrón, faltan comillas simples finales
		{"\"$ \'USER\"", 0},

		// Caso 4: Sin patrón, faltan comillas simples iniciales
		{"\"$ USER\'\"", 0},

		// Caso 5: Comillas simples vacías tras $
		{"\"$ \'\'\"", 1},

		// Caso 6: Patrón con múltiples espacios entre $ y comillas simples
		{"\"$     \'USER\'\"", 1},

		// Caso 7: Sin patrón, contenido sin comillas simples tras $
		{"\"$ USER\"", 0},

		// Caso 8: Patrón válido, comillas simples pero $ dentro de texto
		{"\"TEXT $ \'USER\'\"", 1},

		// Caso 9: Sin patrón, símbolo $ en texto pero no con comillas simples
		{"\"TEXT $ USER\"", 0},

		// Caso 10: Patrón válido, $ al inicio y seguido por comillas simples vacías
		{"\"$ \'\'\"", 1},

		// Caso 11: Sin patrón, comillas simples cerrando texto, pero sin $ válido
		{"\"USER \'\'\"", 0},

		// Caso 12: Patrón válido, $ con comillas simples cerradas en texto complejo
		{"\"$  \'VAR NAME\' and $ \'OTHER\'\"", 1},

		// Caso 13: Sin patrón, múltiples símbolos $ pero sin espacios y comillas simples
		{"\"$$$ USER\"", 0},

		// Caso 14: Patrón válido, $ con espacio pero seguido por comillas vacías
		{"\"$    \'\'\"", 1},

		// Caso 15: Sin patrón, $ en texto sin comillas simples ni espacio
		{"\"$USER and $PATH\"", 0},
	};
	i = 0;
	len = sizeof(basic_cases) / sizeof(basic_cases[0]);

	while (i < len)
	{
		token = init_token(basic_cases[i].input, set_token_type(basic_cases[i].input));

		int result = check_dquote_dollar_and_squotes(token->str);

		snprintf((char *) message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%d]" " | "
				 "ACTUAL=[%d]",
				 i,
				 basic_cases[i].input,
				 basic_cases[i].expected,
				 result);

		TEST_ASSERT_EQUAL_INT_MESSAGE(basic_cases[i].expected, result, message);
		token->str = NULL;
		i++;
	}
}

/**
 * @brief Test the detection of the pattern: ["$'USER' "]
 * @see check_d_quote_dollar_s_quote
 */

void	test_check_d_quote_dollar_s_quote(void)
{
	int			i;
	int			len;
	t_tokens	*token;
	char 		*message[256];

	struct s_test_int	basic_cases[] = {
		// Caso 1: Patrón válido con comillas simples
		{"\"$\'USER\'\"", 1},

		// Caso 2: Patrón válido con texto adicional
		{"\"Text \'$USER\' here\"", 1},

	};

	i = 0;
	len = sizeof(basic_cases) / sizeof(basic_cases[0]);

	while (i < len)
	{
		token = init_token(basic_cases[i].input, set_token_type(basic_cases[i].input));

		int result = check_dollar_and_next_token(&token->str, NULL);

		snprintf((char *) message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%d]" " | "
				 "ACTUAL=[%d]",
				 i,
				 basic_cases[i].input,
				 basic_cases[i].expected,
				 result);

		TEST_ASSERT_EQUAL_INT_MESSAGE(basic_cases[i].expected, result, message);
		token->str = NULL;
		i++;
	}
}

//	echo " ' $USER ' "
/*
	echo """""'hello $HOME '"""""
	'hello /home/dasalaza '
	dasalaza@cbr1s2:~/cursus_42/git_daruuu/minishell$ echo """"""'hello $HOME '""""""
hello $HOME 
dasalaza@cbr1s2:~/cursus_42/git_daruuu/minishell$ echo """""""' hello $HOME '"""""""
' hello /home/dasalaza '
dasalaza@cbr1s2:~/cursus_42/git_daruuu/minishell$ echo """ ' hello ' $HOME """
 ' hello ' /home/dasalaza 
dasalaza@cbr1s2:~/cursus_42/git_daruuu/minishell$ echo """ ' hello ' $HOME """ | cat -e
 ' hello ' /home/dasalaza $
*/
// TODO: terminar de implementar los casos del squote al final 
void	test_handle_special_quotes(void)
{
	int			i;
	int			len;
	t_tokens	*token;
	char 		message[256];

	struct s_test_int	odd_dquotes_cases[] = {
		{"\" \'hello \' \"", 1},                  // Incorrecto: falta """ al inicio
		{"\"\"\"\'hello\'\"\"\"", 1},              // Correcto: comienza y termina con """ y contiene una comilla simple
		{"\" \" \'hello\' \" \"", 0},                // Incorrecto: termina con "" en lugar de """
		{"\"\"\"\'hello\'\"\"\"", 1},              // Correcto: comienza y termina con """ y contiene una comilla simple
		{"\" \" \'hello\' \" \"", 0},              // Incorrecto: las comillas dobles son pares
		{"\"\"\'hello\'\"\"", 0},                  // Incorrecto: faltan """ al inicio y al final
		{"\"\"\"\'hello\'", 0},                    // Incorrecto: falta """ al final
		{"\'hello\'\"\"\"", 0},                    // Incorrecto: falta """ al inicio
		{"\"\"\" \'hello\' \"\"\"", 1},            // Correcto: sigue el patrón """ ' ' """
		{"\"\"\" \'hello there\' \"\"\"", 1},      // Correcto: sigue el patrón con texto adicional dentro
		{"\"\"\"\'hello\' $USER\"\"\"", 1},        // Incorrecto: contiene un `$`
		{"\"\"\" \'hello\' world \"\"\"", 0},      // Incorrecto: contiene texto fuera del patrón permitido
		{"\"\"\"\'\'\"\"\"", 1},                   // Correcto: sigue el patrón con comillas simples vacías

	};

	i = 0;
	len = sizeof(odd_dquotes_cases) / sizeof(odd_dquotes_cases[0]);

	while (i < len)
	{
		token = init_token(odd_dquotes_cases[i].input, set_token_type(odd_dquotes_cases[i].input));

		int result = handle_special_quotes(token);

		snprintf((char *) message, sizeof(message),
				 "FAILED ON CASE (%d):" " INPUT=[%s] "
				 "EXPECTED=[%d]" " | "
				 "ACTUAL=[%d]",
				 i,
				 odd_dquotes_cases[i].input,
				 odd_dquotes_cases[i].expected,
				 result);

		TEST_ASSERT_EQUAL_INT_MESSAGE(odd_dquotes_cases[i].expected, result, message);
		i++;
	}
}

/*
void	test_d_quotes_quantity_of_d_quotes(void)
{
}
*/
