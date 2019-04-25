clear;clc;
%================== 参数矩阵 ===================
A =[1.54510645e+03,0,1.10233044e+03;
    0,1.54874036e+03,6.17808777e+02;
    0 0 1];
D = [-3.65634471e-01,1.40376598e-01,-2.57731555e-03,2.75499711e-04,0];
fx = A(1,1);
fy = A(2,2);
cx = A(1,3);
cy = A(2,3);
k1 = D(1);
k2 = D(2);
k3 = D(5);
p1 = D(3);
p2 = D(4);

%================== 读取图像 ===================
K = A;
Ima=uigetfile('*.png','选择图片');
I_d = imread(Ima);
%     I_d = rgb2gray(I_d);
I_d = im2double(I_d);
[W,H,C]=size(I_d);
I_r = zeros(size(I_d));

%图像坐标系和矩阵的表示是相反的
%[row,col] = find(X)，坐标按照列的顺序排列，这样好和reshape()匹配出响应的图像矩阵
[v,u] = find(~isnan(I_r(:,:,1)));

% XYZc 摄像机坐标系的值，但是已经归一化了，因为没有乘比例因子
%公式 s[u v 1]' = A*[Xc Yc Zc]' ，其中s为比例因子，不加比例因子，Zc就为1，所以此时的Xc相对于( Xc/Zc )
A1=inv(A);
XYZc= A1*[u v ones(length(u),1)]';

% 此时的x和y是没有畸变的
r2 = XYZc(1,:).^2+XYZc(2,:).^2;
x = XYZc(1,:);
y = XYZc(2,:);

% x和y进行畸变的
x = x.*(1+k1*r2 + k2*r2.^2) + 2*p1.*x.*y + p2*(r2 + 2*x.^2);
y = y.*(1+k1*r2 + k2*r2.^2) + 2*p2.*x.*y + p1*(r2 + 2*y.^2);

% (u, v) 对应的畸变坐标 (u_d, v_d)
u_d = reshape(fx*x + cx,W,H);
v_d = reshape(fy*y + cy,W,H);

% 线性插值出非畸变的图像
I_r(:,:,1) = interp2(I_d(:,:,1), u_d, v_d);
I_r(:,:,2) = interp2(I_d(:,:,2), u_d, v_d);
I_r(:,:,3) = interp2(I_d(:,:,3), u_d, v_d);
%对比图像
figure;
%     subplot(121);     
    imshow(I_d);
    title('畸变原图像');
figure;
%     subplot(122);
    imshow(I_r);
    title('校正后图像');
