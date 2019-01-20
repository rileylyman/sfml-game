#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

struct Bound
{
    int id, left, right;
};

struct AnimationBundle
{
    unsigned int currentAnimationIndex;
    unsigned int waitFrames;
    unsigned int currentFramesWaited;
    std::string currentAnimation;

    std::map<std::string, Bound> boundMap;
    std::vector<sf::Texture> textures;
};

AnimationBundle* initAnimationBundle(std::map<std::string, Bound>* bMap, std::vector<sf::Texture>* texs, unsigned int waitFrames)
{
    auto ab = (AnimationBundle *) calloc(sizeof(AnimationBundle), 1);
    ab->boundMap = *bMap;
    ab->textures = *texs;
    ab->waitFrames = waitFrames;

    //TODO: bound check here
    ab->currentAnimation = bMap->begin()->first;
    ab->currentAnimationIndex = bMap->at(ab->currentAnimation).left;

    return ab;
}

inline sf::Texture getCurrentTexture(AnimationBundle* anim)
{
    return anim->textures.at(anim->currentAnimationIndex);
}

void setNext(AnimationBundle* anim)
{
    if (anim->currentFramesWaited < anim->waitFrames)
    {
        anim->currentFramesWaited++;
    }
    else
    {
        anim->currentFramesWaited = 0;
        if (anim->currentAnimationIndex == anim->boundMap.at(anim->currentAnimation).right + 1)
        {
            anim->currentAnimationIndex = anim->boundMap.at(anim->currentAnimation).left;
        }
        else { anim->currentAnimationIndex++; }
    }
}

std::vector<sf::Texture>* retrieveTextures(const char* filePath, int count) throw()
{
    //
    // If filePath = "./res/sprites/somesprite", and count = 3, then
    // this function will return an vector of textures loaded from somesprite0,
    // somesprite1, and somesprite2. 
    //

    std::vector<sf::Texture>* textures = new std::vector<sf::Texture >(count);

    for (int n = 0; n < count; n++) 
    {
        textures->emplace_back();

        if (!textures->at(n).loadFromFile(filePath + std::to_string(n) + ".png"))
        {
            throw "Failed to create texture from file";
        }
    }

    return textures;
}

AnimationBundle* createAnimationBundle(const char* filePath, int animationCount, unsigned int waitFrames, 
    std::vector<const char*>& animationNames, std::vector<int>& animationStarts)
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

    return initAnimationBundle(animationMap, textures, waitFrames);
}
