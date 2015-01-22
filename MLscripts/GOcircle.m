% rul = GOcircle(agent,C,Cang)
% Функция захода на мячь.
% Робот движется приследуя окружность заданного радиуса, выводящую на мячь.
% В качестве аргумента и результата использует структуры из RP
function rul = GOcircle(agent,C,Cang)
%% Параметры локальные (Подлежат настройке)
Crad=500;
Cradmax=700;
dYmax=100;
dANGmax=pi/16;
%% Параметры
global PAR;
KICK_DIST=PAR.KICK_DIST;
[x,y]=rotV(agent.x-C(1),agent.y-C(2),-Cang);
Aang=agent.ang-Cang;

%% Основные направления
GCy=(x.^2+y.^2)./(2*y); %Смещение гравитационной составляющей
angF=azi(angV(-x,GCy-y)-sign(GCy)*( pi/2 )); %Направление фокусировки
angC=azi(angV(-x-Crad,-y)); %Направление притяжения точки разгона
%angC2=azi(angV(-x,-y)); %Направление притяжения цели
N=sqrt(x.^2+y.^2); %Расстояние
%% Подсчёт углов
%Основной фокус
ang=angF+azi((angC-angF)).*max( 0,min((N-Crad)/Cradmax,0.8));
%Выход на радиус
ang2=ang;
ang2(x>0)=azi(ang(x>0))./(1-max(-0.5,min((N(x>0)-Crad)/Crad,0)));
ang2(x<=0)=azi(ang(x<=0)).*(1-max(-0.5,min((N(x<=0)-Crad)/Crad,0)));
%% Kick
if (x<0 && x>-KICK_DIST && abs(y)<dYmax && abs(azi(Aang))<pi/dANGmax)
    kick=1;
else
    kick=0;
end
%% Линейное замедление
if (x<0 && abs(y)<dYmax)
    if (x>-KICK_DIST)
        ang2=0;
    end
    V_=max(0.2,min(1,(-x-200)/200));
else
    V_=1;
end
%% Отход назад
Rsize=400;
if ((norm([x,y])<Rsize) && (abs(azi(ang2-Aang))>pi/2))
    V_=min(1,max(-1,(norm([x,y])-Rsize)/100));
end
%% Вычисление скоростей
%Ub - угловая скорость, V - линейная скорость.
Ub=azi(ang2-Aang)/pi; 
Ub=sign(Ub)*min(1,max(2*min(1/5,abs(Ub)),abs(Ub)));
V=V_*(1-abs(Ub));
%% Переход к колесам
rul=Crul(100*(V-Ub),100*(V+Ub),kick,0,0);
%% debug
%fprintf(' x=%f ,y=%f, Aang=%f, Dang=%f, \n Dangpi=%f, Ub=%f, V_=%f, V=%f, kick=%f\n',x,y,Aang,azi(ang2-Aang),azi(ang2-Aang)/pi,Ub,V_,V,kick);
%fprintf(' Left=%f ,Right=%f, Kick=%f,\n',rul.left,rul.right,rul.kick);

end