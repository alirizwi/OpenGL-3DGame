#include "main.h"

#ifndef SHAPE_H
#define SHAPE_H


class Cube {
public:
    glm::vec3 position;
    Cube() {}
    Cube(float x, float y, float l, color_t color);
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float size;
    float rotation;
    double speed;
    float launch_speed_y;
    float launch_speed_x;
    float launch_speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class Cuboid {
public:
    glm::vec3 position;
    Cuboid() {}
    Cuboid(float x, float y, float l, float b, float h, color_t color);
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speed;
    float rotation;
    bounding_box_t bounding_box();
private:
    VAO *object;
};


class Triangle {
public:
    glm::vec3 position;
    Triangle() {}
    Triangle(float x, float y, float l, float b, color_t color);
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float rotation;
    double speedy;
    double speed;
    double acceleration;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class Boat {
public:
    glm::vec3 position;
    Boat() {}
    Boat(float x, float y, float l, float b, float h, color_t color);
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float rotation;
    float launch_speed;
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object[9];
};

class Mast {
public:
    glm::vec3 position;
    Mast() {}
    Mast(float x, float y,float l, float b, color_t color);
    float rotation;
    float size;
    float launch_speed;
    float launch_speed_x;
    float launch_speed_y;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SHAPE_H
