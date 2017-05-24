#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>
#include <unistd.h>
#include "Communication.h"
using namespace std;

class algorithm
{
    public:
        algorithm();
        virtual ~algorithm();

        void setSteps(int stepsValue);
        int getSteps()const;

        void setXlimit(int xlimitValue);
        int getXlimit()const;

        void setYlimit(int ylimitValue);
        int getYlimit()const;

        void setXbase(int xbaseValue);
        int getXbase()const;

        void setYbase(int ybaseValue);
        int getYbase()const;

        void setXcenter(int xcenterValue);
        int getXcenter()const;

        void setYcenter(int ycenterValue);
        int getYcenter()const;

        void setSleeptime(int sleeptimeValue);
        int getSleeptime()const;

        void setCounter(int countValue);
        int getCounter()const;

        void setX(int xPosition);
        int getX()const;

        void setY(int xPosition);
        int getY()const;

        void setPathPlan(int path);
        int getPathPlan(int index)const;

        void drawPath();// vector pathini doldurur
        bool Continue(Communication *com);
        /*Continue
        **moveSide:
        **RIGHT=0
        **LEFT=1
        **UP=2
        **DOWN=3
        */
        void Continue(Communication *com,int moveSide,int step);

    protected:

    private:
            int steps;//    300 //step boyutu icin kameranin görüs alani
            int xlimit; // 810
            int ylimit; // 650
            int xbase; // 50
            int ybase; // 50
            int xcenter;// 450
            int ycenter;// 450
            int sleeptime;// 250
            int counter;
            int x;//x coordinate
            int y;//y coordinate
            vector<int> pathPlan;

};

#endif // ALGORITHM_H
