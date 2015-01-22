%re=MOD_GO(X,Xang,Rul)
%re=[Xn(1),Xn(2),Xangn] 
%Моделирование движения робота

function re=MOD_GO(X,Xang,Rul)
%% Инициализация параметров
global Modul;
dT=Modul.dT;
l=Modul.l_wheel;
viz=Modul.viz;

global treckcolor; %Цвет трека
if (size(treckcolor)==[0,0])
    treckcolor=[0,1,0.4];
end

%%
Left=Rul(1);
Right=Rul(2);

if (Left==Right)
    Xn=X+dT*Left*[cos(Xang),sin(Xang)];
    re=[Xn(1),Xn(2),Xang];
    if (viz) 
        plot(X(1)+(0:0.01:1)*(Xn(1)-X(1)),X(2)+(0:0.01:1)*(Xn(2)-X(2)),'color',treckcolor);
    end
    return
end
LC=X+l*[cos(Xang+pi/2),sin(Xang+pi/2)];
RC=X+l*[cos(Xang-pi/2),sin(Xang-pi/2)];

D=l*2;
Xr=((Left+Right)/2)*((l*2)/(Left-Right));
Lr=Left*D/(Left-Right);
Rr=Right*D/(Left-Right);

CC=RC+Right*D/(Left-Right)*[cos(Xang-pi/2),sin(Xang-pi/2)];

if (Left==0)
    La=0;
    LnC=CC;
else
    La=angV(LC-CC)-dT*Left/Lr;
    LnC=CC+abs(Lr)*[cos(La),sin(La)];
end

if (Right==0)
    Ra=0;
    RnC=CC;
else
    Ra=angV(RC-CC)-dT*Right/Rr;
    RnC=CC+abs(Rr)*[cos(Ra),sin(Ra)];
end

%  plot(CC(1),CC(2),'K*');
%  plot(LC(1),LC(2),'G*');
%  plot(RC(1),RC(2),'G*');
%  plot(CC(1)+Rr*sin(0:0.1:2*pi),CC(2)+Rr*cos(0:0.1:2*pi));
%  plot(CC(1)+Lr*sin(0:0.1:2*pi),CC(2)+Lr*cos(0:0.1:2*pi));
%  plot(CC(1)+Xr*sin(0:0.1:2*pi),CC(2)+Xr*cos(0:0.1:2*pi),'G');
% plot(LnC(1),LnC(2),'Y*');
% plot(RnC(1),RnC(2),'Y*');


if (viz) 
    a1=angV(LC-RC);
    a2=angV(LnC-RnC);

    if (Right-Left>0)&&(a2<a1)
        a2=a2+2*pi;
    end
    if (Right-Left<0)&&(a2>a1)
        a2=a2-2*pi;
    end
    ad=sign(Right-Left)*abs(a2-a1)/10;
    plot(CC(1)+Xr*cos(a1:ad:a2),CC(2)+Xr*sin(a1:ad:a2),'color',treckcolor);
end


Xn=(LnC+RnC)/2;
Xangn=angV(RnC-LnC)+pi/2;

if (Xangn>pi) 
    Xangn=Xangn-2*pi; 
end; 
re=[Xn(1),Xn(2),Xangn];
end

