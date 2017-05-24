/*--------------- User Interface for Finding Joe ---------------
    |  Author: Semih Bertug Benim
    |  Created on 25.04.2017
    |  ID: 111044073
    |  Lecture: Project II
 *-------------------------------------------------------------------*/

#ifndef COOR_H_
#define COOR_H_

/**
 * it has no getter for x and y, get this values with dot. operator
 */
class Coor {
public:
    /**
     * default constructor,set x-y to 0-0
     */
    Coor() {
        x = 0;
        y = 0;
    }

    /**
     * two parameter constructor
     * @param x_i x coor value
     * @param y_i y coor value
     */
    Coor(int x_i, int y_i) {
        x = x_i;
        y = y_i;
    }

    /**
     * coppy constructor
     */
    Coor(const Coor & copy) :
            x(copy.x), y(copy.y) {
    }

    /**
     * assignment operator
     */
    Coor& operator=(const Coor &rightHandSide)
    {
        x=rightHandSide.x;
        y=rightHandSide.y;
        return *this;
    }

    inline bool operator==(const Coor & comp)const{
        if(x==comp.x && y==comp.y)
        {
            return true;
        }
        return false;
    }

    inline bool operator!=(const Coor & comp)const{
        if(x==comp.x && y==comp.y)
        {
            return false;
        }
        return true;
    }

    inline int getX() const {
        return x;
    }
    inline int getY() const {
        return y;
    }

    int x;/* x coor value*/
    int y;/* y coor value*/
};


#endif /* COOR_H_ */
