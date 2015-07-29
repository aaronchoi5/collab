#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>

using namespace std;

class HashTable{
private:
    // Data
    int TableSize;
    int Num_of_keys;
    double LoadRatio = 0.0;
    int BucketArray[23] = { };

    // Methods
    int HashFunc(int);
    void FillTable(string choice);
    void PrintTable();
public:
    // Constructor/Menu
    HashTable();
    void menu();
};

HashTable::HashTable(){

}

/*==================================================================Menu Function==================================================================*/

void HashTable::menu(){
    string UserInput;

    cout << "To begin, enter a Hash Table size: ";
    while(1){
        cin >> UserInput;
        stringstream(UserInput)>>TableSize;
        if(TableSize <= 0)
            cout << "Do not falter young padawon, you must enter a number greater than 0.\n";
        else
            break;
    }
    cout << "Now ";
    while(1){
        cout << "enter the number of keys (make sure the number is prime): ";
        cin >> UserInput;
        stringstream(UserInput)>>Num_of_keys;
        if(Num_of_keys <= 0){
            cout << "Avast ye scurvy dawg, enter a number greater 'tan zero!\n";
        }
        else
            break;
    }

    cout << "Please enter a load ratio (A 2 digit decimal)\nType \"help\" if your are confused.\n";
    while(1){
        cin >> UserInput;
        if(UserInput == "help")
            cout << "An example of inputting a load ratio of 25% would be entering \"0.25\"\n";
        else{
            stringstream(UserInput)>>LoadRatio;
            if(LoadRatio <= 0 || LoadRatio > 1){
                cout << "Please enter a valid range, input, or command\n";
            }
            else{
                break;
            }
            cout << "Try again (remember \"help\"): ";
        }
    }
    cout << "Now ";
    while(1){
        cout << "please select an option in order to create a table:\n"
             << "(1) Insert the numbers into the hash table manually.\n"
             << "(2) Randomly generate and insert the numbers.\n";
        cin >> UserInput;
        if(UserInput == "1"){
            FillTable("Manual");
            break;
        }
        else if (UserInput == "2"){
            FillTable("RNG");// "RNG" stands for "Random Number Generator"
            break;
        }
        else
            cout << "Please enter 1 or 2 to make a choice. (\"help\" is not available here)\n";
    }
}

/*====================================================================Fill Table===================================================================*/
void HashTable::FillTable(string choice){
    if(choice == "Manual"){

    }
}

/*==================================================================Print Table====================================================================*/
void HashTable::PrintTable(){
    if(TableSize<50){
        cout<<"[";
        for(int k=0; k<TableSize-1; k++){
            if(BucketArray[k]==.5){
                cout<<" ,";
            }
            else{
                cout<<BucketArray[k]<<",";
            }
        }
        if(BucketArray[TableSize-1]==.5){
            cout<<" ]"<<endl;
        }
        else{
            cout<<BucketArray[TableSize-1]<<"]"<<endl;
        }
    }
    return;
}

int main(){

    HashTable HashBrowns;
    HashBrowns.menu();

    return 0;
}
