%% MOD_Ball  
% ћоделирование движени€ м€чика.
% ”чЄт столкновений с роботами (v=100)
% ”чЄт столкновений с бортиками (v=0)
% ”чЄт пинани€ м€чика роботами (v=200)
%% globals
global Yellows;
global Blues;
global Balls;
global PAR;
global Modul

if ~isfield(Modul,'Ball')
    Modul.Ball.V=0;
    Modul.Ball.Ang=0;
end
%% Players kick
for i=1:size(Yellows,1)
    if (Yellows(i,1) && norm(Balls(2:3)-Yellows(i,2:3))<100)
        Modul.Ball.Ang=angV(Balls(2:3)-Yellows(i,2:3));
        Modul.Ball.V=max(50,Modul.Ball.V);        
    end
    if (Yellows(i,1) && Modul.YellowsKick(i,1) && norm(Balls(2:3)-Yellows(i,2:3))<PAR.KICK_DIST)
        %fprintf('BallKick\n');
        Modul.Ball.Ang=Modul.YellowsKick(i,2);
        Modul.Ball.V=max(200,Modul.Ball.V); 
    end
end
for i=1:size(Blues,1)
    if (Blues(i,1) && norm(Balls(2:3)-Blues(i,2:3))<100)
        Modul.Ball.Ang=angV(Balls(2:3)-Blues(i,2:3));
        Modul.Ball.V=max(50,Modul.Ball.V);
    end
    if (Blues(i,1) && Modul.BluesKick(i,1) && norm(Balls(2:3)-Blues(i,2:3))<PAR.KICK_DIST)
        %fprintf('BallKick\n');
        Modul.Ball.Ang=Modul.BluesKick(i,2);
        Modul.Ball.V=max(200,Modul.Ball.V); 
    end
end
%% Bortiki
if ((Balls(2)>PAR.MAP_X/2) || (Balls(2)<=-PAR.MAP_X/2))
    %Modul.Ball.Ang = asin(-sin(Modul.Ball.Ang));
    Balls(2)=PAR.MAP_X/2*sign(Balls(2));
    Modul.Ball.Ang=azi(pi-Modul.Ball.Ang);
    %Modul.Ball.V=Modul.Ball.V+10;
end
if ((Balls(3)>PAR.MAP_Y/2) || (Balls(3)<-PAR.MAP_Y/2))
    %Modul.Ball.Ang = acos(-cos(Modul.Ball.Ang));
    Balls(3)=PAR.MAP_Y/2*sign(Balls(3));
    Modul.Ball.Ang=azi(-Modul.Ball.Ang);
    %Modul.Ball.V=Modul.Ball.V+10;
end 
%% Mooved
if (Balls(1) && (Modul.Ball.V>0))
    Balls(:)=[Balls(1),...
        Balls(2)+Modul.Ball.V*Modul.dT*cos(Modul.Ball.Ang),...
        Balls(3)+Modul.Ball.V*Modul.dT*sin(Modul.Ball.Ang)];
    Modul.Ball.V=max(0,Modul.Ball.V-Modul.dT*4*Modul.Ball.V/100-Modul.dT*2*(Modul.Ball.V>0)); 
end
%% ---------------------------------
if 0 && ((abs(Balls(2))>3000)||(abs(Balls(3))>2000)||abs(Balls(2)>0))%||(BallsV==0))
    Balls=[1,(rand(1,1))*(-2000),(rand(1,1)*2-1)*3000];
     Modul.Ball.Ang=angV([-3500,0]-Balls(2:3));
     Modul.Ball.Ang=200;
end