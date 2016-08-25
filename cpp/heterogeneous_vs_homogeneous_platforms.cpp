// http://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

void decimal_to_binary(int * arr, int num, const int number_of_analytics);

int main()
{
    
    const int number_of_analytics=5;
    const int number_of_compute_units_architecture_A=5;
    const double compute_time_architecture_A[number_of_analytics]={40.0, 100.0, 10.0, 5.0, 2.0};
    const double compute_time_architecture_B[number_of_analytics]={30.0,  10.0,  8.0, 4.0, 1.0};

    ///*
     cout << "jobs are on architecture A: ";
     for(int indx=0; indx<number_of_analytics; indx++){
     cout << compute_time_architecture_A[indx] << ", ";
     }
     cout << endl;
     cout << "jobs are on architecture B: ";
     for(int indx=0; indx<number_of_analytics; indx++){
     cout << compute_time_architecture_B[indx] << ", ";
     }
    cout << endl << endl;
     //*/

    // baseline with existing infrastructure:
    double current_tts = 0;
    for (int indx=0; indx<number_of_compute_units_architecture_A; indx++){
        current_tts += compute_time_architecture_A[indx];
    }
    current_tts /= number_of_compute_units_architecture_A;
    cout << "current time-to-solution on existing "
         << number_of_compute_units_architecture_A
         << " compute units of architecture A: "
         << current_tts << endl << endl;
    
    // monetary values are in dollars
    const double cap_cost_per_compute_unit_A=30.0;
    const double cap_cost_per_compute_unit_B=50.0;
    const double oam_cost_per_compute_unit_A= 5.0;
    const double oam_cost_per_compute_unit_B= 8.0;
    
    const double money_to_invest_in_next_iteration=100.0;

    double available_money_for_next_iteration=0;
    available_money_for_next_iteration = money_to_invest_in_next_iteration -
        oam_cost_per_compute_unit_A*number_of_compute_units_architecture_A;
    cout << "money available for acquisition: "
         << available_money_for_next_iteration << endl << endl;

    // begin homogeneous strategy - buy more of A
    
    int number_of_total_compute_units_architecture_A;
    number_of_total_compute_units_architecture_A=
        number_of_compute_units_architecture_A +
        int((available_money_for_next_iteration)/(cap_cost_per_compute_unit_A+oam_cost_per_compute_unit_A));

    if (number_of_compute_units_architecture_A == number_of_total_compute_units_architecture_A){
        cout << "money available is not sufficient to buy more A. Exiting" << endl;
        exit(0);
    }
    
    cout << "number of A in next fiscal period: "
         << number_of_total_compute_units_architecture_A << endl;
    double homogeneous_tts = 0;
    for (int indx=0; indx<number_of_compute_units_architecture_A; indx++){
        homogeneous_tts += compute_time_architecture_A[indx];
    }
    homogeneous_tts /= number_of_total_compute_units_architecture_A;
    cout << "homogeneous time-to-solution on architecture A: "
         << homogeneous_tts << endl;

    // begin heterogenous strategy - supplement A with B
    int number_of_new_compute_units_architecture_B;
    number_of_new_compute_units_architecture_B=
        int((available_money_for_next_iteration)/(cap_cost_per_compute_unit_B+oam_cost_per_compute_unit_B));

    if (number_of_new_compute_units_architecture_B==0){
        cout << "money available is not sufficient to buy B. Exiting" << endl;
        exit(0);
    }
    
    cout << "number of B in next fiscal period: "
         << number_of_new_compute_units_architecture_B << endl;
    int arr[number_of_analytics];

    double minimum_tts;
    int minimum_indx;

    double time_on_a=0;
    double time_on_b=0;

    double best_time_on_A=0;
    double best_time_on_B=0;
    
    for (int indx=0; indx<pow(2,number_of_analytics); indx++){
        decimal_to_binary(arr, indx,number_of_analytics);

        /*
        cout << "arr: ";
        for(int indx=0; indx<number_of_analytics; indx++){
            cout <<  arr[indx] << ", ";
        }
        cout<<endl;
        //*/
        
        time_on_a=0;
        time_on_b=0;
        
        for (int jndx=0; jndx<number_of_analytics; jndx++){
            time_on_a +=  arr[jndx]*compute_time_architecture_A[jndx]/(number_of_compute_units_architecture_A*1.0);
            time_on_b += !arr[jndx]*compute_time_architecture_B[jndx]/(number_of_new_compute_units_architecture_B*1.0);
        }
        cout << endl << "time on A: " << time_on_a << "; time on B: " << time_on_b << endl;
        double longest_time=0;
        if (time_on_a>time_on_b){
            longest_time=time_on_a;
        }else{
            longest_time=time_on_b;
        }
        ///*
        cout << "longest time for this configuration: ";
        cout << longest_time << endl;
        //*/
        
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
        
        if (indx==0){
            minimum_tts = longest_time;
            minimum_indx=indx;
            best_time_on_A=time_on_a;
            best_time_on_B=time_on_b;
        }else{ // indx>0
            if (longest_time<minimum_tts){
                minimum_tts = longest_time;
                minimum_indx=indx;
                best_time_on_A=time_on_a;
                best_time_on_B=time_on_b;
            }
        }
        
    }
    cout << endl << "minimum tts: " << minimum_tts << endl;
    cout << "time on A: " << best_time_on_A << ";"
         << "time on B: " << best_time_on_B << endl;
   
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
    cout << "array A: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  arr[indx] << ", ";
    }
    cout<<endl;
    cout << "array B: ";
    for(int indx=0; indx<number_of_analytics; indx++){
        cout <<  !arr[indx] << ", ";
    }
    cout<<endl;
    //*/
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