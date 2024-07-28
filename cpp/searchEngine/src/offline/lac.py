import os
import sys
import re
from LAC import LAC

def main():
    # 检查命令行参数
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_folder> <output_file>")
        sys.exit(1)

    input_folder = sys.argv[1]
    output_file = sys.argv[2]

    # 检查输入文件夹是否存在
    if not os.path.isdir(input_folder):
        print(f"Error: '{input_folder}' is not a valid directory.")
        sys.exit(1)

    # 中文标点符号列表，用于分割句子
    punctuations = r'[。！？\?！]'

    # 特殊符号处理，保留其中内容不进行分词
    special_symbols = r'[【《].*?[】》]'

    # 初始化 LAC 分词器
    lac = LAC()

    # 打开输出文件
    with open(output_file, 'w', encoding='utf-8') as out_file:
        # 遍历输入文件夹中的所有文件
        for filename in os.listdir(input_folder):
            file_path = os.path.join(input_folder, filename)
            
            if os.path.isfile(file_path):
                with open(file_path, 'r', encoding='utf-8') as file:
                    content = file.read().replace('\n', '')  # 去掉换行符

                    # 处理特殊符号，保留其中内容不分词
                    special_segments = re.findall(special_symbols, content)
                    for segment in special_segments:
                        content = content.replace(segment, f'__SPECIAL__{segment}__SPECIAL__')

                    # 使用正则按标点分割内容
                    sentences = re.split(punctuations, content)
                    for sentence in sentences:
                        sentence = sentence.strip()  # 去除首尾空白
                        if sentence:
                            # 分词处理，保留特殊内容
                            special_parts = re.split(r'(__SPECIAL__.*?__SPECIAL__)', sentence)
                            processed_parts = []
                            for part in special_parts:
                                if part.startswith('__SPECIAL__') and part.endswith('__SPECIAL__'):
                                    processed_parts.append(part[11:-11])  # 去掉特殊标记
                                else:
                                    seg_result = lac.run(part)
                                    if isinstance(seg_result, tuple):
                                        seg_result = seg_result[0]
                                    flat_result = [item for sublist in seg_result for item in (sublist if isinstance(sublist, list) else [sublist])]
                                    processed_parts.append(' '.join(flat_result))
                            out_file.write(' '.join(processed_parts) + '\n')  # 写入分词结果

    print(f"All segmentation results saved to '{output_file}'.")

if __name__ == "__main__":
    main()
