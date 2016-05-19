function [availability_array_per_hour] = availability_of_system(uptime_duration_distribution_mean,uptime_duration_distribution_standard_deviation,downtime_duration_distribution_mean,downtime_duration_distribution_standard_deviation,max_number_of_days)

hours_in_a_day=24;
minutes_in_an_hour=60;
days_in_a_year=365;

availability_array_per_hour=-1*ones(1,max_number_of_days*hours_in_a_day); % generate availability array
uptime_hours_remaining=0; downtime_hours_remaining=0;
for hour_indx=1:size(availability_array_per_hour,2)
    if (uptime_hours_remaining<1) && (downtime_hours_remaining<1)
        uptime_hours_remaining=normrnd(uptime_duration_distribution_mean,uptime_duration_distribution_standard_deviation);
        if uptime_hours_remaining<=1
            uptime_hours_remaining=1;
        end
        downtime_hours_remaining=normrnd(downtime_duration_distribution_mean,downtime_duration_distribution_standard_deviation);
        if downtime_hours_remaining<=1
            downtime_hours_remaining=1;
        end
    end
    if (uptime_hours_remaining>=1) && (downtime_hours_remaining>=1) % system is up
        availability_array_per_hour(hour_indx)=1; % system is up
        uptime_hours_remaining=uptime_hours_remaining-1;
    elseif (uptime_hours_remaining<1) && (downtime_hours_remaining>=1)
        availability_array_per_hour(hour_indx)=0; % system is down
        downtime_hours_remaining=downtime_hours_remaining-1;
    else % uphours>=1 && downhours<1
        disp('ERROR in ranges');
        uptime_hours_remaining
        downtime_hours_remaining
        break
    end
    if (availability_array_per_hour(hour_indx) == -1)
        disp('ERROR in conditions')
        uptime_hours_remaining
        downtime_hours_remaining
        hour_indx
        availability_array_per_hour(1:10)
        break
    end
end
