clc;clear;close all;  % «Â¿Ì
load data;
tic;
Io=ImgDis(Lc,Lm,Ll); 
toc
imwrite(Io,'final.jpg','jpg');