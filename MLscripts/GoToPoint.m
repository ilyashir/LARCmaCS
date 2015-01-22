%[Left,Right]=GoToPoint(X,Xang,C,Cang,StopDistance);
%[Left,Right]=GoToPoint(X,Xang,C,Cang), StopDistance=200;
%[Left,Right]=GoToPoint(X,Xang,C), Сang=Xang, StopDistance=0;
%Движение робота Х с углом Xang к точке С.
%Остановка в окрестности StopDistance и разворот на угол Сang. 
function [Left,Right]=GoToPoint(X,Xang,C,Cang,StopDistance)
%% Параметры по умолчанию
if (nargin==4)
    StopDistance=200;
end    
if (nargin==3)   
    StopDistance=000;
    Cang=Xang;
end
%% Вычисление скоростей
%Ub - угловая скорость.
%V - линейная скорость.
if (norm(C-X)>StopDistance)
    Ub=azi(angV(C-X)-Xang)/pi; 
    V=1-abs(Ub);
else
    Ub=azi(Cang-Xang)/pi;
    V=0;
end
%% Переход к колесам
Left=100*(V-Ub);
Right=100*(V+Ub);
end