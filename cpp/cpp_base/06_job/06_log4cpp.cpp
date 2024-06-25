#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"
using namespace log4cpp;

//Category 日志记录器
//Priority 优先级（过滤器）
//Layout 布局
//Appender 输出器（目的地）
void test0(){

    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("'%d' %c [%p] %m%n");

    OstreamAppender *pos = new OstreamAppender("consle", &std::cout);
    pos->setLayout(ptn1);

    // Category & sub1 = Category::getRoot().getInstance("sub1");
    Category & sales = Category::getInstance("salesDepart");
    sales.setPriority(Priority::ERROR);
    sales.addAppender(pos);

    // 回收资源
    Category::shutdown();
}

int main(int argc, char** argv) {

    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);

    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("'%d' %c [%p] %m%n");
    appender1->setLayout(ptn1);
    FileAppender *appender2 = new FileAppender("default", "program.log");
    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("'%d' %c [%p] %m%n");
    appender2->setLayout(ptn2);

    Category &root = Category::getRoot();
    root.setPriority(Priority::WARN);

    root.addAppender(appender1);

    Category &sub1 = Category::getInstance("sub1");
    sub1.setPriority(Priority::INFO);
    sub1.addAppender(appender2);
    // sub1.setAdditivity(false);

    root.error("root error");
    root.warn("root warn");
    root.info("root info");
    sub1.info("sub1 info");
    sub1.warn("sub1 warn");

}