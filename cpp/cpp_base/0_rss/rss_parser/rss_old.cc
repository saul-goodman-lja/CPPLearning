#include "tinyxml2.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using std::cin, std::cout, std::endl, std::string, std::istringstream;
using std::ofstream, std::vector;

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
    void parseRss();
    void dump(const string&);

private:
    void parseAndPrintChannelContent(tinyxml2::XMLElement*);
    void removeHtml(RssItem &);
private:
    vector<RssItem> _rss;
};

RssReader::RssReader() {}

void RssReader::parseRss()
{
    // tinyxml2::XMLDocument doc;
    // if(doc.LoadFile("coolshell.xml") == tinyxml2::XML_SUCCESS){
    //     tinyxml2::XMLElement *rss = doc.FirstChildElement("rss");
    //     if (rss) {
    //         tinyxml2::XMLElement* channel = rss->FirstChildElement("channel");
    //         if (channel) {
    //             parseAndPrintChannelContent(channel);
    //         } else {
    //             std::cerr << "Failed to find <channel> element." << std::endl;
    //         }
    //     } else {
    //         std::cerr << "Failed to find <rss> element." << std::endl;
    //     }
    // } else {
    //     std::cerr << "Failed to load XML file." << std::endl;
    // }

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("coolshell.xml") != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file." << std::endl;
        return;
    }
    tinyxml2::XMLElement* channel = doc.FirstChildElement("rss")->FirstChildElement("channel");
    if (!channel) {
        std::cerr << "No channel element found." << std::endl;
        return ;
    }

    parseAndPrintChannelContent(channel);

    // tinyxml2::XMLElement* item = channel->FirstChildElement("item");
    // while (item) {
    //     RssItem rssItem;
    //     // Extract title
    //     tinyxml2::XMLElement* titleElement = item->FirstChildElement("title");
    //     if (titleElement && titleElement->GetText()) {
    //         rssItem.title = titleElement->GetText();
    //         std::cout << "Title: " << titleElement->GetText() << std::endl;
    //     } else {
    //         std::cout << "Title not found or empty." << std::endl;
    //     }

    //     // Extract link
    //     tinyxml2::XMLElement* linkElement = item->FirstChildElement("link");
    //     if (linkElement && linkElement->GetText()) {
    //         rssItem.link = linkElement->GetText();
    //         std::cout << "Link: " << linkElement->GetText() << std::endl;
    //     } else {
    //         std::cout << "Link not found or empty." << std::endl;
    //     }

    //     // Extract description
    //     tinyxml2::XMLElement* descriptionElement = item->FirstChildElement("description");
    //     if (descriptionElement && descriptionElement->GetText()) {
    //         string description = descriptionElement->GetText();
    //         std::regex pattern("<[^>]*>");
    //         description = std::regex_replace(description, pattern, "");
    //         rssItem.description = description;
    //         std::cout << "Description: " << description << std::endl;
    //     } else {
    //         std::cout << "Description not found or empty." << std::endl;
    //     }

    //     // Extract content:encoded (note the namespace)
    //     tinyxml2::XMLElement* contentElement = item->FirstChildElement("content:encoded");
    //     if (contentElement && contentElement->GetText()) {
    //         string content = contentElement->GetText();
    //         std::regex pattern("<[^>]*>");
    //         content = std::regex_replace(content, pattern, "");
    //         rssItem.content = content;
    //         std::cout << "Content: " << content << std::endl;
    //     } else {
    //         std::cout << "Content not found or empty." << std::endl;
    //     }

    //     std::cout << "-----------------------------" << std::endl;

    //     // Move to the next item
    //     item = item->NextSiblingElement("item");

    //     _rss.emplace_back(rssItem);

    //     break;
    // }
}
void RssReader::dump(const string& filename)
{
    ofstream ofs(filename);
    for (int i = 0; i < _rss.size(); i++) {
        ofs << "<doc>" << endl;
        ofs << "   <docid>" << i + 1 << "</docid>" << endl;
        ofs << "   <title>" << _rss[i].title << "</title>" << endl;
        ofs << "   <link>" << _rss[i].link << "</link>" << endl;
        ofs << "   <description>" << _rss[i].description << "</description>" << endl;
        ofs << "   <content>" << _rss[i].content << "</content>" << endl;
        ofs << "<doc>" << endl;
    }
    ofs.close();
}

void RssReader::parseAndPrintChannelContent(tinyxml2::XMLElement* channel)
{
    // const char* title       = channel->FirstChildElement("title")->GetText();
    // const char* link        = channel->FirstChildElement("link")->GetText();
    // const char* description = channel->FirstChildElement("description")->GetText();

    // std::cout << "Channel Title: " << (title ? title : "N/A") << std::endl;
    // std::cout << "Channel Link: " << (link ? link : "N/A") << std::endl;
    // std::cout << "Channel Description: " << (description ? description : "N/A") << std::endl;

    // // 提取 item 级别的信息
    // for (tinyxml2::XMLElement* item = channel->FirstChildElement("item"); item;
    //         item = item->NextSiblingElement("item")) {
        
    //     const char* itemTitle       = item->FirstChildElement("title")->GetText();
    //     const char* itemLink        = item->FirstChildElement("link")->GetText();
    //     const char* itemDescription = item->FirstChildElement("description")->GetText();
    //     const char* itemContent     = item->FirstChildElement("content:encoded")
    //                                       ? item->FirstChildElement("content:encoded")->GetText()
    //                                       : nullptr;

    //     std::cout << "\nItem Title: " << (itemTitle ? itemTitle : "N/A") << std::endl;
    //     std::cout << "Item Link: " << (itemLink ? itemLink : "N/A") << std::endl;
    //     std::cout << "Item Description: " << (itemDescription ? itemDescription : "N/A")
    //               << std::endl;
    //     std::cout << "Item Content: " << (itemContent ? itemContent : "N/A") << std::endl;
    //     break;
    // }
    RssItem rssItem;
    tinyxml2::XMLElement* item = channel->FirstChildElement("item");
    while (item) {
        rssItem.title = item->FirstChildElement("title")->GetText();
        rssItem.link = item->FirstChildElement("link")->GetText();
        rssItem.description = item->FirstChildElement("description")->GetText();
        rssItem.content = item->FirstChildElement("content:encoded")->GetText();
        removeHtml(rssItem);
        _rss.emplace_back(rssItem);
        item = item->NextSiblingElement("item");
        break;
    }
}

void RssReader::removeHtml(RssItem & rssItem){
    std::regex pattern("<[^>]*>");
    rssItem.title = std::regex_replace(rssItem.title, pattern, "");
    rssItem.link = std::regex_replace(rssItem.link, pattern, "");
    rssItem.description = std::regex_replace(rssItem.description, pattern, "");
    rssItem.content = std::regex_replace(rssItem.content, pattern, "");
}


int main(int argc, char* argv[])
{

    RssReader rssReader;
    rssReader.parseRss();

    rssReader.dump("pagelib.txt");
    return 0;
}