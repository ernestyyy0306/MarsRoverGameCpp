#include "rover.h"

Rover::Rover(vector <vector<char> > map_){
    map = map_; 
    gold = 0; 
    steps = 0; 
    score = 0; 
    sequence = 0; 
    target = 0; 
    trapped = false; 
    quitted = false; 
    win = false; 
    srand(time(NULL)); 
    heading = rand() % 4; 

    if(map[0].size() < 30){        
        coordX = map[0].size()/2; 
        coordY = map.size()/2;
        if(coordY % 2 == 0){
            coordY++;
        } 
        if(map[coordY][coordX] == '|'){
            coordX--;
        } 
    }
    else{
        coordX = map[0].size()/2;   
        coordY = map.size()/2; 
        if(coordY % 2 == 0){
            coordY++;
        } 
        if(coordX % 2 == 0){
            coordX--;
        } 
    }
}

int Rover::getScore(){
    return score;
} 

void Rover::setTarget(int target_){
    target = target_;
} 

void Rover::setPosition(int x, int y){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition(hStdout, position);
}

void Rover::setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Rover::showPosition(){
    setColor(15);
    score = gold * 50 - (sequence * 5) - steps; 
    if(map[0].size() < 30){ 
        posX = (18 - map[0].size()/2) + coordX; 
        posY = coordY + 3; 
    }
    else{ 
        posX = coordX + 5; 
        posY = coordY + 3; 
    }
    setPosition(posX, posY); 
    if(heading == Left){ 
        setColor(15);
        cout << '<'; 
        if(!(coordX - 1 == 0)){
            setPosition(posX - 2, posY);
            if(map[coordY][coordX - 2] == '@'){
                setColor(6);
            }
            else if(map[coordY][coordX - 2] == '*'){
                setColor(14);
            }
            else if(map[coordY][coordX - 2] == '#'){
                setColor(12);
            }
            cout << map[coordY][coordX - 2]; 
            if(!(coordY + 1 == map.size() - 1)){ 
                setPosition(posX - 2, posY + 2);
                if(map[coordY + 2][coordX - 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY + 2][coordX - 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY + 2][coordX - 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY + 2][coordX - 2]; 
            }
            if(!(coordY - 1 == 0)){
                setPosition(posX - 2, posY - 2);
                if(map[coordY - 2][coordX - 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY - 2][coordX - 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY - 2][coordX - 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY - 2][coordX - 2]; 
            }
        }
    }
    else if(heading == Up){ 
        setColor(15);
        cout << '^'; 
        if(!(coordY - 1 == 0)){ 
            setPosition(posX, posY - 2);
            if(map[coordY - 2][coordX] == '@'){
                setColor(6);
            }
            else if(map[coordY - 2][coordX] == '*'){
                setColor(14);
            }
            else if(map[coordY - 2][coordX] == '#'){
                setColor(12);
            }
            cout << map[coordY - 2][coordX]; 
            if(!(coordX - 1 == 0)){
                setPosition(posX - 2, posY - 2);
                if(map[coordY - 2][coordX - 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY - 2][coordX - 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY - 2][coordX - 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY - 2][coordX - 2]; 
            }
            if(!(coordX + 1 == map[0].size() - 1)){
                setPosition(posX + 2, posY - 2);
                if(map[coordY - 2][coordX + 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY - 2][coordX + 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY - 2][coordX + 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY - 2][coordX + 2]; 
            }
        }
    }
    else if(heading == Right){ 
        setColor(15);
        cout << '>'; 
        if(!(coordX + 1 == map[0].size() - 1)){ 
            setPosition(posX + 2, posY);
            if(map[coordY][coordX + 2] == '@'){
                setColor(6);
            }
            else if(map[coordY][coordX + 2] == '*'){
                setColor(14);
            }
            else if(map[coordY][coordX + 2] == '#'){
                setColor(12);
            }
            cout << map[coordY][coordX + 2]; 
            if(!(coordY + 1 == map.size() - 1)){
                setPosition(posX + 2, posY + 2);
                if(map[coordY + 2][coordX + 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY + 2][coordX + 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY + 2][coordX + 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY + 2][coordX + 2]; 
            }
            if(!(coordY - 1 == 0)){
                setPosition(posX + 2, posY - 2);
                if(map[coordY - 2][coordX + 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY - 2][coordX + 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY - 2][coordX + 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY - 2][coordX + 2]; 
            }
        }
    }
    else if(heading == Down){ 
        setColor(15);
        cout << 'v'; 
        if(!(coordY + 1 == map.size() - 1)){ 
            setPosition(posX, posY + 2);
            if(map[coordY + 2][coordX] == '@'){
                setColor(6);
            }
            else if(map[coordY + 2][coordX] == '*'){
                setColor(14);
            }
            else if(map[coordY + 2][coordX] == '#'){
                setColor(12);
            }
            cout << map[coordY + 2][coordX]; 
            if(!(coordX - 1 == 0)){
                setPosition(posX - 2, posY + 2);
                if(map[coordY + 2][coordX - 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY + 2][coordX - 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY + 2][coordX - 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY + 2][coordX - 2]; 
            }
            if(!(coordX + 1 == map[0].size() - 1)){
                setPosition(posX + 2, posY + 2);
                if(map[coordY + 2][coordX + 2] == '@'){
                    setColor(6);
                }
                else if(map[coordY + 2][coordX + 2] == '*'){
                    setColor(14);
                }
                else if(map[coordY + 2][coordX + 2] == '#'){
                    setColor(12);
                }
                cout << map[coordY + 2][coordX + 2]; 
            }
        }
    }
    displayInfo(); 
}

void Rover::displayInfo(){
    setPosition(0, map.size() + 6);
    setColor(14); //yellow
    cout << "Mission: Get all the golds!! Do not get trapped!!" << endl;
    cout << "L=Turn Left, R=Turn Right, M=Move, Q=Quit" << endl;
    cout << "@=Hill, #=Trap, *=Gold" << endl << endl;
    cout << "Total Command Sequences = " << sequence << " [S]" << endl;
    cout << "Total Commands = " << steps << " [C]" << endl;
    cout << "Total Golds = " << gold << " [G] out of " << target << endl;
    cout << "Total Score = [G] x 50 - [S] x 5 - [C] x 1 =                                "; //prevent stacking of characters
    cout << "\rTotal Score = [G] x 50 - [S] x 5 - [C] x 1 = " << score << endl <<endl; 

    if(gold == target){
        win = true; 
        return;
    }

    cout << "Example Sequence: MMLMMMRMMRMRMLLL" << endl;
    cout << "Enter command sequence =>                                                   "; 
    cout << "\rEnter command sequence => ";
}

void Rover::executeInstruction(string command){
    int delay = 500; 
    sequence++;
    for(int i = 0; i < command.size(); i++){
        if(command[i] == 'Q' || command[i] == 'q'){ 
            quitted = true;
            return;
        }
        clearInfo(); 
        setColor(14); //yellow
        cout << "Command = " << command[i] << " ...";
        Sleep(delay);

        if(command[i] =='L' || command[i] == 'l'){ 
            clearInfo();
            setColor(14); //yellow
            cout << "Command = " << command[i] << " [executed]"; 
            Sleep(delay);
            heading = (heading - 1) % 4;
            steps++; 
            if(heading == Unknown){
                heading = Down; 
            }
        }

        else if(command[i] == 'R' || command[i] == 'r'){
            clearInfo(); 
            setColor(2); //green
            cout << "Command = " << command[i] << " [executed]"; 
            Sleep(delay); 
            heading = (heading + 1) % 4; 
            steps++; 
        }

        else if(command[i] == 'M' || command[i] == 'm'){
            steps++; 
            if(heading == Up && !(coordY - 1 == 0 || map[coordY - 2][coordX] == '@')){             
                clearInfo(); 
                setColor(2); //green
                cout << "Command = " << command[i] << " [executed]"; 
                Sleep(delay); 
                if(map[coordY - 2][coordX] == '*'){ 
                    gold ++; 
                    map[coordY - 2][coordX] = ' '; 
                }
                if(map[coordY - 2][coordX] == '#'){ 
                    trapped = true; 
                }
                coordY -= 2; 
                setPosition(posX, posY); 
                cout << ' '; 
            }
            else if(heading == Down && !(coordY + 1 == map.size() - 1  || map[coordY + 2][coordX] == '@')){
                clearInfo(); 
                setColor(2); //green
                cout << "Command = " << command[i] << " [executed]"; 
                Sleep(delay); 
                if(map[coordY + 2][coordX] == '*'){ 
                    gold ++; 
                    map[coordY + 2][coordX] = ' ';  
                }
                if(map[coordY + 2][coordX] == '#'){ 
                    trapped = true; 
                }
                coordY += 2; 
                setPosition(posX, posY); 
                cout << ' ';
            }
            else if(heading == Left && !(coordX - 1 == 0 || map[coordY][coordX - 2] == '@')){
                clearInfo(); 
                setColor(2); //green
                cout << "Command = " << command[i] << " [executed]"; 
                Sleep(delay); 
                if(map[coordY][coordX - 2] == '*'){ 
                    gold ++; 
                    map[coordY][coordX - 2] = ' '; 
                }
                if(map[coordY][coordX - 2] == '#'){ 
                    trapped = true; 
                }
                coordX -= 2;
                setPosition(posX, posY); 
                cout << ' '; 
            }
            else if(heading == Right && !(coordX + 1 == map[0].size() - 1 || map[coordY][coordX + 2] == '@')){
                clearInfo(); 
                setColor(2); //green
                cout << "Command = " << command[i] << " [executed]"; 
                Sleep(delay); 
                if(map[coordY][coordX + 2] == '*'){ 
                    gold ++; 
                    map[coordY][coordX + 2] = ' ';
                }
                if(map[coordY][coordX + 2] == '#'){ 
                    trapped = true; 
                }
                coordX += 2;
                setPosition(posX, posY); 
                cout << ' '; 
            }
            else{
                clearInfo(); 
                setColor(12); //red
                cout << "Command = " << command[i] << " [failed to executed]";  //collision fail
                Sleep(delay); 
            }
        }
        else{
            clearInfo(); 
            setColor(12); //red
            cout << "Command = " << command[i] << " [failed to executed]";  //unknown command fail
            Sleep(delay); 
        }
        showPosition();
    }
}

bool Rover::status(){
    
    if(quitted){
        setColor(12);
        cout << endl << "QUITTED!! Mission FAILED!!" << endl;
        setColor(7);
        return quitted;
    }
    
    else if(trapped){
        setColor(12);
        cout << endl << endl << "TRAPPED!! Mission FAILED!!" << endl;
        setColor(7); 
        return trapped;
    }
    
    else if(win){
        setColor(6);
        cout << endl << endl << "Congratz, Mission ACCOMPLISHED!!" << endl;
        setColor(7);
        return win;
    }
}

void Rover::clearInfo(){
    setPosition(0, map.size() + 6);
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    cout << "                                                                 "<< endl;
    setPosition(0, map.size() + 6);
}