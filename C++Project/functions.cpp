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


void attack() {
    cout << "The monster strikes at you!" << endl;
    hp->life--;
    if (sabernumber>0){
        cout << "You strike the lock with your sword!" << endl;
        cout << "The demon lies on the ground, lifeless. You killed it." << endl;
        demon->false;
    }else{
        cout << "You punched the demon." << endl;
        switch (monsterhp){
            case 3:
                monsterhp->2;
                cou << "The demon looks painful. Looks like a couple more punches are needed." << endl;
                break;
            case 2:
                monsterhp->1;
                cou << "The demon hardly stands. Looks like one final hit will do the job!" << endl;
                break;
            case 1:
                monsterhp->0;
                cou << "The demon lies on the ground lifeless. You did it." << endl;
                demon->false;
                break;
        }
    }
}


void chest_interaction() {
    if (chestnum>1){
        if (sabernumber>0){
            switch (saberstatus)
            {
                cout << "You strike the lock with your sword!" << endl;
                case "Perfect":
                    cout << "A crack has appeared on your sword. It is likely to break into pieces after the next strike on chest." << endl;
                    saberstatus->"Damaged";
                    break;
                case "Damaged":
                    cout << "After the strike on the chest, your sword breaks into pieces." << endl;
                    sword-=1;
                    if (sword>=0){
                        cout << "You wield another sword in your hand." << endl;
                        saberstatus->"Perfect";
                    break;
                    }
                cheststatus=0;
            }
        }else{
            cout << "You smash the chest with your bare hand!" << endl; 
            switch cheststatus{
                case 2:
                    cout << "A crack appears on the lock. Regardless of the pain on your hand, you should be able to break it next time." << endl;
                    cheststatus->1;
                    break;
                case 1;
                    cout << "The lock breaks!" << endl;
                    cheststatus->0;
                    break;
            }
        }
        if (cheststatus==0){
            switch (rand()%2+1){
                case 0:
                    cout << "Unlucky! The chest is empty!" << endl;
                    break;
                case 1:
                    cout << "This chest contains a sword. The saber has been added into your inventory." << endl;
                    swordnumber+=1;
                    cout << swordnumber << " sword in total." << endl;
                    break;
                case 2:
                    cout << "This chest contains a glass of potion. The potion has been added into your inventory." << endl;
                    potionnumber+=1;
                    break;
        }
    }else if (key==false){
        cout << "This is the exit chest. Please eliminate the last monster in this dungeon to obtain the key before proceeding." << endl;
    }else{
        cout << "This is the end! Congratulations for surviving this dungeon!" << endl;
    }
}
