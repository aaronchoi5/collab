/*
Authors: Austin Arnett, Aaron Choi, Brian Bauer
Course: Data Structures
Instructor: Anca Ralescu
TA: Suryadip Chakraborty
Abstract:  The program times 3 different algorithms for checking different sized arrays for repeated elements.
Preconditions:  User must be able to use the stimulus in his or her eye to view the screen and
                observe the efficiency of each IsUnique function.
Postconditions: returns a table with the times of the different algorithms on different sized arrays.
*/

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<ctime>
#include<vector>

using namespace std;



void randomArray(int length, int A[]){      //assigns values to the inputted array.
    srand((unsigned)time(NULL));
    for(int k=0; k<length; k++){
        A[k]=rand() % (length*10) + 1;
    }
    return;
}

void PrintArray(int length, int A[]){
    if(length>20){
        return;
    }
    std::cout << "Given: [";
    for(int i = 0; i < length-1; i++){
        std::cout << A[i] << ", ";
    }
    std::cout << A[length-1] << "]" << std::endl;

    return;
}


void selectionSort(int tharray[], int length){   //selection sort
    int minni=0;
    int swapper;
    for(int j=0; j<length-1; j++){
        for(int k=j+1; k<length; k++){
            if(tharray[k]<tharray[minni]){
                minni=k;
            }
        }
        if(minni!=j){
            swapper=tharray[minni];
            tharray[minni]=tharray[j];
            tharray[j]=swapper;
        }
    }
    return;
}

void bubbleSort(int A[], int length){   //classic bubble sort
    bool done=false;
    int temp;
    while(!done){
        done=true;
        for(int k=1; k< length; k++){
            if(A[k]< A[k-1]){
                temp=A[k];
                A[k]=A[k-1];
                A[k-1]=temp;
                done=false;
            }
        }
    }
    return;
}

void QuickSort(int Array[], int first, int last){
    int i = first, j = last;
    int tmp;
    int pivot = Array[first + (last-first)/2];

    // partition
    while (i <= j) {
        while (Array[i] < pivot)
              i++;
        while (Array[j] > pivot)
              j--;
        if (i <= j) {
              tmp = Array[i];
              Array[i] = Array[j];
              Array[j] = tmp;
              i++;
              j--;
        }
    };

    // recursion
    if (first < j)
        QuickSort(Array, first, j);

    if (i < last)
        QuickSort(Array, i, last);
    return;
}

bool isUnique1(int A[], int first, int last){
    if(first>=last){
        return true;
    }
    if(!isUnique1(A, first, last-1)){
        return false;
    }
    if(!isUnique1(A, first+1, last)){
       return false;
    }
//std::cout << "test" << std::endl;
//std::cout << first << " " << A[first] << " " << last << " " << A[last] << std::endl;
    return (A[first]!=A[last]);
}

bool isUnique2(int A[], int first, int last){
    if(first>=last){
        return true;
    }
    for(int k=first; k<last; k++){
        for(int j=k+1; j<=last; j++){
            if(A[k]==A[j]){
                return false;
            }
        }
    }
    return true;
}


bool isUnique3(int A[], int first, int last){
    if(first>=last){
        return true;
    }

    QuickSort(A, first, last);//assuming quick sort is the fastest
    for(int i = first; i < last; i++){
        if(A[i] == A[i+1]){
            return false;
        }
    }
    return true;
}

int main(){
    int length=50;
    int Array[length];
std::cout << "Array has been initialized" << std::endl;
    randomArray(length,Array);
std::cout << "After random generation" << std::endl;
    PrintArray(length,Array);
    int bubbleArray[length];
    for(int k=0; k<length; k++){  //makes bubbleArray a copy of Array
        bubbleArray[k]=Array[k];
    }
    bubbleSort(bubbleArray, length);
std::cout << "after bubble sort" << std::endl;
    int selectionArray[length];
    for(int k=0; k<length; k++){  //makes selectionArray a copy of Array
        selectionArray[k]=Array[k];
    }
    selectionSort(selectionArray, length);  // selection sort
std::cout << "after selection sort" << std::endl;
    int QuickArray[length];
    for(int k=0; k<length; k++){  //makes QuickArray a copy of Array
        QuickArray[k]=Array[k];
    }
    PrintArray(length,QuickArray);
    QuickSort(QuickArray, 0, length);
std::cout << "after quick sort" << std::endl;
   // for(int k=0; k<length; k++){
     //   cout<<"Quick: "<<QuickArray[k]<<endl;
    //}
std::cout << "Before Time" << std::endl;
     std::clock_t    start1;

     start1 = std::clock();
std::cout << "Before Algorithm 1" << std::endl;
     if(isUnique1(Array,0,length)==true){
      cout<<"Algorithm 1 says it is unique."<< endl;
     }
std::cout << "After Algorithm 1" << std::endl;
     std::cout << "Time: " << (std::clock() - start1) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

     std::clock_t    start2;

     start2 = std::clock();
     if(isUnique2(Array, 0, length)==true){
      cout<<"Algorithm 2 says it is unique."<< endl;
     }
     std::cout << "Time: " << (std::clock() - start2) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

     std::clock_t    start3;

     start3 = std::clock();
     PrintArray(length,Array);
     if(isUnique3(Array, 0, length)==true){
      cout<<"Algorithm 3 says it is unique."<< endl;
     }
     std::cout << "Time: " << (std::clock() - start3) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    return 0;
}
