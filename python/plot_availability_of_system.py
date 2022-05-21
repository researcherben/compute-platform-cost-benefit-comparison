#!/usr/bin/env python3

from random import gauss


def availability_of_system(
    uptime_duration_distribution_mean,
    uptime_duration_distribution_standard_deviation,
    downtime_duration_distribution_mean,
    downtime_duration_distribution_standard_deviation,
    max_number_of_days,
):

    hours_in_a_day = 24
    minutes_in_an_hour = 60
    days_in_a_year = 365

    availability_array_per_hour = (
        []
    )  # -1*ones(1,max_number_of_days*hours_in_a_day) # generate availability array
    uptime_hours_remaining = 0
    downtime_hours_remaining = 0
    for hour_indx in range(
        max_number_of_days * hours_in_a_day
    ):  # =1:size(availability_array_per_hour,2)
        if (uptime_hours_remaining < 1) and (downtime_hours_remaining < 1):
            uptime_hours_remaining = gauss(
                uptime_duration_distribution_mean,
                uptime_duration_distribution_standard_deviation,
            )
            if uptime_hours_remaining <= 1:
                uptime_hours_remaining = 1
            downtime_hours_remaining = gauss(
                downtime_duration_distribution_mean,
                downtime_duration_distribution_standard_deviation,
            )
            if downtime_hours_remaining <= 1:
                downtime_hours_remaining = 1
        if (uptime_hours_remaining >= 1) and (
            downtime_hours_remaining >= 1
        ):  # system is up
            availability_array_per_hour[hour_indx] = 1  # system is up
            uptime_hours_remaining = uptime_hours_remaining - 1
        elif (uptime_hours_remaining < 1) and (downtime_hours_remaining >= 1):
            availability_array_per_hour[hour_indx] = 0  # system is down
            downtime_hours_remaining = downtime_hours_remaining - 1
        else:  # uphours>=1 and downhours<1
            print("ERROR in ranges")
            uptime_hours_remaining
            downtime_hours_remaining
            break
        if availability_array_per_hour(hour_indx) == -1:
            print("ERROR in conditions")
            uptime_hours_remaining
            downtime_hours_remaining
            hour_indx
            availability_array_per_hour[1:10]
            break

    return availability_array_per_hour


## contants

hours_in_a_day = 24
minutes_in_an_hour = 60
days_in_a_year = 365
max_number_of_days = days_in_a_year * 5

linewidth = 3

##
system_category = "generic"

uptime_duration_distribution_mean = 24 * 60  # hours mean-time between failure (MTBF)
uptime_duration_distribution_standard_deviation = 1000  # hours
downtime_duration_distribution_mean = 24 * 7  # hours
downtime_duration_distribution_standard_deviation = 100  # hours
"""
# {
time_in_hours=range(0,20000,0.1)
figure plot(time_in_hours,normpdf(time_in_hours,uptime_duration_distribution_mean,uptime_duration_distribution_standard_deviation))
title(['uptime distribution']) xlabel('time [hours]') 
#saveas(gcf,'uptime_distribution_24x60x10_U','png')
saveas(gcf,'uptime_distribution_24x60_U','png')

time_in_hours=range(0,700,0.1)
figure plot(time_in_hours,normpdf(time_in_hours,downtime_duration_distribution_mean,downtime_duration_distribution_standard_deviation))
title(['downtime distribution']) xlabel('time [hours]') 
#saveas(gcf,'downtime_distribution_24x60x10_U','png')
saveas(gcf,'downtime_distribution_24x60_U','png')
#}
"""
availability_array_per_hour = availability_of_system(
    uptime_duration_distribution_mean,
    uptime_duration_distribution_standard_deviation,
    downtime_duration_distribution_mean,
    downtime_duration_distribution_standard_deviation,
    max_number_of_days,
)

"""
figure plot(availability_array_per_hour) hold on
set(gca,'YTick',[0 1])
title('availability to user') xlabel('time [hours]') ylabel('0=down 1=up')
"""

# combine uptime and downtime durations to find "availability percentage" for the year
sum(availability_array_per_hour) / size(availability_array_per_hour, 2)
