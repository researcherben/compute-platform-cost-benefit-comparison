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
    int cut_a[number_of_analytics],cut_b[number_of_analytics];
    cut_a[0]=4;
    cut_a[1]=8;
    cut_a[2]=10;
    cut_a[3]=20;
    cut_b[0]=2;
    cut_b[1]=3;
    cut_b[2]=9;
    cut_b[3]=18;
    
    int arr[number_of_analytics];
    for (int indx=0; indx<pow(2,number_of_analytics); indx++){
        decimal_to_binary(arr, indx);
        for(int indx=number_of_analytics-1; indx>=0; indx--)
            cout<< arr[indx];
        cout<<endl;
        for(int indx=number_of_analytics-1; indx>=0; indx--)
            cout<< !arr[indx];
        cout<<endl;
        cout<<endl;
    }
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