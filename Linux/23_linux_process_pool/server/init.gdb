# fork时自动追踪子进程
set follow-fork-mode child

# 设置父子进程都在gdb控制之下，并不分离出去 ，可以进行多进程的切换
set detach-on-fork off

# GDB 在执行新程序时继续保持相同的执行模式，而不会根据新程序的不同而更改模式。
set follow-exec-mode same

#关闭 GDB 中的确认提示
set confirm off

#关闭这种分页显示
set pagination off

#关闭TUI
tui disable

skip function fork
skip function strlen
skip function strcpy
skip function strchr
skip function print
skip function zalloc
skip function peek
skip function gettoken

# 加载python脚本文件，用来打印文件描述符信息
source visualize.py

break main
break son.c:sonProcMain
break pool.c:initPoll
break main.c:54

# 在程序停止执行时触发pdump,打印文件描述符
define hook-stop
    pdump
end

