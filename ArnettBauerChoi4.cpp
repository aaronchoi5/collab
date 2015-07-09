
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "unistd.h"

using namespace std;

int counter=0;

//================================================================Insertion Sort===============================================================\\

template <typename T>
//takes in a vector of any type and does insert sort:
void insertionSort(vector<T> &v){
  unsigned int i = 0;
  unsigned int j = 0;
  T temp = 0;
  for(i = 1; i < v.size(); i++){
    j = i;
    //when i goes up temp stores the value at array[j] and assigns the one before it to array[j] and then the [j-1] becomes the old [j] write it out if you wanna see
    while(j > 0 && v[j-1] > v[j]){
      temp = v[j];
      v[j] = v[j-1];
      v[j-1] = temp;
      j--;
      counter++;
    }
  }
}

//=================================================================Bubble Sort=================================================================\\

template <typename T>
void bubbleSort(vector<T> &v){

  bool sorted = false;
  while (!sorted) {
      sorted = true;
    for (int i = 0; i < v.size() - 1; i++) {
      counter++;  //number of comparisons
      if (v[i]> v[i + 1]) {
        sorted = false;
        T tmp = v[i];
        v[i] = v[i + 1];
        v[i + 1] = tmp;
      }
    }
  }

}

//==================================================================Merge Sort=================================================================\\

template<typename T>
void merge(vector<T> &a, vector<T> &b, vector<T> &ret){
  unsigned int ai = 0;
  unsigned int bi = 0;
  //vector<int> ret;
  while(ai < a.size() || bi < b.size()){ // pull numbers off!
    if( ai == a.size()){ // a is done
      ret.push_back(b[bi]);
      bi++;
    }else if(bi == b.size()){ // b is done
      ret.push_back(a[ai]);
      ai++;
    }else if( a[ai] < b[bi]){
      ret.push_back(a[ai]);
      ai++;
    }else{
      ret.push_back(b[bi]);
      bi++;
    }
    counter++;
  }
}

template <typename T>
void mergeSort(vector<T> &v){ // In place!
  // base case!
  if(v.size() <= 1){
    return;
  }
  // cut list into two halves
  unsigned int middle = v.size() / 2;
  vector<T> left;
  left.reserve(v.size());
  vector<T> right;
  right.reserve(v.size());
  for(unsigned int i = 0; i < v.size() ;i++){
    if(i < middle){
      left.push_back(v[i]);
    }else{
      right.push_back(v[i]);
    }
  }

  mergeSort(left);
  mergeSort(right);
  // merge them together!
  v.clear();
  merge(left, right, v);
}

//==================================================================Quick Sort=================================================================\\

template <typename T>
void quickSort(vector<T> &v, int left, int right) {
      int i = left, j = right;
      T tmp;
      T pivot = v[(left + right) / 2];
      /* partition section */
      while (i <= j) {
            counter++;
            while (v[i] < pivot)
                  i++;
            while (v[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = v[i];
                  v[i] = v[j];
                  v[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion section*/
      if (left < j)
            quickSort(v, left, j);
      if (i < right)
            quickSort(v, i, right);
}

//=================================================================Hybrid Sort=================================================================\\

//-------------------------------------------------------------Merge sort (hybrid)-------------------------------------------------------------\\

template <typename T>
void mergeHybridSort(vector<T> &v, string smaller,int threshold){ // In place!
  // base case!

  if(v.size() <= 1){
    return;
  }
  if(v.size() < threshold){
    if(smaller == "0"){
      bubbleSort(v);
      return;
    }
    else if(smaller == "1"){
      insertionSort(v);
      return;
    }
  }
  // cut list into two halves
  unsigned int middle = v.size() / 2;
  vector<T> left;
  left.reserve(v.size());
  vector<T> right;
  right.reserve(v.size());
  for(unsigned int i = 0; i < v.size() ;i++){
    if(i < middle){
      left.push_back(v[i]);
    }else{
      right.push_back(v[i]);
    }
  }

  mergeHybridSort(left, smaller, threshold);
  mergeHybridSort(right, smaller, threshold);
  // merge them together!
  v.clear();
  merge(left, right, v);
}

//-------------------------------------------------------------Quick Sort (hybrid)-------------------------------------------------------------\\

template <typename T>
void quickHybridSort(vector<T> &v, int left, int right, string smaller ,int threshold) {
      int i = left, j = right;
      T tmp;
      T pivot = v[(left + right) / 2];
      counter++;
      if(v.size() < threshold){
          if(smaller == "0"){
            bubbleSort(v);
          }
          else if(smaller == "1"){
            insertionSort(v);
          }
       }

      /* partition section */
      while (i <= j) {
            while (v[i] < pivot)
                  i++;
            while (v[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = v[i];
                  v[i] = v[j];
                  v[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion section*/
      if (left < j)
            quickHybridSort(v, left, j, smaller, threshold);
      if (i < right)
            quickHybridSort(v, i, right, smaller, threshold);
  }

//-----------------------------------------------------------------Hybrid Sort-----------------------------------------------------------------\\

template <typename T>
void hybridSort(vector<T> &v, string larger, string smaller, int threshold){


  if(v.size() > threshold){
    if(larger == "0"){
      mergeHybridSort(v, smaller, threshold);
      return;
    }
    else if(larger == "1"){
      quickHybridSort(v, 0, v.size()-1, smaller, threshold);
      return;
    }
  }
  else{
    cout << "Do not enter a threshold value greater than the size of the array!" << endl;
  }
}

//=============================================================================================================================================\\
//<<===========================================================END SORT ALGORITHMS===========================================================>>\\
//<<=========================================================BEGIN PROGRAM FUNCTIONS=========================================================>>\\
//===========================================================================================================================================>>\\

//-----------------------------------------------------------------Display List----------------------------------------------------------------\\

template<typename T>
void displayList(vector<T> &v){
    cout<<"[";
    for(unsigned int k=0; k<v.size()-1; k++){
        cout<<v[k]<<",";
    }
    cout<<v[v.size()-1]<<"]"<<endl;
    return;
}

//----------------------------------------------------------------List Generator---------------------------------------------------------------\\

template<typename T>
vector<T> listGenerator(vector<T> &A, int elements){      //assigns values to the inputted array.

    srand(time(0));
    int number = 0;

    for(int k=0; k<elements; k++){
        number = rand() % 1000;
        A.push_back(number);
    }

    return A;
}

//----------------------------------------------------------------Menu Function----------------------------------------------------------------\\

template <typename T>
void menuGenerator(){
    cout<<"Authors: Austin Arnett, Brian Bauer, Aaron Choi."<<endl;
    cout<<"Description:  This program is meant to analyze and compare the effectiveness of various sorting algorithms against each other.  ";
    cout<<"The algorithms compared are Merge Sort, Quick Sort, Insertion Sort, and Bubble Sort.  The user is asked to enter a threshold value ";
    cout<<"which will determine how long each algorithm is given to sort the elements.  The user will then be asked for the size of ";
    cout<<"the vector to be sorted.  Sizes of over 100 elements will be automatically generated, while if the user inputs a size less than ";
    cout<<"or equal to 100 the user will be given the option to either insert a vector manually or to have one automatically generated.  "<<endl;

    cout<<"BEGIN"<<endl;
    cout<<"Please enter the threshold value for hybrid sort: ";  //Threshold value is length for use by hybrid
    int threshold;
    cin>>threshold; cout<<endl;

    cout<<"Enter the quantity of elements to be sorted: ";
    unsigned int elements;
    cin>>elements; cout<<endl;

    vector<T> templist;
    vector<T> thelist;
    if(elements <= 100){
        bool makelist=false;
        cout<<"Would you like to manually enter the list? (1 for 'yes', 0 for 'no'.  If '0', the list will be generated for you): ";
        cin>>makelist;
        if(makelist){
            cout<<"Please begin entering the list:" << endl;
            T tempval;
            for(unsigned int k=0; k<elements; k++){  // user must enter as many elements as they ask for.
                cout<<k<<": ";
                cin>>tempval;
                thelist.push_back(tempval); // there is no check to make sure the entry is valid.
            }
        }
        else if(!makelist){
            thelist=listGenerator(templist, elements);  //the user said no to manually made list.  generate a list for them.
        }
        else{
            cout<<"invalid response start over"<<endl;
            return;
        }
        bool display=false;
        cout<<"Would you like the list to be displayed? (1 for 'yes', 0 for 'no'): ";
        cin>>display;
        if(display){
            displayList(thelist);
        }
    }
    else{
        thelist = listGenerator(templist, elements);
    }


    bool running = true;
    do{
      vector<T> copyvector = thelist;
      int choice;
      cout << "What sort do you want to do?:" << endl;
      cout << "1) Bubble Sort" << endl;
      cout << "2) Insert Sort" << endl;
      cout << "3) Quick Sort" << endl;
      cout << "4) Merge Sort" << endl;
      cout << "5) Hybrid Sort" << endl;
      cin >> choice;
      if(choice == 1){
        bubbleSort(copyvector);
        if(elements <= 100){
            displayList(copyvector);
        }
      }
      else if(choice == 2){
        insertionSort(copyvector);
        if(elements <= 100){
            displayList(copyvector);
        }
      }
      else if(choice == 3){
        quickSort(copyvector,0, thelist.size()-1);
        if(elements <= 100){
            displayList(copyvector);
        }
      }
      else if(choice == 4){
        mergeSort(copyvector);
        if(elements <= 100){
            displayList(copyvector);
        }
      }
      else if(choice == 5){
        string larger = "";
        string smaller = "";
        cout << "What do you want the sort to be if the list is larger than the threshold?" << endl;
        cout << "0) Merge Sort" << endl;
        cout << "1) Quick Sort" << endl;
        cin >> larger;
        if(larger != "0" && larger != "1"){
          cout << "You seem to have not been able to enter 0 or 1 please restart." << endl;
          continue;
        }
        cout << "What do you want the sort to be if the list is smaller than the threshold?" << endl;
        cout << "0) Bubble Sort" << endl;
        cout << "1) Insert Sort" << endl;
        cin >> smaller;
        if(smaller != "0" && smaller != "1"){
          cout << "You seem to have not been able to enter 0 or 1 please restart." << endl;
          continue;
        }
        hybridSort(copyvector,larger, smaller, threshold);
        if(elements <= 100){
            cout << "Original list: ";
            displayList(thelist);
            cout << endl;
            cout << "Sorted list: ";
            displayList(copyvector);
            cout << endl;
        }
      }
      cout<<"Number of comparisons: "<<counter<<endl;
      cout << "Do you want to choose a sort again? Enter 1 if you want to and 0 if you do not.";
      cin >> running;
      counter=0;  //global variable counting number of comparisons.



    }
    while(running);
    }

//---------------------------------------------------------------------Main--------------------------------------------------------------------\\

int main(){

    menuGenerator<int>();

  return 0;
}


