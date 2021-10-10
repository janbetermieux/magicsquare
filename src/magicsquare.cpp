//
// Created by jan.betermieux on 12/19/20.
//

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <magicsquare/matrixcolors.h>
//#include <magicsquare/magicsquare.h>
#include <GL/GLmagicsquare.h>
#include <unistd.h>


float J_PI = 3.14159265358979323846f;

static int startNumber=3;
static float rotatespeed=12.f;
static float anglex=1.f;
static float angley=0.f;
static float anglez=0.f;

static MagicSquare sqi;
static std::vector<Vector3dColored> magicasvector;
static bool pauze=true;
static double previoustime=0.0;
static float zoom=0;

static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

static void doPauze(){
    previoustime=glfwGetTime();
    glfwSetTime(0.0);
}

static void flipPauze(){
    pauze=!pauze;
    if(pauze){
        doPauze();
    }else{
        glfwSetTime(previoustime);
    }
}
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS) {
        std::cout << "PAGEUp" << "\n";
        if(startNumber <= 40) {
            startNumber++;
            sqi.populate(startNumber);
            cout<<sqi.toString()<<"\n";
            magicasvector = getValueVectorLinesFromMagicSquare(&sqi);
        }

    }else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS) {
        std::cout << "PAGEDown" << "\n";
        if(startNumber > 3) {
            startNumber--;
            sqi.populate(startNumber);
            cout<<sqi.toString()<<"\n";
            magicasvector = getValueVectorLinesFromMagicSquare(&sqi);
        }
    }else if(key==GLFW_KEY_RIGHT){
        doPauze();
        angley++;
    } else if(key==GLFW_KEY_LEFT){
        doPauze();
        angley--;
    }else if(key==GLFW_KEY_UP){
        doPauze();
        anglex++;
    } else if(key==GLFW_KEY_DOWN){
        doPauze();
        anglex--;
    }else if(key==GLFW_KEY_SPACE && action == GLFW_PRESS){
        std::cout << "SPACE" << "\n";
        flipPauze();
    }else if(key==GLFW_KEY_R && action == GLFW_PRESS){
        std::cout << "R" << "\n";
        doPauze();
        anglex=0.f;
        angley=0.f;
    }

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        std::cout << "right";

    }
    if(button == GLFW_MOUSE_BUTTON_MIDDLE){
        std::cout << "wheel";
    }
    std::cout.flush();

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    std::cout << "zoom : "<<yoffset << endl;
    std::cout.flush();

    zoom+=(yoffset*0.1);
}

int main(void){

//    int nummers[8]={3,4,5,8,9,11,12,16};

//
//    for (int i=0;i<8;i++){
//        sqi.populate(nummers[i]);
//        std::cout <<  sqi.toString() <<"\n\n";
//    }
    sqi.populate(6);
    std::cout <<  sqi.toString() <<"\n\n";

    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())exit(EXIT_FAILURE);


    window = glfwCreateWindow(800, 800, "3dview", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

//    if (glfwRawMouseMotionSupported())glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetScrollCallback(window,scroll_callback);
    array<color, 4> matrixcolors=getMatrixColors();
    sqi.populate(startNumber);
    std::cout <<  sqi.toString() <<"\n\n";
    magicasvector = getValueVectorLinesFromMagicSquare(&sqi);

    float ratio;
    int width, height;
    while (!glfwWindowShouldClose(window)) {
        float barwidth=0.2f/sqi.arrSize;
        float barwidthd2=barwidth/2;

            //* Render here //*

            glfwGetFramebufferSize(window, &width, &height);
            ratio = width / (float) height;
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if(!pauze){//calculate new anglex
                anglex= (float) glfwGetTime() * rotatespeed;
            }
            if (anglex >= 0) {
                glRotatef(anglex, 1.f, 0.f, 0.f);
                glRotatef(angley, 0.f, 1.f, 0.f);
            }
            if(zoom!=0){
                glTranslatef(0,0,-zoom);
            }

            glBegin(GL_LINE_LOOP);

            for (auto i = magicasvector.begin(); i != magicasvector.end(); ++i){
                glColor3f( i->red, i->green, i->blue);
                glVertex3f(i->x, i->y, i->z);
            }
            glEnd();


            for (auto i = magicasvector.begin(); i != magicasvector.end(); ++i){
                glBegin(GL_POLYGON);
                glColor3f( i->red, i->green, i->blue);
                //onderste vierkant
                glVertex3f(i->x-barwidth, i->y-barwidth, 0); //linksboven
                glVertex3f(i->x+barwidth, i->y-barwidth, 0); //rechtsboven
                glVertex3f(i->x+barwidth, i->y+barwidth, 0);
                glVertex3f(i->x-barwidth, i->y+barwidth, 0); //linksonder
                glEnd();

                //            //bovenste vierkant
                glBegin(GL_POLYGON);
                glVertex3f(i->x-barwidthd2, i->y+barwidthd2, i->z);
                glVertex3f(i->x+barwidthd2, i->y+barwidthd2, i->z);
                glVertex3f(i->x+barwidthd2, i->y-barwidthd2, i->z);
                glVertex3f(i->x-barwidthd2, i->y-barwidthd2,i->z);
                glVertex3f(i->x, i->y, i->z);
                glEnd();

            }



        //end gl
        //* Swap front and back buffers //*
        glfwSwapBuffers(window);

        //* Poll for and process events //*
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
