# 定义一个srcs变量, 来代指: 使用wildcard函数获取当前目录下的所有.c文件
srcs:=$(wildcard *.c)
# 定义一个objs变量, 来代指: 使用patsubst函数讲srcs中所有的.c文件拓展名替换成.o文件
objs:=$(patsubst %.c,%.o, $(srcs))

# 编译 ' -c $^ '(源依赖项.c文件)  输出到 ' -o $@ '(目标.o)文件
%.o:%.c
	gcc -c $^ -o $@ -g
# mian文件依赖于所有的objs文件
# 把所有依赖项($^) 指定输出到当前目标(-o $@)(即:mian)
main:$(objs)
	gcc $^ -o $@ 
	$(RM) $(objs)

# 清理objs文件 清理mian文件
clean:
	$(RM) $(objs) main

rebuild: clean main