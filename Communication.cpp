//
// Created by emre on 03.12.2016.
//

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <zconf.h>
#include "Communication.h"
#include <fstream>
#include <string>
#include <vector>

int buttonFlag = 0;

#define END_CHAR '}'

using namespace std;

Communication::Communication(string str, SerialPort::BaudRate baud) {

    port = new SerialPort(str,baud);

    communicationReady = false;
    checkConnection();
    makeHandShake();
    buttonState = 0;

    readFile("./son.txt");
}

void Communication::makeHandShake() {

    char ch;
    cout << "Handshake starting" << endl;
    do {
        write('I');
        port->wait(100);
        port->read(&ch);
    }while(ch != 'O');
    cout << "Handshake succesfull" << endl;
    communicationReady = true;
}

bool Communication::write(char *msg) {
    return port->write(msg);
}

bool Communication::write(char ch) {
    return port->write(ch);
}

void Communication::checkConnection() {
    while( !( port->open()) ){
        //sleep(1);
        cout << "Open failed" << endl;
        cout << "Trying to connect again " << endl;
    }
    while( !( port->prepare()) ){
        //sleep(1);
        cout << "Prepare failed" << endl;
        cout << "Trying to connect again " << endl;
    }
}

bool Communication::checkButtonState() {
    if(!communicationReady)
        return false;
    write('G');
    char temp;

    port->read(&temp);

    if (temp == 'P' && buttonState == 0)
    {
        buttonState =1;
        return true;
    }
    else
        return false;
}


bool Communication::moveRight(int step) {

    write('D');
    sendStep(step);
    receiveACK();
    return true;

}

bool Communication::moveLeft(int step) {

    write('A');
    sendStep(step);
    receiveACK();
    return true;

}

bool Communication::moveUp(int step){

    write('W');
    sendStep(step);
    receiveACK();
    return true;
}

bool Communication::moveDown(int step) {

    write('S');
    sendStep(step);
    receiveACK();
    return true;
}

void Communication::sendStep(int step) {
    char temp;
    char str[10];

    port->read(&temp);
    sprintf(str,"%d",step);
    write(str);
}

void Communication::endConnection(){
    cout << "F" << endl;
    write('F');
}

void Communication::restartButtonFLag() {
    buttonState = 0;
}

void Communication::readFile(string Filename)
{
    ifstream myfile (Filename.c_str());

    if (myfile.is_open())
    {
        int i;

        while(myfile >> i)
        {
            v.push_back(i);
        }

        moveRight(v[0]);
        moveUp(v[1]);
        port->write('B');
    }

    else
    {

        port->write('B');


    }
    char temp;
    port->read(&temp);
    while(temp!='K'){
        port->read(&temp);
    }
    cout<<"temp"<<temp<<endl;
    myfile.close();
}

void Communication::saveToFile(string Filename, int xPosition, int yPosition) {

    ofstream myfile(Filename.c_str());

    if (!myfile.is_open())
    {
        cerr<<"could not open file for write"<<endl;
        return;
    }

    myfile<< xPosition << " "<< yPosition;

    myfile.close();
}

int Communication::getRightLeft() const {
    return rightLeft;
}

void Communication::setRightLeft(int rightLeft) {
    this->rightLeft = rightLeft;
}

int Communication::getUpDown() const {
    return upDown;
}

void Communication::setUpDown(int upDown) {
    this->upDown = upDown;
}

bool Communication::receiveACK(){
    char temp;
    do{
       port->read(&temp);
    }while(temp != 'L');
}

