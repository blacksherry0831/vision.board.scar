clc;clear;close all;  % ����
load data;
tic;
Io=ImgDis(Lc,Lm,Ll); 
toc
imwrite(Io,'final.jpg','jpg');