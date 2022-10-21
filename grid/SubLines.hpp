#include <SFML/Graphics.hpp>

using namespace sf;

class SubLines : public Drawable
{
    RectangleShape _line;

    static float stroke;
    int orientation;
    float offset;

public:
    enum Orientation
    {
        Vertical = 0,
        Horizontal = 1
    };

    SubLines(Orientation _orientation, float _offset)
    {
        orientation = _orientation;
        offset = _offset;

        _line.setFillColor(Color(82, 82, 82)); // White Gray

        switch (orientation)
        {
        case Horizontal:
        {
            _line.setPosition(-INT_MAX / 2, -stroke / 2 + offset);
            _line.setSize(Vector2f(UINT_MAX, stroke));
            break;
        }
        case Vertical:
        {
            _line.setPosition(-stroke / 2 + offset, -INT_MAX / 2);
            _line.setSize(Vector2f(stroke, UINT_MAX));
            break;
        }
        }
    }

    voidchangeStroke(float _stroke)
    {
        stroke = _stroke;

        switch (orientation)
        {
        case Horizontal:
        {
            _line.setSize(Vector2f(INT_MAX, stroke));
            _line.setPosition(-INT_MAX / 2, -stroke / 2 + offset);
            break;
        }
        case Vertical:
        {
            _line.setSize(Vector2f(stroke, INT_MAX));
            _line.setPosition(-stroke / 2 + offset, -INT_MAX / 2);
            break;
        }
        }
    }

    void changePos(float _offset)
    {
        offset = _offset;

        switch (orientation)
        {
        case Horizontal:
        {
            _line.setPosition(-INT_MAX / 2, -stroke / 2 + offset);
            break;
        }
        case Vertical:
        {
            _line.setPosition(-stroke / 2 + offset, -INT_MAX / 2);
            break;
        }
        }
    }

    float getStroke()
    {
        return stroke;
    }

    // Overwrite

    void draw(RenderTarget &target, RenderStates states) const
    {
        target.draw(_line, states);
    }
};

float SubLines::stroke = 2;