#include<map>
#include<vector>
#include<ctime>
#include<string>
#include<iomanip>
#include "figures.cpp"
using namespace std;

void generatemap(map<vector<int>, string>& gameboard, map<string, monster*> Mons, map<string, chest*> Chsts, player* plyr, int Wid, int Hei, int Monster_number, int Chest_number) {
	//generate grounds
	for (int i = 0; i < Wid; i++) {
		for (int j = 0; j < Hei; j++) {
			vector<int> temp = { i , j };
			gameboard[temp] = "G";
		}
	}
	//build border walls
	for (int i = 0; i < Wid; i++) {
		for (int j = 0; j < Hei; j++) {
			if ((i == 0) || (j == 0) || (i == Wid - 1) || (j == Wid - 1)) {
				gameboard[{i, j}] = "W";
			}
		}
	}

	//populate the map with monster and chests;
	//monster
	srand(time(NULL));
	for (int i(0); i < Monster_number; i++) {
		int x = rand() % Wid;
		int y = rand() % Hei;
		while (gameboard[{x, y}] != "G") {
			x = rand() % Wid;
			y = rand() % Hei;
		}
		monster* p = new monster;
		p->position = { x,y };
		p->life = 3;
		gameboard[{x, y}] = "M"+to_string(i+1);
		Mons["M" + to_string(i + 1)] = p;
	}
	//chest
	for (int i(0); i < Chest_number; i++) {
		int x=rand()%Wid;
		int y=rand()%Hei;
		while (gameboard[{x, y}] != "G") {
			x = rand() % Wid;
		    y = rand() % Hei;
		}
		chest* p = new chest;
		p->key = false;
		p->life = 3;
		p->position = { x,y };
		gameboard[{x, y}] = "M" + to_string(i + i);
	    Chsts["M" + to_string(i + 1)] = p;
	}
	//finally place the player, default heading is north, carries a saber
	int x = rand() % Wid;
	int y = rand() % Hei;
	while (gameboard[{x, y}] != "G") {
		x = rand() % Wid;
		y = rand() % Hei;
	}
	plyr->direction = 'N';
	plyr->key = false;
	plyr->life = 5;
	plyr->position = { x,y };
	plyr->potion = false;
	plyr->sword = true;
}


void move_player(player*& p, map<vector<int>, string> gameboard, char oper) {
	char heading = p->direction;
	vector<int> previouspos = p->position;
    //position change
	switch (oper)
	{
	case 'w':
		switch (heading)
		{
		case 'N':
			(p->position)[1]++;
			break;
		case 'E':
			(p->position)[0]++;
			break;
		case 'W':
			(p->position)[0]--;
			break;
		case 'S':
			(p->position)[1]--;
			break;
		}
		break;
	case 's':
		switch (heading)
		{
		case 'N':
			(p->position)[1]--;
			break;
		case 'E':
			(p->position)[0]--;
			break;
		case 'W':
			(p->position)[0]++;
			break;
		case 'S':
			(p->position)[1]++;
			break;
		}
		break;
	case 'a':
		switch (heading)
		{
		case 'N':
			p->direction = 'W';
			break;
		case 'E':
			p->direction = 'N';
			break;
		case 'W':
			p->direction = 'S';
			break;
		case 'S':
			p->direction = 'E';
			break;
		}
		break;
	case 'd':
		switch (heading)
		{
		case 'N':
			p->direction = 'E';
			break;
		case 'E':
			p->direction = 'S';
			break;
		case 'W':
			p->direction = 'N';
			break;
		case 'S':
			p->direction = 'W';
			break;
		}
		break;
	}
	if (gameboard[p->position] == "G") {
		gameboard[previouspos] = "G";
		gameboard[p->position] = "P";
	}
	else{
		vector<int> obstacle = p->position;
		p->position = previouspos;
		if (gameboard[obstacle] == "W") {
			cout << "You are running into wall, please try again" << endl;
		}
		if (gameboard[obstacle][0] == 'M') {
			cout << "You ran into a demon, you're injured from your boldness, press 'q' for attack, 'e' for potion, or flee" << endl;
			p->life--;
		}
		if (gameboard[obstacle][0] == 'C') {
			cout << "You ran into a chest, congrats you wasted a step, press 'q' for hacking, or ignore" << endl;
		}
	}
}


void random_move() {

}

void print_peripheral(player* plyr, map<vector<int>,string> gameboard) {
	vector<int> playerpos = plyr->position;
	char heading = plyr->direction;
	int x_start = playerpos[0] - 2;
	int x_end = x_start + 4;
	int y_start = playerpos[1] - 2;
	int y_end = y_start + 4;
	switch (heading)
	{
	case 'N':
		for (int i = x_start; i < x_end; i++) {
			for (int j = y_start; i < y_end; j++) {

				
			}
			cout << endl;
		}
	}
}