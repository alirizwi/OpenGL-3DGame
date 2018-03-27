#include "main.h"
#include "timer.h"
#include "shape.h"
#include "canonaim.h"

using namespace std;

GLuint     programID;
GLMatrices Matrices;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Cube ball1,ball2;
Cube rocks[1000], monsters[1000], cannon, gifts[100], health_pts[100];
Cube bomb;
Cuboid water;
Boat boat;
Mast mast;
Triangle tr1;
Canonaim canon_aim;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float acceleration_y = 0.5 ,level = 3;
int health = 100, lives = 3, score = 0;
float RandomNumber(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}
float camera_view[3]={0,90,100};
float target_view[3]={0,90,0};
int rocks_num = 500, monsters_num = 500;
Timer t60(1.0 / 60);
int view = 1, count = 0, count_bomb = 0;
void cameraview();
void camera_change()
{
    view = (view+1)%view_num;
}
int rock_collision(int i)
{
    if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()) && rocks[i].position.z != -1000)
        return 1;
    return 0;
}
int monster_collision(int i)
{
    if(detect_collision(boat.bounding_box(),monsters[i].bounding_box()) && monsters[i].position.z != -1000)
        return 1;
    return 0;
}
int gifts_collision(int i)
{
    if(detect_collision(boat.bounding_box(),gifts[i].bounding_box()) && gifts[i].position.z != -1000)
        return 1;
    return 0;
}
int health_collision(int i)
{
    if(detect_collision(boat.bounding_box(),health_pts[i].bounding_box()) && health_pts[i].position.z != -1000)
        return 1;
    return 0;
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    glm::vec3 eye(camera_view[0], camera_view[1], camera_view[2]);

    glm::vec3 target (target_view[0], target_view[1], target_view[2]);
    glm::vec3 up (0, 0, 1);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    water.draw(VP);
    for(int i = 0 ; i < rocks_num ; i++){
        rocks[i].draw(VP);
    }
    canon_aim.draw(VP);
    boat.draw(VP);
    cannon.draw(VP);
    for(int i = 0 ; i < monsters_num ; i++){
        monsters[i].draw(VP);
    }
    for(int i = 0 ; i < 100 ; i++){
        health_pts[i].draw(VP);
    } 
    for(int i = 0 ; i < 100 ; i++){
        gifts[i].draw(VP);
    }  
    mast.draw(VP);
    bomb.draw(VP);
    //tr1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    char scorput[100];
    int x=0;
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int camera = glfwGetKey(window, GLFW_KEY_C);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);

    sprintf(scorput,"\t\t\t\t\tScore: %d  | Lives: %d |Health: %d ",score, lives, health);
    glfwSetWindowTitle(window,scorput);
    if (right) {
        //printf("YEs1");
        int flag = 0;
        for (int i = 0 ; i < rocks_num ; i++) {
            if (rock_collision(i)) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            cannon.rotation -= 3;
            canon_aim.rotation_z -= 3;
            boat.rotation -= 3;
        }
    }

    if (left) {
        //printf("YEs2");
        int flag = 0;
        for (int i = 0 ; i < rocks_num ; i++) {
            if (rock_collision(i)) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            cannon.rotation += 3;
            canon_aim.rotation_z += 3;
            boat.rotation += 3;
        }
    }
    /*
    if (down) {
        float angle = boat.rotation*M_PI/180.0f;
        boat.position.x += boat.speed*sin(angle);
        boat.position.y -= boat.speed*cos(angle);
        water.position.y = boat.position.y;        
        if (cannon.position.z == level) {
            cannon.position.y = boat.position.y;        
            cannon.position.x = boat.position.x;        
        }
        canon_aim.position.x = boat.position.x;        
        canon_aim.position.y = boat.position.y;        
    }
    
    if (up) {
        float angle = boat.rotation*M_PI/180.0f;
        boat.position.x -= boat.speed*sin(angle);
        boat.position.y += boat.speed*cos(angle);
        water.position.y = boat.position.y;
        if (cannon.position.z == level) {
            cannon.position.y = boat.position.y;        
            cannon.position.x = boat.position.x;        
        }
        canon_aim.position.x = boat.position.x;        
        canon_aim.position.y = boat.position.y;        
    }*/

    if (up) {
        //printf("YEs3");
        float angle = boat.rotation*M_PI/180.0f;
        boat.position.x -= boat.speed*sin(angle);
        boat.position.y += boat.speed*cos(angle);
        int flag = 0;
        score++;
        for (int i = 0 ; i < rocks_num ; i++) {
            if (rock_collision(i)) {
                flag = 1;
                break;
            }
        }
        for (int i = 0 ; i < rocks_num ; i++) {
            if (monster_collision(i)) {
                if(health > 0 && lives>0)
                    health -= 1;
                else{
                    health = 100;
                    lives--;
                }
            }
        }
        for (int i = 0 ; i < 100 ; i++) {
            if (gifts_collision(i)) {
                lives+=1;
                gifts[i].position.x = -1000;
                gifts[i].position.y = -1000;
            }
        }
        for (int i = 0 ; i < 100 ; i++) {
            if (health_collision(i)) {
                health+=10;
                health_pts[i].position.x = -1000;
                health_pts[i].position.y = -1000;
            }
        }
        if (flag == 0) {
            x=1;
            water.position.y = boat.position.y;
            if (cannon.position.z == level) {
                cannon.position.y = boat.position.y;        
                cannon.position.x = boat.position.x;        
            }
            canon_aim.position.x = boat.position.x;        
            canon_aim.position.y = boat.position.y; 
            mast.position.y = boat.position.y;        
            mast.position.x = boat.position.x;
        }
        else {
            boat.position.y -= boat.speed*cos(angle);
            boat.position.x += boat.speed*sin(angle);
        }
    }

    if (down) {
        //printf("YEs4");
        score++;
        float angle = boat.rotation*M_PI/180.0f;
        boat.position.x += boat.speed*sin(angle);
        boat.position.y -= boat.speed*cos(angle);
        int flag = 0;
        for (int i = 0 ; i < rocks_num ; i++) {
            if (rock_collision(i)) {
                flag = 1;
                break;
            }
            if (monster_collision(i)) {
                if(health > 0 && lives>0)
                    health -= 1;
                else{
                    health = 100;
                    lives--;
                }
            }
        }
        for (int i = 0 ; i < 100 ; i++) {
            if (gifts_collision(i)) {
                lives+=1;
                gifts[i].position.x = -1000;
                gifts[i].position.y = -1000;
            }
        }
        for (int i = 0 ; i < 100 ; i++) {
            if (health_collision(i)) {
                health+=10;
                health_pts[i].position.x = -1000;
                health_pts[i].position.y = -1000;
            }
        }
        if (flag == 0) {
            x=1;
            water.position.y = boat.position.y;
            if (cannon.position.z == level) {
                cannon.position.y = boat.position.y;        
                cannon.position.x = boat.position.x;        
            }
            canon_aim.position.x = boat.position.x;        
            canon_aim.position.y = boat.position.y; 
            mast.position.y = boat.position.y;        
            mast.position.x = boat.position.x;
        }
        else {
            boat.position.y += boat.speed*cos(angle);
            boat.position.x -= boat.speed*sin(angle);
        }
    }
    if (fire && cannon.position.z == boat.position.z && canon_aim.rotation_h > 10) {
        //printf("YEs5");
        score++;
        cannon.launch_speed_y = 10 * cos(canon_aim.rotation_h*M_PI/180) * cos(canon_aim.rotation_z*M_PI/180);
        cannon.launch_speed_x = -10 * cos(canon_aim.rotation_h*M_PI/180) * sin(canon_aim.rotation_z*M_PI/180);
        cannon.launch_speed = 10 * sin(canon_aim.rotation_h*M_PI/180);
    }
    if (camera && count > 30) {
        //printf("YEs6");
        camera_change();
        count = 0;
    }
    if (jump && boat.position.z == level) {
        //printf("YEs7");
        cannon.launch_speed = 6;
        canon_aim.launch_speed = 6;
        boat.launch_speed = 6;
    }
}

void tick_elements() {
    //ball1.tick();

    if(lives == 0)
    {
        printf("Game Over\n");
        printf("Score: %d  | Lives: %d |Health: %d ",score, lives, health);
        exit(0);
    }
    camera_rotation_angle += 1;
    boat.tick();
    cannon.position.x += cannon.launch_speed_x;
    cannon.position.y += cannon.launch_speed_y;
    cannon.position.z += cannon.launch_speed;
    int x=0;
    canon_aim.position.z += canon_aim.launch_speed;
    boat.position.z += boat.launch_speed;
    if (boat.position.z > level || cannon.position.z > level) {
        x=1;
        cannon.launch_speed -= acceleration_y;
        canon_aim.launch_speed -= acceleration_y;
        boat.launch_speed -= acceleration_y;
        //printf("YEs0");
    }

    if (boat.position.z <= level) {
        canon_aim.launch_speed = 0;
        canon_aim.position.z = level;
        boat.launch_speed = 0;
        boat.position.z = level;
        //printf("YEs");
}

    if (cannon.position.z <= level) {
        cannon.position.x = boat.position.x;
        cannon.position.y = boat.position.y;
        cannon.position.z = level;
        cannon.launch_speed_x = 0;
        cannon.launch_speed_y = 0;
        cannon.launch_speed = 0;
        if (cannon.position.x != boat.position.x && cannon.position.y != boat.position.y) {
            bomb.position.y = cannon.position.y;
            bomb.position.x = cannon.position.x;
            //printf("YEs1");
        }
    }
    for(int i = 0 ; i < monsters_num ; i++){
        float angle = RandomNumber(-100,100);
        //float angle = monsters[i].rotation*M_PI/180.0f;
        monsters[i].position.x += monsters[i].speed;
        monsters[i].position.y += monsters[i].speed;
        monsters[i].rotation = 0;
        monsters[i].tick();
        //printf("YEs2");
    }
    cameraview();
    count ++;
    mast.position.z = boat.position.z;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {

    //ball1       = Ball(0, 0, COLOR_RED);
    //ball2       = Ball(2, 2, COLOR_GREEN);
    water = Cuboid(0, 0, 32767, 32767, 32767, COLOR_BLUE);
    water.position.z -= 32767;
    water.speed = 0.2;
    boat = Boat(0, 0, 3.0f, 6.0f, 2.0f, COLOR_RED);
    boat.position.z += level;
    for (int i = 0 ; i < rocks_num ; i++) {
        float x = RandomNumber(-2000,2000);
        float y = RandomNumber(-2000,2000);
        rocks[i] = Cube(x , y, 1.0f, COLOR_BLACK);
        rocks[i].speed = 1;
        rocks[i].size = RandomNumber(5,15);
        rocks[i].position.z += 1;
    }
    for (int i = 0 ; i < monsters_num ; i++) {
        float x = RandomNumber(-2000,2000);
        float y = RandomNumber(-2000,2000);
        monsters[i] = Cube(x , y, 1.0f, COLOR_RED);
        monsters[i].speed = RandomNumber(-0.8,0.8);
        monsters[i].size = RandomNumber(5,15);
        monsters[i].position.z += 1;
    }
    for (int i = 0 ; i < 100 ; i++) {
        float x = RandomNumber(-2000,2000);
        float y = RandomNumber(-2000,2000);
        gifts[i] = Cube(x , y, 1.0f, COLOR_BOAT1);
        gifts[i].speed = 1;
        gifts[i].size = RandomNumber(5,8);
        gifts[i].position.z += 1;
    }
    for (int i = 0 ; i < 100 ; i++) {
        float x = RandomNumber(-2000,2000);
        float y = RandomNumber(-2000,2000);
        health_pts[i] = Cube(x , y, 1.0f, COLOR_BOAT3);
        health_pts[i].speed = 1;
        health_pts[i].size = RandomNumber(5,8);
        health_pts[i].position.z += 1;
    }
    canon_aim = Canonaim(0, 0, 1.0f, 10.0f, COLOR_RED);
    canon_aim.position.z += level;
    cannon = Cube(boat.position.x, boat.position.y, 1.0f, COLOR_RED);
    cannon.position.z += level;
    bomb = Cube(-1000,-1000, 1.0f, COLOR_GREEN);
    bomb.size = 25;
    bomb.position.z -= bomb.size/2;
    mast = Mast(boat.position.x,boat.position.y,1,20,COLOR_BLACK);
    mast.position.z += level;
    //tr1       = Triangle(0, 0,0,0, COLOR_RED);


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int height = 600;
    int width  = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    float x = (a.width+b.width);
    return (sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)) < x);
}
void camera_helicopter(float x, float y){
    if(view == 0) {
        target_view[0] = boat.position.x+(x-300)/2;
        //print(target_view[0]);
        if(y<=300){
            target_view[1] = boat.position.y+(300-y)/2;
        }
    }
}

void cannon_position(float x, float y) {
    if (view != 0) {
        //printf(view);
        canon_aim.rotation_z = boat.rotation-((3*x/5) - 180);
        canon_aim.rotation_h = -(3*y/20) + 90;
    }
}
void reset_screen() {
    float right  = screen_center_x + 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float top    = screen_center_y + 4 / screen_zoom;
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(45.0f, 1.0f, 46.0f, 500.0f);
}
void cameraview(){
    float angle = (boat.rotation)*(pi/180);
    if(view == 0) { //helicopter-view
        camera_view[2] = 46;
    }
    else if(view == 1){ //follow-cam
        camera_view[0] = boat.position.x+100*sin(angle);
        camera_view[1] = boat.position.y-100*cos(angle);
        camera_view[2] = 46;

        target_view[0] = boat.position.x;
        target_view[1] = boat.position.y;
        target_view[2] = boat.position.z;
    } 
    else if(view==2){ //top-view short
        camera_view[0] = boat.position.x+1;
        camera_view[1] = boat.position.y;
        camera_view[2] = boat.position.z+300;

        target_view[0] = boat.position.x;
        target_view[1] = boat.position.y;
        target_view[2] = boat.position.z;
    }
    else if(view==3){ // boat view
        camera_view[0] = boat.position.x;
        camera_view[1] = boat.position.y;
        camera_view[2] = 25;

        target_view[0] = boat.position.x-40*sin(angle);
        target_view[1] = boat.position.y+40*cos(angle);
        target_view[2] = boat.position.z+25;
    }
    else if(view==4){ //tower-view
        camera_view[0] = boat.position.x+100;
        camera_view[1] = boat.position.y;
        camera_view[2] = 46;

        target_view[0] = boat.position.x;
        target_view[1] = boat.position.y;
        target_view[2] = boat.position.z;
    }
}