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
    string BucketArray[2000];
    string collRes;

    // Methods
    int HashFunc(string lekey);
    void FillTable(string choice);
    void PrintTable();
    void TableInsert(int index, string tempkey, string collRes);
    void LinearInsert(int index, string tempkey);
    void QuadraInsert(int index, string tempkey);
    void ChainInsert(int index, string tempkey);
    void DoubleHashing(int index, string tempkey);
public:
    struct Node{
        float value;
        Node* next;
    };
    // Constructor/Menu
    HashTable();
    void menu();
};

HashTable::HashTable(){
}

/*==================================================================Hash Function==================================================================*/
int HashTable::HashFunc(string key){
    int intkey=0;
    stringstream(key)>>intkey;
  return intkey % TableSize;
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

    cout<<"Choose a collision resolution scheme:"<<endl<<"1) linear probing"<<endl<<"2) quadratic probing"<<endl;
    cout<<"3) double hashing"<<endl<<"4) chaining"<<endl<<"5) exit"<<endl;
    cin>>collRes;
    while(collRes!="1"
          && collRes!="2"&&collRes!="3"&&collRes!="4"&& collRes!="5"){
        cout<<"Please enter a number 1 through 5: ";
        cin>>collRes;
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
void HashTable::LinearInsert(int index, string tempkey){
    int i=1;
    while(BucketArray[index+i]!=".5"){
        i++;
    }
    BucketArray[index+i]=tempkey;
    return;
}
/*==================================================================Quadra Insert==================================================================*/
void HashTable::QuadraInsert(int index, string tempkey){
    int i=1;
    while(BucketArray[(index+i*i)%TableSize]!=".5"){
        i++;
    }
    BucketArray[(index+i*i)%TableSize]=tempkey;
    return;
}
/*===================================================================Chain Insert==================================================================*/
void HashTable::ChainInsert(int index, string tempkey){

    if(BucketArray[index]!=".5"){
        BucketArray[index]=BucketArray[index]+" "+tempkey;
    }
    return;
}

/*==================================================================Double Hashing=================================================================*/
void HashTable::DoubleHashing(int index, string tempkey){
    int intkey;
    stringstream(tempkey)>>intkey;
    int i=1;
    while(BucketArray[(index+i*(20-intkey%20))%TableSize]!=".5"){
        i++;
        cout << i << endl;
    }
    BucketArray[(index+i*(20-intkey%20))%TableSize]=tempkey;
    return;
}
/*===================================================================Table Insert==================================================================*/
void HashTable::TableInsert(int index, string tempkey, string collRes){
    if(BucketArray[index]==".5"){
        BucketArray[index]=tempkey;
    }
    else if(collRes=="1"){
        LinearInsert(index, tempkey);  //collision resolution method
    }
    else if(collRes=="2"){
        QuadraInsert(index, tempkey);
    }
    else if(collRes=="3"){
        DoubleHashing(index, tempkey);
    }
    else if(collRes=="4"){
        ChainInsert(index, tempkey);
    }
    return;
}

//void HashTable::ArrayInit(){
//return;
//    }
/*====================================================================Fill Table===================================================================*/
void HashTable::FillTable(string choice){
    for(int i = 0; i < TableSize; i++){
        BucketArray[i] = ".5";
    }
    cout<<"initialized..."<<TableSize<<endl;
    cout<<"third element: "<<BucketArray[2]<<endl;
    int counter=0;
    int index;
    string tempkey;
    if(choice == "Manual"){
        while((counter/TableSize)<=LoadRatio && counter<Num_of_keys){
            cout<<"input key: ";
            cin>>tempkey;
            index=HashFunc(tempkey);
            TableInsert(index, tempkey, collRes);
            counter++;
        }
    }
    else if(choice == "RNG"){
        srand(time(NULL));
        while((counter/TableSize)<=LoadRatio && counter<Num_of_keys){
            int RandNum;
            stringstream ss;
            RandNum=rand()%100000;
            ss << RandNum;
            tempkey = ss.str();
            index=HashFunc(tempkey);
            TableInsert(index, tempkey, collRes);
            counter++;
        }
    }
    PrintTable();
    return;
}

/*==================================================================Print Table====================================================================*/
void HashTable::PrintTable(){
    if(TableSize<50){
        cout<<"[";
        for(int k=0; k<TableSize-1; k++){
            if(BucketArray[k]==".5"){
                cout<<"NULL,";
            }
            else{
                cout<<BucketArray[k]<<",";
            }
        }
        if(BucketArray[TableSize-1]==".5"){
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
