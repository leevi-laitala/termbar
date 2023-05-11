#ifndef _BAR_HPP
#define _BAR_HPP

#include <sys/ioctl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

//enum class FG : uint8_t
//{
//    BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
//    BBLACK = 90, BRED, BGREEN, BYELLOW, BBLUE, BMAGENTA, BCYAN, BWHITE
//};
//
//enum class BG : uint8_t
//{
//    BLACK = 40, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
//    BBLACK = 100, BRED, BGREEN, BYELLOW, BBLUE, BMAGENTA, BCYAN, BWHITE
//}; 
//
//struct StrFX
//{
//    FG fg;
//    BG bg;
//
//    StrFX(const FG& fg, const BG& bg = BG::BLACK)
//        : fg(fg), bg(bg) {}
//};

class Bar
{
public:
    Bar(uint32_t min, uint32_t max, uint8_t size = 10, bool numeric = true)
        : numeric(numeric), min(min), max(max), size(size)
    {}

    void update(float value)
    {
        if (value > max) { this->value = max; }
        else if (value < min) { this->value = min; }
        else { this->value = value; }
    }

    std::string get()
    {
        std::stringstream ss;

        float percentage = (value - min) / (max - min);

        percentage = (percentage > 1 ? 1 : percentage);

        if (numeric)
        {
            float p = std::round(percentage * 100);
            ss << p << "% ";
            if (p < 10)  { ss << ' '; } // Padding
            if (p < 100) { ss << ' '; }
        }
        
        for (uint16_t i = 0; i < size; ++i)
        {
            ss << ((i < size * percentage) ? "\u2588" : "\u2591"); 
        }

        return ss.str();
    }

    void draw(std::ostream& s = std::cout)
    {
        s << "\33[2K\r";
        //s << "\r" << "jeerock\n";
        s << get() << std::flush;
    }

    void clear()
    {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        for (unsigned i = 0; i < w.ws_row - 1; ++i) { std::cout << "\n"; }
    }

private:
    bool numeric;
    float min;
    float max;
    float value;
    uint8_t size;
};

#endif // _BAR_HPP
