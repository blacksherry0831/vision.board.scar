clear; close all; clc;
txt=importdata('3.txt');
S=size(txt);
Image=uint8(zeros(1920,1080));
N=2;
for i=1:1080
    for j=1:1920
        Image(i,j,1)=txt(N,11)+2*txt(N,12)+4*txt(N,13)+8*txt(N,14)+16*txt(N,15)+32*txt(N,16)+64*txt(N,17)+128*txt(N,18);
%         Image(i,j,2)=txt(N-1,2)+2*txt(N-1,3)+4*txt(N-1,4)+8*txt(N-1,5)+16*txt(N-1,6)+32*txt(N-1,7)+64*txt(N-1,8)+128*txt(N-1,9);
%         Image(i,j,3)=txt(N,2)+2*txt(N,3)+4*txt(N,4)+8*txt(N,5)+16*txt(N,6)+32*txt(N,7)+64*txt(N,8)+128*txt(N,9);
        if(N==S(1))
            break;
        end
        N=N+1;
    end
end
imshow(Image);