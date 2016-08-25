clear all
%% 

% fix money
% fix functionality
% fix amount of work

% assume space-time trade-off equivalence: (compute unit)*time is constant on a given architecture
% assume at the current state I have all the same architecture
% assume the current architecture is composed of "compute units"

% question motivating the analysis:
% give an existing architecture (A) and some number of compute units, should I
% * buy more of the same architecture (A)
% * buy architecture B

%%
% input parameters:

% number of existing compute units for architecture A: number_of_compute_units_architecture_A

% capital cost per compute unit for architecture A: cap_cost_per_CU_A
% capital cost per compute unit for architecture B: cap_cost_per_CU_A

% O&M     cost per compute unit for architecture A: oam_cost_per_CU_A
% O&M     cost per compute unit for architecture B: oam_cost_per_CU_A

% (compute unit)*time for analytic {1..N} on architecture A: compute_time_architecture_A_ary
% (compute unit)*time for analytic {1..N} on architecture B: compute_time_architecture_B_ary

% money_to_invest_in_next_iteration % here an "iteration" is a fiscal year

%%
% in case you were wondering, this simulation does handle recurring analytics
% for example, if I ran a single analytic 4 times in a single year and 
% the (compute unit)*time was 20 each instance, then CUT_ary=[20 20 20 20];

%% 

number_of_compute_units_architecture_A = 5; % number of existing compute units for architecture A

compute_time_architecture_A_ary=[40 100 10 5 2]; % cloud architecture
compute_time_architecture_B_ary=[30  10  8 4 1]; % tailored architecture -- big speed-up for analytic #2
% critique: only accounting for CPU*hours neglects mission importance. 
% for example: the fifth analytic may have a required tts threshold
% critique: this analysis doesn't account for constraints like power/space/cooling

current_tts = sum(compute_time_architecture_A_ary)/number_of_compute_units_architecture_A

speed_up_ary= compute_time_architecture_A_ary./compute_time_architecture_B_ary; % not used elsewhere

cap_cost_per_CU_A=30; % in dollars
cap_cost_per_CU_B=50; % in dollars
oam_cost_per_CU_A=5; % in dollars
oam_cost_per_CU_B=8; % in dollars

money_to_invest_in_next_iteration=100; % in dollars

available_money_for_next_iteration = money_to_invest_in_next_iteration - oam_cost_per_CU_A*number_of_compute_units_architecture_A;

%% homogeneous strategy - buy more of architecture A

% available_money_for_next_iteration = \
%       cap_cost_per_CU_A*number_of_new_compute_units_architecture_A + oam_cost_per_CU_A*number_of_new_compute_units_architecture_A
% thus
% available_money_for_next_iteration = \
%       number_of_new_compute_units_architecture_A*(cap_cost_per_CU_A + oam_cost_per_CU_A)
% thus 
% number_of_new_compute_units_architecture_A = available_money_for_next_iteration/(cap_cost_per_CU_A+oam_cost_per_CU_A)

number_of_new_compute_units_architecture_A=number_of_compute_units_architecture_A + floor((available_money_for_next_iteration)/(cap_cost_per_CU_A+oam_cost_per_CU_A));

tts_homogeneous = sum(compute_time_architecture_A_ary)/number_of_new_compute_units_architecture_A

%% heterogeneous strategey - buy architecture B to augment existing A

number_of_new_compute_units_architecture_A=number_of_compute_units_architecture_A; % don't buy anymore of A
number_of_new_compute_units_architecture_B=floor((available_money_for_next_iteration)/(cap_cost_per_CU_B+oam_cost_per_CU_B));

min_tts_heterogeneous = 0;
best_compute_time_architecture_A = zeros(size(compute_time_architecture_A_ary));
best_compute_time_architecture_B = zeros(size(compute_time_architecture_B_ary));

number_of_analytics=size(compute_time_architecture_B_ary,2);

number_of_permutations = 2^number_of_analytics; % "2" is from number of architectures

all_permutations = de2bi(0:number_of_permutations-1); % this doesn't scale well :(

for this_permutation_indx = 1:number_of_permutations
    this_permutation_ary = all_permutations(this_permutation_indx,:);
    this_tts = max([(sum(compute_time_architecture_A_ary.*( this_permutation_ary))/number_of_new_compute_units_architecture_A) ...
                    (sum(compute_time_architecture_B_ary.*(~this_permutation_ary))/number_of_new_compute_units_architecture_B)]);
    
    if (min_tts_heterogeneous==0) % first time through the loop
        min_tts_heterogeneous = this_tts;
        best_compute_time_architecture_A = compute_time_architecture_A_ary.*( this_permutation_ary);
        best_compute_time_architecture_B = compute_time_architecture_B_ary.*(~this_permutation_ary);
    elseif (this_tts<min_tts_heterogeneous)
        min_tts_heterogeneous = this_tts;
        best_compute_time_architecture_A = compute_time_architecture_A_ary.*( this_permutation_ary);
        best_compute_time_architecture_B = compute_time_architecture_B_ary.*(~this_permutation_ary);
    end
end
min_tts_heterogeneous
best_compute_time_architecture_A
best_compute_time_architecture_B

%% scaling observation
% currently 
% number_of_permutations = (number of architectures)^(number_of_analytics)
% this doesn't scale well. 
% 1) naive speedup: random sampling from the search space
% 2) apply hueristics. I expect that analytics with the greatest ratio
%    of CUT_A./CUT_B should run on B first
%    For N>>1, order the analytics on B by size of ratio 
%    Brute force validates this hueristic
