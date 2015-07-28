#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class HashTable{
private:
    int key;
    int HashFunc(int key); //k is key
    int BucketArray[23] = { };
    double LoadRatio;
    void FillTable();
    void PrintTable();
public:
    HashTable();
    void menu();
};

/*==================================================================Menu Function==================================================================*/

void HashTable::menu(){

}
