#include <iostream>
#include <sstream>
#include "GatorAVL.h"
using namespace std;


string isNameValid(string theName) { //makes sure name input by user has only letters //from project 1 breakdown ppt
	string name = theName;
	for (char c : name) {
		if (!isalpha(c)) {
			return "unsuccessful";
		}
	}
	return name;
}

string isIDValid(string theID) { //makes sure UFID input by user has only digits and is 8 characters long //from project 1 breakdown ppt
	string ID = theID;
	
	if(ID.length() != 8) {
		return "unsuccessful";
	}

	for (char c : ID) {
		if (!isdigit(c)) {
			return "unsuccessful";
		}
	}
	return ID;
}

int main() {
	AVLTree tree;
	// read in number of commands
	// for each command, execute on tree
	int numOfCommands;
	cin >> numOfCommands; 
	int counter = 0;

	for(int i = 0; i <= numOfCommands; i++) {
		string line;
		getline(cin, line);
		istringstream in(line);

		string command;
		in >> command;

		if (command == "insert") { // Runs when insert command is called 
			string firstQuotationPass; //Bypasses the first quotation mark for the name input 
			getline(in, firstQuotationPass, '"');
		
			string name; //Gets the name and stores it in string name without the second quotation mark
			getline(in, name, '"');

			string ID;
			in >> ID;

			if(isNameValid(name) != "unsuccessful" && isIDValid(ID) != "unsuccessful") {
				tree.insert(name, ID); //inserts name and ID into tree 
				cout << "successful" << endl; 
			}
			else {
				cout << "unsuccessful" << endl;
			}
		}

		else if (command == "remove") { // Runs when remove command is called 
			string ID;
			in >> ID;
			if(isIDValid(ID) != "unsuccessful") {
				tree.removeID(ID);
			}
			else {
				cout << "ID Not Valid" << endl;
			}
		}

		else if (command == "search") { // Runs when searchID or searchName is called 
			string IDorName;
			in >> IDorName;
			
			int numCheck;
			for (int i = 0; i < IDorName.length(); i++) {
				numCheck = isdigit(IDorName.at(i)); ////determines if we are searching for a UFID or a name 

				if (numCheck) { //if we are searching of an ID, runs this statement 

					Node* resultID = tree.searchID(IDorName); // searches tree for ID number 

					if (resultID == nullptr) { // if ID does not exist, prints unsuccessful 
						cout << "unsuccessful" << endl; 
						break;
					}
					else {
					cout << resultID->name << endl;
					break;
					}
				}
				else { //if we are searching for a name, runs this statement 
					string name;
					name = IDorName.substr(1, IDorName.length()-2); //takes name without the quotation marks 
					vector<string> IDsByName = tree.searchName(name); //stores vector of IDs with corresponding names from the searchName function
					if(IDsByName.empty()) { //if the name was not found and the ID not stored, returns unsuccessful 
						cout << "unsuccessful" << endl; 
						break;
					}
					else {
						for (string theIDs : IDsByName) { //prints IDs that correspond to the name searched by the user 
							cout << theIDs << endl; 
						}
						break;
					}
				}
			}
		}
		
		else if(command == "printInorder") { //prints inorder traversal of tree 
			tree.printTreeInorder();
			cout << endl;
		}

		else if(command == "printPreorder") { //prints preorder traversal of tree
			tree.printTreePreorder();
			cout << endl;
		}

		else if(command == "printPostorder") { //prints postorder traversal of tree 
			tree.printTreePostorder();
			cout << endl;
		}

		else if(command == "printLevelCount") {
			tree.printLevelCount();	
			cout << endl;
		}

		else if(command == "removeInorder") { // Runs when removeInorder command is called 
			string NthGatorID;
			in >> NthGatorID;
			tree.removeInorderN(NthGatorID);
		}
		else {
			if(counter != 0) { //makes sure unsuccessful does not print when user inputs number of commands at start 
			cout << "end.unsuccessful" << endl;
			}
		}
		counter++; 
	}
		
	return 0;
}
