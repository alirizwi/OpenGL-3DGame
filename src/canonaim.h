#include "main.h"

#ifndef CANONAIM_H
#define CANONAIM_H


class Canonaim {
public:
    glm::vec3 position;
    Canonaim() {}
    Canonaim(float x, float y, float l, float b, color_t color);
    void set_position(float x, float y);
    void tick();
    void draw(glm::mat4 VP);
    double speed;
    float launch_speed;
    float rotation_h;
    float rotation_z;
private:
    VAO *object;
};

#endif // CANONAIM_H
