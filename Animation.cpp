#include "Animation.h"

Animation::Animation(std::vector<std::vector<float> > animation): mAnimation(animation), mCurrentFrame(0), mAnimationTerminee(0)
{

}

Animation::~Animation()
{

}

std::vector<float> Animation::Play(int repetition)
{
    mFrame.clear();
    if(repetition == 0)
    {
        if(mCurrentFrame == mAnimation.size())
            mCurrentFrame = 0;

        for(int i(0); i< mAnimation[mCurrentFrame].size(); i++)
            mFrame.push_back(mAnimation[mCurrentFrame][i]);

        mCurrentFrame ++;
    }
    else
    {
        if(mCurrentFrame == mAnimation.size())
        {
            mAnimationTerminee ++;
            mCurrentFrame = 0;
        }
        if(mAnimationTerminee < repetition)
        {
            //std::cout << mAnimationTerminee << std::endl;
            for(int i(0); i< mAnimation[mCurrentFrame].size(); i++)
                mFrame.push_back(mAnimation[mCurrentFrame][i]);

            mCurrentFrame ++;
        }
    }
    return mFrame;
}
