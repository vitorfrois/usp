
g = 9.81;
Vo = 25.6;
dist = 48;
h = 3.81;

syms x;
r = ((tan(d)*dist) - ((g * dist * dist)/(2 * Vo * Vo * cos(d))) - h == 0);
disp(rad2deg(solve(r, x)))
