// http://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
#include <iostream>
#include <cmath>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::setw;

void decimal_to_binary(int * arr, const int input_value, const int arr_size);

int main()
{
    
    const int number_of_existing_racks_of_a=5;
    const int number_of_analytics=5;
    const double cut_a[number_of_analytics]={40, 100, 10, 5, 2}; // architecture A
    const double cut_b[number_of_analytics]={30,  10,  8, 4, 1}; // architecture B

    cout << "current time-to-solution with " <<  number_of_existing_racks_of_a
         << " racks of architecture A: ";
    double total_time=0;
    for (int indx=0; indx<number_of_analytics; indx++){
        total_time += cut_a[indx];
    }
    cout << total_time/(number_of_existing_racks_of_a*1.0) << endl;

    double cap_cost_per_CU_A=30; // capital cost per compute unit of architecture A in dollars
    double cap_cost_per_CU_B=50; // capital cost per compute unit of architecture B in dollars
    double oam_cost_per_CU_A=5; // operations and maintenance cost per compute unit of architecture A in dollars
    double oam_cost_per_CU_B=8; // operations and maintenance cost per compute unit of architecture B in dollars

    double money_to_invest_in_next_iteration=100; // in dollars

    double available_money_for_next_iteration = 
        money_to_invest_in_next_iteration - oam_cost_per_CU_A*number_of_existing_racks_of_a;

    /*
    homogeneous strategy - buy more of architecture A
    */
    int NNCU_A=number_of_existing_racks_of_a + int((available_money_for_next_iteration)/(cap_cost_per_CU_A+oam_cost_per_CU_A));

    cout << "homogeneous time-to-solution with " <<  NNCU_A
         << " racks of architecture A: ";
    total_time=0;
    for (int indx=0; indx<number_of_analytics; indx++){
        total_time += cut_a[indx];
    }
    cout << total_time/(NNCU_A*1.0) << endl;

    /*
    heterogeneous strategey - buy architecture B to augment existing A
    */
    int NNCU_B=int((available_money_for_next_iteration)/(cap_cost_per_CU_B+oam_cost_per_CU_B));

    cout << "searching parameter space when money was invested in architecture B: " << endl;
   
    int arr[number_of_analytics];

    double minimum_tts;
    int minimum_indx;

    for (int indx=0; indx<pow(2,number_of_analytics); indx++){
        decimal_to_binary(arr, indx, number_of_analytics);
    
        double tot=0;
        for (int jndx=0; jndx<number_of_analytics; jndx++){
            tot +=  arr[jndx]*cut_a[jndx]/(number_of_existing_racks_of_a*1.0) +
                   !arr[jndx]*cut_b[jndx]/(NNCU_B*1.0);
        }
        cout << "time to solution: " << setw(10) << tot << "    A:";
        for (int jndx=0; jndx<number_of_analytics; jndx++){
            cout << arr[jndx];
        }
        cout << "   B:";
        for (int jndx=0; jndx<number_of_analytics; jndx++){
            cout << !arr[jndx];
        }
        cout << endl;
        
        if (indx==0){
            minimum_tts = tot;
            minimum_indx=indx;
        }else{ // indx>0
            if (tot<minimum_tts){
                minimum_tts = tot;
                minimum_indx=indx;
            }
        }
        
    }
    cout << "minimum tts: " << minimum_tts << endl;

    decimal_to_binary(arr, minimum_indx, number_of_analytics);
    cout << "which analytics from architecture A: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout << arr[indx]*cut_a[indx] << ", ";
    }
    cout<<endl;
    /*
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  arr[indx] << ", ";
    }
    cout<<endl;
    */

    cout << "which analytics from architecture B: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout << !arr[indx]*cut_b[indx] << ", ";
    }
    cout<<endl;
    /*
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  !arr[indx] << ", ";
    }
    cout<<endl;
    */
}

void decimal_to_binary(int * arr, const int input_value, const int arr_size){
    int counter=0;
    int remainder;
    int num=input_value;
    for (int indx=0; indx<arr_size; indx++){
        arr[indx]=0;
    }
    while(num!=0)
    {
        remainder = num%2;
        arr[counter++] = remainder;
        num /= 2;
    }

/*
    cout << "in the function: " << endl;
    for (int jndx=0; jndx<arr_size; jndx++){
        cout << "jndx=" << jndx << endl;
        cout << "arr @ jndx=" << arr[jndx] << endl;
    }
*/

}
