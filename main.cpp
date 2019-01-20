#include <SFML/Graphics.hpp>
#include "Animation.hpp"

const int WIDTH = 800;
const int HEIGHT = 500;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My Game");

    std::vector<const char *> wolfAnimations; wolfAnimations.push_back("Howl");
    std::vector<int> wolfStarts; wolfStarts.push_back(0);
    AnimationBundle* wolfBundle = createAnimationBundle("./res/wolf/tile", 20, 500, wolfAnimations, wolfStarts);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        setNext(wolfBundle);
        sf::Texture wolfTexture = getCurrentTexture(wolfBundle);
        sf::Sprite sprite(wolfTexture);

        window.clear();
        window.draw(sprite);
        window.display();

    }

    return 0;
}

void updateRenderTexture(sf::RenderTexture &tex, sf::Drawable &d)
{
    tex.clear();
    tex.draw(d);
    tex.display();
}