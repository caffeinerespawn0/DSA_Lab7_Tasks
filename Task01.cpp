#include<iostream>
#include<string>
using namespace std;
//keep cutting the list until every part has just 1 patient
//array of objects
class Hospital{
public:
    string name;
    int uscore;
    int time;

    Hospital(){
        name="";
        uscore=0;
        time=0;
    }
};

void printPart(Hospital hospitals[],int low,int high){
    for(int i=low;i<=high;i++){
        cout<<hospitals[i].name<<"("<<hospitals[i].uscore<<","<<hospitals[i].time<<") ";
    }
    cout<<endl;
}

void merge(Hospital hospitals[],int low,int mid,int high,int &comparisons){
    //sizes of left and right arrays
    int n1=mid-low+1;
    int n2=high-mid;

    //temp arrays
    Hospital *L=new Hospital[n1];
    Hospital *R=new Hospital[n2];

    int i=0;
    int j=0;
    int k=low;

    for(int i=0;i<n1;i++){
        L[i]=hospitals[low+i];
    }

    for(int j=0;j<n2;j++){
        R[j]=hospitals[mid+1+j];
    }

    //join both parts in order
    while(i<n1 && j<n2){
        comparisons++;

        if(L[i].uscore>R[j].uscore){
            hospitals[k]=L[i];
            i++;
        }
        else if(R[j].uscore>L[i].uscore){
            hospitals[k]=R[j];
            j++;
        }
        else if(L[i].time<=R[j].time){
            hospitals[k]=L[i];
            i++;
        }
        else{
            hospitals[k]=R[j];
            j++;
        }

        k++;
    }

    //copy remaining patients
    while(i<n1){
        hospitals[k]=L[i];
        i++;
        k++;
    }

    while(j<n2){
        hospitals[k]=R[j];
        j++;
        k++;
    }

    cout<<"Join: ";
    printPart(hospitals,low,high);

    delete[] L;
    delete[] R;
}

void mergeSort(Hospital hospitals[],int low,int high,int &comparisons){
    if(low<high){
        int mid=low+(high-low)/2;

        //print every cut
        cout<<"Cut:"<<endl;
        cout<<"Left part: ";
        printPart(hospitals,low,mid);

        cout<<"Right part: ";
        printPart(hospitals,mid+1,high);

        mergeSort(hospitals,low,mid,comparisons);
        mergeSort(hospitals,mid+1,high,comparisons);

        merge(hospitals,low,mid,high,comparisons);
    }
}

int main(){
    int n;
    int comparisons=0;

    cout<<"Enter number of patients"<<endl;
    cin>>n;

    if(n<=0){
        cout<<"Invalid number of patients"<<endl;
        return 0;
    }

    Hospital *hospitals=new Hospital[n];

    //input patients
    for(int i=0;i<n;i++){
        cout<<"Enter the details of Patient: "<<i+1<<endl;

        cout<<"Name: ";
        cin>>hospitals[i].name;

        cout<<"Urgency: ";
        cin>>hospitals[i].uscore;

        cout<<"Time of arrival: ";
        cin>>hospitals[i].time;
    }

    mergeSort(hospitals,0,n-1,comparisons);

    //print final patient list
    cout<<endl<<"Final patient list:"<<endl;

    for(int i=0;i<n;i++){
        cout<<"Patient "<<i+1<<": ";
        cout<<"Name: "<<hospitals[i].name<<" ";
        cout<<"Urgency: "<<hospitals[i].uscore<<" ";
        cout<<"Time of arrival: "<<hospitals[i].time<<endl;
    }

    cout<<"Total comparisons: "<<comparisons<<endl;

    cout<<"First patient to see the doctor: "<<hospitals[0].name<<endl;

    delete[] hospitals;
    return 0;
}