#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "tools.h"

// main.c中的核心逻辑
static void run(const char *source)
{
	initScanner(source); // 初始化词法分析器
	int line = -1;		 // 用于记录当前处理的行号,-1表示还未开始解析
	for (;;)
	{
		Token token = scanToken(); // 获取下一个TOKEN
		if (token.line != line)
		{ // 如果Token中记录行和现在的lin不同就执行换行打印的效果
			printf("%4d ", token.line);
			line = token.line;
		}
		else
		{ // 没有换行的打印效果
			printf("   | "); 
		}
		char *str = convert_to_str(token);
		printf("%s '%.*s'\n", str, token.length, token.start);
		// if (token.type == TOKEN_ERROR){
		// 	free(token.start);
		// }
		if (token.type == TOKEN_EOF)
		{
			break; // 读到TOKEN_EOF结束循环
		}
	}
}
// repl是"	"的缩写
// repl 函数定义了一个交互式的读取-求值-打印循环（REPL）逻辑
// 它允许用户输入源代码行，逐行进行词法分析，并打印分析结果
// 也就是说启动时没有主动给出一个命令行参数表示文件路径的话,那么就进行交互式界面进行词法分析
static void repl()
{
	// TODO
	// 这里应该存在一个死循环,而且要逐行的读取键盘输入fgets
	char str[1024];
	while (1)
	{
		fprintf(stdout, "> ");
		fgets(str, 1024, stdin);
		run(str);
	}
}

// 用户输入文件名，将整个文件的内容读入内存，并在末尾添加'\0'
// 注意: 这里应该使用动态内存分配，因此应该事先确定文件的大小。
static char *readFile(const char *path)
{
	// TODO
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "failed open file %s\n", path);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	char *str = (char *)calloc((len + 1), sizeof(char));
	fseek(fp, 0, SEEK_SET);
	fread(str,1,len,fp);
	str[len] = '\0';
	fclose(fp);
	return str;
}

// 该函数表示对传入的文件路径名的字符串进行处理
static void runFile(const char *path)
{
	// 处理'.c'文件:用户输入文件名，分析整个文件，并将结果输出
	// 这个代码非常简单，我帮你直接写好
	// 会调用上面的readFile函数，根据文件路径名生成一个包含文件全部字符信息的字符串
	char *source = readFile(path);

	// 调用run函数处理源文件生成的字符串
	run(source);
	// 及时释放资源
	free(source);
}
/*
 * 主函数支持操作系统传递命令行参数
 * 然后通过判断参数的个数:
 * 1.如果没有主动传入参数(argc=1),因为第一个参数总会传入一个当前可执行文件的目录作为命令行参数
 * 此时执行repl函数
 * 2.如果传递了一个参数(argc=2),说明传递了一个参数,将传递的参数视为某个源代码的路径
 * 然后调用runFile函数,传入该源代码文件的路径,处理源文件
 */
int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		repl();
	}
	else if (argc == 2)
	{
		runFile(argv[1]);
	}
	else
	{
		// 如果主动传入超过一个命令行参数.即参数传递有误,错误处理
		// 告诉用户正确的使用函数的方式
		fprintf(stderr, "Usage: scanner [path]\n");
		exit(1);
	}
	return 0;
}