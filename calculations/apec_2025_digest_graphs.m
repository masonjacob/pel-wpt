clc, clear, clear figure

%
% Simple WPT Circuit:
%
%          C1                 C2
%     _____||_____       _____||_____
%    |     ||     |  M  |     ||     |
%    |            | / \ |            |
%    /            )/   \(            \
% RS \         L1 )     ( L2         / RL
%    /            )     (            \
%    |            |     |            |
%    |            |     |            |
%  __|__          \     /            |
%  | VS |     RL1 /     \ RL2        |   
%  |____|         \     /            |
%    |            |     |            |
%    |____________|     |____________|
%                _|_   _|_
%                 -     -
%                   

% With Mutual Inductance / Coupling, the Equivalent Inductance Circuit Becomes:
%    
%        L1 - M             L2 - M
%     ____∩∩∩∩_______________∩∩∩∩____
%                    |            
%                    |            
%                    (            
%                    ( M         
%                    (
%                    |
%

% Resonant Frequency


D  = [6E-2, 7E-2, 8E-2, 9E-2, 10E-2];
L1 = [33.332770E-6, 33.287701E-6, 33.234215E-6, 33.171497E-6, 33.099117E-6];
L2 = [8.926812E-6, 8.919241E-6, 8.910372E-6, 8.899795E-6, 8.887602E-6];
M  = [6.437812E-6, 5.644129E-6, 4.953291E-6, 4.350364E-6, 3.822937E-6];
C1 = 0.71E-6;
C2 = 0.71E-6;
RL1 = 29.799E-2;
RL2 =29.799E-2./2;
% RS = 10E-3;
% RL = 50;

% RX Coil Length Calculations: 2.34 + 0.33 + 0.4 = 3.07 M
% Resistance of around 0.6684E-3, which doesn't give the right estimated
% coupling coefficent value

% Simple Resonant Frequency
% w = 1./(2 .* pi .* sqrt(L1.*C1))

% Resonant Frequency for Coupled Coils
w = 1./(2 .* pi .* sqrt((L1 - M).*C1));

% Resonant Frequency for WPT
% w = 1./(2.*pi.*sqrt((L1.*L2 - M.^2).*((1./C1)+(1./C2))));

% Coupling Coefficent
k = M./(sqrt(L1.*L2));


% plot(D,w, "Marker","square")
% 
% x = D.*100;
% y = w./1000;
% % Get coefficients of a line fit through the data.
% coefficients = polyfit(x, y, 3);
% % Create a new x axis with exactly 1000 points (or whatever you want).
% xFit = linspace(min(x), max(x), 1000);
% % Get the estimated yFit value for each of those 1000 new x locations.
% yFit = polyval(coefficients , xFit);
% % Plot everything.
% plot(x, y, 'ksquare', 'MarkerSize', 10); % Plot training data.
% hold on;
% yline(y(1), 'b-', 'LineWidth', 2)
% hold on;
% plot(xFit, yFit, 'r-', 'LineWidth', 2); % Plot fitted line.
% xlim([6 10])
% title("Distance v.s. Resonant Frequency")
% xlabel("Distance (cm)")
% ylabel("Frequency (kHz)")
% legend('Simulation Results', 'Static Frequency', 'Frequency Tracking')
% grid on;

% Q1 = (w.*L1)./(RL1)
% Q2 = (w.*L2)./(RL2)
% 
% k_Imax = 1./sqrt(Q1.*Q2)


L_S = readtable('L Table Seawater.csv');
L_A = readtable('L Table Air.csv');


 
idx = (L_A.slide == 0 & L_A.gap == 100);
plot_1 = L_A(idx,:);
idx = (L_A.slide == 0 & L_A.gap == 140);
plot_2 = L_A(idx,:);
idx = (L_A.slide == 0 & L_A.gap == 180);
plot_3 = L_A(idx,:);
idx = (L_S.slide == 0 & L_S.gap == 100);
plot_4 = L_S(idx,:);
idx = (L_S.slide == 0 & L_S.gap == 140);
plot_5 = L_S(idx,:);
idx = (L_S.slide == 0 & L_S.gap == 180);
plot_6 = L_S(idx,:);
x = [-20,-10,0,10,20]
plot_7 = [4.3786,4.3566,4.3467,4.3566,4.3786]
plot_8 = [2.1123,2.1343,2.1405,2.1343,2.1123]
plot_9 = [1.1461,1.1698,1.1771,1.1698,1.1461]

plot(plot_1, "misalignment", "mutual_inductance")
hold on;
plot(plot_2, "misalignment", "mutual_inductance")
hold on;
plot(plot_3, "misalignment", "mutual_inductance")
hold on;
plot(plot_4, "misalignment", "mutual_inductance")
hold on;
plot(plot_5, "misalignment", "mutual_inductance")
hold on;
plot(plot_6, "misalignment", "mutual_inductance")
hold on;
plot(x,plot_7)
hold on; 
plot(x,plot_8)
hold on;
plot(x,plot_9)
title("RX Misalignment v.s. Mutual Inductance at Multiple Gap Distances For Air and Seawater")
xlabel("RX Misalignment (deg)")
ylabel("Mutual Inductance (nH)")
legend('100mm Air Gap', '140mm Air Gap', '180mm Air Gap','100mm Seatwater Gap', '140mm Seawater Gap', '180mm Seawater Gap',"100mm Gap (Neumann's)", "140mm Gap (Neumann's)", "180mm Gap (Neumann's)")

% plot(x, y, 'ksquare', 'MarkerSize', 10); % Plot training data.
% hold on;
% yline(y(1), 'b-', 'LineWidth', 2)
% hold on;
% plot(xFit, yFit, 'r-', 'LineWidth', 2); % Plot fitted line.
% xlim([6 10])
% title("Distance v.s. Resonant Frequency")
% xlabel("Distance (cm)")
% ylabel("Frequency (kHz)")
% legend('Simulation Results', 'Static Frequency', 'Frequency Tracking')
% grid on;