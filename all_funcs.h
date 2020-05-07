#pragma once
#include <iostream>
#include <map>
#include<vector>
#include<string>
using namespace std;

class block{
private:
	char type;//W G C M P
	char heading;
	string name;
	int life;
	char speed;//f s
	bool saber;
	int saberlife;
	bool potion;
	int player_potion;
	vector<int> position;
	bool key;
public:
	//all the constructors
	void initial_W(vector<int> p) {
		type = 'W';
		position = p;
	}
	void print_parameter();
	void initial_G(vector<int> p) {
		type = 'G';
		position = p;
		//needed for printing location
	}
	void initial_B(vector<int> p) {
		type = 'B';
		position = p;
	}
	void initial_C(vector<int> p, int n) {
		srand(time(NULL));
		type = 'C';
		name = 'C' + std::to_string(n);
		life = 3;
		int a = rand() % 10;
		if (a == 0 || a == 1 || a == 2) {
			saber = true;
			potion = false;
			key = false;
		}
		if (a == 3 || a == 4 || a == 5 || a == 6 || a == 7 || a == 8) {
			saber = false;
			potion = true;
			key = false;
		}
		if (a == 9) {
			saber = false;
			potion = false;
			key = false;
		}
		position = p;
	}
	void fill_key() {
		saber = false;
		potion = false;
		key = true;
	}
	void initial_M(vector<int> p, int n) {
		srand(time(NULL));
		type = 'M';
		name = 'M' + std::to_string(n);
		life = 2;
		int a = rand() % 2;
		if (a == 0) {
			speed = 'f';
		}
		else {
			speed = 's';
		}
		position = p;
	}
	void initial_P(vector<int> p) {
		type = 'P';
		heading = 'N';
		life = 20;
		saberlife = 3;
		player_potion = 0;
		position = p;
	}
	vector<int> getpos() {
		return position;
	}
	char gettype() {
		return type;
	}
	char getheading() {
		return heading;
	}
	char getspeed() {
		return speed;
	}
	int getlife() {
		return life;
	}
	int getsaberlife() {
		return saberlife;
	}
	int getpotionnum() {
		return player_potion;
	}
	string getname() {
		return name;
	}
	bool getsaber() {
		return saber;
	}
	
	bool getpotion() {
		return potion;
	}
	void renew_life(int l) {
		life = l;
	}
	void change_type(char i) {
		type = i;
	}
	bool getkey() {
		return key;
	}
	void change_speed() {
		if (speed == 'f') {
			speed = 's';
			std::cout << "You administered potion on monster " << name << " and it became slow." << endl;
		}
		else {
			std::cout << "You are trying to slow down a slow monster, and wasting a bottle of potion" << endl;
		}
	}

	void renew_pos(std::vector<int> pos);
	void renew_head(char h);
	void deduce_life();
	void monster_pursuit(std::map<std::vector<int>, block*>& gameboard, std::vector<int> playerpos);
	void monster_follow(std::map<std::vector<int>, block*>& gameboard, std::vector<int> preplayerpos, std::vector<int> playerpos);
	vector<vector<int>> player_peri_mons(std::map<std::vector<int>, block*>& gameboard, int circle);
	void print_peripheral(std::map<std::vector<int>, block*> gameboard);
	void player_be_attacked(std::map<std::vector<int>, block*>& gameboard);
	void player_attack_CM(std::map<std::vector<int>, block*>& gameboard, char oper);
};
void generatemap(map<vector<int>, block*>& gameboard, int Wid, int Hei, int Monster_number, int Chest_number);
void move_player(map<vector<int>, block*>& gameboard, char& oper, vector<int>& playerpos);
void CM_RandomMove(map<vector<int>, block*>& gameboard, vector<int> playerpos);
bool is_valid(int Win, int Hei, int m, int n);