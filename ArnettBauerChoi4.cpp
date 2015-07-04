
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "unistd.h"
using namespace std;

template <typename T>
//takes in a vector of any type and does insert sort:
void insert(vector<T> moo){
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

void bubble(vector<T> mort){
  
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
void quickSort(vector<T> &v ) {
      int left = 0;
      int right = v.size()-1
      int i = left, j = right;
      T tmp;
      int pivot = v[(left + right) / 2];
      int left = 0;
      int right = v.size()-1;
 
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
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

int main(){

  return 0;
}
