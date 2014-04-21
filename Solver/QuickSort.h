#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <vector>
#include <cmath>

const double seed = 3298712;
const double Modulus = 2147483647;
const double multiplier = 69621;

template<class T>
class CQuickSort
{
public:
	CQuickSort(){};
	~CQuickSort(){};
  void Sort(std::vector<T> *p_vec)
  {
	int size = (*p_vec).size();

	  //return is array is empty or 1
	  if(size>1)
	  {
		// pick an initial random pivot index
		double random, temp, randomNum;
		int randomIndex;
		random = fmod((multiplier*seed),Modulus);
		randomNum = random/Modulus;
		randomIndex=(int)(randomNum*(size-1));

		// partition array
		int left=0, right = randomIndex;

		// sort array
		QuickSort(p_vec,left,(size-1));
	  }
	
  }

  void QuickSort(std::vector<T> *p_vec,int left, int right) {

	T temp,pivot;
	int geBegin;

     if(left<right) 
     {
	  pivot = (*p_vec)[right];
	  geBegin = left;
	
	for(int i=left;i<right;i++)
	{
	  if((*p_vec)[i]<pivot)
	  {
	    temp = (*p_vec)[geBegin];
	    (*p_vec)[geBegin] = (*p_vec)[i];
	    (*p_vec)[i] = temp;
	    geBegin++;
	  }
	}
	temp = (*p_vec)[right];
	(*p_vec)[right] = (*p_vec)[geBegin];
	(*p_vec)[geBegin] = temp;
	
	QuickSort(p_vec,left,(geBegin-1));
	QuickSort(p_vec,(geBegin+1),right);
	
     }

  }

};

#endif
