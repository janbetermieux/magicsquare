//
// Created by jan.betermieux on 12/19/20.
//
#include <array>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>

struct Magic_xy{
    int x;
    int y;
};


class MagicSquare {

private:
    std::map<int,Magic_xy> values;
    std::map<int,int> index;

    void mirrorY(){//swap left/right
        for(int y=0;y<this->number;y++) {
            for (int x = 0; x < (this->number-1) / 2; x++) {
                Magic_xy left;
                Magic_xy right;
                left.x = x;
                left.y = y;
                right.x = (this->number - 1) - x;
                right.y = y;
                swapCells(left, right);
            }
        }
    }

    int hashOfCoordinate(Magic_xy *coord){
        int retval=7;
        retval=(retval*1009)+coord->x;
        retval=((retval*1009)+coord->y);
        return retval;
    }

    void removeValueAt(Magic_xy *xy){
        int value=getValueAt(xy);
        values.erase(value);
        int indexval=hashOfCoordinate(xy);
        index.erase(indexval);
    }
    void setValueAt(int value,Magic_xy xy) {
        if(getValueAt(&xy)>0){
            std::cout <<"\nWarning: a value has already been defined for coordinates "<< xy.x<< ","<<xy.y;
        }
        if(index.count(value)>0){
            std::cout <<"\nWarning: a coordinates has already been defined for value "<< value << " : "<< "" <<xy.y;
        }
        values.insert(std::pair<int,Magic_xy>(value,xy));
        setIndexValue(value,&xy);
    }

    void setIndexValue(int value,Magic_xy *xy){
        int indexval=hashOfCoordinate(xy);
        index.insert(std::pair<int,int>(indexval,value));
    }

    int getValueAt(Magic_xy *xy){
        int retval=0;
        int indexVal=hashOfCoordinate(xy);
        if(index.count(indexVal)){
            retval= index.at(indexVal);
        }
        return retval;
    }

    void swapCells(Magic_xy xy1, Magic_xy xy2){
        int valueXFromRow1=getValueAt(&xy1);
        int valueXFromRow2=getValueAt(&xy2);

        removeValueAt(&xy1);
        removeValueAt(&xy2);
        setValueAt(valueXFromRow2,xy1);
        setValueAt(valueXFromRow1,xy2);
    }

    void swapRows(int row1, int row2){
        Magic_xy xy1,xy2;
        for(int x=0;x< this->number;x++){
            xy1.x=x;
            xy1.y=row1;
            xy2.x=x;
            xy2.y=row2;

            swapCells(xy1,xy2);
        }
    }

    void swapCols(int col1, int col2){
        Magic_xy xy1,xy2;
        for(int y=0;y< this->number;y++){
            xy1.x=col1;
            xy1.y=y;
            xy2.x=col2;
            xy2.y=y;

            swapCells(xy1,xy2);

        }
    }

    void swapLeftSquareCells(int row1, int row2, int col, int size){
        int count, r1, r2;
        int number_cells;
        number_cells = ( size/2 );
        Magic_xy xy_A, xy_D;

        for( count=0; count<number_cells; count++){
            // swap squareA top left with squareB top left
            r1 = row1 + count;
            r2 = row2 + count;
            xy_A.y=r1;xy_A.x=col;
            xy_D.y=r2;xy_D.x=col;
            swapCells(xy_A, xy_D);

            // swap square A center with squareB center
//            r1 = row1 + number_cells;
//            r2 = row2 + number_cells;
//            xy_A.y=r1;xy_A.x=col+number_cells;
//            xy_D.y=r2;xy_D.x=col+number_cells;
//            swapCells(xy_A, xy_D);

            // swap squareA bottom left with squareB top left
            r1 = row1 + size - 1 - count;
            r2 = row2 + size - 1 - count;
            xy_A.y=r1;xy_A.x=col;
            xy_D.y=r2;xy_D.x=col;
            swapCells(xy_A, xy_D);

        }



    }

    /**
     *
     * @param startpos top left corner of "L" (where the last value will be at)
     * @param offset start value, top right corner of L
     */
    void fill_L(Magic_xy *startpos,int offset){
        Magic_xy xy1;
        xy1.x=startpos->x+1;
        xy1.y=startpos->y;
        setValueAt(offset,xy1);
        Magic_xy xy2;
        xy2.x=startpos->x;
        xy2.y=startpos->y+1;
        setValueAt((offset+1),xy2);
        Magic_xy xy3;
        xy3.x=startpos->x+1;
        xy3.y=startpos->y+1;
        setValueAt((offset+2),xy3);
        Magic_xy xy4;
        xy4.x=startpos->x;
        xy4.y=startpos->y;
        setValueAt((offset+3),xy4);
    }
    /**
     *
     * @param startpos top left corner of "U"
     * @param offset start value, top left corner of U
     */
    void fill_U( Magic_xy *startpos,int offset){
        Magic_xy xy1;
        xy1.x=startpos->x;
        xy1.y=startpos->y;
        setValueAt(offset,xy1);
        Magic_xy xy2;
        xy2.x=startpos->x;
        xy2.y=startpos->y+1;
        setValueAt((offset+1),xy2);
        Magic_xy xy3;
        xy3.x=startpos->x+1;
        xy3.y=startpos->y+1;
        setValueAt((offset+2),xy3);
        Magic_xy xy4;
        xy4.x=startpos->x+1;
        xy4.y=startpos->y;
        setValueAt((offset+3),xy4);
    }

    /**
    *
    * @param startpos top left corner of "X"
    * @param offset start value, top left corner of X
    */
    void fill_X(Magic_xy *startpos,int offset){
        Magic_xy xy1;
        xy1.x=startpos->x;
        xy1.y=startpos->y;
        setValueAt(offset,xy1);
        Magic_xy xy2;
        xy2.x=startpos->x+1;
        xy2.y=startpos->y+1;
        setValueAt((offset+1),xy2);
        Magic_xy xy3;
        xy3.x=startpos->x;
        xy3.y=startpos->y+1;
        setValueAt((offset+2),xy3);
        Magic_xy xy4;
        xy4.x=startpos->x+1;
        xy4.y=startpos->y;
        setValueAt((offset+3),xy4);
    }
    void merge(MagicSquare *src, Magic_xy *startpos,int offset){
        Magic_xy xysrc;

        for (int i = 0; i < src->number; i++) {
            for (int j = 0; j < src->number; j++) {
                xysrc.x=i;
                xysrc.y=j;
                int newvalue=src->getValueAt(&xysrc)+offset;
                Magic_xy newyx;
                newyx.x=i+startpos->x;
                newyx.y=j+startpos->y;
                setValueAt(newvalue,newyx);
            }
        }
    }
public:
    int number = 0; // eg 3 or 4 or 6
    int arrSize = 0;
    void resetValues(){
        values.clear();
        index.clear();
    }

    void populate(int pNumber) {
        //set basics
        this->number = pNumber;
        this->arrSize = pNumber*pNumber;
        resetValues();
        //oneven
        //   4 9 2    168
        //   3 5 7    924
        //   8 1 6    573
        Magic_xy nextxy;

        if (this->number % 2 == 1) { //odd
            nextxy.x=0;
            nextxy.y=0;
            for (int i = 1; i <= arrSize; i++) {
                Magic_xy xy = nextxy;
                setValueAt(i,xy);
                //next position
                nextxy.x = xy.x + 1;
                nextxy.y= xy.y + 1;
                nextxy.x=  nextxy.x % this->number;//eg 3 becomes 0
                nextxy.y= nextxy.y % this->number;//eg 2 becomes 2

                if (getValueAt(&nextxy) != 0) {
                    nextxy.x = xy.x;
                    nextxy.y= xy.y + 2;
                    nextxy.x =  nextxy.x % this->number;
                    nextxy.y = nextxy.y % this->number;
                }
            }
        } else if (this->number % 4 == 0) { //double even
            //|--||--||--|
            //-||--||--||-
            nextxy.x=0;
            nextxy.y=0;

            Magic_xy nextxy2;
            nextxy2.x=number - 1;
            nextxy2.y=number - 1;

            for (int i = 1; i <= arrSize / 2; i++) {
                Magic_xy xy;
                xy.x=nextxy.x;
                xy.y=nextxy.y;

                Magic_xy xy2;
                xy2.x=nextxy2.x;
                xy2.y=nextxy2.y;

                int modval = xy.x % 4;
                int mirrorvalue = arrSize - (i - 1);
                int coltype=(xy.y % 2); //works with 2 but nicer with 4?
//                int coltype=(xy.y % 4);
                if (coltype == 0||coltype==3) {
                    //|--||--||--|
                    //012301230123
                    if (modval == 0 || modval == 3) {
                        setValueAt(i,xy);
                        setValueAt(mirrorvalue,xy2);
                    } else {
                        setValueAt(i,xy2);
                        setValueAt(mirrorvalue,xy);
                    }
                } else {
                    //-||--||--||-
                    //012301230123
                    if (modval == 1 || modval == 2) {
                        setValueAt(i,xy);
                        setValueAt(mirrorvalue,xy2);
                    } else {
                        setValueAt(i,xy2);
                        setValueAt(mirrorvalue,xy);
                    }
                }

                //next position
                nextxy.x++;
                if (nextxy.x >= number) {
                    nextxy.x = 0;
                    nextxy.y++;
                }

                nextxy2.x = (number - 1) - nextxy.x;
                nextxy2.y = (number - 1) - nextxy.y;

            }
        } else {//number is 6,10,14,18,22,26,30,34,38,42 etc; x/2 is odd n=4m+2
            // LUX Method (or /_\ |_| X , make 2x2 squares and LUX them up
            int m = (number-2)/4;
            int doublerowscolumns = number/2;
            MagicSquare oddsquare;
            oddsquare.populate(doublerowscolumns);

            int doublerowsL=(m+1)*2;
            int doublerowsU=doublerowsL+2;
            int doubleRowsX=doublerowsU+(2*(m-1));
            Magic_xy startposxy, oddposition;
            startposxy.x=0;
            startposxy.y=0;
            int offset;
            for(int j =0; j<number;j+=2){ //rows
                for(int i =0; i<number;i+=2){ //columns
                    startposxy.x=i;
                    startposxy.y=j;
                    oddposition.x=i/2;
                    oddposition.y=j/2;
                    offset = oddsquare.getValueAt(&oddposition);
                    offset = ((offset*4) -3);
                    if(j<doublerowsL) {
                        fill_L(&startposxy, offset);
                    }else if(j<doublerowsU){
                        fill_U(&startposxy, offset);
                    }else{
                        fill_X(&startposxy,offset);
                    }

                }
            }

        }

    }



    Magic_xy getLocation(int value) {
        Magic_xy retval=this->values.at(value);
        return retval;
    }

    std::string toString() {
        std::string retval="\n";
        int sumy[this->number];
        for (int i = 0; i < this->number; i++)sumy[i] = 0;

        for (int y = 0; y < this->number; y++) {
            int sumx = 0;
            for (int x = 0; x < this->number; x++) {
                Magic_xy xy;
                xy.x=x;
                xy.y=y;
                int value=getValueAt(&xy);
                sumx += value;
                sumy[x] = sumy[x] + value;
                retval= retval + std::to_string(value) + "\t\t";
            }
            retval= retval +" [" + std::to_string(sumx) + "]\n";
            retval= retval +  "\n";

        }

        for (int i = 0; i < this->number; i++) {
            retval= retval + "["  + std::to_string(sumy[i]) + "] \t";
        }
        retval= retval +  "\n";
        return retval;
    }

};




