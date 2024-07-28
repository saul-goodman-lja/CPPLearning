# from LAC import LAC

# # 装载分词模型
# lac = LAC(mode='seg')

# # 单个样本输入，输入为Unicode编码的字符串
# text = u"LAC是,个优秀,的分词/工具"
# seg_result = lac.run(text)

# # 批量样本输入, 输入为多个句子组成的list，平均速率会更快
# # texts = [u"LAC是个优秀的分词工具", u"百度是一家高科技公司"]
# # seg_result = lac.run(texts)
# print(seg_result)

# from LAC import LAC

# 装载分词模型
# lac = LAC(mode='seg')

# # 词频字典
# word_freq = {}

# # 读取文件并进行分词
# with open('art/C3-Art0002.txt', 'r', encoding='utf-8') as file:
#     lines = file.readlines()

# for line in lines:
#     text = line.strip()  # 去掉行末的换行符
#     if text:  # 确保文本不为空
#         seg_result = lac.run(text)
#         for word in seg_result:
#             if word in word_freq:
#                 word_freq[word] += 1  # 词频加1
#             else:
#                 word_freq[word] = 1  # 新词加入词典并初始化为1

# # 将词频结果保存到文件
# with open('word_frequency.txt', 'w', encoding='utf-8') as output_file:
#     for word, freq in word_freq.items():
#         output_file.write(f"{word}: {freq}\n")

# print("词频统计已保存到 'word_frequency.txt'")


from LAC import LAC

# 装载分词模型
lac = LAC(mode='seg')

# 读取文件并进行分词
with open('art/C3-Art0002.txt', 'r', encoding='utf-8') as file:
    lines = file.readlines()

# 存储分词结果
segmented_lines = []

# 逐行分词
for line in lines:
    text = line.strip()  # 去掉行末的换行符
    if text:  # 确保文本不为空
        seg_result = lac.run(text)
        # 将分词结果以空格连接并添加到列表
        segmented_lines.append(' '.join(seg_result))

# 将分词结果保存到文件
with open('segmented_output.txt', 'w', encoding='utf-8') as output_file:
    for segmented_line in segmented_lines:
        output_file.write(segmented_line + '\n')

print("分词结果已保存到 'segmented_output.txt'")