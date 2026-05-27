#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <vector>

class ZBuffer
{
public:
    ZBuffer() = default;
    ZBuffer(double width, double height);

    void reset(double width, double height);
    void clear();

    int getWidth() const;
    int getHeight() const;

    bool contains(int x, int y) const;
    void putDepth(int x, int y, double depth);
    bool isVisible(int x, int y, double depth, double eps) const;

private:
    int index(int x, int y) const;

    int _width{1};
    int _height{1};
    std::vector<double> _depths;
};

#endif
