// $ g++ costbenefit_with_outages_with_moores_law.cpp 

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

void external_cloud(int days_in_a_year,int max_number_of_days,int hours_in_a_day,
                    int minutes_in_an_hour,double normalization_of_money_spent,
                    int capital_cost, int initial_time_to_solution_in_minutes,
                    int time_to_market_in_days, double availability, int* time_in_days_ary);

void selfhosted_commodity(int days_in_a_year,int max_number_of_days,int hours_in_a_day,
                    int minutes_in_an_hour,double normalization_of_money_spent,
                    int capital_cost, int time_to_solution_in_minutes,
                    int time_to_market_in_days, double availability,int* time_in_days_ary);

void soln_count(int max_number_of_days,int hours_in_a_day,
                int minutes_in_an_hour, int availability, 
                double* solutions_per_day_ary,double* solutions_count_ary,
                int* time_in_days_ary,int time_to_market_in_days);

void cost_per_soln_based_on_capital_plus_oandm(int max_number_of_days,
            int capital_cost,
            int operations_and_maintenance_per_year,int days_in_a_year,
            int time_to_market_in_days, double * cost_per_solution_ary,
            double* solutions_count_ary);

/*
void tco_based_on_capital_plus_oandm(int max_number_of_days);
*/
void print_results(int max_number_of_days,int* time_in_days_ary,
                   double* solutions_count_ary, double* cost_per_solution,
                   double* total_cost_of_ownership);

int main(){
    const int hours_in_a_day=24;
    const int minutes_in_an_hour=60;
    const int days_in_a_year=365;
    const int number_of_years=5; // lifespan of systems being investigated
    const double normalization_of_money_spent=1000000.0; // a million bucks

    int max_number_of_days=days_in_a_year*number_of_years; // used to set array sizes; number of days in X years

    int time_in_days_ary[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        time_in_days_ary[day_indx]=day_indx;
    }

    // following parameters are specific to AWS
    int capital_cost=0; // dollars; NRE and acquisition
    int initial_time_to_solution_in_minutes=100; 
    int time_to_market_in_days=1; // days; includes acquisition and coding analytic
    double availability=99.9; // percent of system availability
    external_cloud(days_in_a_year,max_number_of_days,hours_in_a_day,
                   minutes_in_an_hour,normalization_of_money_spent,
                   capital_cost, initial_time_to_solution_in_minutes,
                   time_to_market_in_days, availability, time_in_days_ary);

    // following parameters are specific to self-hosted commodity
    capital_cost=100000; // dollars; NRE and acquisition
    int operations_and_maintenance_per_year=10000; // dollars
    int time_to_solution_in_minutes=60; 
    time_to_market_in_days=5; // days; includes acquisition and coding analytic
    availability=99; // percent
    selfhosted_commodity(days_in_a_year,max_number_of_days,hours_in_a_day,
                   minutes_in_an_hour,normalization_of_money_spent,
                   capital_cost, time_to_solution_in_minutes,
                   time_to_market_in_days, availability, time_in_days_ary);

}
















/* system_category='self-hosted commodity servers' */
void selfhosted_commodity(int days_in_a_year,int max_number_of_days,int hours_in_a_day,
                    int minutes_in_an_hour,double normalization_of_money_spent,
                    int capital_cost, int time_to_solution_in_minutes,
                    int time_to_market_in_days, double availability,int* time_in_days_ary){

    double solutions_per_day=0;
    solutions_per_day=(hours_in_a_day*minutes_in_an_hour)/time_to_solution_in_minutes;
    solutions_per_day=solutions_per_day*(availability/100);
    double solutions_per_day_ary[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_per_day_ary[day_indx]=solutions_per_day;
    }
    
    double solutions_count_ary[max_number_of_days];
    soln_count(max_number_of_days, hours_in_a_day,
               minutes_in_an_hour, availability,solutions_per_day_ary,
               solutions_count_ary,time_in_days_ary,time_to_market_in_days);

    double cost_per_solution[max_number_of_days];
    //cost_per_soln(int max_number_of_days);
    
    double total_cost_of_ownership[max_number_of_days];
    //tco(int max_number_of_days);

    cout << "self-hosted commodity: " << endl;
    print_results(max_number_of_days,time_in_days_ary,
                  solutions_count_ary,cost_per_solution,total_cost_of_ownership);

}




















/* system_category='external cloud, ie AWS' */
void external_cloud(int days_in_a_year,int max_number_of_days,int hours_in_a_day,
                    int minutes_in_an_hour,double normalization_of_money_spent,
                    int capital_cost, int initial_time_to_solution_in_minutes,
                    int time_to_market_in_days, double availability,int* time_in_days_ary){

    // operations_and_maintenance_per_year=0; // dollars
    int cost_per_hour_of_use=100; // dollars; this is in place of O&M

    /*
      The rational for including Moore's Law (https://en.wikipedia.org/wiki/Moore%27s_law) is that when I buy a computer in year X with lifespan Y, then for Y years I have that computer. In contrast, my assumption is that using Amazon's AWS for time period Y, the provider (Amazon) will be constantly refreshing their hardware (invisible to me, the user). AWS tracks with Moore's Law, hardware purchased by me does not.
    */
    int doubling_period_in_days;
    doubling_period_in_days=days_in_a_year*2; // Moore's law

    // time to solution varies due to Moore's law
    double time_to_solution_in_minutes_ary[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        time_to_solution_in_minutes_ary[day_indx]=
            initial_time_to_solution_in_minutes*
            (pow(2,(-1.0*time_in_days_ary[day_indx]/doubling_period_in_days)));
    }
    //figure; plot(time_in_days_ary,time_to_solution); ylabel('time-to-solution'); xlabel('days');

    double solutions_per_day_ary[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_per_day_ary[day_indx]=(hours_in_a_day*minutes_in_an_hour)/
                                    time_to_solution_in_minutes_ary[day_indx];
        // normalize solution count by system availability
        solutions_per_day_ary[day_indx]=solutions_per_day_ary[day_indx]*(availability/100.0);
    }

    double solutions_count_ary[max_number_of_days];
    soln_count(max_number_of_days, hours_in_a_day,
               minutes_in_an_hour, availability,solutions_per_day_ary,
               solutions_count_ary,time_in_days_ary,time_to_market_in_days);

    //cost_per_soln(int max_number_of_days)
    double cost_per_solution[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        cost_per_solution[day_indx]=cost_per_hour_of_use*
            (time_to_solution_in_minutes_ary[day_indx]/minutes_in_an_hour);
    }

    //tco(int max_number_of_days)
    double total_cost_of_ownership[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        total_cost_of_ownership[day_indx]=
            cost_per_hour_of_use*hours_in_a_day*
            time_in_days_ary[day_indx]/normalization_of_money_spent;
    }

    cout << "AWS: " << endl;
    print_results(max_number_of_days,time_in_days_ary,
                  solutions_count_ary,cost_per_solution,total_cost_of_ownership);
}














void soln_count(int max_number_of_days,int hours_in_a_day,
                int minutes_in_an_hour, int availability, 
                double* solutions_per_day_ary,double* solutions_count_ary,
                int* time_in_days_ary,int time_to_market_in_days){


    // cummulative count of solution over time
    double solutions_count_without_time_to_market[max_number_of_days];
    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_count_without_time_to_market[day_indx] = solutions_per_day_ary[day_indx]*time_in_days_ary[day_indx];
    }
    //figure; plot(time_in_days_ary,solutions_per_day_ary); ylabel('solutions per day'); xlabel('days');

    for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
        solutions_count_ary[day_indx]=0;
    }
    for (int day_indx=time_to_market_in_days; day_indx<=max_number_of_days; day_indx++){
        solutions_count_ary[day_indx]=solutions_count_without_time_to_market[day_indx];
    }
}









void cost_per_soln_based_on_capital_plus_oandm(int max_number_of_days,
            int capital_cost,
            int operations_and_maintenance_per_year,int days_in_a_year,
            int time_to_market_in_days, double * cost_per_solution_ary,
            double* solutions_count_ary){
    double money_spent_per_day = capital_cost+(operations_and_maintenance_per_year/days_in_a_year);
    int time_in_days_for_money_ary[max_number_of_days];
    for (int indx=0; indx<time_to_market_in_days; indx++){
        time_in_days_for_money_ary[indx]=0;
    }
    int days_running=1;
    for (int indx=time_to_market_in_days; indx<max_number_of_days; indx++){
        time_in_days_for_money_ary[indx]=money_spent_per_day*days_running++;
    }
    for (int indx=0; indx<max_number_of_days; indx++){
        cost_per_solution_ary[indx]=money_spent_per_day/solutions_count_ary[indx];
    }
}











void tco_based_on_capital_plus_oandm(int max_number_of_days){
}

void print_results(int max_number_of_days,int* time_in_days_ary,
                   double* solutions_count_ary, double* cost_per_solution,
                   double* total_cost_of_ownership){
    //for (int day_indx=0; day_indx<max_number_of_days; day_indx++){
    cout << "time in days, cummulative solution count, cost per solution, TCO in millions" << endl;
    for (int day_indx=0; day_indx<10; day_indx++){
        cout << time_in_days_ary[day_indx] << ", "
             << solutions_count_ary[day_indx] << ", "
             << cost_per_solution[day_indx] << ", "
             << total_cost_of_ownership[day_indx]
             << endl;
    }
}

