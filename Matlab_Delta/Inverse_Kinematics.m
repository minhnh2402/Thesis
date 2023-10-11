function [theta1 theta2 theta3] = inverse_kinematics(xP,yP,zP)
R = 168;
r = 50;
d = 45;
L = 200;
l = 380;
a = r - R;
b = (-sqrt(3)/2)*(r-R);
c = 0.5*(R-r);

E1 = -2*L*(yP + a);
F1 = -2*L*(zP - d);
G1 = xP^2 + yP^2 + zP^2 + L^2 + a^2 + d^2 + 2*yP*a - 2*zP*d - l^2;

E2 = L*(sqrt(3)*(xP + b) + yP + c);
F2 = -2*L*(zP - d);
G2 = xP^2 + yP^2 + zP^2 + L^2 + b^2 + c^2 + d^2 + 2*xP*b + 2*yP*c - 2*zP*d - l^2;

E3 = L*(-sqrt(3)*(xP - b) + yP + c);
F3 = -2*L*(zP - d);
G3 = xP^2 + yP^2 + zP^2 + L^2 + b^2 + c^2 + d^2 - 2*xP*b + 2*yP*c - 2*zP*d - l^2;

t11 = (-F1 + sqrt(E1^2 + F1^2 - G1^2)) /(G1-E1);
t12 = (-F1 - sqrt(E1^2 + F1^2 - G1^2)) /(G1-E1);

t21 = (-F2 + sqrt(E2^2 + F2^2 - G2^2)) /(G2-E2);
t22 = (-F2 - sqrt(E2^2 + F2^2 - G2^2)) /(G2-E2);

t31 = (-F3 + sqrt(E3^2 + F3^2 - G3^2)) /(G3-E3);
t32 = (-F3 - sqrt(E3^2 + F3^2 - G3^2)) /(G3-E3);

%theta11 = 2*atand(t11)
theta12 = round(2*atand(t12),1);
%theta21 = 2*atand(t21)
theta22 = round(2*atand(t22),1);
%theta31 = 2*atand(t31)
theta32 = round(2*atand(t32),1);

if theta12 < exp(-5) theta12 = 0; end
if theta22 < exp(-5) theta22 = 0; end
if theta32 < exp(-5) theta32 = 0; end

theta1 = theta12;
theta2 = theta22;
theta3 = theta32;

end



