clc
syms x y z L l a b c d teta1 teta2 teta3 xd yd zd teta1d teta2d teta3d
f1 = x^2 + y^2 + z^2 + L^2 - l^2 + a^2 + d^2 - 2*(y + a)*L*cos(teta1) -2*(z - d)*L*sin(teta1) + 2*y*a - 2*z*d;
f1_x = diff(f1,x);
f1_y = diff(f1,y);
f1_z = diff(f1,z);
f1_teta1 = diff(f1,teta1);
f1_teta2 = diff(f1,teta2);
f1_teta3 = diff(f1,teta3);
f1_diff = f1_x*xd + f1_y*yd + f1_z*zd + f1_teta1*teta1d + f1_teta2*teta2d + f1_teta3*teta3d;
simplify(f1_diff)

f2 = x^2 + y^2 + z^2 + L^2 - l^2 + b^2 + c^2 + d^2 + (sqrt(3)*(x + b) + y + c)*L*cos(teta2) - 2*(z - d)*L*sin(teta2) + 2*x*b + 2*y*c - 2*z*d;
f2_x = diff(f2,x);
f2_y = diff(f2,y);
f2_z = diff(f2,z);
f2_teta1 = diff(f2,teta1);
f2_teta2 = diff(f2,teta2);
f2_teta3 = diff(f2,teta3);
f2_diff = f2_x*xd + f2_y*yd + f2_z*zd + f2_teta1*teta1d + f2_teta2*teta2d + f2_teta3*teta3d;
simplify(f2_diff)

f3 = x^2 + y^2 + z^2 + L^2 - l^2 + b^2 + c^2 + d^2 + (-sqrt(3)*(x - b) + y + c)*L*cos(teta3) - 2*(z - d)*L*sin(teta3) - 2*x*b + 2*y*c - 2*z*d;
f3_x = diff(f3,x);
f3_y = diff(f3,y);
f3_z = diff(f3,z);
f3_teta1 = diff(f3,teta1);
f3_teta2 = diff(f3,teta2);
f3_teta3 = diff(f3,teta3);
f3_diff = f3_x*xd + f3_y*yd + f3_z*zd + f3_teta1*teta1d + f3_teta2*teta2d + f3_teta3*teta3d;
simplify(f3_diff)
