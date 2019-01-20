#include <SFML/Graphics.hpp>
#include "Animation.hpp"

const int WIDTH = 800;
const int HEIGHT = 500;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My Game");

    std::vector<const char *> wolfAnimations; wolfAnimations.push_back("Howl");
    std::vector<int> wolfStarts; wolfStarts.push_back(0);
    AnimationBundle* wolfBundle = createAnimationBundle("./res/wolf/tile", 20, wolfAnimations, wolfStarts);

    int currentAnimationIndex = 0;
    std::string currentAnimation = "Howl";
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

        if (currentAnimationIndex == wolfBundle->boundMap.at(currentAnimation).right + 1)
        {
            currentAnimationIndex = wolfBundle->boundMap.at(currentAnimation).left;
        }
        sf::Texture wolfTexture = wolfBundle->textures.at(currentAnimationIndex);
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