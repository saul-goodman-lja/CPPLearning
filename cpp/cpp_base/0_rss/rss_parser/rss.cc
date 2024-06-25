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
        ofs << "</doc>" << endl;
    }
    ofs.close();
}

void RssReader::parseAndPrintChannelContent(tinyxml2::XMLElement* channel)
{
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