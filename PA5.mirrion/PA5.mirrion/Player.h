#pragma once
#include <list>
#include <string>
#include <fstream>
#include <iostream>

#define MONSTER 1
#define TRAP 2
#define SPELL 3
#define FACEUP 1
#define FACEDOWN 0
#define DEACTIVE 0

using namespace std;

struct cardNode {
	int id;
	int count = 0;
	string name;
	string description;
	int attack;
	int defense;
	int type;
	int level;
	int active;//works with DEACTIVE
	int faceing;//works with FACEDOWN
	int summon;
	int mode;
};

class Player
{

public:
	int health;
	list<cardNode> _hand;

	Player() {
		this->loadMaster();
		this->printDeck();
		this->createCard();
		this->printDeck();
	}

	void printDeck() {
		/* TODO: research iterating through a list in c++ */
		for (auto it = this->_hand.begin(); it != this->_hand.end(); it++) {
			cout << "Name: " << it->name << " Attack: " << it->attack << " Defense: " << it->defense << " Type: " << it->type << endl;
			cout << "Description: " << it->description << endl << endl;
		}
	}

	void addCard(string name, string description, int attack, int defense, int type, int level) {
		cardNode newNode;
		newNode.name = name;
		newNode.description = description;
		newNode.attack = attack;
		newNode.defense = defense;
		newNode.type = type;
		newNode.level = level;
		this->_hand.push_back(newNode);
	}

	void removeCard(cardNode badCard) {
		for (auto it = this->_hand.begin(); it != this->_hand.end(); it++) {
			// somehow find badCard in list
			//then call | this->_hand.erase() | with the value as a parameter (look at open tab) with "it" being your iterator object needed as a parameter
			//WHEN YOU FIND THE VALUE YOU WANT TO ERASE, PASS THE ITERATOR TO THE .erase() method. not the value you used to find that iterator.
		}

	}

	void loadMaster() {
		ifstream infile;
		infile.open("masterDeck.txt", ios::in);
		while (!infile.eof())
		{
			string token;
			getline(infile, token, '$');
			if (token == "")
				break;
			string name = token;

			getline(infile, token, '$');
			string description = token;

			getline(infile, token, '$');
			int attack = stoi(token);

			getline(infile, token, '$');
			int defense = stoi(token);

			getline(infile, token, '$');
			int type = stoi(token);

			getline(infile, token, '\n');
			int level = stoi(token);

			this->addCard(name, description, attack, defense, type, level);
		}
	}

	void createCard() {
		string name;
		cout << "What is your card's name?" << endl;
		getline(cin, name);

		string discription;
		cout << "What is your card's discription?" << endl;
		getline(cin, discription);

		//Card attack input and check
		int attack;
		do {
			cout << "What is your card's attack power? attack power must be greater then or equal to 0." << endl;
			cin >> attack;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(attack >= 0)) {
				cout << "That is not a valid answer. Try again." << endl;
			}
		} while (!(attack >= 0));

		//Card defence input and check
		int defense;
		do {
			cout << "What is your card's defence? Defence must be greater then or equal to 0." << endl;
			cin >> defense;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(defense >= 0)) {
				cout << "That is not a valid answer. Try again." << endl;
			}
		} while (!(defense >= 0));

		//Card type input and check
		int type;
		do {
			cout << "What card type are you creating?" << endl;
			cout << "Spell	   Trap  Monster" << endl;
			cout << "  1	    2       3" << endl;
			cin >> type;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(type == SPELL || type == TRAP || type == MONSTER)) {
				cout << "That is not a valid answer. Try again." << endl;
			}
		} while (!(type == SPELL || type == TRAP || type == MONSTER));

		//Card level input and check.
		int level;
		do {
			cout << "What level is your card? 1-12" << endl;
			cin >> level;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (!(level <= 12 && level >= 1)) {
				cout << "That is not a valid answer. Try again." << endl;
			}
		} while (!(level <= 12 && level >= 1));

		this->addCard(name, discription, attack, defense, type, level);
		this->addCardToFile(name, discription, attack, defense, type, level);
	}

	void addCardToFile(string name, string discription, int attack, int defense, int type, int level) {
		string marker = "$";
		string data;

		data.append(name);
		data.append(marker);
		data.append(discription);
		data.append(marker);
		data.append(to_string(attack));
		data.append(marker);
		data.append(to_string(defense));
		data.append(marker);
		data.append(to_string(type));
		data.append(marker);
		data.append(to_string(level));
		data.append("\n");

		ofstream outfile("masterDECK.txt", ios_base::app);
		if (outfile.is_open()) {
			outfile << data;
			outfile.close();
		}
	}

};

