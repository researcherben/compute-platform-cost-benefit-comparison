// $ g++ costbenefit_with_outages_with_moores_law.cpp 

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

void print_columns(const int * time_in_days_ary, 
                   const double * cummulative_number_of_solutions_per_day,
                   const double * cummulative_money_spent_per_day,
                   const double * cost_per_solution );

void cost_per_solution(double * cost_per_solution, 
                 const double * cummulative_number_of_solutions_per_day, 
                 const double * cummulative_money_spent_per_day);
                 
void money_spent_per_day(const int time_to_market_in_days, const double capital_cost,
                         const double operations_and_maintenance_per_year,
                         const int days_in_a_year, const int lifespan_in_days,
                         double * cummulative_money_spent_per_day);

void number_solutions_per_day(const int time_to_market_in_days, 
                              const int lifespan_in_days, const int hours_in_a_day,
                              const int minutes_in_an_hour, 
                              const double time_to_solution_in_minutes,
                              double * cummulative_number_of_solutions_per_day);

int main(){
    const int hours_in_a_day=24;
    const int minutes_in_an_hour=60;
    const int days_in_a_year=365;
    const int lifespan_in_years=5; // lifespan of systems being investigated
    const double normalization_of_money_spent=1000000.0; // a million bucks

    int lifespan_in_days=days_in_a_year*lifespan_in_years; // used to set array sizes

    int time_in_days_ary[lifespan_in_days];
    for (int day_indx=0; day_indx<lifespan_in_days; day_indx++){
        time_in_days_ary[day_indx]=day_indx;
    }

    // following parameters are specific to AWS
    double capital_cost_cloud=0; // dollars; NRE and acquisition
    double initial_time_to_solution_in_minutes=100; 
    int time_to_market_in_days_cloud=1; // days; includes acquisition and coding analytic
    double cost_per_hour_of_use=100.0;
    double availability_cloud=99.9; // percent of system availability

    int doubling_period_in_days;
    doubling_period_in_days=days_in_a_year*2; // Moore's law


    double cummulative_money_spent_per_day_cloud[lifespan_in_days];
    for (int day_indx=0; day_indx<time_to_market_in_days_cloud; day_indx++){
        cummulative_money_spent_per_day_cloud[day_indx]=capital_cost_cloud;
    }
    for (int day_indx=time_to_market_in_days_cloud; day_indx<lifespan_in_days; day_indx++){
        cummulative_money_spent_per_day_cloud[day_indx] += cost_per_hour_of_use*hours_in_a_day;
    }
    
    double cummulative_number_of_solutions_per_day_cloud[lifespan_in_days];
    for (int day_indx=0; day_indx<time_to_market_in_days_cloud; day_indx++){
        cummulative_number_of_solutions_per_day_cloud[day_indx]=0;
    }
    double number_of_solutions_today;
    double time_to_solution_today_in_minutes;
    for (int day_indx=time_to_market_in_days_cloud; day_indx<lifespan_in_days; day_indx++){
        // time to solution varies due to Moore's law
        time_to_solution_today_in_minutes=initial_time_to_solution_in_minutes*
                                (pow(2,(-1.0*day_indx/doubling_period_in_days)));
        number_of_solutions_today=(hours_in_a_day*minutes_in_an_hour)/time_to_solution_today_in_minutes;
        cummulative_number_of_solutions_per_day_cloud[day_indx] = 
            cummulative_number_of_solutions_per_day_cloud[day_indx-1]+number_of_solutions_today;
    }

    double cost_per_solution_cloud[lifespan_in_days];
    cost_per_solution(cost_per_solution_cloud, 
                      cummulative_number_of_solutions_per_day_cloud, 
                      cummulative_money_spent_per_day_cloud);
    
    cout << "cloud:" << endl;
    print_columns(time_in_days_ary, 
                  cummulative_number_of_solutions_per_day_cloud,
                  cummulative_money_spent_per_day_cloud,
                  cost_per_solution_cloud );


    
    // following parameters are specific to self-hosted commodity
    double capital_cost_commodity=100000; // dollars; NRE and acquisition
    double operations_and_maintenance_per_year_commodity=10000; // dollars
    double time_to_solution_in_minutes_commodity=60; 
    int time_to_market_in_days_commodity=5; // days; includes acquisition and coding analytic
    double availability_commodity=99; // percent

    double cummulative_money_spent_per_day_commodity[lifespan_in_days];
    money_spent_per_day(time_to_market_in_days_commodity, capital_cost_commodity,
                        operations_and_maintenance_per_year_commodity,
                        days_in_a_year, lifespan_in_days,
                        cummulative_money_spent_per_day_commodity);


    double cummulative_number_of_solutions_per_day_commodity[lifespan_in_days];
    number_solutions_per_day(time_to_market_in_days_commodity, 
                             lifespan_in_days, hours_in_a_day,
                             minutes_in_an_hour, 
                             time_to_solution_in_minutes_commodity,
                             cummulative_number_of_solutions_per_day_commodity);


    double cost_per_solution_commodity[lifespan_in_days];
    cost_per_solution(cost_per_solution_commodity, 
                      cummulative_number_of_solutions_per_day_commodity, 
                      cummulative_money_spent_per_day_commodity);

    cout << "commodity:" << endl;
    print_columns(time_in_days_ary, 
                  cummulative_number_of_solutions_per_day_commodity,
                  cummulative_money_spent_per_day_commodity,
                  cost_per_solution_commodity);


    double capital_cost_tailored=1000000; // dollars; NRE and acquisition
    double operations_and_maintenance_per_year_tailored=100000; // dollars
    double time_to_solution_in_minutes_tailored=1; 
    int time_to_market_in_days_tailored=365; // days; includes acquisition and coding analytic
    double availability_tailored=90; // percent

    double cummulative_money_spent_per_day_tailored[lifespan_in_days];
    money_spent_per_day(time_to_market_in_days_tailored, capital_cost_tailored,
                        operations_and_maintenance_per_year_tailored,
                        days_in_a_year, lifespan_in_days,
                        cummulative_money_spent_per_day_tailored);

    double cummulative_number_of_solutions_per_day_tailored[lifespan_in_days];
    number_solutions_per_day(time_to_market_in_days_tailored, 
                             lifespan_in_days, hours_in_a_day,
                             minutes_in_an_hour, 
                             time_to_solution_in_minutes_tailored,
                             cummulative_number_of_solutions_per_day_tailored);

    double cost_per_solution_tailored[lifespan_in_days];
    cost_per_solution(cost_per_solution_tailored, 
                      cummulative_number_of_solutions_per_day_tailored, 
                      cummulative_money_spent_per_day_tailored);

    cout << "tailored:" << endl;
    print_columns(time_in_days_ary, 
                  cummulative_number_of_solutions_per_day_tailored,
                  cummulative_money_spent_per_day_tailored,
                  cost_per_solution_tailored);

}




void cost_per_solution(double * cost_per_solution, 
                 const double * cummulative_number_of_solutions_per_day, 
                 const double * cummulative_money_spent_per_day){
    for (int day_indx=0; day_indx<10; day_indx++){
        if (cummulative_number_of_solutions_per_day[day_indx]==0){
            cost_per_solution[day_indx]=0;
        }else{
            cost_per_solution[day_indx]=
            cummulative_money_spent_per_day[day_indx]/
            cummulative_number_of_solutions_per_day[day_indx];
        }
    }
}

void print_columns(const int * time_in_days_ary, 
                   const double * cummulative_number_of_solutions_per_day,
                   const double * cummulative_money_spent_per_day,
                   const double * cost_per_solution ){
    cout << "time in days, cummulative number of solutions, cummulative_money_spent_per_day_cloud, cost per solution" << endl;
    //for (int day_indx=0; day_indx<lifespan_in_days; day_indx++){
    for (int day_indx=0; day_indx<10; day_indx++){
        cout << time_in_days_ary[day_indx] << ", "
             << cummulative_number_of_solutions_per_day[day_indx] << ", "
             << cummulative_money_spent_per_day[day_indx] << ", "
             << cost_per_solution[day_indx]
             << endl;
    }

}

void money_spent_per_day(const int time_to_market_in_days, const double capital_cost,
                         const double operations_and_maintenance_per_year,
                         const int days_in_a_year, const int lifespan_in_days,
                         double * cummulative_money_spent_per_day){
    for (int day_indx=0; day_indx<time_to_market_in_days; day_indx++){
        cummulative_money_spent_per_day[day_indx]=capital_cost;
    }
    for (int day_indx=time_to_market_in_days; day_indx<lifespan_in_days; day_indx++){
        cummulative_money_spent_per_day[day_indx] = 
            cummulative_money_spent_per_day[day_indx-1]+
            (operations_and_maintenance_per_year/days_in_a_year)*day_indx;
    }
}

void number_solutions_per_day(const int time_to_market_in_days, 
                              const int lifespan_in_days, const int hours_in_a_day,
                              const int minutes_in_an_hour, 
                              const double time_to_solution_in_minutes,
                              double * cummulative_number_of_solutions_per_day){
    for (int day_indx=0; day_indx<time_to_market_in_days; day_indx++){
        cummulative_number_of_solutions_per_day[day_indx]=0;
    }
    for (int day_indx=time_to_market_in_days; day_indx<lifespan_in_days; day_indx++){
        cummulative_number_of_solutions_per_day[day_indx] = 
            cummulative_number_of_solutions_per_day[day_indx-1]+
            (hours_in_a_day*minutes_in_an_hour)/time_to_solution_in_minutes;
    }
}
