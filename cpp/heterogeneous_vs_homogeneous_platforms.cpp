// http://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

void decimal_to_binary(int * arr, int num, const int number_of_analytics);

int main()
{
    
    const int number_of_analytics=4;
    const int number_of_racks_of_a=5;
    const int number_of_racks_of_b=3;
    const double compute_time_architecture_A[number_of_analytics]={4.0, 8.0, 10.0, 20.0};
    const double compute_time_architecture_B[number_of_analytics]={2.0, 3.0, 9.0,  18.0};

    /*
    cout << "jobs are on architecture A: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout << compute_time_architecture_A[indx] << ", ";
    }
    cout << endl;
    cout << "jobs are on architecture B: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout << compute_time_architecture_B[indx] << ", ";
    }
    cout << endl;
    */
    
    int arr[number_of_analytics];

    double minimum_tts;
    int minimum_indx;

    for (int indx=0; indx<pow(2,number_of_analytics); indx++){
        decimal_to_binary(arr, indx,number_of_analytics);
    
        
        double time_on_a=0;
        double time_on_b=0;
        for (int jndx=0; jndx<number_of_analytics; jndx++){
            time_on_a +=  arr[jndx]*compute_time_architecture_A[jndx]/(number_of_racks_of_a*1.0);
            time_on_b += !arr[jndx]*compute_time_architecture_B[jndx]/(number_of_racks_of_b*1.0);
        }
        double longest_time=0;
        if (time_on_a>time_on_b){
            longest_time=time_on_a;
        }else{
            longest_time=time_on_b;
        }
        /*
        cout << "longest time for this configuration: ";
        cout << longest_time << endl;
        */
        if (indx==0){
            minimum_tts = longest_time;
            minimum_indx=indx;
        }else{ // indx>0
            if (longest_time<minimum_tts){
                minimum_tts = longest_time;
                minimum_indx=indx;
            }
        }
        
    }
    cout << "minimum tts: " << minimum_tts << endl;
   
    decimal_to_binary(arr, minimum_indx, number_of_analytics);
    cout << "which jobs are on architecture A: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  arr[indx]*compute_time_architecture_A[indx] << ", ";
    }
    cout<<endl;
    cout << "which jobs are on architecture B: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout << !arr[indx]*compute_time_architecture_B[indx] << ", ";
    }
    cout<<endl;
    /*
    cout << "array A:";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  arr[indx] << ", ";
    }
    cout<<endl;
    cout << "array B:";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  !arr[indx] << ", ";
    }
    cout<<endl;
    */
}

void decimal_to_binary(int * arr, int num, const int number_of_analytics){
    int counter=0;
    int remainder;
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