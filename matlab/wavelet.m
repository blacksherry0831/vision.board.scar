%==============================================================

%                                 Haar小波变换&反变化  形态学区域收缩

% 

%==============================================================
clear; close all; clc;

Image=uigetfile('*.jpg','选择图片');
Iin = imread(Image);%读取图像
s=double(Iin)/255;
tic;
%=========== 小波变化(Haar) ============
[H,W,C]=size(s);          % 获取搜索区域尺寸
LL=zeros(ceil(H/2),ceil(W/2),C);
HL=LL;
LH=LL;
HH=LL;

for i=1:H-1
    for j=1:W-1
        if mod(i,2)==1 && mod(j,2)==1
%             LL(ceil(i/2),ceil(j/2))=(s(i,j)+s(i+1,j+1))/2;
            LL(ceil(i/2),ceil(j/2),:)=s(i,j,:);
            HL(ceil(i/2),ceil(j/2),:)=s(i+1,j,:)-s(i,j,:);
            LH(ceil(i/2),ceil(j/2),:)=s(i,j+1,:)-s(i,j,:);
            HH(ceil(i/2),ceil(j/2),:)=s(i+1,j+1,:)-s(i,j,:);
        end
    end
end
final=[LL 10*HL;10*LH  10*HH];
imshow(final);

% LL=zeros(ceil(H/2),ceil(W/2));
% HL=zeros(H,W);
% LH=zeros(H,W);
% HH=zeros(H,W);
% for i=1:H-1
%     for j=1:W-1
%         if mod(i,2)==1 && mod(j,2)==1
% %             LL(ceil(i/2),ceil(j/2))=(s(i,j)+s(i+1,j+1))/2;
%             LL(ceil(i/2),ceil(j/2))=s(i,j);
%         end
%         HL(i,j)=s(i+1,j)-s(i,j);
%         LH(i,j)=s(i,j+1)-s(i,j);
%         HH(i,j)=s(i+1,j+1)-s(i,j);
%     end
% end

%=========== 小波反变化(Haar) ============
for i=1:H/2
    for j=1:W/2
        sr(2*i-1,2*j-1,:)=LL(i,j,:);
        sr(2*i,2*j-1,:)=LL(i,j,:)+HL(i,j,:);
        sr(2*i-1,2*j,:)=LL(i,j,:)+LH(i,j,:);
        sr(2*i,2*j,:)=LL(i,j,:)+HH(i,j,:);
    end
end
imshow(sr);

% ========== 形态学滤波（区域收缩）===========

%生成邻域坐标列表 
Epix=1; % 吞噬像素个数
idx=1;
for i=-Epix:Epix
    for j=-Epix:Epix
        if i==0 && j==0
            continue;
        end
        neighbour(idx,:)=[i,j];
        idx=idx+1;
    end
end

s1=s;
for i=1:H
    for j=1:W
        for k=1:(((2*Epix+1))^2-1)
            pix=[i,j]+neighbour(k,:);
            % 越界保护
            if (pix(1)<=0 ||pix(1)>H || pix(2)<=0 || pix(2)>W)
                continue;
            end
            % 最小值滤波
            if sum(s(i,j,:))>sum(s(pix(1),pix(2),:))
                s1(i,j,:)=s(pix(1),pix(2),:);
            end
        end
    end
end
toc
imshow(s1);