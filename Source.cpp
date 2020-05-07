#include<iostream>
#include<map>
#include<vector>
#include<ctime>
#include<string>
#include<iomanip>
#include<climits>
#include "all_funcs.h"

int main() {
    //all the inputs
    int Wid, Hei,Monster_number,Chest_number;
    do {
        cout << "Map Width (not smaller than 20): "; cin >> Wid;
        while (!cin.good()) {
            cout << "Invalid, try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> Wid;
        }
        cout << "Map Height (not smaller than 20): "; cin >> Hei;
        while (!cin.good()) {
            cout << "Invalid, try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> Hei;
        }
        cout << "Number of monster is: "; cin >> Monster_number;
        while (!cin.good()) {
            cout << "Invalid, try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> Monster_number;
        }
        cout << "Tip: To have a better chance of winning, you better set more chests." << endl;
        cout << "But that will also make it harder to find the key." << endl;
        cout << "Number of chest is: "; cin >> Chest_number;
        while (!cin.good()) {
            cout << "Invalid, try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> Chest_number;
        }
        if (is_valid(Wid, Hei, Monster_number, Chest_number)==false) {
            cout << "Invalid data, please enter again." << endl;
        }
    } while (is_valid(Wid, Hei, Monster_number, Chest_number)==false);
    //initialization
    cout << "Initializing map..." << endl;
    map<vector<int>, block*> gameboard;
    generatemap(gameboard,Wid,Hei,Monster_number,Chest_number);
    vector<int> playerpos;
    for (auto& i : gameboard) {
        if (i.second->gettype() == 'P') {
            playerpos = i.second->getpos();
        }
    }
    gameboard[playerpos]->print_peripheral(gameboard);
    int x = playerpos[0];
    int y = playerpos[1];
    cout << "Your are spawned at: ( " << x << " , " <<y<< " )"<<endl;
    cout << "Welcome to The Dungeon." << endl;
    cout << "Basic motor operation: w a s d." << endl;
    cout << "Attack: q for attack, e for using potion." << endl;
    cout << "c for checking your parameters." << endl;
    char oper;
    cout << "Enter your action here 1: ";
    
    int life = gameboard[playerpos]->getlife();
    int monsremain=0;
    for (auto& i : gameboard) {
        if (i.second->gettype() == 'M') {
            monsremain++;
        }
    }
    do {
          cout << "Enter your operation here: ";
          cin >> oper;
          while (oper != 'w' && oper != 'a' && oper != 's' && oper != 'd' && oper != 'q' && oper != 'e' && oper != 'c') {
            cout << "Invalid movement, please enter again: ";
            cin.clear();
            cin.ignore('\0');
            cin >> oper;
          }
            if (oper == 'c') {
                gameboard[playerpos]->print_parameter();
            }
            else if (oper == 'a' || oper == 'd') {
                move_player(gameboard, oper, playerpos);
                gameboard[playerpos]->print_peripheral(gameboard);
            }
            else{
                    if (oper == 'q' || oper == 'e') {
                        gameboard[playerpos]->player_attack_CM(gameboard, oper);
                    }
                    else { move_player(gameboard, oper, playerpos); }
                    gameboard[playerpos]->player_be_attacked(gameboard);
                    gameboard[playerpos]->print_peripheral(gameboard);
                    monsremain = 0;
                    life = gameboard[playerpos]->getlife();
                    for (auto& i : gameboard) {
                        if (i.second->gettype() == 'M') {
                        monsremain++;
                        }
                    }               
            }
            
    }while (life > 0 && ((!gameboard[playerpos]->getkey()) || monsremain > 0));
    if (life <= 0 && monsremain!=0) {
        cout << "You died." << endl;
    }
    else { cout << "You won." << endl; }

 }