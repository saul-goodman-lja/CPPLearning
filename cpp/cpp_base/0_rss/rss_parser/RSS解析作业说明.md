### RSS解析作业

RSS(Really Simple Syndication)是一种描述和同步网站内容的格式，基于XML，能够被客户端解析程序用做数据源。

1、使用tinyXml2解析RSS文件，并生成一个网页库pagelib.dat

    tinyXml2 -- https://github.com/leethomason/tinyxml2
    rss      -- https://coolshell.cn/feed
             -- http://www.runoob.com/rss/rss-tutorial.html


 参考接口:   

```C++
struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
 };   
```

要求：最后生成一个 pagelib.txt, 其格式:

    <doc>
    	<docid>1</docid>
    	<title>...</title>
    	<link>...</link>
    	<description>...</description>
    	<content>...</content>
    </doc>
    <doc>
    	<docid>2</docid>
    	<title>...</title>
    	<link>...</link>
    	<description>...</description>
    	<content>...</content>
    </doc>
    <doc>
      ...
    </doc>

RSS文件解析作业思路：
xml -->rss-->tinyxml2(使用该库对rss文件进行解析)--> std::regex(使用正则表达式去除html标签)



提示：首先去读coolshell.xml文件，因为是一个rss文件，而我们需要找到rss的channel节点下面的item节点的title节点、link节点中间的文本，至于这些文本可以使用tinyxml2这个第三方库进行解析，所以这里需要看看timyxml2如何解析第三方库（可以看看timyxml2的源码），解析完成一个item后，可以将其存到vector中（也可以将这些原始信息经过后面正则表达式去除标签后再存起来），然后再去读第二个item（其实就是一个循环操作），其实第二个item是第一个item的兄弟节点（可以使用tinyxml2里面的函数进行跳转到第二个item），这样就可以解析coolshell.xml文档了。接着，因为description信息中包含html的标签，所以需要去除这样的html标签，如`<p>``</p>`,这个可以使用正则表达式，也就是std::regex进行去除，这个可以在cppreference.html中进行查找使用方法。

最后就是遍历vector，讲读取到的信息存到另外一个文件，格式需要自己定义，使用我们自定义的`<doc>` `</doc>`格式

rss文件其实就是一个树形结构：

```C++
<rss>
	<channel>
		<item>
 			 <title>  </title>
 			 <link>   </link>
  			 <description>   </description>
 			 <content>   </content>
		</item>

		<item>
    		 <title>  </title>
    		 <link>   </link>
    		 <description>   </description>
    		 <content>   </content>
		</item>
		<item>
		</item>
</channel>
</rss>
```

