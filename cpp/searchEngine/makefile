# 编译器
CXX = g++

# 编译器选项
# CXXFLAGS = -Wall -std=c++20 -pthread
CXXFLAGS = -std=c++20 -pthread -lpthread

# 链接器选项
LDFLAGS = -lhiredis -llog4cpp 

# 源文件目录
SRC_DIR = src/online

# 目标文件目录
OBJ_DIR = obj

# 二进制文件目录
BIN_DIR = bin

# 可执行文件名
TARGET = $(BIN_DIR)/my_program

# 搜索所有源文件
SRCS = $(wildcard $(SRC_DIR)/*.cc)

# 将源文件转换为目标文件
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRCS))

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 编译源文件生成目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# 显示内容
show:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Target: $(TARGET)"

.PHONY: all clean show
