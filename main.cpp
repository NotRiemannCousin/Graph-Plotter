#include "Graph.hpp"
using namespace sf;

int main()
{
    Graph graph;

    graph.init();
    graph.Run();
    
    graph.finish();
}
/*


-IC:/SFML-2.5.1-gcc/include
-LC:/SFML-2.5.1-gcc/lib
-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -static-libstdc++

*/