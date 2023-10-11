% for i = 1:101
%     [xP(i,1) yP(i,1) zP(i,1) f] = Forward_Kinematics(A(i,1),A(i,2),A(i,3))
% end
% 
% 
% %figure;
% hold on;
% for j = 1:101
%     scater3(xP(j), yP(j), zP(j), 'ro', 'filled');
%     pause(0.1); % Dừng 1 giây giữa các điểm
% end
% hold off;
% 
% % Tùy chỉnh đồ thị
% title('Vẽ lần lượt điểm trong không gian 3D');
% xlabel('Trục x');
% ylabel('Trục y');
% zlabel('Trục z');

% Tạo dữ liệu điểm
x = [1, 2, 3, 4, 5];
y = [2, 4, 6, 8, 10];
z = [3, 6, 9, 12, 15];

% Vẽ lần lượt các điểm
figure;
hold on;

% for i = 1:numel(x)
%     plot3(x(i), y(i), z(i), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
%     pause(1);  % Dừng 1 giây giữa các điểm
% end

scatter3(xP, yP, zP)

hold off;

% Tùy chỉnh đồ thị
title('Vẽ lần lượt các điểm trong không gian 3D');
xlabel('Trục x');
ylabel('Trục y');
zlabel('Trục z');
grid on;





% for j = 1:101
%     scatter(xP(i,1), yP(i,1));
%     pause(1);
% end
%scatter(xP,yP)
% figure;
% hold on;
xlim([-170, 170]); % Giới hạn trục x từ 3 đến 7
ylim([-170, 170]);
zlim([-170, 170]);% Giới hạn trục y từ 10 đến 5
% for j = 1:101
%     scatter3(xP(j), yP(j), zP(j),'ro')
%     %surf(xP(j), yP(j), zP(j),'ro');
%     %plot3(xP(j), yP(j), zP(j),'ro')
%     pause(0.5)
% end
% hold off;
% grid on;