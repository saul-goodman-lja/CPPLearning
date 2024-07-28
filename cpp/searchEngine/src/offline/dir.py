import os
import sys

# 获取命令行参数
if len(sys.argv) != 3:
    print("请提供文件夹路径和输出文件名。")
    sys.exit(1)

folder_path = sys.argv[1]  # 第一个参数是文件夹路径
output_file = sys.argv[2]  # 第二个参数是输出文件名

# 检查文件夹是否存在
if not os.path.isdir(folder_path):
    print("提供的路径不是一个有效的文件夹。")
    sys.exit(1)

# 获取文件名列表
file_names = os.listdir(folder_path)

# 将文件名写入指定的输出文件
with open(output_file, 'w', encoding='utf-8') as f:
    for file_name in file_names:
        f.write(file_name + '\n')

print(f"文件名已保存到 '{output_file}'。")