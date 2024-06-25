#ifndef SCANNER_H
#define SCANNER_H

// ����һ��TokenTypeö�٣����ڱ�ǲ�ͬ�����Token
typedef enum {
    /* ���ַ� Token */
    TOKEN_LEFT_PAREN,        // '(' ��С����
    TOKEN_RIGHT_PAREN,       // ')' ��С����
    TOKEN_LEFT_BRACKET,      // '[' ��������
    TOKEN_RIGHT_BRACKET,     // ']' ��������
    TOKEN_LEFT_BRACE,        // '{' �������
    TOKEN_RIGHT_BRACE,       // '}' �Ҵ�����
    TOKEN_COMMA,             // ',' ����
    TOKEN_DOT,               // '.' ��
    TOKEN_SEMICOLON,         // ';' �ֺ�
    TOKEN_TILDE,             // '~' ���˺�

    /* �����ǵ��ַ���˫�ַ���Token */
    TOKEN_PLUS,                  // '+' �Ӻ�
    TOKEN_PLUS_PLUS,             // '++' ���������
    TOKEN_PLUS_EQUAL,            // '+=' �Ӹ������
    TOKEN_MINUS,                 // '-' ���Ż򸺺�
    TOKEN_MINUS_MINUS,           // '--' �Լ������
    TOKEN_MINUS_EQUAL,           // '-=' ���������
    TOKEN_MINUS_GREATER,         // '->' �ṹ��ָ�����
    TOKEN_STAR,                  // '*' �˺�
    TOKEN_STAR_EQUAL,            // '*=' �˸������
    TOKEN_SLASH,                 // '/' ����
    TOKEN_SLASH_EQUAL,           // '/=' ���������
    TOKEN_PERCENT,               // '%' ȡģ�����
    TOKEN_PERCENT_EQUAL,         // '%=' ȡģ�������
    TOKEN_AMPER,                 // '&' ��λ�������
    TOKEN_AMPER_EQUAL,           // '&=' ��λ�븳�����
    TOKEN_AMPER_AMPER,           // '&&' �߼��������
    TOKEN_PIPE,                  // '|' ��λ�������
    TOKEN_PIPE_EQUAL,            // '|=' ��λ�������
    TOKEN_PIPE_PIPE,             // '||' �߼��������
    TOKEN_HAT,                   // '^' ��λ��������
    TOKEN_HAT_EQUAL,             // '^=' ��λ��������
    TOKEN_EQUAL,                 // '=' ��ֵ�����
    TOKEN_EQUAL_EQUAL,           // '==' ���ڱȽ������
    TOKEN_BANG,                  // '!' �߼��������
    TOKEN_BANG_EQUAL,            // '!=' �����ڱȽ������
    TOKEN_LESS,                  // '<' С�ڱȽ������
    TOKEN_LESS_EQUAL,            // '<=' С�ڵ��ڱȽ������
    TOKEN_LESS_LESS,             // '<<' ���������
    TOKEN_GREATER,               // '>' ���ڱȽ������
    TOKEN_GREATER_EQUAL,         // '>=' ���ڵ��ڱȽ������
    TOKEN_GREATER_GREATER,       // '>>' ���������

    // ���е����ַ�Token��ȥ���� >>= <<= ʵ������Ҳûʲô����ģ���������ķ��������ԾͶ�ȥ����
    /* ���ֽ�Token: ��ʶ�����ַ����ַ��������� */
    TOKEN_IDENTIFIER,            // ��ʶ��
    TOKEN_CHARACTER,             // �ַ�
    TOKEN_STRING,                // �ַ���
    TOKEN_NUMBER,                // ���֣����������͸�����

    /* �ؼ���Token �漰C99���йؼ��� */
    TOKEN_SIGNED, TOKEN_UNSIGNED,
    TOKEN_CHAR, TOKEN_SHORT, TOKEN_INT, TOKEN_LONG,
    TOKEN_FLOAT, TOKEN_DOUBLE,
    TOKEN_STRUCT, TOKEN_UNION, TOKEN_ENUM, TOKEN_VOID,
    TOKEN_IF, TOKEN_ELSE, TOKEN_SWITCH, TOKEN_CASE, TOKEN_DEFAULT,
    TOKEN_WHILE, TOKEN_DO, TOKEN_FOR,
    TOKEN_BREAK, TOKEN_CONTINUE, TOKEN_RETURN, TOKEN_GOTO,
    TOKEN_CONST, TOKEN_SIZEOF, TOKEN_TYPEDEF,

    // ע�⣺#define #include������Ԥ����ָ�� ���ǹؼ���
    // ����Token
    // �ʷ������׶�Ҳ�ǿ��Լ���һЩ����� ����$ֻ�����ַ����ַ����� �����ַ���"acb ȱ���ұ�˫����
    // �ʷ������׶β����д�����ֻ�ǽ������Token��Ϣ�׳����Դ�����ͳһ���д���
    // ��ˮ�߼ܹ�ÿ���׶ζ����ܳ������ÿ���׶ζ����д������Ǵ���Ŀ�ά���Ծ�̫����
    TOKEN_ERROR,                 // ����Token �ʷ�����ʱ�����޷�ʶ����ı�
    TOKEN_EOF                    // �ļ�����Token ��ʾԴ�����Ѿ��������
} TokenType;

// �ʷ���������Ŀ�ľ�������һ��һ����Token���� 
typedef struct {
    TokenType type;		// Token������, ȡ��һö��ֵ
    // Token����ʼ�ַ�ָ��
    const char *start;	// startָ��source�е��ַ���sourceΪ�����Դ���롣
    int length;		    // length��ʾ���Token�ĳ���
    int line;		    // line��ʾ���Token��Դ�������һ��, �������ı��������Token
} Token;	// ���Tokenֻ�漰һ���ַ�ָ��ָ��Դ������ַ���Ϣ,û�����ڲ������ַ�����


// �� �ʷ�������Scanner ���г�ʼ�� 
void initScanner(const char *source);	// Դ�����ַ���(�����漰һ����Դ��ת�����ַ����ĺ���)
// ����API, ����scanToken(), ������һ��Token, Ҳ����Դ��������һ���ַ����ݵ�Token
Token scanToken();	// ��Token���ص���TOKEN_EOFʱ��Դ�ļ���������ϣ��ʷ���������

#endif  // !SCANNER_H