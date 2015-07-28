#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>

using namespace std;

class HashTable{
private:
    int key;
    int HashFunc(int key); //k is key
    int BucketArray[23] = { };
    double LoadRatio = 0.0;
    void FillTable();
    void PrintTable();
public:
    HashTable();
    void menu();
};

HashTable::HashTable(){

}

/*==================================================================Menu Function==================================================================*/

void HashTable::menu(){
    string UserInput;
    stringstream ss;
    cout << "Please enter a load ratio to begin (Please enter a 2 digit decimal)\nType \"help\" if your are ever confused.\n";
    while(1){
        cin >> UserInput;
        if(UserInput == "help")
            cout << "An example of inputting a load ratio of 25% would be entering \"0.25\"\n";
        else{
            stringstream(UserInput)>>LoadRatio;
            ss.clear();
            if(LoadRatio <= 0 || LoadRatio > 1){
                cout << "Please enter a valid range, input, or command\n";
            }
            else{
                break;
            }
            cout << "Try again (remember \"help\"): ";
        }
    }
    while(1){
        cout << "Now please select an option in order to create a table:" << endl
             << "(1) Insert the numbers into the hash table manually." << endl
             << "(2) Randomly generate and insert the numbers." << endl;
        cin >> UserInput;
    }
}


int main(){

    HashTable HashBrowns;
    HashBrowns.menu();

    return 0;
}
