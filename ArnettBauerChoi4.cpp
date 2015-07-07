
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "unistd.h"
using namespace std;

template <typename T>
//takes in a vector of any type and does insert sort:
void insert(vector<T> &moo){
  unsigned int i = 0;
  unsigned int j = 0;
  T temp = 0;
  for(i = 1; i < moo.size(); i++){
    j = i;
    //when i goes up temp stores the value at array[j] and assigns the one before it to array[j] and then the [j-1] becomes the old [j] write it out if you wanna see
    while(j > 0 && moo[j-1] > moo[j]){
      temp = moo[j];
      moo[j] = moo[j-1];
      moo[j-1] = temp;
      j--;
    }
  }
}

template <typename T>

void bubble(vector<T> &mort){

  bool sorted = false;
  int maxIdx = mort.size() - 1;
  while (!sorted) {
      sorted = true;
    for (int i = 0; i < mort.size() - 1; i++) {
      if (mort[i]> mort[i + 1]) {
        sorted = false;
        T tmp = mort[i];
        mort[i] = mort[i + 1];
        mort[i + 1] = tmp;
    }
  }
    maxIdx--;
       }

}
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

template <typename T>
void quickSort(vector<T> &v, int left, int right) {
      int i = left, j = right;
      T tmp;
      int pivot = v[(left + right) / 2];


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
            quickSort(v, left, j);
      if (i < right)
            quickSort(v, i, right);
}

void displayList(vector<int> &lelist){
    cout<<"[";
    for(unsigned int k=0; k<lelist.size()-1; k++){
        cout<<lelist[k]<<",";
    }
    cout<<lelist[lelist.size()-1]<<"]"<<endl;
    return;
}

vector<int> listGenerator(vector<int> &A, int elements){      //assigns values to the inputted array.
    for(int k=0; k<elements; k++){
        A.push_back(k);
    }
    int temp;
    for(int k=0; k<A.size()-1; k=k+2){
        temp=A[k+1];
        A[k+1]=A[k];
        A[k]=temp;
    }

    return A;
}

vector<int> hybridSort(vector<int> &derVektor){
return derVektor;
}

bool menuGenerator(vector<int> &emptylist){
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

    bool hybridbool=false;
    if(elements>threshold){
        hybridbool=true;
    }

    vector<int> templist;
    vector<int> thelist;
    if(elements <= 100){
        bool makelist=false;
        cout<<"Would you like to manually enter the list? (1 for 'yes', 0 for 'no'.  If '0', the list will be generated for you): ";
        cin>>makelist;
        if(makelist){
            cout<<"Please begin entering the list:"<<endl;
            int tempval;
            for(unsigned int k=0; k<elements; k++){  // user must enter as many elements as they ask for.
                cout<<k<<": ";
                cin>>tempval;
                thelist.push_back(tempval); // there is no check to make sure the entry is valid.
            }
            emptylist=thelist;
        }
        else if(!makelist){
            emptylist=listGenerator(templist, elements);  //the user said no to manually made list.  generate a list for them.
        }
        else{
            cout<<"invalid response"<<endl;
            return hybridbool;
        }
        bool display=false;
        cout<<"Would you like the list to be displayed? (1 for 'yes', 0 for 'no'): ";
        cin>>display;
        if(display){
            displayList(emptylist);
        }

    }
    else{
        emptylist=listGenerator(templist, elements);
    }
    return hybridbool;
    }

int main(){
    vector<int> workeronni;
    menuGenerator(workeronni);
    quickSort(workeronni, 0, workeronni.size());
    cout<<"sorted: "<<endl;
    displayList(workeronni);
/*    vector<int> pleaseronni;
    listGenerator(pleaseronni, 11);
    cout<<"list generated"<<endl;
    displayList(pleaseronni);
    insert(pleaseronni);
    cout<<"after: ";
    displayList(pleaseronni);*/
  return 0;
}
