%==============================================================

%                                               直方图聚类算法（DEMO）

% 等间隔初始化种子，生产超像素，散点归并(去噪)，等容限粗聚类(θ&L)，直方图分段最大值聚类(θ)

%==============================================================

function[ImgOut]= ImgDis(Lc,Lm,Ll)
Image=uigetfile('*.jpg','选择图片');
Iin = imread(Image);%读取图像
sz=size(Iin);

% 基于查找表的色彩空间转换
Ii=zeros(sz(1),sz(2),sz(3));
for u=1:sz(1)
    for v=1:sz(2)
        idx= ( int64(Iin(u,v,1))*65536 + int64(Iin(u,v,2))*256 + int64(1+Iin(u,v,3)) );
        Ii(u,v,1)=Lc(idx);
        Ii(u,v,2)=Lm(idx);
        Ii(u,v,3)=Ll(idx);
    end
end

%============== 参数初始化 ==============
k=1000;                     % 预估划分块数
die=3;                       % 超像素获取迭代次数
Cmax=360;                % θ直方图点数
Lmax=100;                 % L直方图点数
Mth=80000;  % 分通道阈值

s=(sz(1)*sz(2)/k)^0.5;s=ceil(s);    %初始分割网格间距s
r=ceil(sz(1)/s);	  %网格行数r
w=ceil(sz(2)/s);	%网格列数w
ct=r*w;               %计算种子点数
thd=sz(1)*sz(2)/ct/4;    % 散点归并阈值
belongo=uint16(ones(sz(1),sz(2)));     % 初始化归属矩阵
center=zeros(ct,6);                         % 初始化种子列表


%% 尝试移植开始>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

%=============== 等间隔初始化种子 ==================
% 初始中心节点center(图像空域固定间隔撒点) **idx为查找表下标**
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
        %初始中心像素点 [角度、模值、亮度、横坐标、纵坐标]
        center((i-1)*w+j,:)=[Ii(x1,y1,1),Ii(x1,y1,2),Ii(x1,y1,3),x1,y1,0];
    end
end

%=============================== 迭代细化超像素 ===============================
% move=99999;
dist=999999*ones(sz(1),sz(2));    %以最大值初始每个像素点的距离
for c=1:die    %进行迭代die次
%     if move<10
%         break;
%     end
%     move=0;
    for i=1:ct
        % 根据像素与最邻近种子的广义距离（色彩亮度&空域距离 dc&ds）,重新定义归属
        for u=center(i,4)-s:center(i,4)+s
            if(u>=1)&&(u<=sz(1))
                for v=center(i,5)-s:center(i,5)+s
                    if(v>=1)&&(v<=sz(2))
                        %  dc:(θ m L相似度)；ds:(空域距离)
                        dc=((Ii(u,v,1)-center(i,1))^2+(Ii(u,v,2)-center(i,2))^2+(Ii(u,v,3)-center(i,3))^2)^0.5;
                        ds=((u/sz(1)-center(i,4)/sz(1))^2+(v/sz(2)-center(i,5)/sz(2))^2)^0.5;
                        % 计算广义距离
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

% 尝试移植结束<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

%=============================== 散点归并 ===============================
belong=0*belongo;       %创建新归属矩阵
[m,n]=size(belong);       % 获取搜索区域尺寸
label=1;                        % 归属值初始化
nbv=1;                          % 临近归属值初始化
neighbour=[-1 0;0 -1;0 1;1 0];  % 4邻域坐标偏移列表
% neighbour=[-1 -1;-1 0;-1 1;0 -1;0 1;1 -1;1 0;1 1];  % 8邻域坐标偏移列表

for i=1:m
    for j=1:n       % 遍历归属矩阵(新归属阵中0表示常委处理)
        opix=[i,j];
        % 若新归属阵当前点未处理，则赋当前归属值label
        if belong(opix(1),opix(2))==0      
            belong(opix(1),opix(2))=label;
            pix=[i,j];
            q(1,:)=pix; 
            for k=1:4       % 搜索4邻域
                pix1=pix+neighbour(k,:);    % 获取当前邻域元素坐标
                if pix1(1)>=1 && pix1(1)<=m && pix1(2) >=1 &&pix1(2)<=n       %越界保护
                    % 若新归属阵当前邻域点已处理，以此点归属值为临近归属值(散点周围的归属值)
                    if belong(pix1(1),pix1(2)) >0
                        nbv=belong(pix1(1),pix1(2));    % 记录临近归属值
                    end
                end              
            end
        
            c=1;Lmun=1;
            while (c<=Lmun)
                for k=1:4           % 搜索4邻域
                    pix=q(c,:);     % 取待分析点坐标
                    pix1=pix+neighbour(k,:);    % 计算邻域元素坐标
                    if pix1(1)>=1 && pix1(1)<=m && pix1(2) >=1 &&pix1(2)<=n      %越界保护
                        % 若新归属阵当前邻域点未处理，且旧归属阵中待分析点与邻域点归属相同，则赋予其当前标记值，计数器++，当前邻域点坐标入队
                        if belong(pix1(1),pix1(2)) == 0 && belongo(pix1(1),pix1(2))==belongo(opix(1),opix(2))
                            belong(pix1(1),pix1(2))=label;
                            Lmun=Lmun+1;
                            q(Lmun,:)=[pix1(1),pix1(2)];
                        end  
                    end              
                end
                c=c+1;
            end
            % 若新归属阵同归属值区域过小，将其归属值用记录的临近归属nbv值代替（就近归并）
            if Lmun<(thd)
                G=uint16(belong==label);
                belong=belong-G.*label+G*nbv;
                label=label-1;
            end
            label=label+1;
        end

    end
end

%====== 更新种子列表（去除消失区域对应的种子）======
label=label-1;  % 矫正区域个数
center=zeros(label,6);    % 初始化种子列表
c1=zeros(label,1);          % 初始化种子列表中各值得存储数组
ct_x=zeros(label,1);
ct_y=zeros(label,1);
ct_c=zeros(label,1);
ct_m=zeros(label,1);
ct_l=zeros(label,1);

for k=1:sz(1)
    for g=1:sz(2)
        i=belong(k,g);                      % 获取当前点归属值
        c1(i)=c1(i)+1;                        % 属于各种子的像素数
        ct_x(i)=ct_x(i)+k;                   % 各超像素的平均c
        ct_y(i)=ct_y(i)+g;                  % 各超像素的平均m
        ct_c(i)=ct_c(i)+Ii(k,g,1);           % 各超像素的平均l
        ct_m(i)=ct_m(i)+Ii(k,g,2);        % 各超像素的平均x
        ct_l(i)=ct_l(i)+Ii(k,g,3);            % 各超像素的平均y
    end
end

for i=1:label
    center(i,1)=(ct_c(i)/c1(i));        % 种子列表各值归一化，
    center(i,2)=(ct_m(i)/c1(i));
    center(i,3)=(ct_l(i)/c1(i));
    center(i,4)=fix(ct_x(i)/c1(i));
    center(i,5)=fix(ct_y(i)/c1(i));
    center(i,6)=c1(i);                  % 统计各归属区域像素数
end

%=========== 相邻关系矩阵 ===========
% 相邻1，否则0
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

%====== 创建无符号整形种子列表 ======
% 非必要（方便移植）

center1=int32(zeros(label,6));
center1(:,1)=uint32(center(:,1)*(Cmax-1));
center1(:,2)=uint32(center(:,2)*(1000000));
center1(:,3)=uint32(center(:,3)*(Lmax-1));
center1(:,4)=uint32(center(:,4));
center1(:,5)=uint32(center(:,5));
center1(:,6)=uint32(center(:,6));
% center1(:,7)=uint32(0);

%=================== 等容限粗聚类(θ&L) =====================

% 颜色向量模较小 θ聚类； 较大 L聚类
for i=1:label
    if sum(center1(i,:))==0
        continue;
    end

    for j=i+1:label
        if center1(j,6)==0
            continue;
        end
        % 模较小L聚类(center1第3列，100直方图分16段)，
        if(center1(i,2)<=Mth && center1(j,2)<=Mth)
            chn=3;div=6.25;
        % 模较大θ聚类(center1第1列，360直方图分60段)
        elseif (center1(i,2)>Mth && center1(j,2)>Mth)
            chn=1;div=6;
        else
            continue;
        end
        iidx=ceil(center1(i,chn)/div);        % 计算待归并种子归属段
        jidx=ceil(center1(j,chn)/div);
        if (iidx==jidx && EMtx(i,j)~=0 )    % 两种子同段（颜色相近）且相邻则合并
            % 更新种子列表(按比例更新θ m L x y，种子数叠加)
            center1(i,6)=center1(i,6)+center1(j,6);
%             jratio=double(center1(j,6))/double(center1(i,6));
%             center1(i,1:5)=int32( (1-jratio)*center1(i,1:5)+jratio*center1(j,1:5) );
            center1(j,:)=0;     % 清除被合并种子
            
            % 更新相邻关系矩阵(合并的种子相邻关系归并，被合并种子对应行列、对角线元素请0)
            EMtx(i,:)=EMtx(i,:)+EMtx(j,:);
            EMtx(:,i)=EMtx(:,i)+EMtx(:,j);
            EMtx(j,:)=0;
            EMtx(:,j)=0;
            EMtx(i,i)=0;
            
            % 更新归属矩阵(更新被合并区域归属值)
            for k=1:sz(1)
                for l=1:sz(2)
                    if belong(k,l)==j
                        belong(k,l)=i;      % 标识矩阵
                    end
                end
            end

        end
    end
end

%===================== 直方图分段最大值聚类(θ 1次) =====================
% 获取θ直方图
Hc=zeros(Cmax,1);
szc=size(center1);
for i=1:szc(1)
    if(center1(i,6)~=0 && center1(i,2)>Mth)
        Hc( center1(i,1)+1 ) = Hc( center1(i,1)+1 )+center1(i,6);
    else
        center1(i,1)=0;
    end
end

hr=5;                     % 相似度容限
hd=uint16(Cmax/9);  % 直方图分段宽度
Ccmax=zeros(9,1);
mid=int32(zeros(9,1));
for i=1:9
    [Ccmax(i),mi]=max( Hc( hd*(i-1)+1 : hd*i ) );
    mid(i)=mi-1+hd*(i-1);
    if(Ccmax(i)==0)
        continue;
    end
    % 寻找概率最大亮度对应的种子
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
    % 直方图各段内向最大值对应的种子聚类
        for j=1:label
            if  center1(j,2)>Mth
                continue;
            end
            % 在色盘上计算角度差(循环数组)
            if (center1(j,1)-hr<1 && mid(i)+hr>Cmax)
                cn=center1(j,1)+Cmax-mid(i);
            elseif (mid(i)-hr<1 && center1(j,1)+hr>Cmax)
                cn=mid(i)+Cmax-center1(j,1);
            else
                cn=abs(mid(i)-center1(j,1));
            end

            if ( EMtx(cidx(g),j)~=0 && (cn<hr))
                % 更新种子列表(按比例更新θ m L x y，种子数叠加)
                center1(cidx(g),6)=center1(cidx(g),6)+center1(j,6);
%                 jratio=double(center1(j,6))/double(center1(cidx(g),6));
%                 center1(i,1:5)=int32( (1-jratio)*center1(cidx(g),1:5)+jratio*center1(j,1:5) );
                center1(j,:)=0;     % 清空被合并种子

                % 更新相邻关系矩阵(合并的种子相邻关系归并，被合并种子对应行列、对角线元素请0)
                EMtx(cidx(g),:)=EMtx(cidx(g),:)+EMtx(j,:);
                EMtx(:,cidx(g))=EMtx(:,cidx(g))+EMtx(:,j);
                EMtx(j,:)=0;
                EMtx(:,j)=0;
                EMtx(cidx(g),cidx(g))=0;

                % 更新归属矩阵
                for k=1:sz(1)
                    for l=1:sz(2)
                        if belong(k,l)==j
                            belong(k,l)=cidx(g);      % 标识矩阵
                        end
                    end
                end

            end
            
        end
    end
end

%================= 输出聚类结果(非必要) ===================
ImgOut=uint8(zeros(sz(1),sz(2),sz(3)));    % 初始化输出图像存储空间
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
BW1=uint8(~Bedge); % 提取边界
ImgOut(:,:,1)=ImgOut(:,:,1).*BW1;
ImgOut(:,:,2)=ImgOut(:,:,2).*BW1;
ImgOut(:,:,3)=ImgOut(:,:,3).*BW1;
imshow(ImgOut);
label
