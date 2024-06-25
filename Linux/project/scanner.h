#ifndef SCANNER_H
#define SCANNER_H

// 定义一个TokenType枚举，用于标记不同种类的Token
typedef enum {
    /* 单字符 Token */
    TOKEN_LEFT_PAREN,        // '(' 左小括号
    TOKEN_RIGHT_PAREN,       // ')' 右小括号
    TOKEN_LEFT_BRACKET,      // '[' 左中括号
    TOKEN_RIGHT_BRACKET,     // ']' 右中括号
    TOKEN_LEFT_BRACE,        // '{' 左大括号
    TOKEN_RIGHT_BRACE,       // '}' 右大括号
    TOKEN_COMMA,             // ',' 逗号
    TOKEN_DOT,               // '.' 点
    TOKEN_SEMICOLON,         // ';' 分号
    TOKEN_TILDE,             // '~' 波浪号

    /* 可能是单字符或双字符的Token */
    TOKEN_PLUS,                  // '+' 加号
    TOKEN_PLUS_PLUS,             // '++' 自增运算符
    TOKEN_PLUS_EQUAL,            // '+=' 加赋运算符
    TOKEN_MINUS,                 // '-' 减号或负号
    TOKEN_MINUS_MINUS,           // '--' 自减运算符
    TOKEN_MINUS_EQUAL,           // '-=' 减赋运算符
    TOKEN_MINUS_GREATER,         // '->' 结构体指针访问
    TOKEN_STAR,                  // '*' 乘号
    TOKEN_STAR_EQUAL,            // '*=' 乘赋运算符
    TOKEN_SLASH,                 // '/' 除号
    TOKEN_SLASH_EQUAL,           // '/=' 除赋运算符
    TOKEN_PERCENT,               // '%' 取模运算符
    TOKEN_PERCENT_EQUAL,         // '%=' 取模赋运算符
    TOKEN_AMPER,                 // '&' 按位与运算符
    TOKEN_AMPER_EQUAL,           // '&=' 按位与赋运算符
    TOKEN_AMPER_AMPER,           // '&&' 逻辑与运算符
    TOKEN_PIPE,                  // '|' 按位或运算符
    TOKEN_PIPE_EQUAL,            // '|=' 按位或赋运算符
    TOKEN_PIPE_PIPE,             // '||' 逻辑或运算符
    TOKEN_HAT,                   // '^' 按位异或运算符
    TOKEN_HAT_EQUAL,             // '^=' 按位异或赋运算符
    TOKEN_EQUAL,                 // '=' 赋值运算符
    TOKEN_EQUAL_EQUAL,           // '==' 等于比较运算符
    TOKEN_BANG,                  // '!' 逻辑非运算符
    TOKEN_BANG_EQUAL,            // '!=' 不等于比较运算符
    TOKEN_LESS,                  // '<' 小于比较运算符
    TOKEN_LESS_EQUAL,            // '<=' 小于等于比较运算符
    TOKEN_LESS_LESS,             // '<<' 左移运算符
    TOKEN_GREATER,               // '>' 大于比较运算符
    TOKEN_GREATER_EQUAL,         // '>=' 大于等于比较运算符
    TOKEN_GREATER_GREATER,       // '>>' 右移运算符

    // 所有的三字符Token都去掉了 >>= <<= 实现它们也没什么特殊的，但会很无聊繁琐，所以就都去掉了
    /* 多字节Token: 标识符、字符、字符串、数字 */
    TOKEN_IDENTIFIER,            // 标识符
    TOKEN_CHARACTER,             // 字符
    TOKEN_STRING,                // 字符串
    TOKEN_NUMBER,                // 数字，包含整数和浮点数

    /* 关键字Token 涉及C99所有关键字 */
    TOKEN_SIGNED, TOKEN_UNSIGNED,
    TOKEN_CHAR, TOKEN_SHORT, TOKEN_INT, TOKEN_LONG,
    TOKEN_FLOAT, TOKEN_DOUBLE,
    TOKEN_STRUCT, TOKEN_UNION, TOKEN_ENUM, TOKEN_VOID,
    TOKEN_IF, TOKEN_ELSE, TOKEN_SWITCH, TOKEN_CASE, TOKEN_DEFAULT,
    TOKEN_WHILE, TOKEN_DO, TOKEN_FOR,
    TOKEN_BREAK, TOKEN_CONTINUE, TOKEN_RETURN, TOKEN_GOTO,
    TOKEN_CONST, TOKEN_SIZEOF, TOKEN_TYPEDEF,

    // 注意：#define #include这样的预处理指令 不是关键字
    // 辅助Token
    // 词法分析阶段也是可以检测出一些错误的 比如$只能在字符和字符串中 比如字符串"acb 缺少右边双引号
    // 词法分析阶段不进行错误处理，只是将错误的Token信息抛出，以待后续统一进行处理
    // 流水线架构每个阶段都可能出错，如果每个阶段都进行错误处理，那代码的可维护性就太差了
    TOKEN_ERROR,                 // 错误Token 词法分析时遇到无法识别的文本
    TOKEN_EOF                    // 文件结束Token 表示源代码已经分析完毕
} TokenType;

// 词法分析器的目的就是生产一个一个的Token对象 
typedef struct {
    TokenType type;		// Token的类型, 取任一枚举值
    // Token的起始字符指针
    const char *start;	// start指向source中的字符，source为读入的源代码。
    int length;		    // length表示这个Token的长度
    int line;		    // line表示这个Token在源代码的哪一行, 方便后面的报错和描述Token
} Token;	// 这个Token只涉及一个字符指针指向源代码的字符信息,没有在内部保存字符数据


// 对 词法分析器Scanner 进行初始化 
void initScanner(const char *source);	// 源代码字符串(这里涉及一个将源码转换成字符串的函数)
// 核心API, 调用scanToken(), 就生产一个Token, 也就是源代码中下一段字符数据的Token
Token scanToken();	// 当Token返回的是TOKEN_EOF时，源文件被消耗完毕，词法分析结束

#endif  // !SCANNER_H