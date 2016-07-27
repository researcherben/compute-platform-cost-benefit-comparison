// $ g++ costbenefit_with_outages_with_moores_law.cpp 

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

void soln_count(int max_number_of_days,int hours_in_a_day,
                int minutes_in_an_hour, int availability, 
                double* time_to_solution_in_minutes,double* solutions_count,
                int* time_in_days,int time_to_market_in_days);
/*
void cost_per_soln(int max_number_of_days);
void tco(int max_number_of_days);
*/
void print_results(int max_number_of_days,int* time_in_days,
                   double* solutions_count, double* cost_per_solution,
                   double* total_cost_of_ownership);

int main(){
    /* contants */
    int hours_in_a_day=24;
    int minutes_in_an_hour=60;
    int days_in_a_year=365;
    int number_of_years=5; // lifespan of systems being investigated
    double normalization_of_money_spent=1000000.0; // a million bucks

    int max_number_of_days=0; // used to set array sizes
    max_number_of_days=days_in_a_year*number_of_years; // number of days in X years

    /* system_category='external cloud, ie AWS' */

    int capital_cost=0; // dollars; NRE and acquisition
    // operations_and_maintenance_per_year=0; // dollars
    int cost_per_hour_of_use=100; // dollars; this is in place of O&M

    int initial_time_to_solution_in_minutes=100; 
    int time_to_market_in_days=1; // days; includes acquisition and coding analytic

    double availability=99.9; // percent of system availability

    /*
      The rational for including Moore's Law (https://en.wikipedia.org/wiki/Moore%27s_law) is that when I buy a computer in year X with lifespan Y, then for Y years I have that computer. In contrast, my assumption is that using Amazon's AWS for time period Y, the provider (Amazon) will be constantly refreshing their hardware (invisible to me, the user). AWS tracks with Moore's Law, hardware purchased by me does not.
    */
    int doubling_period_in_days;
    doubling_period_in_days=days_in_a_year*2; // Moore's law

    int time_in_days[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        time_in_days[day_indx]=day_indx;
    }

    // time to solution varies due to Moore's law
    double time_to_solution_in_minutes[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        time_to_solution_in_minutes[day_indx]=initial_time_to_solution_in_minutes*(pow(2,(-1.0*time_in_days[day_indx]/doubling_period_in_days)));
    }
    //figure; plot(time_in_days,time_to_solution); ylabel('time-to-solution'); xlabel('days');

    double solutions_count[max_number_of_days];
    soln_count(max_number_of_days, hours_in_a_day,
               minutes_in_an_hour, availability,time_to_solution_in_minutes,
               solutions_count,time_in_days,time_to_market_in_days);

    //cost_per_soln(int max_number_of_days)
    double cost_per_solution[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        cost_per_solution[day_indx]=cost_per_hour_of_use*
            (time_to_solution_in_minutes[day_indx]/minutes_in_an_hour);
    }

    //tco(int max_number_of_days)
    double total_cost_of_ownership[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        total_cost_of_ownership[day_indx]=
            cost_per_hour_of_use*hours_in_a_day*
            time_in_days[day_indx]/normalization_of_money_spent;
    }

    print_results(max_number_of_days,time_in_days,
                  solutions_count,cost_per_solution,total_cost_of_ownership);

}

void soln_count(int max_number_of_days,int hours_in_a_day,
                int minutes_in_an_hour, int availability, 
                double* time_to_solution_in_minutes,double* solutions_count,
                int* time_in_days,int time_to_market_in_days){
    double solutions_per_day[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_per_day[day_indx]=(hours_in_a_day*minutes_in_an_hour)/
                                    time_to_solution_in_minutes[day_indx];
        // normalize solution count by system availability
        solutions_per_day[day_indx]=solutions_per_day[day_indx]*(availability/100.0);
    }

    // cummulative count of solution over time
    double solutions_count_without_time_to_market[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_count_without_time_to_market[day_indx] = solutions_per_day[day_indx]*time_in_days[day_indx];
    }
    //figure; plot(time_in_days,solutions_per_day); ylabel('solutions per day'); xlabel('days');

    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_count[day_indx]=0;
    }
    for (int day_indx=time_to_market_in_days; day_indx<=max_number_of_days; day_indx++){
        solutions_count[day_indx]=solutions_count_without_time_to_market[day_indx];
    }
}

void cost_per_soln(int max_number_of_days){
}

void tco(int max_number_of_days){
}

void print_results(int max_number_of_days,int* time_in_days,
                   double* solutions_count, double* cost_per_solution,
                   double* total_cost_of_ownership){
    //for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
    for (int day_indx=0; day_indx<10; day_indx++){
        cout << time_in_days[day_indx] << ", "
             << solutions_count[day_indx] << ", "
             << cost_per_solution[day_indx] << ", "
             << total_cost_of_ownership[day_indx]
             << endl;
    }
}
