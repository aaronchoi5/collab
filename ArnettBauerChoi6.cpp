#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

int counter=0;

//==============================================================Comparison Counter=============================================================\\

//This function, "Comparison Counter" (CC for short) counts up every time a comparison is made
bool CC(string i, string mode, string j){
    //Increment counter
    counter++;
    //Check case
    if(mode == "!="){
        if (i != j) return true; else return false;
    }
    else if(mode == "=="){
        if (i == j) return true; else return false;
    }
    else{
        cout << "wrong input, user should not ever see this message, fix code" << endl;
        counter--;
        return false;
    }
}

/*=================================================================Class Definition================================================================*/

class HashTable{
private:
    // Data
    int TableSize;    //The range of elements selected within "BucketArray"
    int Num_of_keys;  // obvious
    double LoadRatio; // also obvious
    int TotalInsertions;
    int TotalComparisons;
    string collRes;   // collision-resolution scheme
    string BucketArray[2000]; //initialized at compile time for most practical ranges. User is unable to change this (due to arrays being static).
    struct KeyNode{//An array of keys determined at run time
        string value;
        KeyNode* next;
    } *head, *Key;//pointer to head node and pointer for traversing the array.

    // Methods
    void InitKeyArray(int Num_of_keys);
    int HashFunc(string lekey); //Hash function given in assignment
    void FillKeyArray(string choice); //
    void PrintTable(); //obvious
    void Key2Table(string KeyVal, string collRes);
    void ResetTable(); //Resets the table to NULL values
    //collision-resolution schemes
    void LinearInsert(int index, string KeyVal);
    void QuadraInsert(int index, string KeyVal);
    void ChainInsert(int index, string KeyVal);
    void DoubleHashing(int index, string KeyVal);
public:
    // Constructor/Menu
    HashTable(); //Constructor (does nothing).
    void menu(); //User interactivity.
};

/*===================================================================Constructor===================================================================*/

HashTable::HashTable(){
    TableSize = 0;
    Num_of_keys = 0;
    LoadRatio = 0;
    TotalInsertions = 1;
    TotalComparisons = 0;
    collRes = "";
    for(int i = 0; i < 2000; i++){
        BucketArray[i] = "NULL";
    }
    head = nullptr;
    Key = nullptr;
}

/*==================================================================Menu Function==================================================================*/

void HashTable::menu(){
    string UserInput;//It's the user's input

    //Set TableSize
    cout << "To begin, enter a Hash Table size (make sure the number is prime): ";
    while(1){
        cin >> UserInput;
        stringstream(UserInput)>>TableSize; //converts string to int. (returns 0 on failure... e.g. "Words")
        if(TableSize > 0 && TableSize <= 2000)//Correct range
            break;//exit loop on correct input
        else//Incorrect input/range
            cout << "Do not falter young padawon, you must enter a number greater than 0. (and <= 2000)\n";
    }

    //Set Num_of_keys
    cout << "Now ";
    while(1){
        cout << "enter the number of keys: ";
        cin >> UserInput;
        stringstream(UserInput)>>Num_of_keys; //string to int.
        if(Num_of_keys > 0)//no upper limit to number of keys... load ratio catches infinite numbers.
            break;//exit loop on correct input
        else//Incorrect input/range
            cout << "Avast ye scurvy dawg, enter a number greater 'tan zero!\n";
    }

    //Set LoadRatio
    cout << "Please enter a load ratio as a decimal.\nType \"help\" for an example of the correct format.\n";
    while(1){
        cin >> UserInput;
        if(UserInput == "help")
            cout << "An example of inputting a load ratio of 25% would be entering \"0.25\" (or \".25\")\n";
        else{
            stringstream(UserInput)>>LoadRatio;//string to double
            if(LoadRatio > 0 && LoadRatio <= 1)//correct range
                break;
            else{
                cout << "Please enter a valid range, input, or command (> 0 and <= 1)\n";
                cout << "Try again (remember \"help\"): ";
            }
        }
    }

    //Initialize a list for keys
    InitKeyArray(Num_of_keys);

    //Fill list of keys
    cout << "Now ";
    while(1){
        cout << "please select an option in order to create a table:\n"
        << "(1) Insert the numbers into the hash table manually.\n"
        << "(2) Randomly generate and insert the numbers.\n";
        cin >> UserInput;
        if(UserInput == "1"){
            while(Num_of_keys > 50){
                cout << "Are you sure you want to input them manually? You have more than 50 keys. (y/n)\n";
                cin >> UserInput;
                if(UserInput == "y")
                    break;
                else if(UserInput == "n")
                    break;
                else
                    cout << "Come on now... input \"y\" or \"n\" for yes or no\n";
            }
            if(UserInput == "n") continue; //If the user had more than 50 keys, and wanted to reconsider inputting them manually, reset.
            FillKeyArray("Manual");
            break;
        }
        else if (UserInput == "2"){
            FillKeyArray("RNG");// "RNG" stands for "Random Number Generator"
            break;
        }
        else
            cout << "Please enter 1 or 2 to make a choice. (\"help\" is not available here)\n";
    }

    while(1){
        cout<<"Choose a collision resolution scheme:"<<endl<<"1) linear probing"<<endl<<"2) quadratic probing"<<endl;
        cout<<"3) double hashing"<<endl<<"4) chaining"<<endl<<"5) exit"<<endl;
        cin>>collRes;
        while(collRes!="1"&&collRes!="2"&&collRes!="3"&&collRes!="4"&&collRes!="5"){
            cout<<"Please enter a number 1 through 5: ";
            cin>>collRes;
        }
        if(collRes == "5") break;
        Key = head;//Reset Key to beginning of array
        for(int i = 0; (double)(i+1)/(double)TableSize<LoadRatio && i<Num_of_keys; i++){
            Key2Table(Key->value, collRes);
            Key = Key->next;
        }
        PrintTable();
        ResetTable();
    }
    return;
}
/*=================================================================Init Key Array==================================================================*/
void HashTable::InitKeyArray(int Num_of_keys){
    //first node
    head = new KeyNode;
    head->value = "NULL";
    head->next = nullptr;

    KeyNode *PrevNode = head;

    //the remaining nodes
    for(int i = 0; i < Num_of_keys-1; i++){
        //creation
        KeyNode *NewNode = new KeyNode; //create new node
        NewNode->value = "NULL";             //set data
        NewNode->next = nullptr;        //set next to null

        //pointers
        PrevNode->next = NewNode;       //Set PrevNode's pointer
        PrevNode = NewNode;             //Set PrevNode to current node
    }

    return;
}

/*==================================================================Hash Function==================================================================*/
int HashTable::HashFunc(string key){
    int intkey=0;
    stringstream(key)>>intkey;
    return intkey % TableSize;
}

/*==================================================================Linear Insert==================================================================*/
void HashTable::LinearInsert(int index, string KeyVal){
    int i=1;
    while(CC(BucketArray[index+i],"!=","NULL")){
        i++;
    }
    BucketArray[index+i]=KeyVal;
    return;
}
/*==================================================================Quadra Insert==================================================================*/
void HashTable::QuadraInsert(int index, string KeyVal){
    int i=1;
    while(CC(BucketArray[(index+i*i)%TableSize],"!=","NULL")){
        i++;
    }
    BucketArray[(index+i*i)%TableSize]=KeyVal;
    return;
}
/*===================================================================Chain Insert==================================================================*/
void HashTable::ChainInsert(int index, string KeyVal){

    if(CC(BucketArray[index],"!=","NULL")){
        BucketArray[index]=BucketArray[index]+" & "+KeyVal;
    }
    return;
}

/*==================================================================Double Hashing=================================================================*/
void HashTable::DoubleHashing(int index, string KeyVal){
    int intkey;
    stringstream(KeyVal)>>intkey;
    int i=1;
    while(CC(BucketArray[(index+i*(20-intkey%20))%TableSize],"!=","NULL")){
        i++;
    }
    BucketArray[(index+i*(20-intkey%20))%TableSize]=KeyVal;
    return;
}
/*===================================================================Key to Table==================================================================*/
void HashTable::Key2Table(string KeyVal, string collRes){
    int index = HashFunc(KeyVal);
    TotalInsertions++;

    if(CC(BucketArray[index],"==","NULL")){
        BucketArray[index]=KeyVal;
    }
    else if(collRes=="1"){
        LinearInsert(index, KeyVal);  //collision resolution method
    }
    else if(collRes=="2"){
        QuadraInsert(index, KeyVal);
    }
    else if(collRes=="3"){
        DoubleHashing(index, KeyVal);
    }
    else if(collRes=="4"){
        ChainInsert(index, KeyVal);
    }
    return;
}

//void HashTable::ArrayInit(){
//return;
//    }
/*==================================================================Fill Key Array=================================================================*/
void HashTable::FillKeyArray(string choice){
    /*int counter=0;
    int index;
    string KeyVal;*/
    Key = head;
    if(choice == "Manual"){
        for(int i = 0; i < Num_of_keys; i++){
            cout << "input key #" << i+1 << ": ";
            cin >> Key->value;
            Key = Key->next;
        }
    }
    else if(choice == "RNG"){
        srand(time(NULL));
        for(int i = 0; i < Num_of_keys; i++){
            int RandNum;
            stringstream ss;
            RandNum = (rand()%100000+rand()%100000+rand()%100000+rand()%100000)/4; //average of 4 random numbers "to avoid statistical biasing"
            ss << RandNum; Key->value = ss.str(); //convert type int to type string and store in Key->value.
            Key = Key->next;//increment
        }
    }
    //PrintTable();
    return;
}

/*==================================================================Reset Table====================================================================*/
void HashTable::ResetTable(){
    for(int i = 0; i < TableSize; i++){
        BucketArray[i] = "NULL";
    }
    return;
}

/*==================================================================Print Table====================================================================*/
void HashTable::PrintTable(){
    TotalComparisons = counter;
    if(TableSize<=50){
        cout<<"[";
        for(int k=0; k<TableSize-1; k++){
            if(k%10 == 0 && k!=0)//formats the table to 10 elements per line
                cout << "\n ";
            cout<<BucketArray[k]<<",";
        }
        cout<< BucketArray[TableSize-1] << "]\n";
    }
    cout << "The average number of comparisons: " << fixed << setprecision(3) << (double)TotalComparisons/(double)TotalInsertions << endl;
    return;
}

/*=======================================================================Main======================================================================*/
int main(){

    HashTable HashBrowns;

    HashBrowns.menu();

    return 0;
}
