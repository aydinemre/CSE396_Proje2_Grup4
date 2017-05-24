#include "algorithm.h"
#include <iostream>
#include <cstdio>
#include <stdlib.h>
using namespace std;

const int RIGHT=0;
const int LEFT=1;
const int UP=2;
const int DOWN=3;

algorithm::algorithm()
{
    setSteps(90);//   //step boyutu icin kameranin g�r�s alani
    setXlimit(950); // 810
    setYlimit(800); // 650
    setXbase(0); // 50
    setYbase(0); // 50
    setXcenter(475);// 450
    setYcenter(400);// 450
    setSleeptime(10000);// 250
    setCounter(0);
    drawPath();

}
algorithm::~algorithm()
{
    //dtor
}

/*setter for steps
*/
void algorithm::setSteps(int stepsValue){
    steps=stepsValue;
}

/*getter for cameraofview
*/
int algorithm::getSteps()const{
    return steps;
}

/*setter for xlimit
*/
void algorithm::setXlimit(int xlimitValue){
    xlimit=xlimitValue;
}

/*getter for xlimit
*/
int algorithm::getXlimit()const{
    return xlimit;
}

/*setter for ylimit
*/
void algorithm::setYlimit(int ylimitValue){
    ylimit=ylimitValue;
}

/* getter for xlimit
*/
int algorithm::getYlimit()const{
    return ylimit;
}
/*setter for xbase
*/
void algorithm::setXbase(int xbaseValue){
    xbase=xbaseValue;
}
/*getter for xbase
*/
int algorithm::getXbase()const{
    return xbase;
}
/*setter for ybase
*/
void algorithm::setYbase(int ybaseValue){
    ybase=ybaseValue;
}
/*getter for ybase
*/
int algorithm::getYbase()const{
    return ybase;
}
/* setter for xcenter
*/
void algorithm::setXcenter(int xcenterValue){
    xcenter=xcenterValue;
}
/*getter for xcenter
*/
int algorithm::getXcenter()const{
    return xcenter;
}
/*setter for ycenter
*/
void algorithm::setYcenter(int ycenterValue){
    ycenter=ycenterValue;
}
/*getter for ycenter
*/
int algorithm::getYcenter()const{
    return ycenter;
}
/*setter for sleeptime
*/
void algorithm::setSleeptime(int sleeptimeValue){
    sleeptime=sleeptimeValue;
}
/*getter for sleeptime
*/
int algorithm::getSleeptime()const{
    return sleeptime;
}
/*setter counter
*/
void algorithm::setCounter(int countValue){
    counter=countValue;
}
/*getter counter
*/
int algorithm::getCounter()const{
    return counter;
}
/*setter x
*/
void algorithm::setX(int xPosition){
    x=xPosition;
}
/*getter x
*/
int algorithm::getX()const{
    return x;
}
/*setter y
*/
void algorithm::setY(int yPosition){
    y=yPosition;
}
/*getter y
*/
int algorithm::getY()const{
    return y;
}
/*setter for pathPlan
*/
void algorithm::setPathPlan(int path){
    pathPlan.push_back(path);
}
/*getter pathPlan
*/
int algorithm::getPathPlan(int index)const{
    return pathPlan[index];
}
/*
*/
void algorithm::drawPath(){// vector pathini doldurur

    setX(getXcenter());//x koordinate rightleft
    setY(getYcenter());//y koordinate upDown
    int skipcount=0;// travers sayisi
    int left=1;//left
    int down=2;//down
    int right=2;//right
    int up=2;//up
    int i;
    int check=0;

        while(1){//icden disa kare tarama
            if((y-steps)>ybase){
                y -=steps;
                setPathPlan(UP);//up instruction
              //  cout<<"UP  y= "<<y<<endl;
            }
            else if(x>=xlimit  && y>=ylimit ){
              //  cout << "icten disa bitti" << endl;
                break;
            }
            else{
                y=ybase;
              //  cout<<"UP  else y= "<<y<<endl;
            }
            for(i=0;i<left;++i){
                if((x+steps)<xlimit){
                    x += steps;
                    setPathPlan(LEFT);//left instruction
                //    cout<<"LEFT  x= "<<x<<endl;
                }
                else{
                    x=xlimit;
                //    cout<<"LEFT  else x= "<<x<<endl;
                    break;
                }
            }
            if(x>=xlimit  && y>=ylimit ){
              //  cout << "icten disa bitti" << endl;
                break;
            }
            for(i=0;i<down;++i){
                if((y+steps)<ylimit){
                    y +=steps;
                    setPathPlan(DOWN);//down instruction
               //     cout<<"DOWN  y= "<<y<<endl;
                }
                else{
                    y=ylimit;
                //    cout<<"DOWN  else y= "<<y<<endl;
                    break;
                }
            }
            if(x>=xlimit  && y>=ylimit ){
            //    cout << "icten disa bitti" << endl;
                break;
            }
            for(i=0;i<right;++i){
                if(( x -steps)> xbase){
                    x -= steps;
                    setPathPlan(RIGHT);//right instruction
                 //   cout<<"RIGHT  x= "<<x<<endl;
                }
                else{
                    x=xbase;
                 //   cout<<"RIGHT  else x= "<<x<<endl;
                    break;
                }
            }
            if(x>=xlimit  && y>=ylimit ){
             //   cout << "icten disa bitti" << endl;
                break;
            }
            for(i=0;i<up;++i){
                if((y-steps)>ybase){
                    y -=steps;
                    setPathPlan(UP);//up instruction
                  //  cout<<"UP  y= "<<y<<endl;
                }
                else{
                    y=ybase;
                   // cout<<"UP  else y= "<<y<<endl;
                    break;
                }
            }
            if(x>=xlimit  && y>=ylimit ){
               // cout << "icten disa bitti" << endl;
                break;
            }
            up+=2;
            left+=2;
            right+=2;
            down+=2;
            ++skipcount;
        }
/***************************************************************************************************/
/***************************************************************************************************/
        while(1){//distan ice kare tarama
            if(skipcount==-1){//cikis kosulu
               // cout<<"x= "<<x<<"y= "<<y<<endl;
                break;
            }
            ++check;
            for(i=0; i<right; ++i){
                if(( x -steps)> xbase){
                    x -= steps;
                    setPathPlan(RIGHT);//   right instruction
                  //  cout<<"DRIGHT  x= "<<x<<endl;
                }
                else{
                    x=xbase;
                  //  cout<<"DRIGHT  else x= "<<x<<endl;
                    break;
                }
            }
            for(i=0; i<up; ++i){
                if((y-steps)>ybase){
                    y -=steps;
                    setPathPlan(UP);//up instruction
                   // cout<<"DUP  y= "<<y<<endl;
                }
                else{
                    y=ybase;
                  //  cout<<"DUP  else y= "<<y<<endl;
                    break;
                }

            }
            for(i=0; i<left; ++i){
                if((x+steps)<xlimit){
                    x += steps;
                    setPathPlan(LEFT);//left instruction
                  //  cout<<"DLEFT  x= "<<x<<endl;
                }
                else{
                    x=xlimit;
                  //  cout<<"DLEFT  else x= "<<x<<endl;
                    break;
                }
            }
            for(i=0; i<down; ++i){
               if((y+steps)<ylimit){
                    y +=steps;
                    setPathPlan(DOWN);//down instruction
                  //  cout<<"DDOWN  y= "<<y<<endl;
                }
                else{
                    y=ylimit;
                   // cout<<"DDOWN  else y= "<<y<<endl;
                    break;
                }
            }
            if(check == 1){
                right-=1;
            }
            else{
                right -=2;
            }
            down -= 2;
            up -= 2;
            left -=2;
            --skipcount;
        }
        setX(475);
        setY(400);
}
bool algorithm::Continue(Communication *com){
    if(pathPlan.size()<=counter){
        cout<<"Continue Tarama bitti"<<endl;
        return false;
    }
    else{
        if(getPathPlan(counter)==RIGHT){
            if(abs(x-xbase)<steps && abs(y-ylimit)<steps){
                com->moveRight(abs(x-xbase));
                //usleep(getSleeptime());//sleep
                x-=abs(x-xbase);
                //cout<<"if Right"<<endl;
            }
            else{
                x -= steps;
                com->moveRight(getSteps());
                //usleep(getSleeptime());//sleep
                ++counter;
               // cout<<"else Right"<<endl;
            }
        }
        else if(getPathPlan(counter)==LEFT){
            if(abs(x-xlimit)<steps && abs(y-ybase)<steps){
                com->moveRight(abs(x-xlimit));
                //usleep(getSleeptime());//sleep
                x+=abs(x-xlimit);
                //cout<<"if Left"<<endl;
            }
            else{
                x += steps;
                com->moveLeft(getSteps());
                //usleep(getSleeptime());//sleep
                ++counter;
               // cout<<"else Left"<<endl;
            }
        }
        else if(getPathPlan(counter)==UP){
            if(abs(x-xlimit)<steps && abs(y-ybase)<steps){
                com->moveRight(abs(y-ybase));
                //usleep(getSleeptime());//sleep
                y-=abs(y-ybase);
               // cout<<"if Up"<<endl;
            }
            else{
                y -=steps;
                com->moveUp(getSteps());
                //usleep(getSleeptime());//sleep
                ++counter;
                //cout<<"else Up"<<endl;
            }
        }
        else if(getPathPlan(counter)==DOWN){
            if(abs(x-xbase)<steps && abs(y-ylimit)<steps){
                com->moveRight(abs(y-ylimit));
                //usleep(getSleeptime());//sleep
                y+=abs(y-ylimit);
               // cout<<"if Down"<<endl;
            }
            else{
                y +=steps;
                com->moveDown(getSteps());
                //usleep(getSleeptime());//sleep
                ++counter;
               // cout<<"else Down"<<endl;
            }
        }
        return true;
    }
}
/*Continue
**moveSide:
**RIGHT=0
**LEFT=1
**UP=2
**DOWN=3
*/
void algorithm::Continue(Communication *com,int moveSide,int step){
    if(moveSide==RIGHT){
        x -= step;
        com->moveRight(step);
        //usleep(getSleeptime());//sleep
    }
    else if(moveSide==LEFT){
        x += step;
        com->moveLeft(step);
        //usleep(getSleeptime());//sleep
    }
    else if(moveSide==UP){
        y -=step;
        com->moveUp(step);
        //usleep(getSleeptime());//sleep
    }
    else if(moveSide==DOWN){
        y +=step;
        com->moveDown(step);
        //usleep(getSleeptime());//sleep
    }
}
