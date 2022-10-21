#include <iostream>
#include <SFML/Graphics.hpp>
#include "grid/Axis.hpp"
#include "grid/SubLines.hpp"

using namespace sf;
using std::cin;
using std::cout;
using std::string;
using std::to_string;
using std::vector;

class Graph
{
    int SizeScreenX = 720, SizeScreenY = 720;
    float factor = 1, offset_size_lines = 80;
    const float line_n = 30;
    Vector2f MousePos;
    Color backgroundColor = Color::White;

    bool KPshift = 0, KPctrl = 0, KPalt = 0, KPrbm = 0;

    RenderWindow window;
    Image icon;

    View camera;
    Axis axis;
    vector<SubLines> grid;

    Text output;
    Font font;

    void events()
    {
        Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
            {
                window.close();
            }
            break;
            case Event::MouseButtonPressed:
            {
                KPrbm = e.mouseButton.button == Mouse::Left;
            }
            break;
            case Event::MouseButtonReleased:
            {
                KPrbm = (!e.mouseButton.button == Mouse::Left);
            }
            break;
            case Event::KeyPressed:
            {
                KPshift = e.key.shift;
                KPalt = e.key.alt;
                KPctrl = e.key.control;
            }
            break;
            case Event::KeyReleased:
            {
                KPshift = e.key.shift;
                KPalt = e.key.alt;
                KPctrl = e.key.control;
            }
            break;
            case Event::MouseWheelScrolled:
            {
                if (KPrbm) // Move bidirectional
                    ;

                if (KPctrl) // Zoom
                {
                    camera.zoom(-e.mouseWheelScroll.delta * .1f + 1);

                    factor = camera.getSize().x / window.getSize().x;

                    float new_stroke = camera.getSize().x / 360;
                    float new_offset = (int)camera.getSize().x / 10;
                    axis.changeStroke(new_stroke);
                    for (auto &line : grid)
                    {
                        line.changeStroke(new_stroke);
                    }
                }

                if (KPshift) // Move X
                    camera.move(e.mouseWheelScroll.delta * factor * 50, 0);

                if (KPalt) // Move Y
                    camera.move(0, -e.mouseWheelScroll.delta * factor * 50);
            }
            break;
            case Event::MouseMoved:
            {
                if (KPrbm)
                {
                    auto var = MousePos - Vector2f(e.mouseMove.x, e.mouseMove.y);
                    var.x *= factor;
                    var.y *= factor;
                    camera.move(var);
                }
                MousePos = {(float)e.mouseMove.x, (float)e.mouseMove.y};
            }
            break;
            }
        }
        window.setView(camera);

        auto view_box = FloatRect(camera.getCenter().x - camera.getSize().x / 2,
                                  camera.getCenter().y - camera.getSize().y / 2,
                                  camera.getSize().x,
                                  camera.getSize().y);

        // if(view_box.height)

        for (auto &line : grid)
        {
            auto box = line.getBox();

            if (view_box.intersects(box))
                continue;

            if (line.getOrientation() == SubLines::Vertical)
            {
                if (box.left + box.width < view_box.left)
                {
                    line.setOffset(line.getOffset() + offset_size_lines * line_n / 2);
                    continue;
                }
                else if (box.left > view_box.width + view_box.left)
                {
                    line.setOffset(line.getOffset() - offset_size_lines * line_n / 2);
                    continue;
                }
            }

            if (line.getOrientation() == SubLines::Horizontal)
            {
                if (box.top + box.height < view_box.top)
                {
                    line.setOffset(line.getOffset() + offset_size_lines * line_n / 2);
                    continue;
                }
                else if (box.top > view_box.height + view_box.top)
                {
                    line.setOffset(line.getOffset() - offset_size_lines * line_n / 2);
                    continue;
                }
            }
        }
    }

    void draw()
    {
        string out;

        out = "KPctrl : " + to_string(KPctrl);
        out += "\nKPalt : " + to_string(KPalt);
        out += "\nKPshift : " + to_string(KPshift);
        out += "\nKPrbm : " + to_string(KPrbm);
        out += "\nfactor : " + to_string(factor);
        out += "\naxis.getStroke() : " + to_string(axis.getStroke());
        output.setString(out);

        window.clear(backgroundColor);
        for (auto &line : grid)
            window.draw(line);
        window.draw(axis);
        window.draw(output);
        window.display();
    }

public:
    Graph() : window(VideoMode(SizeScreenX, SizeScreenY, 64), "SFML works! (sometimes)", Style::Close),
              camera(Vector2f(0, 0), Vector2f(window.getSize()))
    {
    }

    void init()
    {
        icon.loadFromFile("C:/Users/Aluno/Documents/Marcelo/C++/SFML C++/SFML projetos/graph/res/img/icon.png");
        window.setIcon(32, 32, icon.getPixelsPtr());

        font.loadFromFile("C:/Users/Aluno/Downloads/Arialn.ttf");
        output = Text("", font, 30U);
        output.setFillColor(Color::Black);

        grid.reserve(line_n);

        for (int i = -7; i < 8; i++) // H
        {
            grid.push_back(SubLines(SubLines::Orientation::Horizontal, SizeScreenX / 9 * i));
        }
        for (int i = -7; i < 8; i++) // V
        {
            grid.push_back(SubLines(SubLines::Orientation::Vertical, SizeScreenX / 9 * i));
        }
    }

    void Run()
    {
        while (window.isOpen())
        {
            events();
            draw();
        }
    }

    void finish()
    {
    }
};