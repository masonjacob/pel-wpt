% % (theta, phi)
% 
% N_1 = 20;
% N_2 = 20;
% mu_0 = 1;
% mu_r = 1; %81
% r_1 = 0.062;
% r_2 = 0.062;
% alpha = 20..* (pi ./ 180);
% c = 0
% d = 0.18;
% f = @(x,y) (r_1 ..* r_2 ..* ((sin(x) ..* sin(y)) + (cos(alpha) ..* cos(x) ..* cos(y))) ./ sqrt(((r_1 ..* cos(x)) - (r_2 ..* cos(y)))..^2 + ((r_1 ..* sin(x)) - (r_2 ..* sin(y) ..* cos(alpha)) - c)..^2 +((r_2 ..* sin(y) ..* sin(alpha)) - d)..^2));
% result = integral2(f,0,2..*pi,0,2..*pi);
% M = ((N_1 ..* N_2 ..* mu_0 ..* mu_r) ./ (4 ..* pi)) ..* result

Ri1 = .0315;
Ri2 = .0315;
s1 = .0035;
s2 = .0035;
N1 = 20;
N2 = 20;

x2 = 0;
y2 = 0;
z2 = .02;

gamma = 0;
beta = 20 .* (pi/180);
alpha = 0;

R_s = 0.140; % measured
mu0 = 0.1;

f = @(theta1, theta2) (((Ri1 + (s1) / (2 .* pi) .* theta1) .* cos(theta1) .* ((Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(theta2) .* (cos(alpha) .* cos(gamma) + sin(alpha) .* sin(beta) .* sin(gamma)) - (Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(beta) .* sin(alpha) .* sin(theta2)) ...
                            - (Ri1 + (s1) / (2 .* pi) .* theta1) .* sin(theta1) .* ((Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(theta2) .* (-cos(gamma) .* sin(alpha) + cos(alpha) .* sin(beta) .* sin(gamma)) - (Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(alpha) .* cos(beta) .* sin(theta2))) / ...
                            sqrt((z2 - (Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(theta2) .* sin(beta) + (Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(beta) .* sin(gamma) .* sin(theta2)) .^ 2 ...
                            + (x2 - (Ri1 + (s1) / (2 .* pi) .* theta1) .* cos(theta1) + (Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(alpha) .* cos(beta) .* cos(theta2) + (Ri2 + (s2) / (2 .* pi) .* theta2) .* (- cos(gamma) .* sin(alpha) + cos(alpha) .* sin(beta) .* sin(gamma)) .* sin(theta2)) .^ 2 ...
                            + (y2 + (Ri2 + (s2) / (2 .* pi) .* theta2) .* cos(beta) .* cos(theta2) .* sin(alpha) - (Ri1 + (s1) / (2 .* pi) .* theta1) .* sin(theta1) + (Ri2 + (s2) / (2 .* pi) .* theta2) .* (cos(alpha) .* cos(gamma) + sin(alpha) .* sin(beta) .* sin(gamma)) .* sin(theta2)) .^ 2));

integral = integral2(f, 0, 2 .* pi .* N1, 0, 2 .* pi .* N2);
coefficent = (mu0) / (4 .* pi);
result = coefficent .* integral;
disp(result)