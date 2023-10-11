function [A, n] = WorkSpace()
clear all;
n = 1; 
h = 5;
A = zeros((80/h)^3, 3);
for th1 = 10 : h : 90
    for th2 = 10 : h : 90
        for th3 = 10 : h : 90
            [xP, yP, zP, fl] = Forward_Kinematics(th1, th2, th3);
            if fl == 0 
               A(n, 1) = xP;
               A(n, 2) = yP;
               A(n, 3) = zP;
%                A(n, 4) = th1;
%                A(n, 5) = th2;
%                A(n, 6) = th3;
               n = n+1;
            end
         end
    end
end
end