function GrafSpace(A, n)
subplot(2,2,1)
plot3(A(:,1), A(:,2), A(:,3),'.','color', [0.5 0 0.5], 'MarkerSize',3)
grid on
xlabel("x axis","FontSize",10)
ylabel("y axis","FontSize",10)
zlabel("z axis","FontSize",10)
title("XYZ Space","FontSize",15)
rotate3d on
axis equal 

subplot(2,2,2)
plot(A(:,1), A(:,2),'.','color', [0.5 0 0.5], 'MarkerSize',3)
grid on
xlabel("x axis","FontSize",10)
ylabel("y axis","FontSize",10)
title("XY Plane","FontSize",15)
axis equal 

subplot(2,2,3)
plot(A(:,1), A(:,3),'.','color', [0.5 0 0.5], 'MarkerSize',3)
grid on
xlabel("x axis","FontSize",10)
ylabel("z axis","FontSize",10)
title("XZ Plane","FontSize",15)
axis equal 

subplot(2,2,4)
plot(A(:,2), A(:,3),'.','color', [0.5 0 0.5], 'MarkerSize',3)
grid on
xlabel("y axis","FontSize",10)
ylabel("z axis","FontSize",10)
title("YZ Plane","FontSize",15)
axis equal 