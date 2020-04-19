#include <iostream>
#include <vector>
using namespace std;

struct monster {
public:
	vector<int> position;
	int life;
	monster()
	{
		life = 2;
	}
	/*monster(vector<int> n_position, int n_life)
	{
		position = n_position;
		life = n_life;
	}
	vector<int> getposition() {
		return position;
	}
	int getlife() {
		return life;
	}*/

};

struct chest {
	vector<int> position;
	bool key;
	int life;
	chest() {
		key = false;
		life = 3;
	}
	/*chest(vector<int> n_position,bool thekey) {
		position = n_position;
		key = thekey;
	}
	vector<int> getposition() {
		return position;
	}
	int getlife() {
		return life;
	}
	bool getkey() {
		return key;
	}*/
	
	
};

struct player
{
	vector<int> position;
	bool sword;
	bool potion;
	bool key;
	char direction;
	int life;
	player() 
	{
		sword = true;
		potion = false;
		key = false;
		direction = 'N';
		life = 5;
	}
	/*player(bool n_sword, bool n_potion, bool n_key, char n_direction, int n_life)
	{   
		sword = n_sword;
		potion = n_potion;
		key = n_key;
		direction = n_direction;
		life = n_life;
	}
	bool getsword() {
		return sword;
	}
	bool getpotion() {
		return potion;

	}
	bool getkey() {
		return potion;

	}
	char getdirection() {
		return direction;
	}*/

};