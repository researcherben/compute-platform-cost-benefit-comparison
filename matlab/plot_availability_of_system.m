close all
clear
%% contants

hours_in_a_day=24;
minutes_in_an_hour=60;
days_in_a_year=365;
max_number_of_days=days_in_a_year*5;

linewidth=3;

%% 
system_category='generic';

uptime_duration_distribution_mean=24*60; % hours; mean-time between failure (MTBF)
uptime_duration_distribution_standard_deviation=1000; % hours
downtime_duration_distribution_mean=24*7; % hours
downtime_duration_distribution_standard_deviation=100; % hours

% {
time_in_hours=[0:0.1:20000];  
figure; plot(time_in_hours,normpdf(time_in_hours,uptime_duration_distribution_mean,uptime_duration_distribution_standard_deviation))
title(['uptime distribution']); xlabel('time [hours]'); 
%saveas(gcf,'uptime_distribution_24x60x10_U','png');
saveas(gcf,'uptime_distribution_24x60_U','png');

time_in_hours=[0:0.1:700];  
figure; plot(time_in_hours,normpdf(time_in_hours,downtime_duration_distribution_mean,downtime_duration_distribution_standard_deviation))
title(['downtime distribution']); xlabel('time [hours]'); 
%saveas(gcf,'downtime_distribution_24x60x10_U','png');
saveas(gcf,'downtime_distribution_24x60_U','png');
%}

availability_array_per_hour=availability_of_system(uptime_duration_distribution_mean,uptime_duration_distribution_standard_deviation,downtime_duration_distribution_mean,downtime_duration_distribution_standard_deviation,max_number_of_days);

figure; plot(availability_array_per_hour); hold on;
set(gca,'YTick',[0 1]);
title('availability to user'); xlabel('time [hours]'); ylabel('0=down; 1=up');

% combine uptime and downtime durations to find "availability percentage" for the year
sum(availability_array_per_hour)/size(availability_array_per_hour,2)