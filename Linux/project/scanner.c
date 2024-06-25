#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

typedef struct
{
	const char *start;	 // 指向当前正在扫描的Token的起始字符
	const char *current; // 词法分析器当前正在处理的Token的字符,一开始它就是start开始,直到遍历完整个Token,指向该Token的下一个字符
	int line;			 // 记录当前Token所处的行
} Scanner;

// 全局变量结构体对象
static Scanner scanner;
char message[50];

void initScanner(const char *source)
{
	// 初始化全局变量Scanner
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}

// 下面我给大家提供了很多会用到的辅助函数,建议使用
// 判断当前字符是不是字母或者下划线
static bool isAlpha(char c)
{
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}
// 判断当前字符是不是数字
static bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}
// 判断Scanner当前正在处理的字符是不是空字符,判断是不是处理完了
static bool isAtEnd()
{
	return *scanner.current == '\0';
}

// curr指针前进一个字符,并返回之前curr指针指向的元素
static char advance()
{
	return *scanner.current++;
}
// 查看当前正在处理的字符是什么,curr不动
static char peek()
{
	return *scanner.current;
}
// 如果当前正在处理的字符不是空字符,那就瞥一眼下一个字符是什么,curr不动
static char peekNext()
{
	if (isAtEnd())
	{
		return '\0';
	}
	return *(scanner.current + 1);
}

// 判断当前正在处理的字符是不是符合预期,如果符合curr前进一位
static bool match(char expected)
{
	if (isAtEnd())
	{
		return false; // 如果正在处理的是空字符,那就返回false
	}
	if (peek() != expected)
	{
		return false; // 如果不符合预期,也返回false
	}
	scanner.current++;
	return true; // 只有符合预期才会返回true 而且curr会前进一位
}

// 根据传入的TokenType类型来制造返回一个Token
static Token makeToken(TokenType type)
{
	Token token;
	token.type = type;
	token.start = scanner.start;
	token.length = (int)(scanner.current - scanner.start); // 计算Token字符串的长度
	token.line = scanner.line;
	return token;
}

// 遇到不能解析的情况时，我们创建一个ERROR Token. 比如：遇到@，$等符号时，比如字符串，字符没有对应的右引号时。
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
	// 跳过空白字符: ' ', '\r', '\t', '\n'和注释
	// 注释以'//'开头, 一直到行尾
	// 注意更新scanner.line！
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
		// 判断是否是注释
		if (peek() == '/')
		{
			if (peekNext() == '/')
			{
				is_annotation = true;
				continue;
			}
		}
		// 跳过空白字符: ' ', '\r', '\t', '\n'和注释
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
	// 提示: 整个过程需要跳过中间的很多字符,所以需要死循环
}

// 用于检查当前扫描的Token的类型是不是type 如果是就返回type
static TokenType checkKeyword(int start, int length, const char *rest, TokenType type)
{
	/*
		start: 待检查序列的起始字符下标
			比如要检查关键字break，那么在case b的前提下，需要传入reak来进行检查
			这里start就等于1，scanner.start[1]
		length: 待检查序列的长度，如果检查的是break，就是检查剩余的reak
			需要传入4
		rest指针，待检查的剩余序列字符串，这里直接传入一个字面值字符串就行了
			比如检查break，传入"reak"就好了
		type：你要检查的关键字Token的类型，比如检查break，那就传入Token_BREAK
	*/
	if (scanner.current - scanner.start == start + length &&
		/*
					int memcmp(const void *s1, const void *s2, size_t n);
					这里的参数分别是：

					s1：指向第一块内存区域的指针。
					s2：指向第二块内存区域的指针。
					n：要比较的字节数。
					memcmp 函数会逐字节比较 s1 和 s2 指向的内存区域，直到有不相等的字节或比较了 n 个字节为止。
					如果两个内存区域完全相同，
					则 memcmp 返回 0；如果第一个不同的字节在 s1 中的值小于 s2 中对应的值，返回负数；
					反之，返回正数。
		*/
		memcmp(scanner.start + start, rest, length) == 0)
	{
		return type;
	}
	return TOKEN_IDENTIFIER;
}

static TokenType identifierType()
{
	// 确定identifier类型主要有两种方式：
	// 1. 将所有的关键字放入哈希表中，然后查表确认
	// Key-Value 就是"关键字-TokenType" 可以做 但存在额外内存占用且效率不如下一个方式好
	// 2. 将所有的关键字放入Trie树(字典查找树)中，然后查表确认
	// Trie树的方式不管是空间上还是时间上都优于哈希表的方式
	// 用switch...switch...if组合构建逻辑上的trie树
	char first = scanner.start[0]; // 该Token的第一个字符
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
	// 没有进switch一定是标识符
	return TOKEN_IDENTIFIER;
}

// 当前Token的开头是下划线或字母判断它是不是标识符Token
static Token identifier()
{
	// 判断curr指针当前正在处理的字符是不是 字母 下划线 数字
	while (isAlpha(peek()) || isDigit(peek()))
	{
		advance(); // 继续前进看下一个字符 直到碰到下一个字符不是字母 下划线 以及数字 结束Token
	}
	// 当while循环结束时，curr指针指向的是该Token字符串的下一个字符
	// 这个函数的意思是: 只要读到字母或下划线开头的Token我们就进入标识符模式
	// 然后一直找到此Token的末尾
	// 但代码运行到这里还不确定Token是标识符还是关键字, 因为它可能是break, var, goto, max_val...
	// 于是执行identifierType()函数，它是用来确定Token类型的
	return makeToken(identifierType());
}

static Token number()
{
	// 简单起见，我们将NUMBER的规则定义如下:
	// 1. NUMBER可以包含数字和最多一个'.'号
	// 2. '.'号前面要有数字
	// 3. '.'号后面也要有数字
	// 这些都是合法的NUMBER: 123, 3.14
	// 这些都是不合法的NUMBER: 123., .14(虽然在C语言中合法)
	// 提示: 这个过程需要不断的跳过中间的数字包括小数点,所以也需要循环
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
	// 字符串以"开头，以"结尾，而且不能跨行
	// 为了简化工作量,简化了字符串
	// 如果下一个字符不是末尾也不是双引号，全部跳过(curr可以记录长度，不用担心)
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
	// 字符'开头，以'结尾，而且不能跨行
	// 如果下一个字符不是末尾也不是单引号，全部跳过(curr可以记录长度，不用担心)
	// 这两个函数不能说一模一样，也是几乎一样
	advance();
	while (peek() != '\0' || peek() != '\'')
	{
		advance();
	}
	return makeToken(TOKEN_CHARACTER);
}

// 处理无法识别的字符
static Token errorTokenWithChar(char character)
{
	// char *message = (char *)malloc(sizeof(char) * 50);
	// 将无法识别的字符是什么输出
	sprintf(message, "Unexpected character: %c", character);
	return errorToken(message);
}

// Scanner核心逻辑,用于返回一个制作好的Token
Token scanToken()
{
	// 跳过前置空白字符和注释
	skipWhitespace();
	// 记录下一个Token的起始位置
	scanner.start = scanner.current;

	// 如果已经处理完毕了 直接返回TOKEN_EOF
	if (isAtEnd())
	{
		return makeToken(TOKEN_EOF);
	}

	// curr指针现在指向Token的第二个字符,但这个字符c仍然是第一个字符的值
	char c = advance();

	// 如果Token的第一个字符是字母和下划线就进入标识符的处理模式
	if (isAlpha(c))
	{
		return identifier();
	}
	// 如果Token的第一个字符是数字,那就进入数字的处理模式
	if (isDigit(c))
	{
		return number();
	}
	// 如果Token的第一个字符既不是数字也不是字母和下划线,那么就switch处理它
	switch (c)
	{
		// 第一部分: 处理单字符Token
	case '(':
		return makeToken(TOKEN_LEFT_PAREN);
	case ')':
		return makeToken(TOKEN_RIGHT_PAREN);
		// ...TODO
	case '[':
		return makeToken(TOKEN_LEFT_BRACKET); // 左中括号 '['
	case ']':
		return makeToken(TOKEN_RIGHT_BRACKET); // 右中括号 ']'
	case '{':
		return makeToken(TOKEN_LEFT_BRACE); // 左大括号 '{'
	case '}':
		return makeToken(TOKEN_RIGHT_BRACE); // 右大括号 '}'
	case ',':
		return makeToken(TOKEN_COMMA); // 逗号 ','
	case '.':
		return makeToken(TOKEN_DOT); // 点 '.'
	case ';':
		return makeToken(TOKEN_SEMICOLON); // 分号 ';'
	case '~':
		return makeToken(TOKEN_TILDE); // 波浪号 '~'

		// 可单可双字符的Token处理会稍微复杂一点,但不多
		// 如果Token的第一个字符是+号
	case '+':
		// 如果Token的第二个字符也是+,那就生产++双字符Token返回
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
		// 第一个是-
	case '-':
		// 如果Token的第二个字符也是+,那就生产++双字符Token返回
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
		return string(); // 如果Token的第一个字符是双引号,那就解析出字符串Token返回
	case '\'':
		return character(); // 如果Token的第一个字符是单引号,那就解析出字符Token返回
	}
	// 如果上述处理都没有处理成功,都没有生成合适的Token,说明该字符无法识别
	return errorTokenWithChar(c);
}
