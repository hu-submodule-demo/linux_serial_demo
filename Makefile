# 指定使用的交叉编译工具(根据项目情况修改)
CC = gcc

# 生成的可执行文件名(根据项目情况修改)
TARGET = linux_serial_demo

# 输出文件存放路径(根据项目情况修改)
OUT_DIR := output

# --------------------以下为指定编译器参数(根据项目情况修改)--------------------
# -std=gnu99: 支持C99标准 这里不要使用-std=c99, 否则会报警告提示部分库函数未包含对应头文件
# -Wall: 打开所有警告信息
# -O0: 不优化代码
# -Werror: 警告报错误
CFLAGS := -std=gnu99 -Wall -O0 # -Werror

# --------------------以下为指定头文件路径(根据项目情况修改)--------------------
# CFLAGS +=

# ------------------以下为链接器的链接参数设置(根据项目情况修改)-----------------
LDFLAGS := -lpthread

# 获取各工程文件所在的相对目录(根据项目情况修改)
TOP_PATH = .
LINUX_SERIAL_PATH = ./linux_serial

# 获取工程中各文件夹下的源文件(.c)、目标文件(.o)的文件列表(根据项目情况修改)
# 获取当前目录下的所有的.c文件列表
TOP_SRC = $(wildcard $(TOP_PATH)/*.c)
# 将列表中所有文件名的后缀.c替换为.o, 这样就可以得到在当前目录可生成的.o文件列表, patsubst：替换通配符
TOP_OBJ = $(patsubst %.c, %.o, $(TOP_SRC))

LINUX_SERIAL_SRC = $(wildcard $(LINUX_SERIAL_PATH)/*.c)
LINUX_SERIAL_OBJ = $(patsubst %.c, %.o, $(LINUX_SERIAL_SRC))

# 所有目标文件的集合(根据项目情况修改)
TARGET_OBJS := $(TOP_OBJ) $(LINUX_SERIAL_OBJ)

# --------------------以下为编译默认目标规则(不需要修改)--------------------
# Makefile的默认目标
$(TARGET):$(TARGET_OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET)
	@mkdir -p $(OUT_DIR)
	@mv $(TARGET) $(TARGET_OBJS) $(OUT_DIR)
	@echo "compile done, target file: $(TARGET)"

# --------------------以下为清除规则(不需要修改)--------------------
# 清理目标设置为伪目标，防止外面有clean文件 阻止执行clean
.PHONY:clean
clean:
	@rm $(OUT_DIR)/*.o
	@echo "clean object file done!"

# 清理目标设置为伪目标
.PHONY:distclean
distclean:
	@rm $(OUT_DIR) -rf
	@echo "clean target and object file done!"
