#include<iostream>
#include<map>
#include<vector>
#include<ctime>
#include<string>
#include<iomanip>
#include "all_funcs.h"


void block::print_parameter() {
	cout << "Your life is: " << life << endl;
	cout << "You " << ((saberlife) ? "have" : "don't have") << " a saber." << endl;
	cout << "You have " << player_potion << " potions." << endl;
	cout << "Your position: ( " << position[0] << " , " << position[1] << " )" << endl;
	cout << "You're headed " << heading << endl;
}
void block::renew_pos(std::vector<int> pos) {
	position = pos;
}
void block::renew_head(char h) {
	heading = h;
}
void block::deduce_life() {
	life--;
}
//plays on monster position
void block::monster_pursuit(std::map<std::vector<int>, block*>& gameboard, std::vector<int> playerpos) {
	int dx = position[0] - playerpos[0];
	int dy = position[1] - playerpos[1];
	int circle;
	if (abs(dx) > abs(dy)) {
		circle = abs(dx);
	}
	else {
		circle = abs(dy);
	}
	//the first priority locations that the monster is heading toward, which is advancing a circle toward the player
	std::vector < std::vector<int >> priority1;
	//the second, which doesn't change the circle
	std::vector<vector<int>> priority2;
	//the third, which will move the monster further from the player
	vector<vector<int>> priority3;
	//this vector is used to explore the positions around the monster
	vector<int> surrounding_move = { -1,0,1 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(surrounding_move[i] == 0 && surrounding_move[j] == 0)) {
				int explore_x = position[0] + surrounding_move[i];
				int explore_y = position[1] + surrounding_move[j];
				int new_dx = abs(explore_x - playerpos[0]);
				int new_dy = abs(explore_y - playerpos[1]);
				int new_circle;
				if (new_dx > new_dy) {
					new_circle = new_dx;
				}
				else {
					new_circle = new_dy;
				}
				if (new_circle < circle) {
					priority1.push_back({ explore_x,explore_y });
				}
				else if (new_circle = circle) {
					priority2.push_back({ explore_x,explore_y });
				}
				else {
					priority3.push_back({ explore_x,explore_y });
				}
			}
		}
	}
	//now move the monster
	vector<vector<int>>::iterator it;
	it = priority1.begin();
	bool found = false;
	while (it != priority3.end()) {
		if (it == priority1.end()) {
			it = priority2.begin();
		}
		else if (it == priority2.end()) { it = priority3.begin(); }
		else { it++; }

		if (gameboard[*it]->gettype() == 'G') {
			found = true;
			break;
		}
	}
	if (found) {
		//temp point to the found ground;
		block* temp = gameboard[*it];
		//ground point to moved monster
		gameboard[*it] = gameboard[position];
		//monster point to ground
		gameboard[position] = temp;
		//don't forget the renew the player position
		position = *it;
	}
}
void block::monster_follow(map<vector<int>, block*>& gameboard, vector<int> preplayerpos, vector<int> playerpos) {
	int dx = position[0] - preplayerpos[0];
	int dy = position[1] - preplayerpos[1];
	int circle;
	if (abs(dx) > abs(dy)) {
		circle = abs(dx);
	}
	else {
		circle = abs(dy);
	}
	vector<int> newpos;
	//the first priority locations that the monster is heading toward, which is advancing a circle toward the player
	//vector<vector<int>> priority1; follow can't shrik the circle

	//the second, which doesn't change the circle
	vector<vector<int>> priority2;
	//the third, which will move the monster further from the player
	vector<vector<int>> priority3;
	//this vector is used to explore the positions around the monster
	vector<int> surrounding_move = { -1,0,1 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(surrounding_move[i] == 0 && surrounding_move[j] == 0)) {
				int explore_x = position[0] + surrounding_move[i];
				int explore_y = position[1] + surrounding_move[j];
				int new_dx = abs(explore_x - playerpos[0]);
				int new_dy = abs(explore_y - playerpos[1]);
				int newcircle;
				if (new_dx > new_dy) {
					newcircle = new_dx;
				}
				else { newcircle = new_dy; }
				if (newcircle == circle) {
					priority2.push_back({ explore_x,explore_y });
				}
				else if (newcircle > circle) {
					priority3.push_back({ explore_x,explore_y });
				}

			}
		}
	}
	//now move the monster
	vector<vector<int>>::iterator it;
	it = priority2.begin();
	bool found = false;
	while (it != priority2.end()) {
		if (it == priority2.end()) { it = priority3.begin(); }
		else { it++; }
		if (gameboard[*it]->gettype() == 'G') {
			found = true;
			break;
		}
	}
	//temp point to the found ground;
	if (found) {
		block* temp = gameboard[*it];
		//ground point to moved monster
		gameboard[*it] = gameboard[position];
		//monster point to ground
		gameboard[position] = temp;
		//don forget to renew the player position
		position = *it;
	}
}

vector<vector<int>> block::player_peri_mons(map<vector<int>, block*>& gameboard, int circle) {
	// 5  5  5  5  5  if the circle parameter is 5
	// 5  5  5  5  5 then sigleedge is 2
	// 5  5  5  5  5 the outermost layer of this grid will be examined
	// 5  5  5  5  5
	// 5  5  5  5  5
	vector<vector<int>> perimons;
	vector<int> singlepos;
	int singleedge = circle / 2;
	vector<int> move;
	for (int i = 0 - singleedge; i <= singleedge; i++) {
		move.push_back(i);
	}
	for (int i = 0; i < circle; i++) {
		for (int j = 0; j < circle; j++) {
			if (abs(move[i]) == singleedge || abs(move[j]) == singleedge) {
				singlepos = { position[0] + move[i], position[1] + move[j] };
				if (gameboard[singlepos]->gettype() == 'M') {
						perimons.push_back(singlepos);
				}
			}
		}
	}
	return perimons;

}

void block::print_peripheral(map<vector<int>, block*> gameboard) {
	int x_start = position[0] - 2;
	int x_end = x_start + 4;
	int y_start= position[1] - 2;
	int y_end = y_start + 4;
	switch (heading)
	{
	case 'N':
		for (int j = y_end; j >= y_start; j--) {
			for (int i = x_start; i <= x_end; i++) {
				char type = gameboard[{i, j}]->gettype();
				if (type == 'P') {
					std::cout << setw(4)<< 'A';
				}
				else if (type == 'C' || type == 'M') {
					string name = gameboard[{i, j}]->getname();
					std::cout << setw(4) << name;
				}
				else if (type == 'G') {
					cout << setw(4)<<"";
				}
				else { std::cout << setw(4) << type; }
			}
			cout << endl;
			cout << endl;
		}
	    std::cout << endl;
	    break;
	case 'E':
		for (int i = x_end; i >= x_start; i--) {
			for (int j = y_end; j >= y_start; j--) {
				char type = gameboard[{i, j}]->gettype();
				if (type == 'P') {
					std::cout << setw(4) << 'A';
				}
				else if (type == 'G') {
					cout << setw(4)<<"";
				}
				else if (type == 'C' || type == 'M') {
					string name = gameboard[{i, j}]->getname();
					std::cout << setw(4) << name;
				}
				else { std::cout << setw(4) << type; }
			}
			std::cout << endl;
			cout << endl;
		}
		std::cout << endl;
		break;
	case 'W':
		for (int i = x_start;  i<= x_end; i++) {
			for (int j = y_start; j <= y_end; j++) {
				char type = gameboard[{i, j}]->gettype();
				if (type == 'P') {
					std::cout << setw(4) << 'A';
				}
				else if (type == 'G') {
					cout << setw(4)<<"";
				}
				else if (type == 'C' || type == 'M') {
					string name = gameboard[{i, j}]->getname();
					std::cout << setw(4) << name;
				}
				else { std::cout << setw(4) << type; }
			}
			std::cout << endl;
			cout << endl;
		}
		
		std::cout << endl;
		break;
	case 'S':
		for (int j = y_start; j <= y_end; j++) {
			for (int i = x_end; i >= x_start; i--) {
				char type = gameboard[{i, j}]->gettype();
				if (type == 'P') {
					std::cout << setw(4) << 'A';
				}
				else if (type == 'G') {
					cout << setw(4)<<"";
				}
				else if (type == 'C' || type == 'M') {
					string name = gameboard[{i, j}]->getname();
					std::cout << setw(4) << name;
				}
				else { std::cout << setw(4) << type; }
			}
			std::cout << endl;
			cout << endl;
		}
		std::cout << endl;
		break;
	}
}

void block::player_be_attacked(map<vector<int>, block*>& gameboard) {
	vector<vector<int>> adjacentmons = gameboard[position]->player_peri_mons(gameboard, 3);
	vector<vector<int>>::iterator it = adjacentmons.begin();
	int l=life;
	for (it; it != adjacentmons.end(); it++){
		life--;
	}
}

void block::player_attack_CM(map<vector<int>, block*>& gameboard, char oper ){
	vector<int> pos = position;
	char target;
	switch (oper)
	{
	case 'e':
		if (player_potion) {
			cout << "Your life prolonged." << endl;
			life += 3;
			player_potion--;
		}
		else {
			cout << "You don't have potion." << endl;
			cout << "You wasted time and life." << endl;
			life--;
		}
		break;
		//attack the chest
	case 'q':
		switch (heading) {
		case 'N':
			pos[1]++;
			break;
		case 'E':
			pos[0]++;
			break;
		case 'S':
			pos[1]--;
			break;
		case 'W':
			pos[0]--;
			break;
		}
		char type = gameboard[pos]->gettype();
		string name = gameboard[pos]->getname();
		switch (type) {
		case 'M':
			if (saberlife) {
				cout << "You killed monster " << name << endl;
				gameboard[pos]->renew_life(0);
			}
			else {
				gameboard[pos]->deduce_life();
				cout << "Monster " << name << " is damaged" << endl;
				if (gameboard[pos]->getlife() == 0) {
					cout << "You killed Monster " << name << " with bare hands, congrats!" << endl;
				}
			}
			if (gameboard[pos]->getlife() == 0) {
				delete gameboard[pos];
				gameboard[pos]->initial_G(pos);
			}
			break;
		case 'C':
			if (saberlife) {
				gameboard[pos]->renew_life(0);
				saberlife--;
				cout << "You opened chest " << name << " congrats!" << endl;
				if (saberlife == 0) {
					cout << "Your saber wore out" << endl;
				}
			}
			else {
				gameboard[pos]->deduce_life();
				if (gameboard[pos]->getlife())
					cout << "Chest " << name << " is damaged." << endl;
				else
					cout << "You opened chest " << name << " with bare hands, congrats!" << endl;
			}
			if (gameboard[pos]->getlife() == 0) {
				if (gameboard[pos]->getkey()) {
					cout << "Keep on conquering the monsters." << endl;
					key = true;
				}
				if (gameboard[pos]->getpotion()) {
					cout << "This chest has potion inside it." << endl;
					player_potion++;
				}
				if (gameboard[pos]->getsaber()) {
					if (saberlife == 0) {
						saberlife = 3;
						cout << "You got a new saber." << endl;
					}
					else {
						cout << "You opened an empty chest." << endl;
					}
				}
				else {
					cout << "You opened an empty chest" << endl;
				}
			    delete gameboard[pos];
				gameboard[pos]->initial_G(pos);
			}
		    break;
	    case 'W':
		    cout << "You are attacking wall" << endl;
		    break;
	    case 'G':
		    cout << "You are attacking nothing........." << endl;
		    break;
		}
	    break;
    }
}
////---------------------------------------------------
////---------------------------------------------------
////              NON-MEMBER FUNCTIONS
////---------------------------------------------------
////---------------------------------------------------

bool is_valid(int Win, int Hei, int m, int n) {
	if (Win < 20 || Hei < 20) {
		cout << "Too small a map" << endl;
		return false;
		
	}
	int court = (Win - 2) * (Hei - 2);
	if (m + n > court / 2) {
		cout << "Too many chests and monsters." << endl;
		return false;
	}
	return true;
}
void generatemap(map<vector<int>, block*>& gameboard, int Wid, int Hei, int Monster_number, int Chest_number) {
	//generate grounds
	for (int i = 1; i < Wid-1; i++) {
		for (int j = 1; j < Hei-1; j++) {
			vector<int> p = { i , j };
			block* blk = new block;
			blk->initial_G(p);
			//char a= blk->gettype();
			gameboard[p] = blk;
		}
	}
	//build border walls
	for (int i = 0; i < Wid; i++) {
		for (int j = 0; j < Hei; j++) {
			if ((i == 0) || (j == 0) || (i == Wid - 1) || (j == Hei - 1)) {
				vector<int> p = { i , j };
				block* blk = new block;
				blk->initial_W(p);
				gameboard[p] = blk;
			}
		}
	}

	//build buffer zone for movement, printing, in case NULL is met
	for (int i = -2; i < Wid + 2; i++) {
		for (int j = -2; j < Hei + 2; j++) {
			if (!(i >= 0 && i < Wid && j >= 0 && j < Hei)) {
				vector<int> p = { i,j };
				block* blk = new block;
				blk->initial_B(p);
				gameboard[p] = blk;
			}
		}
	}
	//populate the map with monsters and chests;
	//monster
	srand(time(NULL));
	for (int i(0); i < Monster_number; i++) {
		int x = rand() % Wid;
		int y = rand() % Hei;
		vector<int> p = { x,y };
		block* blok=gameboard[p];
		while (gameboard[p]->gettype()!='G') {
		    x = rand() % Wid;
			y = rand() % Hei;
			p = { x,y };
		}
		block* blk = new block;//use a dynamic block
		blk->initial_M(p,i+1);
		delete gameboard[p];//delete the ground block
		gameboard[p] = blk;
	}

	//adding chests
	for (int i(0); i < Chest_number; i++) {
		//randomly decide which chest to carry the key;
		int key_chest = rand() % Chest_number;
		int x = rand() % Wid;
		int y = rand() % Hei;
		vector<int> p = { x,y };
		while (gameboard[p]->gettype() != 'G') {
			x = rand() % Wid;
			y = rand() % Hei;
			p = { x,y };
		}
		block* blk = new block;
		blk->initial_C(p, i + 1);
		if (i == key_chest) {
			blk->fill_key();
		}
		delete gameboard[p];//delete the ground block
		gameboard[p] = blk;
	}
	//place the player
	int x = rand() % Wid;
	int y = rand() % Hei;
	vector<int> p = { x,y };
	while (gameboard[p]->gettype() != 'G') {
		x = rand() % Wid;
		y = rand() % Hei;
		p = { x,y };
	}
	block* blk = new block;//a dynamic block, stored on heap
	blk->initial_P(p);
	delete gameboard[p];//delete the ground block
	gameboard[p] = blk;
}
void move_player(map<vector<int>, block*>& gameboard, char& oper, vector<int>& playerpos) {
	char heading = gameboard[playerpos]->getheading();
	vector<int> previouspos = playerpos;
	switch (oper) {
	case 'w':
		switch (heading)
		{
		case 'N':
			playerpos[1]++;
			break;
		case 'E':
			playerpos[0]++;
			break;
		case 'W':
			playerpos[0]--;
			break;
		case 'S':
			playerpos[1]--;
			break;
		}
		break;
	case 's':
		switch (heading)
		{
		case 'N':
			playerpos[1]--;
			break;
		case 'E':
			playerpos[0]--;
			break;
		case 'W':
			playerpos[0]++;
			break;
		case 'S':
			playerpos[1]++;
			break;
		}
		break;
	case 'a':
		switch (heading)
		{
		case 'N':
			heading = 'W';
			break;
		case 'E':
			heading = 'N';
			break;
		case 'W':
			heading = 'S';
			break;
		case 'S':
			heading = 'E';
			break;
		}
		break;
	case 'd':
		switch (heading)
		{
		case 'N':
			heading = 'E';
			break;
		case 'E':
			heading = 'S';
			break;
		case 'W':
			heading = 'N';
			break;
		case 'S':
			heading = 'W';
			break;
		}
		break;
	}

	gameboard[playerpos]->renew_head(heading);
	char type = gameboard[playerpos]->gettype();
	if (type =='G'||type=='P') {
	block* temp = gameboard[playerpos];
	//point the pointer at the new position at the player
	gameboard[playerpos] = gameboard[previouspos];
	//point the previous place at the groung that temp is pointing to
	gameboard[previouspos] = temp;
	gameboard[playerpos]->renew_pos(playerpos);
    }
	else {
		if (type == 'W') {
			cout << "You are running into wall." << endl;;
		}
		else if (type == 'M') {
			cout << "You are running into monster." << endl;;
		}
		else if (type == 'C') {
			cout << "You are running into chest." << endl;;
		}
		playerpos = previouspos;
	}
    
}


void CM_RandomMove(map<vector<int>, block*>& gameboard, vector<int> playerpos) {
	for (auto& x : gameboard) {
		vector<int> moves = { 1,0,-1 };
		if (x.second->gettype() == 'M'|| x.second->gettype() == 'C')
		{
			vector<int> pos = x.second->getpos();
			if ((abs(playerpos[0] - pos[0]) > 3) || (abs(playerpos[1] - pos[1]) > 3))
			{
				vector<int> newpos=pos;
				int count = 0;
				do
				{
					//randomly choose a mode
					int x_which_move = rand() % 3;
					int y_which_move = rand() % 3;
					newpos = { pos[0] + moves[x_which_move], pos[1] + moves[y_which_move] };
					count++;
				} while (gameboard[newpos]->gettype() != 'G'&&count<10);
				//create a tempblock pointer pointing to the found ground
				block* temp = gameboard[newpos];
				//point the pointer on the new coordinate to the moved object
				gameboard[newpos] = gameboard[pos];
				//point the pointer on the old place to the temp ground
				gameboard[pos] = temp;
			}

			//if the monster is within the 7x7 around the player, fast monster pursuits every step
			//slow monster purisuit every other st
		}
	}
}
