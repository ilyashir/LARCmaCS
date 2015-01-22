%[Left,Right] = TrackAvoidance(Xagent,Xang,Ball,Cang,algN,Opponent,C_dist,BallDangArea);
%[Left,Right] = TrackAvoidance(Xagent,Xang,Ball,Cang,algN,Opponent,C_dist), BallDangArea=0;
%[Left,Right] = TrackAvoidance(Xagent,Xang,Ball,Cang,algN,Opponent), C_dist=200, BallDangArea=5;
% ѕриводит агента Xagent к цели Ball под углом Cang.
% algN - дл€ каждого робота должен быть свой номер.
% Opponent - массив координат оппонентов.
% C_dis - рассто€ние безопасного захода на м€чь.
% BallDangArea - рассто€ние безопасного объезда цели..
function [Left,Right] = TrackAvoidance(Xagent,Xang,Ball,Cang,algN,Opponent,...
C_dist,BallDangArea)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
TrAv_WorkTime=tic();
show=1;
depth=6;

if (nargin==6)
    BallDangArea=5;
    C_dist=200;
end
if (nargin==7)
    BallDangArea=0;
end    

C=Ball-C_dist*[cos(Cang),sin(Cang)];
%% ALR{N} PAR
global trackavoi
if isempty(trackavoi) || ~isfield(trackavoi,'weight')
    TrackAvoi_INI();
    trackavoi.weight=[];
    trackavoi.MAP=[];
end

szX=trackavoi.PAR.szX;
szY=trackavoi.PAR.szY;
X=trackavoi.PAR.X;
Y=trackavoi.PAR.Y;
lsloy=trackavoi.PAR.lsloy;
sdvig=trackavoi.PAR.sdvig;
sdvig1=trackavoi.PAR.sdvig1;
sdvig2=trackavoi.PAR.sdvig2;
lsd=trackavoi.PAR.lsd;
algK=trackavoi.PAR.algK;
algStep=trackavoi.PAR.algStep;
d=trackavoi.PAR.d;
if ((length(trackavoi.weight)>=algN) ...
    &&(size(trackavoi.weight{algN},1)==szY) ...
    &&(size(trackavoi.weight{algN},2)==szX))
    weight=trackavoi.weight{algN};
else
    weight=ones(szY,szX)*inf;
end
%%
FF=ones(szY,szX);
for i=1:size(Opponent,1)
    FF=FF+algK./(((X-Opponent(i,1)).^2+(Y-Opponent(i,2)).^2).^(algStep/2));
end
%if 0
if ~isnan(Cang)
    rz=coor(C,X,Y);   
    rz2=coor(Ball,X,Y);
    for i=-BallDangArea:BallDangArea
        for j=-BallDangArea:BallDangArea
            if ((rz(2)+i<=szY) && (rz(2)+i>0) && (rz(1)+j<=szX) && (rz(1)+j>0))
                qwert=[X(rz(2)+i,rz(1)+j)-X(rz(2),rz(1)),...
                       Y(rz(2)+i,rz(1)+j)-Y(rz(2),rz(1))];
                if ((abs(azi(angV(qwert)-Cang))<4*pi/6) && norm(qwert)>d*2)
                    FF(rz(2)+i,rz(1)+j)=1000;            
                end
            end
            if ((rz2(2)+i<=szY) && (rz2(2)+i>0) && (rz2(1)+j<=szX) && (rz2(1)+j>0))
                qwert=[X(rz2(2)+i,rz2(1)+j)-X(rz2(2),rz2(1)),...
                       Y(rz2(2)+i,rz2(1)+j)-Y(rz2(2),rz2(1))];
                if ((abs(azi(angV(qwert)-Cang))<4*pi/6) && norm(qwert)>d*2)
                    FF(rz2(2)+i,rz2(1)+j)=1000;            
                end
            end
        end
    end
end
%end
FF=[ones(lsloy+szY+lsloy,lsloy)*inf,...
    [ones(lsloy,szX)*inf;FF;ones(lsloy,szX)*inf],...
    ones(lsloy+szY+lsloy,lsloy)*inf];
%toc()
weight(Z(C,X,Y))=0;

FShelp=zeros(szY,szX,size(sdvig1,1));
for i=1:size(sdvig1,1)
    FShelp(1:2:szY,1:szX,i)=lsd(i)*( FF((1:2:szY)+lsloy,(1:szX)+lsloy)+...
        FF((1:2:szY)+lsloy+sdvig2(i,2),(1:szX)+lsloy+sdvig2(i,1)) )/2;
    FShelp(2:2:szY,1:szX,i)=lsd(i)*( FF((2:2:szY)+lsloy,(1:szX)+lsloy)+...
        FF((2:2:szY)+lsloy+sdvig1(i,2),(1:szX)+lsloy+sdvig1(i,1)) )/2; 
end

TFS=zeros(szY,szX,size(sdvig1,1));
for j=1:depth
    %ƒополнение T на lsloy.
    TT=[ones(lsloy+szY+lsloy,lsloy)*inf,[ones(lsloy,szX)*inf;weight;ones(lsloy,szX)*inf],ones(lsloy+szY+lsloy,lsloy)*inf];
    %for i=1:size(sdvig1,1)
    %    TFS(1:2:szY,1:szX,i)=TT((1:2:szY)+lsloy+sdvig2(i,2),(1:szX)+lsloy+sdvig2(i,1));
    %    TFS(2:2:szY,1:szX,i)=TT((2:2:szY)+lsloy+sdvig1(i,2),(1:szX)+lsloy+sdvig1(i,1));
    %end    
    %TFS=TFS+FShelp;
    for i=1:size(sdvig1,1)  
        TFS(1:2:szY,1:szX,i)=TT((1:2:szY)+lsloy+sdvig2(i,2),(1:szX)+lsloy+sdvig2(i,1))+FShelp(1:2:szY,1:szX,i);
        TFS(2:2:szY,1:szX,i)=TT((2:2:szY)+lsloy+sdvig1(i,2),(1:szX)+lsloy+sdvig1(i,1))+FShelp(2:2:szY,1:szX,i);        
        %TFS(1:2:szY,1:szX,i)=TT((1:2:szY)+lsloy+sdvig2(i,2),(1:szX)+lsloy+sdvig2(i,1))+lsd(i)*(FF((1:2:szY)+lsloy,(1:szX)+lsloy)+FF((1:2:szY)+lsloy+sdvig2(i,2),(1:szX)+lsloy+sdvig2(i,1)))/2;
        %TFS(2:2:szY,1:szX,i)=TT((2:2:szY)+lsloy+sdvig1(i,2),(1:szX)+lsloy+sdvig1(i,1))+lsd(i)*(FF((2:2:szY)+lsloy,(1:szX)+lsloy)+FF((2:2:szY)+lsloy+sdvig1(i,2),(1:szX)+lsloy+sdvig1(i,1)))/2;        
    end
    [weight,R]=min(TFS,[],3);
    weight(Z(C,X,Y))=0;
    weight([1,2,end-1,end],:)=100000;
%    weight(:,[round(szY/2)]+[3:5])=100000;
    weight(:,[1,2,end-1,end])=100000;
%    weight([round(szX/4)],[round(szY/2)])=10000;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% ReControl
if ~isnan(weight(Z(Xagent,X,Y)))
    dang=sdvig(R(Z(Xagent,X,Y)),:);
    Ub=azi(angV(dang)-Xang)/pi;
    V=1-abs(Ub);
    Left =100*(V-Ub);
    Right=100*(V+Ub);
else
    fprintf('TrackAvoidance: stop=1');
    Left=0;
    Right=0;
end
%toc()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% SaveResults
trackavoi.weight{algN}=weight;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% PLOTTING
if show
    ShowWeight(Xagent,weight,R,TrAv_WorkTime);
end
%==========================================================================
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function ShowWeight(Xagent,weight,R,TrAv_WorkTime)
It=['TrAv_WorkTime=',sprintf('%f',toc(TrAv_WorkTime))];  
global trackavoi
sdvig=trackavoi.PAR.sdvig;
X=trackavoi.PAR.X;
Y=trackavoi.PAR.Y;
    if (get(0,'CurrentFigure')==100)
        hold on;
        %plot(X,Y,'K.')
        %p=plot(C(1),C(2),'Y*',Opponent(:,1),Opponent(:,2),'R*');
        %set(p,'linewidth',3);

        %for i=1:size(sdvig,1)
        %    Q=[-62,-508];
        %    plot([Q(1),Q(1)+30*sdvig(i,1)],[Q(2),Q(2)+30*sdvig(i,2)],'R');    
        %end

        Tmax=weight(Z(Xagent,X,Y));%10000;
        Tmax=max(Tmax,0);
        if (Tmax==inf)
            Tmax=10000000;
        end
        weight(weight>Tmax)=NaN;
        if ~isfield(trackavoi.MAP,'weight')
            trackavoi.MAP.weight=surf(X,Y,weight-Tmax);
        else
            set(trackavoi.MAP.weight,'zdata',weight-Tmax);
        end
        colormap(cool)

        Xtrack(1,:)=Xagent;
        for i=1:15
            Xtrack(i+1,:)=Xtrack(i,:)+sdvig(R(Z(Xtrack(i,:),X,Y)),:);
            %rnm=repmat(Xtrack,[size(Opponent,1),1])-Opponent;
            %sqrt(min(rnm(:,1).^2+rnm(:,2).^2));
        end     
        if ~isfield(trackavoi.MAP,'text_stat')
            trackavoi.MAP.text_stat=text(min(min(X)),max(max(Y))+100,It);
        else
            set(trackavoi.MAP.text_stat,'String',It);
        end
        if ~isfield(trackavoi.MAP,'track')
            trackavoi.MAP.track=plot(Xtrack(:,1),Xtrack(:,2),'Y');
            set(trackavoi.MAP.track,'linewidth',3');
        else
            set(trackavoi.MAP.track,'xdata',Xtrack(:,1),'ydata',Xtrack(:,2));
        end
    end
end
function z = Z(r,X,Y)
    [~,ryi]=min(abs(r(2)-Y(:,1)));
    [~,rxi]=min(abs(r(1)-X(ryi,:)));
    z=ryi+(rxi-1)*size(Y,1);
end

function TrackAvoi_INI()
 global trackavoi;
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %% ALG PAR
 %%OST PAR
    algStep=10;
    d=50;
    algr0=500;
 %%
 algK=(algr0^algStep)/(algStep-1);
 
%global MAP_X MAP_Y;
global PAR;
 dx=d;
 dy=dx*sqrt(3)/2;
 MX=[fliplr(-(dx:dx:((PAR.MAP_X)/2+dx))),0,(dx:dx:((PAR.MAP_X)/2+dx))];
 MY=[fliplr(-(dy:dy:((PAR.MAP_Y)/2+dy))),0,(dy:dy:((PAR.MAP_Y)/2+dy))];
 sdvig=[[0,2];...
    [-1.5,1];[-0.5,1];[0.5,1];[1.5,1];...
    [-1,0];[1,0];...
    [-1.5,-1];[-0.5,-1];[0.5,-1];[1.5,-1];...
    [0,-2]].*repmat([dx,dy],[12,1]);  
 normsdvig=sdvig./repmat([dx,dy],[12,1]);
 modsdvig=[[0;1;1;1;1;0;0;1;1;1;1;0],zeros(12,1)]/2;
 sdvig1=normsdvig+modsdvig;
 sdvig2=normsdvig-modsdvig;
 lsd=sqrt(sdvig(:,1).^2+sdvig(:,2).^2);
 lsloy=max(max(max(max(sdvig1,sdvig2))));
 [X,Y]=meshgrid(MX,MY);
 szX=size(X,2);
 szY=size(X,1);
 X(1:2:szY,:)=X(1:2:szY,:)+dx/2;
 %xi=(1:szX)+lsloy;
 %yi=(1:szY)+lsloy;
 trackavoi.PAR.szX=szX;
 trackavoi.PAR.szY=szY;
 trackavoi.PAR.X=X;
 trackavoi.PAR.Y=Y;
 trackavoi.PAR.lsloy=lsloy;
 trackavoi.PAR.sdvig=sdvig;
 trackavoi.PAR.sdvig1=sdvig1;
 trackavoi.PAR.sdvig2=sdvig2;
 trackavoi.PAR.lsd=lsd;
 trackavoi.PAR.algK=algK;
 trackavoi.PAR.algStep=algStep;
 trackavoi.PAR.d=d;
end
%%
function rz = coor(r,X,Y)
[~,ryi]=min(abs(r(2)-Y(:,1)));
[~,rxi]=min(abs(r(1)-X(ryi,:)));
rz=[rxi,ryi];
end


