clear all
clc
file = 'Book2.xlsx'
A = xlsread(file)
for i = 1:101
    [xP(i,1) yP(i,1) zP(i,1) f] = Forward_Kinematics(A(i,1),A(i,2),A(i,3))
end

%plot(xP, yP, 'o-', 'LineWidth',1);
xlim([-170, 170]); % Giới hạn trục x từ 3 đến 7
ylim([-170, 170]);
zlim([0, 500]);% Giới hạn trục y từ 10 đến 5
 plot3(xP, yP, zP, 'o-', 'LineWidth',1);
