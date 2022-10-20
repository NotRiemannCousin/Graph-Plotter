#include <SFML/Graphics.hpp>

using namespace sf;
using std::string;
using std::to_string;

class NumberGraph : public Drawable{

    static Font* font;
    static size;
    Text text;
    int num;

public:
    static setFont(Font *f)
    {
        font = f;
    }

    static setSize(float s)
    {
        size = s;
    }

    NumberGraph(int _num) : text(to_string(num), font, s){
        num = _num;
        
    }
}