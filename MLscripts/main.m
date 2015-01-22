%% MAIN START HEADER
global Blues Yellows Balls Rules RP
mainHeader();
if (RP.Pause) %Выход.
    return;
end
%% Параметры поля
global PAR
PAR.KICK_DIST=200;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% CONTRIL BLOCK
%Пинающий
if (RP.Yellow(11).I>0 && RP.Ball.I>0)
    G=[-3100,0];            %Ворота
    RP.Yellow(11).rul=GOcircle(RP.Yellow(11),RP.Ball.z,angV(G-RP.Ball.z));
    RP.Yellow(11).rul.kick=-RP.Yellow(11).rul.kick;
    Rule(2,RP.Yellow(11));
else
    Rule(2,0,0,0,0,0);
end

%% Голкипер.
if (RP.Yellow(9).I>0 && RP.Ball.I>0)
G=[-2800,0]; %Уровень ворот
RP.Yellow(9).rul=GoalKeeper(RP.Yellow(9),RP.Ball.z,G);
RP.Yellow(9).KickAng=-pi/2;    
    Rule(3,RP.Yellow(9));
    RP.Yellow(9).rul.kick=-RP.Yellow(9).rul.kick;    
else
    Rule(3,0,0,0,0,0);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% MAIN END
MAP(); %Отрисовка карты.
zMain_End = mainEnd();