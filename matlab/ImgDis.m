%==============================================================

%                                               ֱ��ͼ�����㷨��DEMO��

% �ȼ����ʼ�����ӣ����������أ�ɢ��鲢(ȥ��)�������޴־���(��&L)��ֱ��ͼ�ֶ����ֵ����(��)

%==============================================================

function[ImgOut]= ImgDis(Lc,Lm,Ll)
Image=uigetfile('*.jpg','ѡ��ͼƬ');
Iin = imread(Image);%��ȡͼ��
sz=size(Iin);

% ���ڲ��ұ��ɫ�ʿռ�ת��
Ii=zeros(sz(1),sz(2),sz(3));
for u=1:sz(1)
    for v=1:sz(2)
        idx= ( int64(Iin(u,v,1))*65536 + int64(Iin(u,v,2))*256 + int64(1+Iin(u,v,3)) );
        Ii(u,v,1)=Lc(idx);
        Ii(u,v,2)=Lm(idx);
        Ii(u,v,3)=Ll(idx);
    end
end

%============== ������ʼ�� ==============
k=1000;                     % Ԥ�����ֿ���
die=3;                       % �����ػ�ȡ��������
Cmax=360;                % ��ֱ��ͼ����
Lmax=100;                 % Lֱ��ͼ����
Mth=80000;  % ��ͨ����ֵ

s=(sz(1)*sz(2)/k)^0.5;s=ceil(s);    %��ʼ�ָ�������s
r=ceil(sz(1)/s);	  %��������r
w=ceil(sz(2)/s);	%��������w
ct=r*w;               %�������ӵ���
thd=sz(1)*sz(2)/ct/4;    % ɢ��鲢��ֵ
belongo=uint16(ones(sz(1),sz(2)));     % ��ʼ����������
center=zeros(ct,6);                         % ��ʼ�������б�


%% ������ֲ��ʼ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

%=============== �ȼ����ʼ������ ==================
% ��ʼ���Ľڵ�center(ͼ�����̶��������) **idxΪ���ұ��±�**
for i=1:r
    for j=1:w
        if (i<r)
            x1=(i-1)*s+fix(s/2);
        else
            x1=(i-1)*s+fix(rem(sz(1),s)/2);
        end
        if (j<w)
            y1=(j-1)*s+fix(s/2);
        else
            y1=(j-1)*s+fix(rem(sz(2),s)/2);
        end
        %��ʼ�������ص� [�Ƕȡ�ģֵ�����ȡ������ꡢ������]
        center((i-1)*w+j,:)=[Ii(x1,y1,1),Ii(x1,y1,2),Ii(x1,y1,3),x1,y1,0];
    end
end

%=============================== ����ϸ�������� ===============================
% move=99999;
dist=999999*ones(sz(1),sz(2));    %�����ֵ��ʼÿ�����ص�ľ���
for c=1:die    %���е���die��
%     if move<10
%         break;
%     end
%     move=0;
    for i=1:ct
        % �������������ڽ����ӵĹ�����루ɫ������&������� dc&ds��,���¶������
        for u=center(i,4)-s:center(i,4)+s
            if(u>=1)&&(u<=sz(1))
                for v=center(i,5)-s:center(i,5)+s
                    if(v>=1)&&(v<=sz(2))
                        %  dc:(�� m L���ƶ�)��ds:(�������)
                        dc=((Ii(u,v,1)-center(i,1))^2+(Ii(u,v,2)-center(i,2))^2+(Ii(u,v,3)-center(i,3))^2)^0.5;
                        ds=((u/sz(1)-center(i,4)/sz(1))^2+(v/sz(2)-center(i,5)/sz(2))^2)^0.5;
                        % ����������
                        d=((dc)^2+(ds)^2)^0.5;
%                         d=((dc)^2+(ds*m/s)^2)^0.5;
                        if d<dist(u,v)
                            dist(u,v)=d;
                            belongo(u,v)=i; 
%                             move=move+1;
                        end
                    end
                end
            end
        end
    end 

end

% ������ֲ����<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

%=============================== ɢ��鲢 ===============================
belong=0*belongo;       %�����¹�������
[m,n]=size(belong);       % ��ȡ��������ߴ�
label=1;                        % ����ֵ��ʼ��
nbv=1;                          % �ٽ�����ֵ��ʼ��
neighbour=[-1 0;0 -1;0 1;1 0];  % 4��������ƫ���б�
% neighbour=[-1 -1;-1 0;-1 1;0 -1;0 1;1 -1;1 0;1 1];  % 8��������ƫ���б�

for i=1:m
    for j=1:n       % ������������(�¹�������0��ʾ��ί����)
        opix=[i,j];
        % ���¹�����ǰ��δ�����򸳵�ǰ����ֵlabel
        if belong(opix(1),opix(2))==0      
            belong(opix(1),opix(2))=label;
            pix=[i,j];
            q(1,:)=pix; 
            for k=1:4       % ����4����
                pix1=pix+neighbour(k,:);    % ��ȡ��ǰ����Ԫ������
                if pix1(1)>=1 && pix1(1)<=m && pix1(2) >=1 &&pix1(2)<=n       %Խ�籣��
                    % ���¹�����ǰ������Ѵ����Դ˵����ֵΪ�ٽ�����ֵ(ɢ����Χ�Ĺ���ֵ)
                    if belong(pix1(1),pix1(2)) >0
                        nbv=belong(pix1(1),pix1(2));    % ��¼�ٽ�����ֵ
                    end
                end              
            end
        
            c=1;Lmun=1;
            while (c<=Lmun)
                for k=1:4           % ����4����
                    pix=q(c,:);     % ȡ������������
                    pix1=pix+neighbour(k,:);    % ��������Ԫ������
                    if pix1(1)>=1 && pix1(1)<=m && pix1(2) >=1 &&pix1(2)<=n      %Խ�籣��
                        % ���¹�����ǰ�����δ�����Ҿɹ������д�������������������ͬ�������䵱ǰ���ֵ��������++����ǰ������������
                        if belong(pix1(1),pix1(2)) == 0 && belongo(pix1(1),pix1(2))==belongo(opix(1),opix(2))
                            belong(pix1(1),pix1(2))=label;
                            Lmun=Lmun+1;
                            q(Lmun,:)=[pix1(1),pix1(2)];
                        end  
                    end              
                end
                c=c+1;
            end
            % ���¹�����ͬ����ֵ�����С���������ֵ�ü�¼���ٽ�����nbvֵ���棨�ͽ��鲢��
            if Lmun<(thd)
                G=uint16(belong==label);
                belong=belong-G.*label+G*nbv;
                label=label-1;
            end
            label=label+1;
        end

    end
end

%====== ���������б�ȥ����ʧ�����Ӧ�����ӣ�======
label=label-1;  % �����������
center=zeros(label,6);    % ��ʼ�������б�
c1=zeros(label,1);          % ��ʼ�������б��и�ֵ�ô洢����
ct_x=zeros(label,1);
ct_y=zeros(label,1);
ct_c=zeros(label,1);
ct_m=zeros(label,1);
ct_l=zeros(label,1);

for k=1:sz(1)
    for g=1:sz(2)
        i=belong(k,g);                      % ��ȡ��ǰ�����ֵ
        c1(i)=c1(i)+1;                        % ���ڸ����ӵ�������
        ct_x(i)=ct_x(i)+k;                   % �������ص�ƽ��c
        ct_y(i)=ct_y(i)+g;                  % �������ص�ƽ��m
        ct_c(i)=ct_c(i)+Ii(k,g,1);           % �������ص�ƽ��l
        ct_m(i)=ct_m(i)+Ii(k,g,2);        % �������ص�ƽ��x
        ct_l(i)=ct_l(i)+Ii(k,g,3);            % �������ص�ƽ��y
    end
end

for i=1:label
    center(i,1)=(ct_c(i)/c1(i));        % �����б��ֵ��һ����
    center(i,2)=(ct_m(i)/c1(i));
    center(i,3)=(ct_l(i)/c1(i));
    center(i,4)=fix(ct_x(i)/c1(i));
    center(i,5)=fix(ct_y(i)/c1(i));
    center(i,6)=c1(i);                  % ͳ�Ƹ���������������
end

%=========== ���ڹ�ϵ���� ===========
% ����1������0
EMtx=zeros(label);
for i=2:sz(1)-1
    for j=2:sz(2)-1
        for k=i-1:i+1
            for l=j-1:j+1
                if(belong(i,j)~=belong(k,l))
                  EMtx(belong(i,j),belong(k,l))=1;
                end
            end
        end
    end
end

%====== �����޷������������б� ======
% �Ǳ�Ҫ��������ֲ��

center1=int32(zeros(label,6));
center1(:,1)=uint32(center(:,1)*(Cmax-1));
center1(:,2)=uint32(center(:,2)*(1000000));
center1(:,3)=uint32(center(:,3)*(Lmax-1));
center1(:,4)=uint32(center(:,4));
center1(:,5)=uint32(center(:,5));
center1(:,6)=uint32(center(:,6));
% center1(:,7)=uint32(0);

%=================== �����޴־���(��&L) =====================

% ��ɫ����ģ��С �Ⱦ��ࣻ �ϴ� L����
for i=1:label
    if sum(center1(i,:))==0
        continue;
    end

    for j=i+1:label
        if center1(j,6)==0
            continue;
        end
        % ģ��СL����(center1��3�У�100ֱ��ͼ��16��)��
        if(center1(i,2)<=Mth && center1(j,2)<=Mth)
            chn=3;div=6.25;
        % ģ�ϴ�Ⱦ���(center1��1�У�360ֱ��ͼ��60��)
        elseif (center1(i,2)>Mth && center1(j,2)>Mth)
            chn=1;div=6;
        else
            continue;
        end
        iidx=ceil(center1(i,chn)/div);        % ������鲢���ӹ�����
        jidx=ceil(center1(j,chn)/div);
        if (iidx==jidx && EMtx(i,j)~=0 )    % ������ͬ�Σ���ɫ�������������ϲ�
            % ���������б�(���������¦� m L x y������������)
            center1(i,6)=center1(i,6)+center1(j,6);
%             jratio=double(center1(j,6))/double(center1(i,6));
%             center1(i,1:5)=int32( (1-jratio)*center1(i,1:5)+jratio*center1(j,1:5) );
            center1(j,:)=0;     % ������ϲ�����
            
            % �������ڹ�ϵ����(�ϲ����������ڹ�ϵ�鲢�����ϲ����Ӷ�Ӧ���С��Խ���Ԫ����0)
            EMtx(i,:)=EMtx(i,:)+EMtx(j,:);
            EMtx(:,i)=EMtx(:,i)+EMtx(:,j);
            EMtx(j,:)=0;
            EMtx(:,j)=0;
            EMtx(i,i)=0;
            
            % ���¹�������(���±��ϲ��������ֵ)
            for k=1:sz(1)
                for l=1:sz(2)
                    if belong(k,l)==j
                        belong(k,l)=i;      % ��ʶ����
                    end
                end
            end

        end
    end
end

%===================== ֱ��ͼ�ֶ����ֵ����(�� 1��) =====================
% ��ȡ��ֱ��ͼ
Hc=zeros(Cmax,1);
szc=size(center1);
for i=1:szc(1)
    if(center1(i,6)~=0 && center1(i,2)>Mth)
        Hc( center1(i,1)+1 ) = Hc( center1(i,1)+1 )+center1(i,6);
    else
        center1(i,1)=0;
    end
end

hr=5;                     % ���ƶ�����
hd=uint16(Cmax/9);  % ֱ��ͼ�ֶο��
Ccmax=zeros(9,1);
mid=int32(zeros(9,1));
for i=1:9
    [Ccmax(i),mi]=max( Hc( hd*(i-1)+1 : hd*i ) );
    mid(i)=mi-1+hd*(i-1);
    if(Ccmax(i)==0)
        continue;
    end
    % Ѱ�Ҹ���������ȶ�Ӧ������
    fid=1;
    for t=1:label
        if center1(t,1)==mid(i) && center1(t,2)>Mth
            cidx(fid) = t;
            fid=fid+1;
        end
    end

    if isempty(cidx)
        continue;
    end
    Mcidx=length(cidx);
    for g=1:Mcidx
    % ֱ��ͼ�����������ֵ��Ӧ�����Ӿ���
        for j=1:label
            if  center1(j,2)>Mth
                continue;
            end
            % ��ɫ���ϼ���ǶȲ�(ѭ������)
            if (center1(j,1)-hr<1 && mid(i)+hr>Cmax)
                cn=center1(j,1)+Cmax-mid(i);
            elseif (mid(i)-hr<1 && center1(j,1)+hr>Cmax)
                cn=mid(i)+Cmax-center1(j,1);
            else
                cn=abs(mid(i)-center1(j,1));
            end

            if ( EMtx(cidx(g),j)~=0 && (cn<hr))
                % ���������б�(���������¦� m L x y������������)
                center1(cidx(g),6)=center1(cidx(g),6)+center1(j,6);
%                 jratio=double(center1(j,6))/double(center1(cidx(g),6));
%                 center1(i,1:5)=int32( (1-jratio)*center1(cidx(g),1:5)+jratio*center1(j,1:5) );
                center1(j,:)=0;     % ��ձ��ϲ�����

                % �������ڹ�ϵ����(�ϲ����������ڹ�ϵ�鲢�����ϲ����Ӷ�Ӧ���С��Խ���Ԫ����0)
                EMtx(cidx(g),:)=EMtx(cidx(g),:)+EMtx(j,:);
                EMtx(:,cidx(g))=EMtx(:,cidx(g))+EMtx(:,j);
                EMtx(j,:)=0;
                EMtx(:,j)=0;
                EMtx(cidx(g),cidx(g))=0;

                % ���¹�������
                for k=1:sz(1)
                    for l=1:sz(2)
                        if belong(k,l)==j
                            belong(k,l)=cidx(g);      % ��ʶ����
                        end
                    end
                end

            end
            
        end
    end
end

%================= ���������(�Ǳ�Ҫ) ===================
ImgOut=uint8(zeros(sz(1),sz(2),sz(3)));    % ��ʼ�����ͼ��洢�ռ�
Bedge= false(sz(1),sz(2));
for t1=min(belong(:)):max(belong(:))
    
    Fg = belong == t1;
    Fg = uint8(Fg);
    num=sum(Fg(:));
    if num==0
        continue;
    end
    Bedge=Bedge|edge(Fg,'sobel');
%     imagesc(Bedge);
    Ic(1)=sum(sum(Iin(:,:,1).* Fg))/num;
    Ic(2)=sum(sum(Iin(:,:,2).* Fg))/num;
    Ic(3)=sum(sum(Iin(:,:,3).* Fg))/num;
    ImgOut(:,:,1) =  ImgOut(:,:,1)+Ic(1).* Fg;
    ImgOut(:,:,2) =  ImgOut(:,:,2)+Ic(2).* Fg;
    ImgOut(:,:,3) =  ImgOut(:,:,3)+Ic(3).* Fg;

end
BW1=uint8(~Bedge); % ��ȡ�߽�
ImgOut(:,:,1)=ImgOut(:,:,1).*BW1;
ImgOut(:,:,2)=ImgOut(:,:,2).*BW1;
ImgOut(:,:,3)=ImgOut(:,:,3).*BW1;
imshow(ImgOut);
label
