#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <iostream>
#include <vector>

class Animation
{
public:
    Animation(std::vector<std::vector<float> > animation);
    ~Animation();

    std::vector<float> Play(int repetition);
private:
    std::vector<std::vector<float> > mAnimation;
    std::vector<float> mFrame;
    float mCurrentVertices[5000];
    int mCurrentFrame;
    int mAnimationTerminee;
};

#endif // ANIMATION_H_INCLUDED
