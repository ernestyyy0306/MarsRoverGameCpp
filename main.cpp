#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "map.h"
#include "rover.h"

void setColour(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setPositionXY(int x, int y){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition(hStdout, position);
}

string enterPlayerName(){

    string playerName;

    system("cls");
    setColour(6);
    cout << "       *                 `                         `          .           *        " << endl;
    cout << "                  .             *             .                                   ." << endl;
    cout << "   `        *                        .             .      *       `                " << endl;
    cout << "               .      *                      `                                   ` " << endl;
    cout << "   *     `                   .       *          .          `       .    `     *    " << endl;
    cout << "                 .                                                        .        " << endl;
    cout << ".      .       *         `               .           *          .                ` " << endl;
    cout << "      *           .             *             .             `             *       ." << endl;
    cout << "   `        .                        .             .      *                        " << endl;
    cout << "                      *                      `                     *               " << endl;
    cout << "   *     `                   .       *          .          `            `       *  " << endl;
    cout << "                                                      .                    .       " << endl;
    cout << ".      .       *         `               .                     .                   " << endl;
    cout << "      *           .             *                                      `         ` " << endl;
    cout << "   `                                .             .      *                         " << endl;
    cout << "               .      *                      `                     *               " << endl;
    cout << "   *     `                   .       *          .          `            `     *    " << endl;
    cout << "                                                                                   " << endl;
    cout << ".     .         `         `               .          *          .                ` " << endl;
    cout << "                  .             *                                      *           " << endl;
    cout << "   `        *                        .             .        *                 `    " << endl;
    cout << "               .      *                      `                        .            " << endl;
    cout << "   *     `                   .       *          .          `                  *    " << endl;
    cout << "                  .                                                        .       " << endl;
    cout << "       .       *         `               .           *               *            ." << endl;
    cout << " `                               *                             .                   " << endl;
    
    setColour(14);
    setPositionXY(22, 11); cout << "Please enter your name (without spaces)";
    setPositionXY(22, 12); cout << "=> ";
    cin >> playerName;

    while (playerName.size() > 18){
        setPositionXY(24, 5); cout << "Name is too long! Please try again";
        setPositionXY(22, 13); cout << "=> ";
        cin.clear();
        cin.ignore();
        cin >> playerName;
    }

    return playerName;
}

void start(string &playerName){

    string player = playerName;
    int spaces = 0;
    spaces = (77 - player.size())/2;

    setColour(6);
    cout << "Pay & Aiman 2021" << endl << endl;
    cout << "      *           .             *             .             `           *         ." << endl;
    cout << "   `        *           .            .             .      *       `                " << endl;
    cout << "               .      *                      `                     *             ` " << endl;
    cout << "   *     `                   .       *          .          `       .    `     *   ." << endl;
    cout << "                 .                                                         .       " << endl;
    cout << ".      .       *         `       *       .           *         .     *           ` " << endl << endl;
    setColour(12);
	cout << "            ****       ****      ******      *******         *******               " << endl;
	cout << "            *****     *****     ********     *********      **********             " << endl;
	cout << "            *** **   ** ***    ***    ***    ***    ***    ****     ***            " << endl;
	cout << "            ***  ** **  ***    ***    ***    ***    ***    ***                     " << endl;
	cout << "            ***   ***   ***    **********    **********     **********             " << endl;
	cout << "            ***   ***   ***    **********    *********              ***            " << endl;
	cout << "            ***         ***    ***    ***    *** ***       ***     ****            " << endl;
	cout << "            ***         ***    ***    ***    ***  ***       **********             " << endl;
	cout << "            ***         ***    ***    ***    ***    ***      *******               " << endl << endl;
	setColour(6);
    cout << "      *           .             *             .             `           *         ." << endl;
    cout << "   `        *           .            .             .      *       `                " << endl;
    cout << "                     *                      `                     *            `   " << endl;
    cout << "   *     `    .               .       *          .          `       .    `     *   " << endl;
    cout << "                 .                                                         .       " << endl;
    cout << ".      .       *         `       *       .           *         .     *            `" << endl << endl << endl;
    setColour(13);
    cout << string(spaces, ' '); cout << "HELLO, " << player << endl;
    cout << "                                  WELCOME TO MARS                                  " << endl;
    setColour(7);
}

int displayMenu(){
    int mX = 34;
    int mY = 32;
    int choice;
	
    setColour(9);
	setPositionXY(mX, mY); cout << "1. START GAME";
	setPositionXY(mX, mY + 1); cout << "2. VIEW SCORE";
    setPositionXY(mX, mY + 2); cout << "3. CHANGE PLAYER";
	setPositionXY(mX, mY + 3); cout << "4. QUIT";

    setColour(11);
    setPositionXY(mX - 28, mY + 5); cout << "Please enter your choice => ";
    cin.sync();
    cin >> choice;

    while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4)){
    setPositionXY(mX - 29, mY + 6); cout << "Invalid, please try again => ";
    cin.clear();
    cin.ignore();
    cin >> choice;
    }

    setColour(7);

    return choice;
}

void createText(int score, string name){
    
    fstream outfile;
    outfile.open("Highscore.txt",ios::app);

    if (!outfile){
        cout << "Error creating the file" << endl;
    }

    outfile << setw(27) << "" << name;
    outfile << setw(28 - name.size()) << "" << score << endl;
    outfile.close();
}

void readFile(fstream &infile){
    char text; 

    while (!infile.eof()){
        infile >> noskipws >> text;
        cout << text;
    }

    infile.close();
}

void startGame(string &playerName){

    bool running = true;
    string player = playerName;
    string input;

    while (running){
        system("cls");
        vector < vector<char> > map;
        int column;
        int row;
        int gold;

        cout << "Let's explore Mars!" << endl << endl;
        cout << "Mars dimension X => ";
        cin >> column;

        while (column < 2 || column > 75){
            cout << "Invalid, dimension X in Mars must be within the range of 2 to 75." << endl;
            cout << "Please try again => ";
            cin.clear();
            cin.ignore();
            cin >> column;
        }

        cout << endl;
        cout << "Mars dimension Y => ";
        cin >> row;

        while (row < 2 || row > 75){
            cout << "Invalid, dimension Y in Mars must be within the range of 2 to 75." << endl;
            cout << "Please try again => ";
            cin.clear();
            cin.ignore();
            cin >> row;
        }

        cout << endl;
        cout << "No of Golds (MAX = " << (row*column/2) - 1 << "): ";
        cin >> gold;

        while (gold < 1 || gold >= (row*column/2) - 1) {
            cout << "Invalid, number of golds shouldn't exceed 50% of the Mars dimension area or less than 1." << endl;
            cout << "Please try again => ";
            cin.clear();
            cin.ignore();
            cin >> gold;
        }

        Map Mars(column, row, gold);
        Mars.generateMap();
        Mars.generateResource();
        Mars.displayMap(true);
        map = Mars.getMap();
        Rover rover(map);
        rover.setTarget(Mars.getGoldNum());
        rover.showPosition();
        bool gameOver = false;
        bool win = false;

        while(!gameOver){
            cin >> input;
            rover.executeInstruction(input);
            gameOver = rover.status();
        }

        int totalScore = rover.getScore();
        createText(totalScore, player);

        cout << endl << "Do you want to see the Map of Mars? => ";
        cin >> input;

        while (!(input[0] == 'y' ||input[0] == 'Y' || input[0] == 'n' ||input[0] == 'N')){
            cout << "Invalid, please enter either Y or N => ";
            cin >> input;
        }

        if(input[0] == 'y' ||input[0] == 'Y'){
            Mars.displayMap(false);
        }

        cout << endl << "Do you want to explore Mars again? => ";      
        cin >> input;

        while (!(input[0] == 'y' ||input[0] == 'Y' || input[0] == 'n' ||input[0] == 'N')){
            cout << "Invalid, please enter either Y or N => ";
            cin >> input;
        }

        if(input[0] == 'y' || input[0] == 'Y'){
        gameOver = false;
        }
        else if(input[0] == 'n' || input[0] == 'N'){
        break;
        }
    }
}

void viewScore(){
    int hsx = 26;

    setColour(9);
    setPositionXY(hsx, 1); cout << "  _   _ _       _                                        ";
    setPositionXY(hsx, 2); cout << " | | | (_) __ _| |__  ___  ___ ___  _ __ ___  ___        ";
    setPositionXY(hsx, 3); cout << " | |_| | |/ _' | '_ \\/ __|/ __/ _ \\| '__/ _ \\/ __|    ";
    setPositionXY(hsx, 4); cout << " |  _  | | (_| | | | \\__ \\ (_| (_) | | |  __/\\__ \\   ";
    setPositionXY(hsx, 5); cout << " |_| |_|_|\\__, |_| |_|___/\\___\\___/|_|  \\___||___/   ";
    setPositionXY(hsx, 6); cout << "          |___/                                          ";

    setColour(14);
    setPositionXY(hsx + 1, 9); cout << "PLAYERS:"; 
    setPositionXY(hsx + 29, 9); cout << "SCORES:" << endl;

    setColour(7);
    fstream infile("Highscore.txt", ios::in);

    if (infile.fail()){
        setPositionXY(hsx + 1, 11); cout << "No Record Found";
        setPositionXY(hsx + 1, 12); cout << "Please Start Game first and come back later.";
    } 
    else {
        readFile(infile);
    }

    cout << endl << endl << endl;
    setColour(11);
    cout << "Press any key to go back . . . " << endl;
    getch();
    setColour(7);
}

int main(){

    int choice;
    string playerName;
    
    do { 
        playerName = enterPlayerName();

        do {
            choice = 0;
            system("cls");
            start(playerName);
            choice = displayMenu();

            switch (choice) {

                case 1: {
                    startGame(playerName);
                    break;
                }
                                                                
                case 2: {                                               
                    system("cls");    
                    viewScore();                               
                    break;
                }

                case 3: {
                    system("cls");
                    break;
                }

                case 4: {
                    system("cls");
                    cout << "Good Bye From Mars!" << endl;
                    exit(0);
                }

            }

        } while (!(choice == 4 || choice == 3));

    } while (choice == 3);

    return 0;
}