%Функция начинающая основную "main" функцию.
%Обязательная для функционирования структуры RP .
%
% Описание структура RP
%        zMain_End: true          %флаг завершения выполнения main
%          OnModul: 0             %Использование моледирования
%              PAR: [1x1 struct]  %Набор основных параметров поля
%               dT: 0.5           %Шаг дискретизации
%         T_timerH: 24084895062   %Хедер таймера.
%                T: 12.5          %Врея от первого запуска
%     YellowsSpeed: [12x1 double] %Скорости жёлтых
%       BluesSpeed: [12x1 double] %Скорости Синих
%       BallsSpeed: 0             %Скорость мяча
%         Ballsang: 0             %Угол направления мяча
%            Blues: [12x4 double] %Входящий массив синих
%          Yellows: [12x4 double] %Входящий массив жёлтых
%            Balls: [0 0 0]       %Входящий массив мячей
%            Rules: [4x7 double]  %Исходящий массив управления
%             Ball: [1x1 struct]  %Структура мяча
%             Blue: [1x12 struct] %Структура синих
%           Yellow: [1x12 struct] %Структура жёлтых
%            Pause: 0             %Пауза
%
% Описание структуры агентов RP.Blue(N) или RP.Yellow(N)
% Если робот не был найден, то все поля empty
%           I: 1                  %Индекс камеры, которая нашла робота
%           x: 1.0360e+03         %X координата робота
%           y: -905.6405          %Y координата робота 
%           z: [1.0360e+03 -905.6405]           %[X,Y] координаты
%         ang: 0.1835             %Угол направления робота 
%           v: 97.3253            %Скорость движения робота
%        Nrul: 0                  %Номер исходящего управления
%         rul: [1x1 struct]       %Исходящее управление
%     KickAng: 0                  %Направление удара робота
%
% Описание управления RP.Blue(10).rul
%      sound: 0                   %Издать звук [0..1]
%     sensor: 0                   %Задействовать сенсор [0..4]
%       left: 100                 %Мощьность левого колеса [-100..100]
%      right: 99.2465             %Мощьность правого колеса [-100..100]
%       kick: -1                  %Удар пиналкой [-1,0,1]

function RPre=mainHeader()
%% RP
global RP;
if isempty(RP)
    fprintf('<RP>: ---RP initial---\n');
    RP.inpair=false;    
end
if isfield(RP,'zMain_End') && (RP.zMain_End==false)
    warning('<RP>: main if FAIL!');
end
RP.zMain_End=false;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Data %%
emptyrul=Crul(0,0,0,0,0);
%от SSL
% --- Balls ----
global Balls;
if isempty(Balls)   
    Balls=zeros(1,3);  
end
% --- Blues ----
global Blues;
if isempty(Blues)
    Blues=zeros(12,4);
end
% --- Blues ----
global Yellows;
if isempty(Yellows)
   Yellows=zeros(12,4);
end
% --- Rules для BT ---
global Rules;
if isempty(Rules)
    Rules=zeros(4,7);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Разбор входящих данных %%
if ~isfield(RP,'pair')
    RP.pair=struct();
    if ~isfield(RP.pair,'Yellows')
        RP.pair.Yellows=-ones(size(Yellows,1),1);
    end
    if ~isfield(RP.pair,'Blues')
        RP.pair.Blues=-ones(size(Blues,1),1);
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% SYS %%
global PAR;
if isempty(PAR)
    PAR=struct();
end
if ~isfield(PAR,'MAP_X')
    PAR.MAP_X=6000; %6
end
if ~isfield(PAR,'MAP_Y')
    PAR.MAP_Y=4000; %4
end
if ~isfield(PAR,'KICK_DIST')
    PAR.KICK_DIST=120;
end
if ~isfield(PAR,'LGate')
    PAR.LGate.X=-PAR.MAP_X/2;
    PAR.LGate.Y=0;    
    PAR.LGate.ang=0;    
    PAR.LGate.width=1000;
end
if ~isfield(PAR,'RGate')
    PAR.RGate.X=PAR.MAP_X/2;
    PAR.RGate.Y=0;
    PAR.RGate.ang=-pi;    
    PAR.RGate.width=1000;
end
if ~isfield(PAR,'RobotSize')
    PAR.RobotSize=100;
end
if ~isfield(PAR,'RobotArm')
    PAR.RobotArm=100;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%--- time ---
global Modul;
if isempty(Modul)
    RP.OnModul=false;
else
    RP.OnModul=true;
end
RP.PAR=PAR;
% RP.T
if isfield(RP,'T')
    if isempty(Modul)
        RP.dT=toc(RP.T_timerH);
    else
        RP.dT=Modul.dT;
    end
    RP.T_timerH=tic();
    RP.T=RP.T+RP.dT;
else
    RP.dT=0;
    RP.T_timerH=tic();
    RP.T=0;
end
%--- speed ---
% RP.YellowsSpeed
if isfield(RP,'Yellows') && norm(size(Yellows)-size(RP.Yellows))==0    
    RP.YellowsSpeed=sqrt((Yellows(:,2)-RP.Yellows(:,2)).^2+(Yellows(:,3)-RP.Yellows(:,3)).^2)/RP.dT;
    RP.YellowsAngSpeed=(Yellows(:,4)-RP.Yellows(:,4))/RP.dT;
else
    RP.YellowsAngSpeed=zeros(size(Yellows,1),1);
    RP.YellowsSpeed=zeros(size(Yellows,1),1);
end
% RP.BluesSpeed
if isfield(RP,'Blues') && norm(size(Blues)-size(RP.Blues))==0
    RP.BluesSpeed=sqrt((Blues(:,2)-RP.Blues(:,2)).^2+(Blues(:,3)-RP.Blues(:,3)).^2)/RP.dT;
    RP.BluesAngSpeed=(Blues(:,4)-RP.Blues(:,4))/RP.dT;
else
    RP.BluesAngSpeed=zeros(size(Blues,1),1);
    RP.BluesSpeed=zeros(size(Blues,1),1);
end
% RP.BallsSpeed
if isfield(RP,'Balls') && norm(size(Balls)-size(RP.Balls))==0
    RP.BallsSpeed=sqrt((Balls(2)-RP.Balls(2)).^2+(Balls(3)-RP.Balls(3)).^2)/RP.dT;
    RP.Ballsang=angV(RP.Balls(2:3)-Balls(2:3));
else
    RP.BallsSpeed=zeros(size(Balls,1),1);
    RP.Ballsang=0;
end
%--- Save ---
RP.Blues=Blues;
RP.Yellows=Yellows;
RP.Balls=Balls;
RP.Rules=Rules;
%--- RP interface ---
RP.Ball.I=Balls(1);
RP.Ball.x=Balls(2);
RP.Ball.y=Balls(3);
RP.Ball.z=Balls(2:3);
RP.Ball.ang=RP.Ballsang;
RP.Ball.v=RP.BallsSpeed;


for i=1:size(Blues,1)
        RP.Blue(i).I=Blues(i,1);
        RP.Blue(i).x=Blues(i,2);
        RP.Blue(i).y=Blues(i,3);
        RP.Blue(i).z=Blues(i,2:3);
        RP.Blue(i).ang=Blues(i,4);
        RP.Blue(i).v=RP.BluesSpeed(i);
        RP.Blue(i).u=RP.BluesAngSpeed(i);
        RP.Blue(i).Nrul=RP.pair.Yellows(i);
        RP.Blue(i).rul=emptyrul;
        RP.Blue(i).KickAng=0;
end
for i=1:size(Yellows,1)
        RP.Yellow(i).I=Yellows(i,1);
        RP.Yellow(i).x=Yellows(i,2);
        RP.Yellow(i).y=Yellows(i,3);
        RP.Yellow(i).z=Yellows(i,2:3);
        RP.Yellow(i).ang=Yellows(i,4);
        RP.Yellow(i).v=RP.YellowsSpeed(i);
        RP.Yellow(i).u=RP.YellowsAngSpeed(i);
        RP.Yellow(i).Nrul=RP.pair.Yellows(i);
        RP.Yellow(i).rul=emptyrul;
        RP.Yellow(i).KickAng=0;
end
% --- RP.Pause ---
if ~isfield(RP,'Pause')    
    RP.Pause=0;
end
pair();
%if (RP.Pause)
%    return;
%end
%% re
RPre=RP;
end