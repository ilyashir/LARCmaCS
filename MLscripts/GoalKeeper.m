%[Left,Right,Kick]=GoalKeeper(X,Xang,B,G)
%rul=GoalKeeper(Agent,B,G)
%Функция движения воротаря в точке X с углом Xang
%B - положение мяча. G - положение центра ворот.
%Алгоритм
%А1)Приехать в ворота.
%А2)Встать на заданную точку в воротах для отражения мяча. 
%А3)Выбить пойманый мяч.
%---v0.7--- 
function [Left,Right,Kick]=GoalKeeper(X,Xang,B,G)
if (nargin==3)
    Agent=X;
    X=Agent.z;
    G=B;
    B=Xang;
    Xang=Agent.ang;
end
%Cx=G(1)%-400*sign(G(1));
%пиналка на левой стороне!!!
%% Параметры
lgate=1000; %Ширина ворот.
DefDist=300; %Глубина ворот.
XaccelL=150;
YaccelL=50;
%% Определение точки защиты С
%B(2)/3000*lgate
%---Биссектриса---
C=G;
C(2)=C(2)-lgate+2*lgate*norm(G-[0,lgate]-B,2)/( norm(G-[0,lgate]-B,2)+norm(G+[0,lgate]-B,2) );
%---Не помню что---
%C=[G(1),-((1-abs(B(1)-G(1))/PAR.MAP_X))^3*B(2)];
if abs(C(2))>lgate
    C(2)=sign(C(2))*lgate;
end

%% А1) Движение к воротам
% Методом скользящей траектории.

Cang=angV(C-X);
if (abs(azi(Cang-Xang))<=abs(azi(Cang-Xang+pi)))
    RT=1; %Движение прямо
else
    RT=-1;%Движение назад
end    
%% Параметры
%w-угол доворота до желаемого направления движения
if (abs(C(1)-X(1))>100 || abs(C(2)-X(2))>50)
    Ub=azi(Cang-Xang+pi*(RT==-1))/pi; 
else
    Cang=-sign(G(1))*pi/2; %Установка желаемого направления становления
    Ub=azi(Cang-Xang)/pi;
end

if (abs(G(1)-X(1))>DefDist && abs(azi(Cang-Xang))/pi>0.5)
    Ub=azi(Cang-Xang)/pi;   
end

V_=max( (abs(C(2)-X(2))-50)/YaccelL , (abs(C(1)-X(1))-50)/XaccelL );%Плавное замедление
V_=max(0,min(1,V_));
V=V_*RT*(1-abs(Ub));


%global PAR
%if (norm(B-X)<300 && abs(azi(angV(B-X)-Xang-sign(G(1))*pi/2))<pi/4)
%    Kick=1
%end
MOD=-1; %1
if (norm(B-X)<300 && abs(azi(angV(B-X)-Xang-MOD*pi/2))<pi/4)
    Kick=1;
else
    Kick=0;
end
%% RE
Left =100*(V-Ub);
Right=100*(V+Ub);
if (nargin==3)
    rul=Crul(Left,Right,Kick,0,0);
    Left=rul;
    Right=0;
    Kick=0;
end
%% Визуализация
% global viz_gk_C;
% global MAP_H;
% if (1)  
%     H = get(0, 'CurrentFigure');
%     if ((~isempty(MAP_H)) && (~isempty(H)) && (H==MAP_H))
%         if (isempty(viz_gk_C))
%             plot([G(1),G(1)],[-lgate,lgate],'B');
%             plot([C(1)-DefDist,C(1)-DefDist],[-lgate,lgate],'R');
%             plot([C(1)+DefDist,C(1)+DefDist],[-lgate,lgate],'R');
%             viz_gk_C=plot([B(1),C(1)],[B(2),C(2)],'R-');
%         else
%             set(viz_gk_C,'xdata',[B(1),C(1)],'ydata',[B(2),C(2)]); 
%         end
%     end
% end
end