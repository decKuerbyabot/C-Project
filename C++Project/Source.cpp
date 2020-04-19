#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "figures.cpp"
#include "functions.cpp"

int main() {
    int Wid, Hei; 
    cout << "Your desired game board width and height are: ";
    cin >> Wid>> Hei;
    int Monster_number;
    cout << "Number of monster is: ";
    cin >> Monster_number;
    int Chest_number;
    cout << "Number of chest is: ";
    cin >> Chest_number;
    map<vector<int>, string> gameboard;
    map<string, monster*> Mons;
    map<string, chest*> Chsts;
    player* plyr = new player;
    generatemap(gameboard,Mons,Chsts,plyr,Wid,Hei,Monster_number,Chest_number);
    
}