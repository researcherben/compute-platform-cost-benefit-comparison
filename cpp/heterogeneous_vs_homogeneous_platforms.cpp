// http://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

void decimal_to_binary(int * arr,const int number_of_analytics);

int main()
{
    
    int number_of_analytics=4;
    int number_of_racks_of_a=5;
    int number_of_racks_of_b=3;
    double cut_a[number_of_analytics],cut_b[number_of_analytics];
    cut_a[0]=4.0;
    cut_a[1]=8.0;
    cut_a[2]=10.0;
    cut_a[3]=20.0;
    cut_b[0]=2.0;
    cut_b[1]=3.0;
    cut_b[2]=9.0;
    cut_b[3]=18.0;
    
    int arr[number_of_analytics];

    double minimum_tts;
    int minimum_indx;

    for (int indx=0; indx<pow(2,number_of_analytics); indx++){
        decimal_to_binary(arr, indx);
    
        double tot=0;
        for (int jndx=0; jndx<number_of_analytics; jndx++){
            tot +=  arr[jndx]*cut_a[jndx]/(number_of_racks_of_a*1.0) +
                   !arr[jndx]*cut_b[jndx]/(number_of_racks_of_b*1.0);
        }
        cout << tot << endl;
        if (indx==0){
            minimum_tts = tot;
            minimum_indx=indx;
        }else{ // indx>0
            if (tot<minimum_tts){
                minimum_tts = tot;
                minimum_indx=indx;
            }
        }
        
        /*
        for(int indx=number_of_analytics-1; indx>=0; indx--)
            cout<< arr[indx];
        cout<<endl;
        for(int indx=number_of_analytics-1; indx>=0; indx--)
            cout<< !arr[indx];
        cout<<endl;
        cout<<endl;
        */
    }
    cout << "minimum tts: " << minimum_tts << endl;

    decimal_to_binary(arr, minimum_indx);
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  arr[indx]*cut_a[indx] << ", ";
    }
    cout<<endl;
    for(int indx=0; indx<number_of_analytics; indx++){
        cout << !arr[indx]*cut_b[indx] << ", ";
    }
    cout<<endl;
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  arr[indx] << ", ";
    }
    cout<<endl;
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  !arr[indx] << ", ";
    }
    cout<<endl;
}

void decimal_to_binary(int * arr,const int number_of_analytics){
    int counter=0;
    int remainder;
    int num=number_of_analytics;
    for (int indx=0; indx<number_of_analytics; indx++){
        arr[indx]=0;
    }
    while(num!=0)
    {
        remainder = num%2;
        arr[counter++] = remainder;
        num /= 2;
    }

}