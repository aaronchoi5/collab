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
    double LoadRatio;
    double BucketArray[];

    // Methods
    int HashFunc(int);
    void FillTable(string choice);
    void PrintTable();
    void TableInsert(int index, int number);
    void LinearInsert(int index, int number);
public:
    // Constructor/Menu
    HashTable();
    void menu();
};

HashTable::HashTable(){

}

/*==================================================================Hash Function==================================================================*/
int HashTable::HashFunc(int key){
  return key % TableSize;
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
        BucketArray[TableSize];
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

/*==================================================================Linear Insert==================================================================*/
void HashTable::LinearInsert(int index, int tempkey){
    int i=1;
    while(BucketArray[index+i]!=.5){
        i++;
    }
    BucketArray[index+i]=tempkey;
    return;
}
/*===================================================================Table Insert==================================================================*/
void HashTable::TableInsert(int index, int tempkey){
    if(BucketArray[index]==.5){
        BucketArray[index]=tempkey;
    }
    else{
        LinearInsert(index, tempkey);  //collision resolution method
    }
    return;
}
/*====================================================================Fill Table===================================================================*/
void HashTable::FillTable(string choice){
    cout<<"initialized..."<<TableSize<<endl;
    for(int k=0; k<TableSize; k++){
            cout<<"boom";
        BucketArray[k]=.5;
    }
    cout<<"third element: "<<BucketArray[2]<<endl;
    int counter=0;
    int index;
    int tempkey;
    if(choice == "Manual"){
        while((counter/TableSize)<=LoadRatio){
            cout<<"input key: ";
            cin>>tempkey;
            index=HashFunc(tempkey);
            TableInsert(index, tempkey);
            counter++;
        }
    }
    else if(choice == "RNG"){
        srand(time(NULL));
        while((counter/TableSize)<=LoadRatio){
            tempkey=rand();
            index=HashFunc(tempkey);
            TableInsert(index, tempkey);
            counter++;
        }
    }
    return;
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
