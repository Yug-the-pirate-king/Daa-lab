#include<stdio.h>

struct min_max
{
    int min;
    int max;
};

struct min_max find_min_max(int arr[], int low,int high){
    struct min_max result, mml,mmr;
    int mid = low + (high-low)/2;

    if(low == high){
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    if(high - low == 2){
        if(arr[high] >= arr[low]){
            result.max = arr[high];
            result.min = arr[low];
        }else{
            result.max = arr[low];
            result.min = arr[high];
        }
        return result;
    }

    mml = find_min_max(arr,low,mid);
    mmr = find_min_max(arr,mid+1,high);

    if(mml.max >= mmr.max){
        result.max = mml.max;
    }
    else{
        result.max = mmr.max;
    }

    if(mml.min >= mmr.min){
        result.min = mmr.min;
    }
    else{
        result.min = mml.min;
    }

    return result;
};

int main(){
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int n = sizeof(arr)/sizeof(int);

    struct min_max printout = find_min_max(arr,0,n-1);

    printf("The max : %d \n",printout.max);
    printf("The min : %d \n",printout.min);
}

