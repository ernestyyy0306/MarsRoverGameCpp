#ifndef MAP_H
#define MAP_H
#include <iostream> 
#include <iomanip> 
#include <cstdlib> 
#include <stdlib.h>
#include <string> 
#include <vector> 
#include <ctime> 
#include <windows.h>
using namespace std;

class Map{
    private:
        int row;
        int column;
        int hill;
        int gold;
        int trap;
        int midX;
        int midY;
        int killLoad;
        vector < vector<char> > map;

    public:
        Map(int x, int y, int z); 
        void setPosition(int x, int y);
        void displayMap(bool hide);
        void generateMap();
        void generateResource();
        void setColourMap(int color);
        int getGoldNum();
        void resizeMap(vector < vector<char> > map_, int mapsizeX, int mapsizeY);
        void numberDisplay(int offsetX, int offsetY, bool hide);
        bool isMid(int x, int y);
        vector < vector<char> > getMap();
        bool inside(int i, int j);
        bool recursiveFind(int i, int j, vector < vector<bool> > visited, int coordY, int coordX);
        bool gotPath(int x, int y);
        void mid();
        void createPath();
};

#endif