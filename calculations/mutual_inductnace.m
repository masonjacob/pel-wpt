% (theta, phi)

N_1 = 5; %20
N_2 = 5; %20
mu_0 = 1;
mu_r = 1; %81
r_1 = 0.1;
r_2 = 0.1;
alpha = 0.* (pi ./ 180);
c = 0;
d = 0.2;
f = @(x,y) (r_1 .* r_2 .* ((sin(x) .* sin(y)) + (cos(alpha) .* cos(x) .* cos(y))) ./ sqrt(((r_1 .* cos(x)) - (r_2 .* cos(y))).^2 + ((r_1 .* sin(x)) - (r_2 .* sin(y) .* cos(alpha)) - c).^2 +((r_2 .* sin(y) .* sin(alpha)) - d).^2));
result = integral2(f,0,2.*pi,0,2.*pi);
M = ((N_1 .* N_2 .* mu_0 .* mu_r) ./ (4 .* pi)) .* result