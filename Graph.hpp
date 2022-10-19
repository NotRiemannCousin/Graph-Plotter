#include <iostream>
#include <SFML/Graphics.hpp>
#include "grid/Axis.hpp"

using namespace sf;
using std::cin;
using std::cout;
using std::string;
using std::to_string;

class Graph
{
    int SizeScreenX = 720, SizeScreenY = 720;
    float factor = 1;
    Vector2f MousePos;
    Color backgroundColor = Color::White;

    bool KPshift = 0, KPctrl = 0, KPalt = 0, KPrbm = 0;

    RenderWindow window;
    Image icon;

    View camera;
    Axis axis;
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

                    axis.changeStroke(camera.getSize().x / 360);
                    cout << camera.getSize().x / 360;
                }

                if (KPshift) // Move X
                    camera.move(e.mouseWheelScroll.delta * factor * 50, 0);

                if (KPalt)                                                                    // Move Y
                    camera.move(0, -e.mouseWheelScroll.delta * factor * 50), backgroundColor; // = Color::Blue;
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