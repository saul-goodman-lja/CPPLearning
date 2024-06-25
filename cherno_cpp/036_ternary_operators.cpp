#include <iostream>
#include <string>

static int s_Level = 1;
static int s_Speed = 2;

int main()
{
    if (s_Level > 5) 
    {
        s_Speed = 10;
    }
    else 
    {
        s_Speed = 5;
    }

    // condition assigment

    s_Speed = s_Level > 5 ? 10 : 5;
    s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;
    s_Speed = s_Level > 5 ? (s_Level > 10 ? 15 : 10) : 5;
    s_Speed = s_Level > 5 && s_Level < 100 ? s_Level > 10 ? 15 : 10 : 5;

    std::string rand = s_Level > 10 ? "Master" : "Beginner";

    std::cin.get();
}