#include "map.h"

Map::Map(int x, int y, int z){
    column = x;                 
    row = y;                    
    gold = z;       
    hill = column * row / 4;    
    trap = column * row / 4;    
    resizeMap(map, column * 2 + 1, row * 2 + 1); 
}

vector < vector<char> > Map::getMap(){
    return map;
} 

int Map::getGoldNum(){
    return gold;
} 

void Map::resizeMap(vector < vector<char> > map_, int mapsizeX, int mapsizeY){
    map.resize(mapsizeY); 
    for (int i=0; i<mapsizeY; i++){
        map[i].resize(mapsizeX); 
    }
}

void Map::setPosition(int x, int y) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);   //take control over the console window
	COORD position = {x,y};                             //control the cursor position on coordinate x & y
	SetConsoleCursorPosition(hStdout, position);        
}

void Map::setColourMap(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Map::numberDisplay(int offsetX, int offsetY, bool hide){
    int x = 1; 
    int y = 1; 
    int i, j;  


    setColourMap(3); //cyan
    for(i = 0; i < row ; i++){ 
        setPosition(offsetX - 3, map.size() + 1 - (2 * i)); 
        cout << setfill('0') << setw(2) << y; 
        y++; 
    }
    for(i = 0; i < column ; i++){ 
        setPosition(offsetX + 1 +(i * 2), map.size() + 3); 
        cout << x/10 % 10; 
        setPosition(offsetX + 1+ (i * 2), map.size() + 4); 
        cout << x % 10; 
        x++; 
    }

    //display map
    if(!hide){ 
        for(i = 0; i < map.size() ; i++){
            for(j = 0; j < map[0].size() ; j++){
                setPosition(offsetX + j, offsetY + i); 
                setColourMap(4); //red
                if(map[i][j] == '@'){
                    setColourMap(6);
                }
                else if(map[i][j] == '*'){
                    setColourMap(14);
                }
                else if(map[i][j] == '#'){
                    setColourMap(12);
                }
                cout << map[i][j]; 
            }
        }
    }
    else{
        for(i = 0; i < map.size() ; i++){
            for(j = 0; j < map[0].size() ; j++){
                setPosition(offsetX + j, offsetY + i); 
                if(i % 2 != 0 && j % 2 != 0){ 
                    setColourMap(4); //brown
                    cout << '?'; 
                }
                else{      
                    setColourMap(4); //red
                    cout << map[i][j];  //fences
                }
            }
        }
    }
}

void Map::mid(){
    midX = map[0].size()/2; 
    midY = map.size()/2; 
    if(midY % 2 == 0){
        midY++;
    } 
    if(map[midY][midX] == '|'){
        midX--;
    } 
}

bool Map::isMid(int x, int y){
    if(x == midX && y == midY){return true;} 
    else{return false;} 
}

void Map::displayMap(bool hide){
    system("cls"); 
    
    setColourMap(9); //lighblue
    if(map[0].size() < 30){ 
        setPosition(0, 1); 
        cout << "--__--__ Mars Rover Mapper__--__--"; 
        numberDisplay(18 - map[0].size()/2, 3, hide); 
    }
    else{ //map bigger than the title
        setPosition((map[0].size() + 7)/2 - 17, 1); 
        cout << "--__--__ Mars Rover Mapper__--__--"; 
        numberDisplay(5, 3, hide); 
    }
    setColourMap(15);
    cout << endl << endl << endl; 
}

void Map::generateMap(){
    int i, j;
    for(i=0;i<map.size();i++){
        for(j=0;j<map[0].size();j++){
            if(j % 2 == 0 && i % 2 == 0){ 
                map[i][j] = '+';
            }    
            else if(j % 2 != 0 && i % 2 == 0){ 
                map[i][j] = '-';
            }
            else if(i % 2 != 0 && j % 2 == 0){ 
                map[i][j] = '|';
            }
            else{
                map[i][j] = ' '; 
            }
        }
    }
}

void Map::generateResource(){
    mid();
    srand(time(NULL)); 
    int count = 0;
    int randomY; 
    int randomX;
    while(count < hill){
        randomY = rand() % map.size(); 
        randomX = rand() % map[0].size(); 

        if(randomX % 2 != 0 && randomY % 2 != 0 && map[randomY][randomX] != '@'){ 
            if(isMid(randomX, randomY)){ 
                continue;
            }
            map[randomY][randomX] = '@'; 
            count++; 
        }
    }
    
    count = 0;
    while(count < trap){
        randomY = rand() % map.size();
        randomX = rand() % map[0].size();
        
        if(randomX % 2 != 0 && randomY % 2 != 0  && map[randomY][randomX] != '@'  && map[randomY][randomX] != '#'){
            if(isMid(randomX, randomY)){ 
                continue;
            }
            map[randomY][randomX] = '#'; 
            count++; 
        }
    }
    
    count = 0; 
    while(count < gold){ 
        randomY = rand() % map.size(); 
        randomX = rand() % map[0].size(); 

        if(randomX % 2 != 0 && randomY % 2 != 0 && map[randomY][randomX] != '*' 
            && map[randomY][randomX] != '@' && map[randomY][randomX] != '#'){ 
            if(isMid(randomX, randomY)){ 
                continue;
            }
            map[randomY][randomX] = '*';
            count++;
        }
    }
    createPath();
}

bool Map::inside(int i, int j){
  if (i >= 1 && i < map[0].size() - 1 && j >= 1 && j < map.size() - 1){return true;}
  return false;
}
 
bool Map::recursiveFind(int i, int j, vector < vector<bool> > visited, int midY, int midX){
  killLoad++;
  if(killLoad > 1000){return false;}
  if (inside(i, j) && map[i][j] != '#' && map[i][j] != '@' && !visited[i][j]) {
    visited[i][j] = true; 
    if (i == midY && j == midX){return true;}
    bool up = recursiveFind(i - 2, j, visited, midY, midX); 
    if (up){return true;}
    bool left = recursiveFind(i, j - 2, visited, midY, midX);  
    if (left){return true;}
    bool down = recursiveFind(i + 2, j, visited, midY, midX);
    if (down){return true;}
    bool right = recursiveFind(i, j + 2, visited, midY, midX);
    if (right){return true;}
  }
  return false; 
}
 
bool Map::gotPath(int x, int y){
  vector < vector<bool> > visited;
  visited.resize(map.size()); 
  for (int i=0; i<map.size(); i++){
    visited[i].resize(map[0].size()); 
  }

  bool flag = false;
  if(recursiveFind(x, y, visited, midY, midX)){return true;}
  else{return false;}
}

void Map::createPath(){
    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map[0].size(); x++){
            killLoad = 0;
            if((map[y][x] == '*' && !gotPath(y, x))){
                if(x < midX){
                    for(int i = x + 2; i <= midX; i+=2){
                        if(map[y][i] == '#' || map[y][i] == '@'){
                            map[y][i] = ' ';
                        }
                    }
                }
                if(x > midX){
                    for(int i = x - 2; i >= midX; i-=2){
                        if(map[y][i] == '#' || map[y][i] == '@'){
                            map[y][i] = ' ';
                        }
                    }
                }
                if(y < midY){
                    for(int i = y + 2; i <= midX; i+=2){
                        if(map[i][midX] == '#' || map[i][midX] == '@'){
                            map[i][midX] = ' ';
                        }
                    }
                }
                if(y > midY){
                    for(int i = y - 2; i >= midX; i-=2){
                        if(map[i][midX] == '#' || map[i][midX] == '@'){
                            map[i][midX] = ' ';
                        }
                    }
                }
            }
        }
    }
}
