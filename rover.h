#ifndef ROVER_H
#define ROVER_H
#include <iostream> 
#include <iomanip> 
#include <cstdlib> 
#include <stdlib.h>
#include <vector> 
#include <ctime> 
#include <string>
#include <windows.h>
using namespace std;

class Rover{
    private:
        int posX;
        int posY;
        int coordX;
        int coordY;
        int score;
        int steps;
        int gold;
        int target;
        int sequence;
        int heading;
        bool trapped;
        bool quitted;
        bool win;
        vector <vector<char> > map;

    public:
        enum direction{Unknown = -1, Left = 0, Up = 1, Right = 2, Down = 3};
        Rover(vector <vector<char> > map_);
        void setPosition(int x, int y);
        void setColor(int color);
        void copyMap(vector <vector<char> > map_);
        void showPosition();
        void executeInstruction(string command);
        void setTarget(int target_);
        void addSequence();
        bool status();
        void clearInfo();
        void displayInfo();
        int getScore();
};

#endif