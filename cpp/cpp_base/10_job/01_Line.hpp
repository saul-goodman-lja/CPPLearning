#ifndef _LINE_HPP
#define _LINE_HPP

class Line{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine() const;
private:
    class LineImpl;
    LineImpl * _pimpl;
};

#endif