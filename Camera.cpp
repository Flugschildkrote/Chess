#include "Camera.h"

Camera::Camera(): mPhi(0.0),mTheta(0.0),mOrientation(),
                  mAxeVertical(0,0,1),mDeplacementLateral(),mPosition(),mPointCible(),
                  mSensibility(0.0), mVitesse(0.0)
{

}

Camera::Camera(glm::vec3 position,glm::vec3 pointCible,glm::vec3 axeVertical,
                                            float sensibilite, float vitesse): mPhi(0.0),mTheta(-0.0),mOrientation(),
                                                                               mAxeVertical(axeVertical),
                                                                               mDeplacementLateral(),
                                                                               mPosition(position),mPointCible(pointCible),
                                                                               mSensibility(sensibilite),mVitesse(vitesse)
{
    setPointCible(mPointCible);
}

Camera::~Camera()
{

}

void Camera::orienter(int xRel,int yRel)
{
    mPhi += -yRel* mSensibility;
    mTheta += -xRel* mSensibility;

    if(mPhi > 89.0)
        mPhi = 89.0;

    if(mPhi < -89.0)
        mPhi = -89.0;

    float phiRadian = mPhi* M_PI/180;
    float thetaRadian = mTheta* M_PI/180;

    if(mAxeVertical.x == 1.0)
    {
        mOrientation.x = sin(phiRadian);
        mOrientation.y = cos(phiRadian)*cos(thetaRadian);
        mOrientation.z = cos(phiRadian)*sin(thetaRadian);
    }
    else if(mAxeVertical.y == 1.0)
    {
        mOrientation.x = cos(phiRadian)*sin(thetaRadian);
        mOrientation.y = sin(phiRadian);
        mOrientation.z = cos(phiRadian)*cos(thetaRadian);
    }
    else
    {
        mOrientation.x = cos(phiRadian)*cos(thetaRadian);
        mOrientation.y = cos(phiRadian)*sin(thetaRadian);
        mOrientation.z = sin(phiRadian);
    }

    mDeplacementLateral = glm::cross(mAxeVertical,mOrientation);
    mDeplacementLateral = glm::normalize(mDeplacementLateral);

    mPointCible = mPosition + mOrientation;
}

void Camera::deplacerFPS(Input const &input)
{
    if(input.getKey(SDL_SCANCODE_UP))
    {
        mPosition = mPosition + mOrientation * mVitesse;
        mPointCible = mPosition + mOrientation;
    }
    if(input.getKey(SDL_SCANCODE_DOWN))
    {
        mPosition = mPosition - mOrientation * mVitesse;
        mPointCible = mPosition + mOrientation;
    }
    if(input.getKey(SDL_SCANCODE_LEFT))
    {
        mPosition = mPosition + mDeplacementLateral * mVitesse;
        mPointCible = mPosition + mOrientation;
    }
    if(input.getKey(SDL_SCANCODE_RIGHT))
    {
        mPosition = mPosition - mDeplacementLateral * mVitesse;
        mPointCible = mPosition + mOrientation;
    }

    if(input.mouseMoved())
        orienter(input.getXRel(),input.getYRel());
}

void Camera::deplacerCHESS(Input const &input, int sensibility)
{
    mPointCible = mOrientation + mPosition;
    int moveCamX;
    int moveCamY;
    if(input.getKey(SDL_SCANCODE_UP))
    {
        moveCamY = 1;
    }
    else if(input.getKey(SDL_SCANCODE_DOWN))
    {
        moveCamY = -1;
    }else
    {
        moveCamY = 0;
    }

    if(input.getKey(SDL_SCANCODE_LEFT))
    {
        moveCamX = 1;
    }
    else if(input.getKey(SDL_SCANCODE_RIGHT))
    {
        moveCamX = -1;
    }else
    {
        moveCamX = 0;
    }
    if(moveCamX != 0 || moveCamY != 0)
    {
        orienter(moveCamX*sensibility,moveCamY*sensibility);
    }

    mPosition.x = 0-mOrientation.x*20;
    mPosition.y = 0-mOrientation.y*20;
    mPosition.z = 0-mOrientation.z*20;
    mPointCible = mPosition + mOrientation;

}

void Camera::lookAt(glm::mat4 &modelview)
{
    modelview = glm::lookAt(mPosition,mPointCible,mAxeVertical);
}

void Camera::setPointCible(glm::vec3 pointCible)
{
    mOrientation = pointCible - mPosition;
    mOrientation = glm::normalize(mOrientation);

    if(mAxeVertical.x == 1.0)
    {
        mPhi = asin(mOrientation.x);
        mTheta = acos(mOrientation.y/cos(mPhi));

        if(mOrientation.z < 0)
            mTheta *= -1;
    }
    else if(mAxeVertical.y == 1.0)
    {
        mPhi = asin(mOrientation.y);
        mTheta = acos(mOrientation.z/cos(mPhi));

        if(mOrientation.z < 0)
            mTheta *= -1;
    }
    else
    {
        mPhi = asin(mOrientation.x);
        mTheta = acos(mOrientation.z/cos(mPhi));

        if(mOrientation.z < 0)
            mTheta *= -1;
    }
        mPhi = mPhi*180/M_PI;
        mTheta = mTheta*180/M_PI;
}

void Camera::setPosition(glm::vec3 newPosition)
{
    mPosition = newPosition;
    mPointCible = mPosition + mOrientation;
}

float Camera::getSensibility() const
{
    return mSensibility;
}

float Camera::getSpeed() const
{
    return mVitesse;
}

glm::vec3 Camera::getPosition() const
{
    return mPosition;
}

void Camera::setSensibility(float sensibility)
{
    mSensibility = sensibility;
}

void Camera::setSpeed(float speed)
{
    mVitesse = speed;
}
