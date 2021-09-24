#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string.h>

#include "Input.h"

#ifndef M_PI
#define M_PI 3.141592658979323846
#endif // M_PI

class Camera
{
public:
    Camera();
    Camera(glm::vec3 position,glm::vec3 pointCible,glm::vec3 axeVertical,float sensibilite, float vitesse);
    ~Camera();

    void orienter(int xRel, int yRel);
    void deplacerFPS(Input const &input);
    void deplacerCHESS(Input const &input, int sensibility);
    void lookAt(glm::mat4 &modelview);
    void setPointCible(glm::vec3 pointCible);
    void setPosition(glm::vec3 newPosition);

    float getSensibility() const;
    float getSpeed() const;
    glm::vec3 getPosition() const;

    void setSensibility(float sensibility);
    void setSpeed(float speed);

private:
    float mPhi;
    float mTheta;
    glm::vec3 mOrientation;
    glm::vec3 mAxeVertical;
    glm::vec3 mDeplacementLateral;
    glm::vec3 mPosition;
    glm::vec3 mPointCible;
    float mSensibility;
    float mVitesse;
};

#endif // CAMERA_H_INCLUDED
