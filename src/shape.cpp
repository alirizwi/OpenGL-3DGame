#include "shape.h"
#include "main.h"

Cube::Cube(float x, float y, float l, color_t color) {
    this->launch_speed = 0;
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    speed = 1;
    size = 1;
    static const GLfloat vertex_buffer_data[] = {
        -l,-l,-l, // trilngle 1 : begin
        -l,-l, l,
        -l, l, l, // trilngle 1 : end
        l, l,-l, // trilngle 2 : begin
        -l,-l,-l,
        -l, l,-l, // trilngle 2 : end
        l,-l, l,
        -l,-l,-l,
        l,-l,-l,
        l, l,-l,
        l,-l,-l,
        -l,-l,-l,
        -l,-l,-l,
        -l, l, l,
        -l, l,-l,
        l,-l, l,
        -l,-l, l,
        -l,-l,-l,
        -l, l, l,
        -l,-l, l,
        l,-l, l,
        l, l, l,
        l,-l,-l,
        l, l,-l,
        l,-l,-l,
        l, l, l,
        l,-l, l,
        l, l, l,
        l, l,-l,
        -l, l,-l,
        l, l, l,
        -l, l,-l,
        -l, l, l,
        l, l, l,
        -l, l, l,
        l,-l, l
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale    = glm::scale(glm::vec3(this->size, this->size, this->size));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cube::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cube::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Cube::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->size, this->size };
    return bbox;
}

Cuboid::Cuboid(float x, float y, float l, float b, float h, color_t color) {
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        -l,-b,-h, // trilngle 1 : begin
        -l,-b, h,
        -l, b, h, // trilngle 1 : end
        l, b,-h, // trilngle 2 : begin
        -l,-b,-h,
        -l, b,-h, // trilngle 2 : end
        l,-b, h,
        -l,-b,-h,
        l,-b,-h,
        l, b,-h,
        l,-b,-h,
        -l,-b,-h,
        -l,-b,-h,
        -l, b, h,
        -l, b,-h,
        l,-b, h,
        -l,-b, h,
        -l,-b,-h,
        -l, b, h,
        -l,-b, h,
        l,-b, h,
        l, b, h,
        l,-b,-h,
        l, b,-h,
        l,-b,-h,
        l, b, h,
        l,-b, h,
        l, b, h,
        l, b,-h,
        -l, b,-h,
        l, b, h,
        -l, b,-h,
        -l, b, h,
        l, b, h,
        -l, b, h,
        l,-b, h
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cuboid::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cuboid::tick() {
    this->rotation += speed;
}

bounding_box_t Cuboid::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

Triangle::Triangle(float x, float y, float l, float b, color_t color) {
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    speed = 0.05;
    speedy = 0;
    acceleration = 0.01;
    static const GLfloat vertex_buffer_data[] = {
        l,  b, 0, // vertex 1
        l,  b, 0, // vertex 2
        l,  b, 0, // vertex 3

    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Triangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Triangle::tick() {
    this->position.x -= speed;
    this->speedy -= acceleration;
    // this->position.y -= speed;
}

bounding_box_t Triangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

Boat::Boat(float x, float y, float l, float b, float h, color_t color) {
    this->rotation = 0;
    this->launch_speed = 0;
    this->position = glm::vec3(x, y, 0);
    speed = 1.0;
    static const GLfloat vertex_buffer_data[] = {
        l,b, h,
        -l,b,-h,
        l,b,-h,
        l,b, h,
        -l,b,-h,
        -l,b, h,

        -l, b, h,
        -2*h,-b,-h,
        -l, b,-h,
        -l, b, h,
        -2*h,-b,-h,
        -2*h,-b, h,

        2*h,-b,-h, 
        l, b, h, 
        2*h,-b, h, 
        2*h,-b,-h, 
        l, b, h, 
        l, b,-h, 

         2*h,-b,-h,
        -l, b,-h,
         l, b,-h,
         2*h,-b,-h,
        -l, b,-h,
        -2*h,-b,-h,

        -2*h,-b,-h,
         2*h,-b, h,
        -2*h,-b, h,
        -2*h,-b,-h,
         2*h,-b, h,
         2*h,-b,-h,

         l, b,-h,
        -l, b,-h,
         0.0f,2*b, l,

        l, b, h, 
        l, b,-h, 
        0.0f,2*b, l,

        -l, b, h,
         l, b, h,
         0.0f,2*b, l,

        -l, b,-h,
        -l, b, h,
         0.0f,2*b, l,

    };

    color_t COLOR_BOAT[9] = {COLOR_BOAT1, COLOR_BOAT2, COLOR_BOAT3, COLOR_BOAT4, COLOR_BOAT5, COLOR_BOAT6, COLOR_BOAT7, COLOR_BOAT8, COLOR_BOAT9};
    for(int i=0;i<5;i++){
        this->object[i] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+18*i, COLOR_BOAT[i], GL_FILL);
    }
    for(int i=5;i<9;i++){
        this->object[i] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+9*(i+5), COLOR_BOAT[i], GL_FILL);
    }
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
    draw3DObject(this->object[5]);
    draw3DObject(this->object[6]);
    draw3DObject(this->object[7]);
    draw3DObject(this->object[8]);
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    //return
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 9, 9};
    return bbox;
}

Mast::Mast(float x, float y,float l, float b, color_t color) {
    this->launch_speed = 0;
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    size = 1;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        0,0,18,
        0,0,3,
        -14,0,8,
        l,0,0,
        0,0,b,
        -l,0,0,
        l,l,0,
        0,0,b,
        -l,l,0,
        l,0,0,
        0,0,b,
        l,l,0,
        -l,0,0,
        0,0,b,
        -l,l,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}

void Mast::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale    = glm::scale(glm::vec3(this->size, this->size, this->size));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Mast::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Mast::tick() {
    this->rotation += speed;
}

bounding_box_t Mast::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->size, this->size };
    return bbox;
}