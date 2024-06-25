# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

# 目标可执行文件的名称
TARGET = my_program

# 源文件和头文件
SRCS = main.c
HEADERS = maic.h

# 对应的目标文件
OBJS = $(SRCS:.c=.o)

# 默认规则：编译并链接可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 编译每个源文件的模式规则
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的目标文件和可执行文件
.PHONY: clean rebuild
clean:
	rm -f $(OBJS) $(TARGET)
rebuild: clean my_program
