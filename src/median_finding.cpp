//
// Created by kaustubh0x77 on 31/3/19.
//

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

template <class T>
T findMedian5size(std::vector<T>& arr, int l, int r){
    sort(arr.begin() + l, arr.begin() + r + 1);
    return arr[(l+r)/2];
}

template <class T>
int partition(vector<T>& v, int l, int r, int x){
    int i;
    for(i = l; i < r; i++){
        if(v[i] == x)
            break;
    }

    swap(v[i],v[r]);

    i = l;
    for(int j = l; j < r; j++){
        if (v[j] <= x){
            swap(v[i],v[j]);
            i++;
        }
    }
    swap(v[i],v[r]);
    return i;
}

/**
 *
 */




template <class T>
T kth_smallest(vector<T> v, int l, int r, int k){
    //int l = v.size();
    if(!(k > 0 && k <= r -l + 1)){
        //return T::MAX_INT;
        return INT_MAX;
        //exit(123);
    }

    int n = r - l + 1;
    vector<T> medians;//((n+4)/5);
    medians.reserve((n+4)/5);
    int i = 0;
    for(i = 0; i < n/5; i++){
        medians.push_back(findMedian5size(v,l+5*i,l+5*i+4));
    }

    if(i*5 < n){
        medians.push_back(findMedian5size(v,l+5*i,v.size()-1));
        i++;
    }

    T medOfMed = (i == 1) ? medians[i-1] : kth_smallest(medians,0,i-1,i/2);

    int pos = partition(v,l,r,medOfMed);

    if (pos-l == k-1)
        return v[pos];
    if (pos - l > k - 1)
        return kth_smallest(v,l,pos-1,k);

    return kth_smallest(v,pos+1,r,k-pos+l-1);



}


/**
 * This function implements the quickselect algorithm
 * @tparam T class for which you have to find the median
 * @param input an stl vector container of the object who's median you want to find
 * @return
 */
template <class T>
T find_median(vector<T> input){
    return kth_smallest(input,0,input.size()-1,input.size()/2);
}
