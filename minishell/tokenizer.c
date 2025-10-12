#include "minishell_types.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

// Should heredoc be handled in this part?
t_token	*tokenize(const char *input)
{
	t_token *head = NULL, *tail = NULL;
	size_t i = 0, len = strlen(input);

	while (i < len)
	{
		// Skip whitespace
		while (i < len && isspace(input[i]))
			i++;
		if (i >= len)
			break ;

		// Parentheses
		if (input[i] == '(')
		{
			t_token *tok = new_token(TOKEN_LPAREN, strdup("("));
			if (!head)
				head = tok;
			else
				tail->next = tok;
			tail = tok;
			i++;
			continue ;
		}
		if (input[i] == ')')
		{
			t_token *tok = new_token(TOKEN_RPAREN, strdup(")"));
			if (!head)
				head = tok;
			else
				tail->next = tok;
			tail = tok;
			i++;
			continue ;
		}

		// Operators
		if (is_operator_char(input[i]))
		{
			t_token_type type;
			size_t op_len = 1;
			if (input[i] == '|' && input[i + 1] == '|')
			{
				type = TOKEN_OR;
				op_len = 2;
			}
			else if (input[i] == '&' && input[i + 1] == '&')
			{
				type = TOKEN_AND;
				op_len = 2;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				type = TOKEN_HEREDOC;
				op_len = 2;
			}
			else if (input[i] == '>' && input[i + 1] == '>')
			{
				type = TOKEN_APPEND;
				op_len = 2;
			}
			else if (input[i] == '|')
			{
				type = TOKEN_PIPE;
			}
			else if (input[i] == '<')
			{
				type = TOKEN_REDIR_IN;
			}
			else if (input[i] == '>')
			{
				type = TOKEN_REDIR_OUT;
			}
			else
			{
				break ;
			}
			char *val = strndup(input + i, op_len);
			t_token *tok = new_token(type, val);
			if (!head)
				head = tok;
			else
				tail->next = tok;
			tail = tok;
			i += op_len;
			continue ;
		}

		// Quoted strings
		if (input[i] == '\'' || input[i] == '"')
		{
			char quote = input[i++];
			size_t start = i;
			while (i < len && input[i] != quote)
				i++;
			char *val = strndup(input + start, i - start);
			t_token *tok = new_token(TOKEN_WORD, val);
			if (!head)
				head = tok;
			else
				tail->next = tok;
			tail = tok;
			if (i < len)
				i++; // skip closing quote
			continue ;
		}

		// Words (including wildcards)
		size_t start = i;
		while (i < len && !isspace(input[i]) && !is_operator_char(input[i])
			&& input[i] != '(' && input[i] != ')')
			i++;
		char *val = strndup(input + start, i - start);
		t_token *tok = new_token(TOKEN_WORD, val);
		if (!head)
			head = tok;
		else
			tail->next = tok;
		tail = tok;
	}
	return (head);
}