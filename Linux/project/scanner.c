#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

typedef struct
{
	const char *start;	 // ָ��ǰ����ɨ���Token����ʼ�ַ�
	const char *current; // �ʷ���������ǰ���ڴ����Token���ַ�,һ��ʼ������start��ʼ,ֱ������������Token,ָ���Token����һ���ַ�
	int line;			 // ��¼��ǰToken��������
} Scanner;

// ȫ�ֱ����ṹ�����
static Scanner scanner;
char message[50];

void initScanner(const char *source)
{
	// ��ʼ��ȫ�ֱ���Scanner
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}

// �����Ҹ�����ṩ�˺ܶ���õ��ĸ�������,����ʹ��
// �жϵ�ǰ�ַ��ǲ�����ĸ�����»���
static bool isAlpha(char c)
{
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}
// �жϵ�ǰ�ַ��ǲ�������
static bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}
// �ж�Scanner��ǰ���ڴ�����ַ��ǲ��ǿ��ַ�,�ж��ǲ��Ǵ�������
static bool isAtEnd()
{
	return *scanner.current == '\0';
}

// currָ��ǰ��һ���ַ�,������֮ǰcurrָ��ָ���Ԫ��
static char advance()
{
	return *scanner.current++;
}
// �鿴��ǰ���ڴ�����ַ���ʲô,curr����
static char peek()
{
	return *scanner.current;
}
// �����ǰ���ڴ�����ַ����ǿ��ַ�,�Ǿ�Ƴһ����һ���ַ���ʲô,curr����
static char peekNext()
{
	if (isAtEnd())
	{
		return '\0';
	}
	return *(scanner.current + 1);
}

// �жϵ�ǰ���ڴ�����ַ��ǲ��Ƿ���Ԥ��,�������currǰ��һλ
static bool match(char expected)
{
	if (isAtEnd())
	{
		return false; // ������ڴ�����ǿ��ַ�,�Ǿͷ���false
	}
	if (peek() != expected)
	{
		return false; // ���������Ԥ��,Ҳ����false
	}
	scanner.current++;
	return true; // ֻ�з���Ԥ�ڲŻ᷵��true ����curr��ǰ��һλ
}

// ���ݴ����TokenType���������췵��һ��Token
static Token makeToken(TokenType type)
{
	Token token;
	token.type = type;
	token.start = scanner.start;
	token.length = (int)(scanner.current - scanner.start); // ����Token�ַ����ĳ���
	token.line = scanner.line;
	return token;
}

// �������ܽ��������ʱ�����Ǵ���һ��ERROR Token. ���磺����@��$�ȷ���ʱ�������ַ������ַ�û�ж�Ӧ��������ʱ��
static Token errorToken(const char *message)
{
	Token token;
	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = (int)strlen(message);
	token.line = scanner.line;
	return token;
}

static void skipWhitespace()
{
	// �����հ��ַ�: ' ', '\r', '\t', '\n'��ע��
	// ע����'//'��ͷ, һֱ����β
	// ע�����scanner.line��
	bool is_annotation = false;
	while (1)
	{
		if (is_annotation)
		{
			if (peek() == '\n')
			{
				is_annotation = false;
				scanner.line++;
			}
			advance();
			continue;
		}
		// �ж��Ƿ���ע��
		if (peek() == '/')
		{
			if (peekNext() == '/')
			{
				is_annotation = true;
				continue;
			}
		}
		// �����հ��ַ�: ' ', '\r', '\t', '\n'��ע��
		char c = peek();
		if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
		{	
			if (c == '\n') {
				scanner.line++;
			}
			advance();
		}
		else
		{
			break;
		}
	}
	// ��ʾ: ����������Ҫ�����м�ĺܶ��ַ�,������Ҫ��ѭ��
}

// ���ڼ�鵱ǰɨ���Token�������ǲ���type ����Ǿͷ���type
static TokenType checkKeyword(int start, int length, const char *rest, TokenType type)
{
	/*
		start: ��������е���ʼ�ַ��±�
			����Ҫ���ؼ���break����ô��case b��ǰ���£���Ҫ����reak�����м��
			����start�͵���1��scanner.start[1]
		length: ��������еĳ��ȣ����������break�����Ǽ��ʣ���reak
			��Ҫ����4
		restָ�룬������ʣ�������ַ���������ֱ�Ӵ���һ������ֵ�ַ���������
			������break������"reak"�ͺ���
		type����Ҫ���Ĺؼ���Token�����ͣ�������break���Ǿʹ���Token_BREAK
	*/
	if (scanner.current - scanner.start == start + length &&
		/*
					int memcmp(const void *s1, const void *s2, size_t n);
					����Ĳ����ֱ��ǣ�

					s1��ָ���һ���ڴ������ָ�롣
					s2��ָ��ڶ����ڴ������ָ�롣
					n��Ҫ�Ƚϵ��ֽ�����
					memcmp ���������ֽڱȽ� s1 �� s2 ָ����ڴ�����ֱ���в���ȵ��ֽڻ�Ƚ��� n ���ֽ�Ϊֹ��
					��������ڴ�������ȫ��ͬ��
					�� memcmp ���� 0�������һ����ͬ���ֽ��� s1 �е�ֵС�� s2 �ж�Ӧ��ֵ�����ظ�����
					��֮������������
		*/
		memcmp(scanner.start + start, rest, length) == 0)
	{
		return type;
	}
	return TOKEN_IDENTIFIER;
}

static TokenType identifierType()
{
	// ȷ��identifier������Ҫ�����ַ�ʽ��
	// 1. �����еĹؼ��ַ����ϣ���У�Ȼ����ȷ��
	// Key-Value ����"�ؼ���-TokenType" ������ �����ڶ����ڴ�ռ����Ч�ʲ�����һ����ʽ��
	// 2. �����еĹؼ��ַ���Trie��(�ֵ������)�У�Ȼ����ȷ��
	// Trie���ķ�ʽ�����ǿռ��ϻ���ʱ���϶����ڹ�ϣ��ķ�ʽ
	// ��switch...switch...if��Ϲ����߼��ϵ�trie��
	char first = scanner.start[0]; // ��Token�ĵ�һ���ַ�
	switch (first)
	{
	case 'b':
		return checkKeyword(1, 4, "reak", TOKEN_BREAK); // break
	case 'c':
		switch (scanner.start[1])
		{
		case 'a':
			return checkKeyword(2, 2, "se", TOKEN_CASE); // "case"
		case 'h':
			return checkKeyword(2, 2, "ar", TOKEN_CHAR); // "char"
		case 'o':
			switch (scanner.start[3])
			{
			case 't':
				return checkKeyword(4, 4, "inue", TOKEN_CONTINUE); // "continue"
			case 's':
				return checkKeyword(4, 1, "t", TOKEN_CONST); // "continue"
			}
		}
	case 'd':
		switch (scanner.start[1])
		{
		case 'o':
			if (scanner.start[2] == 'u')
			{
				return checkKeyword(3, 3, "ble", TOKEN_DOUBLE); // "double"
			}
			if (!isAlpha(scanner.start[2]))
			{
				return checkKeyword(1, 1, "o", TOKEN_DO); // "do"
			}
		case 'e':
			return checkKeyword(2, 5, "fault", TOKEN_DEFAULT); // "default"
		}
	case 'e':
		switch (scanner.start[1])
		{
		case 'l':
			return checkKeyword(2, 2, "se", TOKEN_ELSE); // "else"
		case 'n':
			return checkKeyword(2, 2, "um", TOKEN_ENUM); // "enum"
		}
	case 'f':
		switch (scanner.start[1])
		{
		case 'o':
			return checkKeyword(2, 1, "r", TOKEN_FOR); // "for"
		case 'l':
			return checkKeyword(2, 3, "oat", TOKEN_FLOAT); // "float"
		}
	case 'g':
		return checkKeyword(1, 3, "oto", TOKEN_GOTO); // "goto"
	case 'i':
		switch (scanner.start[1])
		{
		case 'f':
			return checkKeyword(1, 1, "f", TOKEN_IF); // "if"
		case 'n':
			return checkKeyword(2, 1, "t", TOKEN_INT); // "int"
		}
	case 'l':
		return checkKeyword(1, 3, "ong", TOKEN_LONG); // "long"
	case 'r':
		return checkKeyword(1, 5, "eturn", TOKEN_RETURN); // "return"
	case 's':
		switch (scanner.start[1])
		{
		case 'h':
			return checkKeyword(2, 3, "ort", TOKEN_SHORT); // "short"
		case 'i':
			if (scanner.start[2] == 'z')
			{
				return checkKeyword(3, 3, "eof", TOKEN_SIZEOF); // "sizeof"
			}
			if (scanner.start[2] == 'g')
			{
				return checkKeyword(3, 3, "ned", TOKEN_SIGNED); // "signed"
			}
		case 't':
			return checkKeyword(2, 4, "ruct", TOKEN_STRUCT); // "struct"
		case 'w':
			return checkKeyword(2, 4, "itch", TOKEN_SWITCH); // "switch"
		}
	case 't':
		return checkKeyword(1, 6, "ypedef", TOKEN_TYPEDEF); // "typedef"
	case 'u':
		switch (scanner.start[1])
		{
		case 'n':
			if (scanner.start[2] == 'i')
			{
				return checkKeyword(3, 3, "ion", TOKEN_UNION); // "union"
			}
			else if (scanner.start[2] == 's')
			{
				return checkKeyword(3, 5, "igned", TOKEN_UNSIGNED); // "unsigned"
			}
			break;
		}
	case 'v':
		return checkKeyword(1, 3, "oid", TOKEN_VOID); // "void"
	case 'w':
		return checkKeyword(1, 4, "hile", TOKEN_WHILE); // "while"
	}
	// û�н�switchһ���Ǳ�ʶ��
	return TOKEN_IDENTIFIER;
}

// ��ǰToken�Ŀ�ͷ���»��߻���ĸ�ж����ǲ��Ǳ�ʶ��Token
static Token identifier()
{
	// �ж�currָ�뵱ǰ���ڴ�����ַ��ǲ��� ��ĸ �»��� ����
	while (isAlpha(peek()) || isDigit(peek()))
	{
		advance(); // ����ǰ������һ���ַ� ֱ��������һ���ַ�������ĸ �»��� �Լ����� ����Token
	}
	// ��whileѭ������ʱ��currָ��ָ����Ǹ�Token�ַ�������һ���ַ�
	// �����������˼��: ֻҪ������ĸ���»��߿�ͷ��Token���Ǿͽ����ʶ��ģʽ
	// Ȼ��һֱ�ҵ���Token��ĩβ
	// ���������е����ﻹ��ȷ��Token�Ǳ�ʶ�����ǹؼ���, ��Ϊ��������break, var, goto, max_val...
	// ����ִ��identifierType()��������������ȷ��Token���͵�
	return makeToken(identifierType());
}

static Token number()
{
	// ����������ǽ�NUMBER�Ĺ���������:
	// 1. NUMBER���԰������ֺ����һ��'.'��
	// 2. '.'��ǰ��Ҫ������
	// 3. '.'�ź���ҲҪ������
	// ��Щ���ǺϷ���NUMBER: 123, 3.14
	// ��Щ���ǲ��Ϸ���NUMBER: 123., .14(��Ȼ��C�����кϷ�)
	// ��ʾ: ���������Ҫ���ϵ������м�����ְ���С����,����Ҳ��Ҫѭ��
	bool is_has_dot = false;
	while (isDigit(peek()) || peek() == '.')
	{
		if (is_has_dot && peek() == '.')
		{
			return makeToken(TOKEN_ERROR);
		}
		if (peek() == '.')
		{
			is_has_dot = true;
			if (!isDigit(peekNext()))
			{
				return makeToken(TOKEN_ERROR);
			}
		}
		advance();
	}
	return makeToken(TOKEN_NUMBER);
}

static Token string()
{
	// �ַ�����"��ͷ����"��β�����Ҳ��ܿ���
	// Ϊ�˼򻯹�����,�����ַ���
	// �����һ���ַ�����ĩβҲ����˫���ţ�ȫ������(curr���Լ�¼���ȣ����õ���)
	advance();
	while (peek() != '\0' && peek() != '"')
	{	
		if (peek() == '\n') {
			return makeToken(TOKEN_ERROR);
		}
		advance();
	}
	if (peek() == '\0') {
		return makeToken(TOKEN_EOF);
	}
	return makeToken(TOKEN_STRING);
}

static Token character()
{
	// �ַ�'��ͷ����'��β�����Ҳ��ܿ���
	// �����һ���ַ�����ĩβҲ���ǵ����ţ�ȫ������(curr���Լ�¼���ȣ����õ���)
	// ��������������˵һģһ����Ҳ�Ǽ���һ��
	advance();
	while (peek() != '\0' || peek() != '\'')
	{
		advance();
	}
	return makeToken(TOKEN_CHARACTER);
}

// �����޷�ʶ����ַ�
static Token errorTokenWithChar(char character)
{
	// char *message = (char *)malloc(sizeof(char) * 50);
	// ���޷�ʶ����ַ���ʲô���
	sprintf(message, "Unexpected character: %c", character);
	return errorToken(message);
}

// Scanner�����߼�,���ڷ���һ�������õ�Token
Token scanToken()
{
	// ����ǰ�ÿհ��ַ���ע��
	skipWhitespace();
	// ��¼��һ��Token����ʼλ��
	scanner.start = scanner.current;

	// ����Ѿ���������� ֱ�ӷ���TOKEN_EOF
	if (isAtEnd())
	{
		return makeToken(TOKEN_EOF);
	}

	// currָ������ָ��Token�ĵڶ����ַ�,������ַ�c��Ȼ�ǵ�һ���ַ���ֵ
	char c = advance();

	// ���Token�ĵ�һ���ַ�����ĸ���»��߾ͽ����ʶ���Ĵ���ģʽ
	if (isAlpha(c))
	{
		return identifier();
	}
	// ���Token�ĵ�һ���ַ�������,�Ǿͽ������ֵĴ���ģʽ
	if (isDigit(c))
	{
		return number();
	}
	// ���Token�ĵ�һ���ַ��Ȳ�������Ҳ������ĸ���»���,��ô��switch������
	switch (c)
	{
		// ��һ����: �����ַ�Token
	case '(':
		return makeToken(TOKEN_LEFT_PAREN);
	case ')':
		return makeToken(TOKEN_RIGHT_PAREN);
		// ...TODO
	case '[':
		return makeToken(TOKEN_LEFT_BRACKET); // �������� '['
	case ']':
		return makeToken(TOKEN_RIGHT_BRACKET); // �������� ']'
	case '{':
		return makeToken(TOKEN_LEFT_BRACE); // ������� '{'
	case '}':
		return makeToken(TOKEN_RIGHT_BRACE); // �Ҵ����� '}'
	case ',':
		return makeToken(TOKEN_COMMA); // ���� ','
	case '.':
		return makeToken(TOKEN_DOT); // �� '.'
	case ';':
		return makeToken(TOKEN_SEMICOLON); // �ֺ� ';'
	case '~':
		return makeToken(TOKEN_TILDE); // ���˺� '~'

		// �ɵ���˫�ַ���Token�������΢����һ��,������
		// ���Token�ĵ�һ���ַ���+��
	case '+':
		// ���Token�ĵڶ����ַ�Ҳ��+,�Ǿ�����++˫�ַ�Token����
		if (match('+'))
		{
			return makeToken(TOKEN_PLUS_PLUS);
		}
		else if (match('='))
		{
			return makeToken(TOKEN_PLUS_EQUAL);
		}
		else
		{
			return makeToken(TOKEN_PLUS);
		}
		// ...TODO
		// ��һ����-
	case '-':
		// ���Token�ĵڶ����ַ�Ҳ��+,�Ǿ�����++˫�ַ�Token����
		if (match('-'))
		{
			return makeToken(TOKEN_MINUS_MINUS);
		}
		else if (match('='))
		{
			return makeToken(TOKEN_MINUS_EQUAL);
		}
		else if (match('>'))
		{
			return makeToken(TOKEN_MINUS_GREATER);
		}
		else
		{
			return makeToken(TOKEN_MINUS);
		}
	case '*':
		if (match('='))
		{
			return makeToken(TOKEN_STAR_EQUAL);
		}
		return makeToken(TOKEN_STAR);
	case '/':
		if (match('='))
		{
			return makeToken(TOKEN_SLASH_EQUAL);
		}
		return makeToken(TOKEN_SLASH);
	case '%':
		if (match('='))
		{
			return makeToken(TOKEN_PERCENT_EQUAL);
		}
		return makeToken(TOKEN_PERCENT);
	case '&':
		if (match('='))
		{
			return makeToken(TOKEN_AMPER_EQUAL);
		}
		else if (match('&'))
		{
			return makeToken(TOKEN_AMPER_AMPER);
		}
		return makeToken(TOKEN_AMPER);
	case '|':
		if (match('='))
		{
			return makeToken(TOKEN_PIPE_EQUAL);
		}
		else if (match('|'))
		{
			return makeToken(TOKEN_PIPE_PIPE);
		}
		return makeToken(TOKEN_PIPE);
	case '^':
		if (match('='))
		{
			return makeToken(TOKEN_HAT_EQUAL);
		}
		return makeToken(TOKEN_HAT);
	case '=':
		if (match('='))
		{
			return makeToken(TOKEN_EQUAL_EQUAL);
		}
		return makeToken(TOKEN_EQUAL);
	case '!':
		if (match('='))
		{
			return makeToken(TOKEN_BANG_EQUAL);
		}
		return makeToken(TOKEN_BANG);
	case '<':
		if (match('='))
		{
			return makeToken(TOKEN_LESS_EQUAL);
		}
		else if (match('<'))
		{
			return makeToken(TOKEN_LESS_LESS);
		}
		return makeToken(TOKEN_LESS);
	case '>':
		if (match('='))
		{
			return makeToken(TOKEN_GREATER_EQUAL);
		}
		else if (match('>'))
		{
			return makeToken(TOKEN_GREATER_GREATER);
		}
		return makeToken(TOKEN_GREATER);

	case '"':
		return string(); // ���Token�ĵ�һ���ַ���˫����,�Ǿͽ������ַ���Token����
	case '\'':
		return character(); // ���Token�ĵ�һ���ַ��ǵ�����,�Ǿͽ������ַ�Token����
	}
	// �����������û�д���ɹ�,��û�����ɺ��ʵ�Token,˵�����ַ��޷�ʶ��
	return errorTokenWithChar(c);
}
