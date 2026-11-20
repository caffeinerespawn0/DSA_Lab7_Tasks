#include<iostream>
#include<algorithm>
using namespace std;

int partition(int arr[],int low,int high,int &swaps){
    int pivot=arr[high];
    int i=low;
    int j=high-1;

    while(i<=j){
        while(i<=j && arr[i]<=pivot){
            i++;
        }
        while(j>=i && arr[j]>pivot){
            j--;
        }
        if(i<j){
            swap(arr[i],arr[j]);
            swaps++;
            i++;
            j--;
        }
    }

    if(i!=high){
        swap(arr[i],arr[high]);
        swaps++;
    }

    cout<<"Array after pivot placement: ";
    for(int x=0;x<=high;x++){
        cout<<arr[x]<<" ";
    }
    cout<<endl;
    cout<<"Pivot "<<pivot<<" final position: "<<i+1<<endl;

    return i;
}

void quickSelect(int arr[],int low,int high,int k,int &swaps,int &skipped){
    if(low<=high){
        int p=partition(arr,low,high,swaps);

        if(p==k-1){
            if(low<p){
                skipped++;
            }
            if(p<high){
                skipped++;
            }
            return;
        }
        else if(k-1<p){
            if(p<high){
                skipped++;
            }
            quickSelect(arr,low,p-1,k,swaps,skipped);
        }
        else{
            if(low<p){
                skipped++;
            }
            quickSelect(arr,p+1,high,k,swaps,skipped);
        }
    }
}

int main(){
    int n,k;
    int swaps=0;
    int skipped=0;

    cout<<"Enter number of parcels: ";
    cin>>n;

    if(n<=0){
        cout<<"Invalid number of parcels"<<endl;
        return 0;
    }

    int* arr=new int[n];

    for(int i=0;i<n;i++){
        cout<<"Enter weight of parcel "<<i+1<<": ";
        cin>>arr[i];
    }

    cout<<"Enter K: ";
    cin>>k;

    if(k<1 || k>n){
        cout<<"Invalid K"<<endl;
        delete[] arr;
        return 0;
    }

    quickSelect(arr,0,n-1,k,swaps,skipped);

    cout<<"K-th lightest weight: "<<arr[k-1]<<endl;
    cout<<"Total swaps: "<<swaps<<endl;
    cout<<"Groups skipped: "<<skipped<<endl;

    delete[] arr;
    return 0;
}
