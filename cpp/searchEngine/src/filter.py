# import os
# import xml.etree.ElementTree as ET

# # 设置文件夹路径
# folder_path = '/home/lja/user/CppLearning/cpp/searchEngine/resources/模块二/人民网语料'  # 请替换为你的文件夹路径

# # 遍历文件夹中的所有文件
# for filename in os.listdir(folder_path):
#     file_path = os.path.join(folder_path, filename)
#     # 检查是否为文件而不是目录，并且是否为 XML 文件
#     if os.path.isfile(file_path) and file_path.lower().endswith('.xml'):
#         tree = ET.parse(file_path)  # 解析 XML 文件
#         root = tree.getroot()        # 获取根元素
        
#         # 遍历所有 'item' 元素
#         for item in root.findall('.//item'):
#             for elem in item:
#                 if elem.tag not in ['description', 'title', 'link', 'pubDate', 'author', 'hitCount', 'docId', 'channel', 'source', 'pubTime']:
#                     # 输出文件名和非指定标签名
#                     print(f'File: {filename}, Tag: {elem.tag}')

import os
import xml.etree.ElementTree as ET

# 设置文件夹路径
folder_path = '/home/lja/user/CppLearning/cpp/searchEngine/resources/模块二/人民网语料'  # 请替换为你的文件夹路径
exclude_files = ['dataparse.xml', 'latest.xml','coolshell.xml']  # 要排除的文件列表

# 遍历文件夹中的所有文件
for filename in os.listdir(folder_path):
    file_path = os.path.join(folder_path, filename)
    
    # 检查是否为文件而不是目录，并且是否为 XML 文件，且不在排除名单中
    if (os.path.isfile(file_path) and 
        file_path.lower().endswith('.xml') and 
        filename not in exclude_files):
        
        tree = ET.parse(file_path)  # 解析 XML 文件
        root = tree.getroot()        # 获取根元素
        
        # 遍历所有 'item' 元素
        for item in root.findall('.//item'):
            for elem in item:
                if elem.tag not in ['description', 'title', 'link', 'pubDate', 'author', 'hitCount', 'docId', 'channel', 'source', 'pubTime', 'category']:
                    # 输出文件名和非指定标签名
                    print(f'File: {filename}, Tag: {elem.tag}')