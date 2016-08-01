clear
close all
cloud=load('cloud.dat');
commodity=load('commodity.dat');
tailored=load('tailored.dat');
% the four columns in these files are
% "time in days, cumulative number of solutions, cumulative money spent, cost per solution"

setenv("GNUTERM","qt"); % may be specific to Mac OS X
figure;
plot(cloud(:,1),cloud(:,2),"DisplayName","cloud","color","blue","LineWidth",3); hold on; 
plot(commodity(:,1),commodity(:,2),"DisplayName","commodity","color","red","LineWidth",3); 
plot(tailored(:,1),tailored(:,2),"DisplayName","tailored","color","green","LineWidth",3); 
set(gca, "fontsize", 18); xlabel('time [days]'); ylabel("cumulative number of solutions");

figure;
plot(cloud(:,1),cloud(:,3),"DisplayName","cloud","color","blue","LineWidth",3); hold on; 
plot(commodity(:,1),commodity(:,3),"DisplayName","commodity","color","red","LineWidth",3); 
plot(tailored(:,1),tailored(:,3),"DisplayName","tailored","color","green","LineWidth",3); 
set(gca, "fontsize", 18); xlabel('time [days]'); ylabel("cumulative money spent");

figure;
semilogy(cloud(:,1),cloud(:,4),"DisplayName","cloud","color","blue","LineWidth",3); hold on; 
semilogy(commodity(:,1),commodity(:,4),"DisplayName","commodity","color","red","LineWidth",3); 
semilogy(tailored(:,1),tailored(:,4),"DisplayName","tailored","color","green","LineWidth",3); 
set(gca, "fontsize", 18); xlabel('time [days]'); ylabel("cost per solution");
