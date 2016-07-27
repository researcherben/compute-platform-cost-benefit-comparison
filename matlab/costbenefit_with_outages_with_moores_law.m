close all

%% contants

hours_in_a_day=24;
minutes_in_an_hour=60;
days_in_a_year=365;
max_number_of_days=days_in_a_year*5;

normalization_of_money_spent=1000000; % a million bucks
linewidth=3;

%% 
system_category='external cloud, ie C2S';

capital_cost=0; % dollars; NRE and acquisition
% operations_and_maintenance_per_year=0; % dollars
cost_per_hour_of_use=100; % dollars; this is in place of O&M

initial_time_to_solution_in_minutes=100; 
time_to_market_in_days=1; % days; includes acquisition and coding analytic

availability=99.9; % percent of system availability

% The rational for including Moore's Law (https://en.wikipedia.org/wiki/Moore%27s_law) is that when I buy a computer in year X with lifespan Y, then for Y years I have that computer. In contrast,
% my assumption is that using Amazon's AWS for time period Y, the provider (Amazon) will be constantly refreshing their hardware
% (invisible to me, the user). AWS tracks with Moore's Law, hardware purchased by me does not.
doubling_period_in_days=days_in_a_year*2; % Moore's law
time_in_days=[0:max_number_of_days];
time_to_solution_in_minutes=initial_time_to_solution_in_minutes*(2.^(-time_in_days/doubling_period_in_days));
%figure; plot(time_in_days,time_to_solution); ylabel('time-to-solution'); xlabel('days');

solutions_per_day=(hours_in_a_day*minutes_in_an_hour)./time_to_solution_in_minutes;
solutions_per_day=solutions_per_day*(availability/100.0);
%figure; plot(time_in_days,solutions_per_day); ylabel('solutions per day'); xlabel('days');

solutions_count_without_time_to_market = solutions_per_day.*time_in_days;
solutions_count=zeros(1,max_number_of_days+1);
solutions_count(1+time_to_market_in_days:max_number_of_days+1)=...
      solutions_count_without_time_to_market(1:(max_number_of_days+1-time_to_market_in_days));
figure(10); plot(time_in_days,solutions_count,'DisplayName',system_category,'LineWidth',linewidth); hold on; 

% calculate cost per solution
cost_per_solution=cost_per_hour_of_use*(time_to_solution_in_minutes./minutes_in_an_hour);
%{
figure(20); plot(solutions_count,cost_per_solution); hold on;
title('cost of system vs solutions provided'); xlabel('number of solutions provided'); ylabel('cost per solution');
%}
% "bang for your buck"
figure(25); plot(time_in_days,cost_per_solution,'DisplayName',system_category,'LineWidth',linewidth); hold on;

% total cost of ownership
figure(30); plot(time_in_days,cost_per_hour_of_use*hours_in_a_day*time_in_days/normalization_of_money_spent,'DisplayName',system_category,'LineWidth',linewidth); hold on;


%% 
system_category='self-hosted commodity servers';

capital_cost=100000; % dollars; NRE and acquisition
operations_and_maintenance_per_year=10000; % dollars
cost_per_hour_of_use=0; % dollars; this is in place of O&M

time_to_solution_in_minutes=60; 
time_to_market_in_days=5; % days; includes acquisition and coding analytic

availability=99; % percent

solutions_per_day=(hours_in_a_day*minutes_in_an_hour)/time_to_solution_in_minutes;
solutions_per_day=solutions_per_day*(availability/100);
time_in_days=[0:max_number_of_days];
solutions_count = solutions_per_day*time_in_days-(solutions_per_day*time_to_market_in_days);
solutions_count=solutions_count.*(solutions_count>0);
figure(10); plot(time_in_days,solutions_count,'DisplayName',system_category,'LineWidth',linewidth); hold on; 

% calculate cost per solution
time_in_days_for_money=time_in_days-time_to_market_in_days;
time_in_days_for_money(1:time_to_market_in_days)=0;
money_spent = capital_cost+(operations_and_maintenance_per_year/days_in_a_year)*time_in_days_for_money;
cost_per_solution=money_spent./solutions_count;
%{
figure(20); plot(solutions_count,cost_per_solution); hold on;
title('cost of system vs solutions provided'); xlabel('number of solutions provided'); ylabel('cost per solution');
%}
% "bang for your buck"
figure(25); plot(time_in_days,cost_per_solution,'DisplayName',system_category,'LineWidth',linewidth)

% total cost of ownership
figure(30); plot(time_in_days,money_spent/normalization_of_money_spent,'DisplayName',system_category,'LineWidth',linewidth)



%% 
system_category='tailored platform';

capital_cost=1000000; % dollars; NRE and acquisition
operations_and_maintenance_per_year=100000; % dollars
cost_per_hour_of_use=0; % dollars; this is in place of O&M

time_to_solution_in_minutes=1; 
time_to_market_in_days=365; % days; includes acquisition and coding analytic

availability=90; % percent

solutions_per_day=(hours_in_a_day*minutes_in_an_hour)/time_to_solution_in_minutes;
solutions_per_day=solutions_per_day*(availability/100);
time_in_days=[0:max_number_of_days];
solutions_count = solutions_per_day*time_in_days-(solutions_per_day*time_to_market_in_days);
solutions_count=solutions_count.*(solutions_count>0);
figure(10); plot(time_in_days,solutions_count,'DisplayName',system_category,'LineWidth',linewidth); hold on; 
set(gca,'XTick',[0 365 730 1095 1460 1825 2000]);
title('time-to-market and time-to-solution; no outages'); xlabel('time [days]'); ylabel('number of solutions provided');
legend('show');
saveas(gcf,'platform_comparison_tts_and_ttm_U','png');

% calculate cost per solution
time_in_days_for_money=time_in_days-time_to_market_in_days;
time_in_days_for_money(1:time_to_market_in_days)=0;
money_spent = capital_cost+(operations_and_maintenance_per_year/days_in_a_year)*time_in_days_for_money;

cost_per_solution=money_spent./solutions_count;
%{
figure(20); plot(solutions_count,cost_per_solution); hold on;
title('cost of system vs solutions provided'); xlabel('number of solutions provided'); ylabel('cost per solution');
%}
% "bang for your buck"
figure(25); plot(time_in_days,cost_per_solution,'DisplayName',system_category,'LineWidth',linewidth);
set(gca,'XTick',[0 365 730 1095 1460 1825 2000]);
title('bang for your buck; no outages'); xlabel('time [days]'); ylabel('cost per solution provided');
legend('show');
saveas(gcf,'platform_comparison_bang_for_your_buck_U','png');

% total cost of ownership
figure(30); plot(time_in_days,money_spent/normalization_of_money_spent,'DisplayName',system_category,'LineWidth',linewidth);
set(gca,'XTick',[0 365 730 1095 1460 1825 2000]);
title('total cost of ownership (TCO); no outages'); xlabel('time [days]'); ylabel('cost in millions of dollars');
legend('show');
saveas(gcf,'platform_comparison_tco_U','png');

