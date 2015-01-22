%[Left,Right,Kick]=GoSlide(X,Xang,B,Bang) 
%≈щЄ один алгоритм забивани€ м€ча
function [Left,Right,Kick]=GOSlide(X,Xang,B,Bang)
global PAR;
KICK_DIST=PAR.KICK_DIST;
Kick=0;
Dist=350;
NDist=200;

DT=-(cos(Bang)*(X(1)-B(1))+sin(Bang)*(X(2)-B(2)));
DN=(sin(Bang)*(X(1)-B(1))-cos(Bang)*(X(2)-B(2)));

if (norm(B-X)<Dist && DT>0)
    C=B-norm(B-X)*[cos(Bang),sin(Bang)];    
else
    C=B-Dist*[cos(Bang),sin(Bang)];
end
%%  ћетодом скольз€щей траектории.
%объезд м€ча
if abs(azi(angV(B-X)-Bang))>pi/4
    C2ang=angV(X-B)+pi/4*sign(azi(angV(X-B)-Bang));
    C=B+Dist*[cos(C2ang),sin(C2ang)];
end
Cang1=angV(C-X); %ƒвижение к точке запаса
Cang2=Bang; %ƒвидение к м€чу

if (abs(DN)>NDist || abs(azi(angV(B-X)-Bang))>pi/4)
    Cang=Cang1;
else
    Cang=Cang1+(1-(abs(DN)/NDist)^2)*(azi(Cang2-Cang1));
end
%Cang
%Xang
Ub=azi(Cang-Xang)/pi;
%% ѕр€мое замедление
V=(1-abs(Ub));
 DistSleep=300;%+abs(X(1)-B(1))/20;
 if (DT<DistSleep && abs(azi(angV(B-X)-Bang))<=pi/3 && DT>-100)
     V=V*(DT)/(DistSleep);
 end
%% kick
% if (DT>=0 && DT<KICK_DIST && DN<100 && ((abs(azi(Xang-Bang))<pi/5)||abs(azi(Xang-Cang)<pi/4)))
%     CangB=angV(B-X);
%     Ub=azi(CangB-Xang)/pi;
%     Kick=1;
%     V=0.5;
% %    Ub=Ub*2;
% end
if (DT>=0 && DT<KICK_DIST && DN<70 && (abs(azi(angV(B-X)-Bang))<pi/4) )
%if (DT>=0 && DT<KICK_DIST && DN<70 && (abs(azi(angV(B-X)-Bang))<pi/4) && (abs(azi(Xang-Cang))<pi/4) )
    CangB=angV(B-X);    
    Ub=azi(CangB-Xang)/pi;
    if (abs(azi(Xang-Cang))<pi/4)
        Kick=1;
        V=(1-abs(Ub));

%        V=1;%0.7;
    end
%    Ub=Ub*2;
end
%% RE
Left =100*(V-Ub);
Right=100*(V+Ub);
%    Left(Left>0)=Left(Left>0)*0.8+20;
%    Right(Right>0)=Right(Right>0)*0.8+20;
re=[Left,Right,Kick];
%% ¬изуализаци€
% global MAP_C2;
% if 0 %(size(MODUL_ON)~=[0,0])    
%     plot(C(1),C(2),'Y.');
%         
%     plot(B(1)-Dist*cos(Bang),B(2)-Dist*sin(Bang),'Yo');
%       %plot([X(1),X(1)+100*cos(Cang1)],[X(2),X(2)+100*sin(Cang1)],'K')     
%       %plot([X(1),X(1)+100*cos(Cang)],[X(2),X(2)+100*sin(Cang)],'R')     
%     
%     plot([B(1),B(1)-500*cos(Bang)],[B(2),B(2)-500*sin(Bang)],'Y-');    
%     %plot([X(1),X(1)+DT*cos(Bang+pi/2)],[X(2),X(2)+DT*sin(Bang+pi/2)],'W')
%     %plot([X(1),X(1)+DN*cos(Bang)],[X(2),X(2)+DN*sin(Bang)],'W')
% 
% 
%     if isempty(MAP_C2)
%         %MAP_C2=plot(C2(1),C2(2),'Y.');
%     else
%         global MAP_H;
%         H = get(0, 'CurrentFigure');
%         if ((~isempty(MAP_H)) && (~isempty(H)) && (H==MAP_H))
%         %    set(MAP_C2,'xdata',C2(1),'ydata',C2(2));        
%         end
%     end
end
