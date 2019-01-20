#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "sys/dir.h"

struct Bound
{
    int id, left, right;
};

struct AnimationBundle
{
    std::map<std::string, Bound> boundMap;
    std::vector<sf::Texture> textures;
};


std::vector<sf::Texture>* retrieveTextures(const char* filePath, int count)
{
    //
    // If filePath = "./res/sprites/somesprite", and count = 3, then
    // this function will return an vector of textures loaded from somesprite0,
    // somesprite1, and somesprite2. 
    //

    std::vector<sf::Texture>* textures = new std::vector<sf::Texture >(count);

    sf::Texture* tex;
    for (int n = 0; n < count; n++) 
    {
        if (!tex->loadFromFile(filePath + std::to_string(n) + ".png"))
        {
            throw "Failed to create texture from file";
        }
        textures->push_back(*tex);
    }
    tex= NULL;

    return textures;
}

AnimationBundle* createAnimationBundle(const char* filePath, int animationCount, std::vector<const char*>& animationNames,
    std::vector<int>& animationStarts)
{
    std::vector<sf::Texture>* textures = retrieveTextures(filePath, animationCount);
    std::map<std::string, Bound>* animationMap = new std::map<std::string, Bound>();

    for (int i = 0; i < animationNames.size(); i++) {
        std::string name = std::string(animationNames[i]);
        int start = animationStarts[i];
        
        int last = i == animationStarts.size() - 1 ? animationCount - 1 : animationStarts[i + 1] - 1;

        Bound* bound = (Bound *)malloc(sizeof(Bound));
        bound->id = i;
        bound->left = start;
        bound->right = last;

        animationMap->insert(std::pair<std::string, Bound>(name, *bound));
    }

    AnimationBundle* ab = (AnimationBundle *) malloc(sizeof(AnimationBundle));
    ab->textures = *textures;
    ab->boundMap = *animationMap;

    return ab;
}
