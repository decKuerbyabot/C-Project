#include<iostream>
#include<map>
#include<vector>
#include<ctime>
#include<string>
#include<iomanip>
#include<climits>
#include "all_funcs.h"

void input_regulations() {
    cout << endl;
    cout << "==========DEFINE YOUR DIFFICLUTY==========" << endl;
    cout << endl;
    cout << "THE MONSTERS AND CHESTS COMBINED SHOULD NOT TAKE UP MORE HALF THE SIZE\n";
    cout << "OF YOUR AVAILABE GROUND, FOR EXAMPLE A 20X20 GAMEBOARD WILL BE INITIALIZED WITH A 18X18 SIZED\n";
    cout << "AVAILABLE FREE GROUND, WHICH, IN THIS CASE, MEANS THAT YOUR CHEST AND MONSTER\n";
    cout <<  "IN TOTAL CANNOT EXCEED 162.";
    cout << endl;
    cout << "ALSO NOTE THAT THE GAME WILL BECOME IMPOSSIBLE TO WIN IF YOU DON'T SET ENOUGH CHESTS\n";
    cout << "BECASE THERE IS NOT MUCH LEEWAY AND YOU WILL DIE AT A VERY EARLY STAGE\n";
    cout << endl;
    cout << "Is that clear? (Y/N) " << endl;
}
void tip1() {
    cout << endl;
    cout << "Tip: To have a better chance of winning, you better set more chests." << endl;
    cout << "But that will also make it harder to find the key." << endl;
    cout << endl;
}
void print_initial_result(map<vector<int>, block*> gameboard, vector<int> playerpos) {
    cout << endl;
    cout << "Your are spawned at: ( " << playerpos[0] << " , " << playerpos[1] << " )" << endl;
    cout << "Welcome to The Dungeon." << endl;
    cout << "Basic motor operations: w a s d." << endl;
    cout << "Attack: q for attack, e for using potion to gain 3 points of life." << endl;
    cout << "Using c, you can check your parameters, including your life, if or not you have saber-" << endl;
    cout << "-the number of your potion, your locationand heading direction." << endl;
    cout << "Using m, you can reveal a random monster's location." << endl;
    cout<<"You are headed N (north, the same applies for other directions too) by default, with 20 life points"<<endl;
    cout << "Press k to kill the gaming process." << endl;
    cout << endl;

}
bool is_valid_parameterlogic(int Win, int Hei, int m, int n) {
    if (Win < 20 || Hei < 20) {
        cout << "Too small a map" << endl;
        return false;

    }
    if (m < 5 || n < 5) {
        return false;
    }
    int court = (Win - 2) * (Hei - 2);
    if (m + n > court / 2) {
        cout << "Too many chests and monsters." << endl;
        return false;
    }
    return true;
}
bool is_valid_parameterfromat(string a) {
    string standard = "0123456789";
    for (int i = 0; a[i] != '\0'; i++) {
        if (standard.find(a[i],0)==string::npos){
            return false;
        }
    }
    return true;
}
int main() {
    //all the inputs
    int Wid, Hei,Monster_number,Chest_number;
    do {
        string raw;
        do 
        { 
            cout << "Please enter the map width you want (NO LESS THAN 20): "; 
            getline(cin, raw); 
            if (!is_valid_parameterfromat(raw))
            {
                cout << "Invalid" << endl;
            }
            else
            {
                Wid = stoi(raw);
            }
        } while (!is_valid_parameterfromat(raw));
        do
        {
            cout << "Please enter the map height you want (NO LESS THAN 20): ";
            getline(cin, raw);
            if (!is_valid_parameterfromat(raw))
            {
                cout << "Invalid" << endl;
            }
            else
            {
                Hei = stoi(raw);
            }
        } while (!is_valid_parameterfromat(raw));       
        char confirm;
        //CONFIRMATION THAT THE USER IS CLEAR
        input_regulations();
        do
        {
            string reference;
            string standardYN = "YN";
            do
            {                
                getline(cin, reference);
                if (reference.length() != 1 || standardYN.find(reference , 0 )==string::npos) {
                    cout << "I DIDN'T QUITE GET YOU" << endl;
                }
            } while (reference.length() != 1 || standardYN.find(reference, 0)==string::npos);
            confirm = reference[0];
            if (confirm == 'N') {
                cout << "THEN READ AGAIN." << endl;
            }
        } while (confirm == 'N');
        tip1();
        //MONSTER NUMBER INPUT
        do
        {
            cout << "Please enter the number of monsters you want (NO LESS THAN 5): ";
            getline(cin, raw);
            if (!is_valid_parameterfromat(raw))
            {
                cout << "Invalid" << endl;
            }
            else
            {
                Monster_number = stoi(raw);
            }
        } while (!is_valid_parameterfromat(raw));
        //CHEST NUMBER INPUT
        do
        {
            cout << "Please enter the number of chests you want (NO LESS THAN 5): ";
            getline(cin, raw);
            if (!is_valid_parameterfromat(raw))
            {
                cout << "Invalid" << endl;
            }
            else
            {
                Chest_number = stoi(raw);
            }
        } while (!is_valid_parameterfromat(raw));
        if (!is_valid_parameterlogic(Wid, Hei, Monster_number, Chest_number)) {
            cout << "Parameters not valid, please enter again." << endl;
            cout << endl;
        }
    } while (!is_valid_parameterlogic(Wid, Hei, Monster_number, Chest_number));
    //initialization
    cout << "Initializing map..." << endl;
    map<vector<int>, block*> gameboard;
    generatemap(gameboard,Wid,Hei,Monster_number,Chest_number);
    vector<int> playerpos;
    //FIND THE PLAYER
    for (auto& i : gameboard) {
        if (i.second->gettype() == 'P') {
            playerpos = i.second->getpos();
        }
    }
    //PRINT THE INITIALIZED PERIPHERY OF THE PLAYER
    gameboard[playerpos]->print_peripheral(gameboard);
    //PRINT THE PARAMETER RESULTS
    print_initial_result(gameboard, playerpos);
    //THE PARAMETERS USED AS CONDITIONS IN THIS DO WHILE LOOP
    int life=gameboard[playerpos]->getlife();
    int monsremain = 1;
    vector<vector<int>> monsterlist;
    //THE MAIN DO WHILE LOOP WHICH IS THE ENTIRE GAME
    do {
        char oper;
        string medium;
        string standard = "wasdqecmk";
        do {
            cout << "Enter your operation here: ";
            getline(cin, medium);
            if (medium.length() != 1 || standard.find(medium)==string::npos) {
                cout << "Invalid move" << endl;
            }
        } while (medium.length() != 1 || standard.find(medium)==string::npos);
        oper = medium[0];
        //doen't consume step
        if (oper == 'k') { break; }
        else if (oper == 'c') {
            gameboard[playerpos]->print_parameter();
        }
        else if (oper == 'm') {
            if (monsremain!=0){
            	int index = rand() % monsremain;
		cout << "There is a monster at position ( " << monsterlist[index][0] << " , " << monsterlist[index][1] << " )" << endl;
	    }
	    else{
		cout << "You killed all the monsters, keep looking for the key!" << endl;
	    }
        }
        else if (oper == 'a' || oper == 'd') {
            move_player(gameboard, oper, playerpos);
            gameboard[playerpos]->print_peripheral(gameboard);
        }
        //will consume step
        else {
            if (oper == 'q' || oper == 'e') {
                gameboard[playerpos]->player_attack_CM(gameboard, oper);
            }
            else { move_player(gameboard, oper, playerpos); }
            gameboard[playerpos]->player_be_attacked(gameboard);
            gameboard[playerpos]->print_peripheral(gameboard);            
        }
        monsremain = 0;
        monsterlist.clear();
        life = gameboard[playerpos]->getlife();
        for (auto& i : gameboard) {
            if (i.second->gettype() == 'M') {
                monsremain++;
                monsterlist.push_back(i.second->getpos());
            }
        }
    } while (life > 0 && ((!gameboard[playerpos]->getkey()) || monsremain > 0));
    if (life > 0 && monsremain > 0) {
        cout << "You quitted." << endl;
    }
    else {
        if (life <= 0) {
            cout << "You died." << endl;
        }
        else { cout << "You won." << endl; }
    }
    //release memory
    for (auto& i : gameboard) {
        delete i.second;
    }
 }
