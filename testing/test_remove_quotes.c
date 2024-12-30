//
// Created by daruuu on 12/29/24.
//

# include "testing.h"

/**
 * @brief Prueba remove_quotes_str.
 * @example remove_quotes_str("'  \$hello world'", S_QUOTE) => "  \$hello world"
 * @see remove_quotes_str
 */

void	test_01_remove_quotes_literals(void)
{
	struct s_test_str	t_literal_test_cases[] =
			{
					{"'$hei .!$%&/()=?a'", "$hei .!$%&/()=?a"}, // Cadena con caracteres comunes
					{"'|@#~{[]}\\_ abcd  0'", "|@#~{[]}\\_ abcd  0"},     // Combinación con caracteres especiales y alfanuméricos
					{"'Hello World!'", "Hello World!"},         // Frase sencilla con signos de exclamación
					{"'$1 + $2 = $3'", "$1 + $2 = $3"},         // Cadena con variables representadas como literales
					{"'[ASCII] #42'", "[ASCII] #42"},           // Caracteres de control con numeración
					{"'\\n\\t\\r literal'", "\\n\\t\\r literal"}, // Secuencias de escape tratadas como literales
					{"'A~B^C_D*E&F'", "A~B^C_D*E&F"},           // Uso de varios caracteres de la tabla ASCII
					{"'?$<>|:\"/'", "?$<>|:\"/"},                 // Caracteres de comparación y especiales
					{"'`echo test(`)'", "`echo test(`)"},           // Uso de backticks como literales
					{"'\\\"Quoted\\\"'", "\\\"Quoted\\\""}      // Cadena con comillas escapadas
			};

	int		i = 0;
	int		len_edge_cases = sizeof(t_literal_test_cases) / sizeof(t_literal_test_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// function on test
		result = remove_quotes_str(t_literal_test_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_literal_test_cases[i].input, t_literal_test_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_literal_test_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_02_remove_quotes_general(void)
{
// Casos para cadenas literales generales
	struct s_test_str	t_literal_general_cases[] = {
	{"'~/,.;[]{}+_)(*&^%$#@!~.'", "~/,.;[]{}+_)(*&^%$#@!~."},
//	{"'$hei !·a'", "$hei !·a"},
	{"'$hei !_$%&/()=?a'", "$hei !_$%&/()=?a"},
	{"'|@#~{[]}\\abcd'", "|@#~{[]}\\abcd"}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_literal_general_cases) / sizeof(t_literal_general_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_literal_general_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_literal_general_cases[i].input, t_literal_general_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_literal_general_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_03_remove_quotes_backslash(void)
{
// Casos para comillas escapadas
	struct s_test_str	t_escaped_quote_cases[] = {
			{"'\\$USER quote'", "\\$USER quote"},
			{"'  \\$USER quote  '", "  \\$USER quote  "},
			{"'\\$USER quote\\'", "\\$USER quote\\"},
			{"' \\/ \\$USER quote\\'", " \\/ \\$USER quote\\"},
			{"' \\\\$USER quote \\\\'", " \\\\$USER quote \\\\"},
			{"' \\_\\ \\$USER quote \\\\'", " \\_\\ \\$USER quote \\\\"}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_escaped_quote_cases) / sizeof(t_escaped_quote_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_escaped_quote_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_escaped_quote_cases[i].input, t_escaped_quote_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_escaped_quote_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_04_remove_quotes_spaces(void)
{
// Casos con espacios y comillas simples normales
	struct s_test_str	t_space_handling_cases[] = {
			{"'   hello world'", "   hello world"},
			{"' spaced string '", " spaced string "},
			{"'   multiple   spaces   '", "   multiple   spaces   "}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_space_handling_cases) / sizeof(t_space_handling_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_space_handling_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_space_handling_cases[i].input, t_space_handling_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_space_handling_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_05_remove_quotes_no_expand(void)
{
// Casos para variables sin expansión y escapes
	struct s_test_str	t_variable_and_escape_cases[] = {
			{"'$HOME'", "$HOME"},
			{"'$USER'", "$USER"},
			{"'$PATH'", "$PATH"},
			{"'$HOME case'", "$HOME case"},
			{"'   $HOME case '", "   $HOME case "},
			{"'   \\$HOME case '", "   \\$HOME case "}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_variable_and_escape_cases) / sizeof(t_variable_and_escape_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_variable_and_escape_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_variable_and_escape_cases[i].input, t_variable_and_escape_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_variable_and_escape_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_06_remove_quotes_empty_cases(void)
{
//	Casos extremos o vacíos
	struct s_test_str	t_edge_cases[] = {
			{"''", ""},
			{"' '", " "},
			{"'\\'", "\\"}
	};

	int		i = 0;
	int		len = sizeof(t_edge_cases) / sizeof(t_edge_cases[0]);
	char	*result;
	char	message[256];

	while (i < len)
	{
		// original function on test
		result = remove_quotes_str(t_edge_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_edge_cases[i].input, t_edge_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_edge_cases[i].expected, result, message);
		free(result);
		i++;
	}
}
