//
// Created by jan.betermieux on 12/20/20.
//

#ifndef GLTEST_GLMAGICSQUARE_H
#define GLTEST_GLMAGICSQUARE_H
#include "magicsquare/magicsquare.h"
#include <vector>

struct Vector3dColored {
    float red, green, blue;
    float x, y, z;
};


void GLMagicSquareDraw(int** square, int number){
    int maxval=number*number;
    for (int i=0;i<maxval;i++){

    }
}


std::vector<Vector3dColored> getValueVectorLinesFromMagicSquare(MagicSquare *ms){
    std::vector<Vector3dColored> retval;
    for (int i=1;i<=ms->arrSize;i++){
        Magic_xy xy=ms->getLocation(i);
        Vector3dColored vectorci;
        /*
        vectorci.x=((float)xy.x/(float)ms->arrSize);
        vectorci.y=((float)xy.y/(float)ms->arrSize);
        vectorci.z=(float)i/(float)ms->arrSize;*/
        vectorci.x=((ms->number/2+(float)xy.x)/(ms->number*2.f))-0.25;
        vectorci.y=((ms->number/2-(float)xy.y)/(ms->number*2.f));
        vectorci.z=(float)i/(float)ms->arrSize;

        vectorci.red=(i+(i*xy.x))/ms->arrSize;if(vectorci.red<0.4)vectorci.red=0.4;
        vectorci.green=(i+(i*xy.y))/ms->arrSize;if(vectorci.green<0.4)vectorci.green=0.4;
        vectorci.blue=(i+(i*(xy.x+xy.y)))/ms->arrSize;if(vectorci.blue<0.4)vectorci.blue=0.4;

        retval.push_back(vectorci);
    }
    return retval;
}
#endif //GLTEST_GLMAGICSQUARE_H
