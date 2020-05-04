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


//Edited by Victor/////////start////
void random_move(chest*& c, map<vector<int>, string> gameboard) {
	switch(rand()%4)
	{
	case 0:
		if (gameboard[W direction][0] == 'G') //If the chest tries to walk towards a wall, monster or other chest, it wont be able to do it.
			(c->position)[1]++;        // This also takes the situation that the chest is cornered then it will not be able to move.
		break;
	case 1:
		if (gameboard[E direction][0] == 'G')
			(c->position)[0]++;
		break;
	case 2:
		if (gameboard[S direction][0] == 'G')
			(c->position)[1]--;
		break;
	case 3:
		if (gameboard[A direction][0] == 'G')
			(c->position)[0]--;
		break;
	}
}
//Edited by Victor/////////end//////
	
	
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

//Edited by Victor///////////start////
void attack() {
    	if (swordnumber>0){ //Probably add number of sword and potion since there maybe more than 1?
        	cout << "You strike the lock with your sword!" << endl;
        	cout << "The demon lies on the ground, lifeless. You killed it." << endl;
        	monster->life=0;
    	}else{
        	cout << "You punched the demon." << endl;
		int health point = monster->life;
		switch (health point){
            	case 3:
                	monster->life=2;
                	cou << "The demon looks painful. Looks like a couple more punches are needed." << endl;
                	break;
            	case 2:
                	monsterhp->1;
                	cou << "The demon hardly stands. Looks like one final hit will do the job!" << endl;
                	break;
            	case 1:
                	monsterhp->0;
                	cou << "The demon lies on the ground lifeless. You did it." << endl;
                	demon->life=0;
                	break;
        }
    }
}

void chest_interaction() {
    	if (exitchest){ //Boolean value whether the chest is the exit. There should only be one exit chest out of all chest.
        	if (swordnumber>0){ //Player prioritize using sword over bare hand
            		switch (swordstatus) //Probably a boolean value which change when get sword or use sword
            		{
                	cout << "You strike the lock with your sword!" << endl;
                	case "Perfect":
                    		cout << "A crack has appeared on your sword. It is likely to break into pieces after the next strike on the chest." << endl;
                    		swordstatus="Damaged";
                    		break;
                	case "Damaged":
                    		cout << "After the strike on the chest, your sword breaks into pieces." << endl;
                    		swordnumber--;
                    		swordstatus="Perfect"; // The status return normal since it only applies when the player has a sword
		    		if (swordnumber>0){
		    			cout << "You wield another sword from your inventory";
		    		}
                    		break;
                	cheststatus=0;
            		}
        	}else{
            		cout << "You smash the chest with your bare hand!" << endl; 
            		switch cheststatus{
                	case 2:
                    		cout << "A crack appears on the lock. Regardless of the pain on your hand, you should be able to break it next time." << endl;
                    		cheststatus=1;
                    		break;
                	case 1;
                    		cout << "The lock breaks!" << endl;
                    		cheststatus=0;
                    		break;
            		}
        	}
        	if (cheststatus==0){
            		switch (rand()%2+1){ //3 cases of chest's reward
                	case 0:
                    		cout << "Unlucky! The chest is empty!" << endl;
                    		break;
                	case 1:
                    		if (swordnumber>0)
			    		cout << "This chest contains a sword. The sword has been added into your inventory." << endl;
                    		else
					cout << "You wielded the sword." << endl;
		    		swordnumber++;
                    		break;
                	case 2:
                    		cout << "This chest contains a glass of potion. The potion has been added into your inventory." << endl;
                    		potionnumber++;
                    		break;
        	}
    	}else if (key==false){
        	cout << "This is the exit chest. Please eliminate the last monster in this dungeon to obtain the key before proceeding." << endl;
    	}else{
        	cout << "This is the end! Congratulations for surviving this dungeon!" << endl;
		//boolean value change to True, thus ending the loop in main function
    	}
}
//Edited by Victor//////////end//
