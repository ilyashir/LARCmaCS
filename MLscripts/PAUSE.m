%PAUSE
%Создаёт и отменяет паузу 
%Во время паузы Rule не передаёт данные
global RP;
global Rules;

%% Пересборка управляющего потока
pcode main.m;
Rules=zeros(size(Rules));
%Смена паузы.
RP.Pause=1-RP.Pause;
if (RP.Pause)
    fprintf('Pause = ON\n');
else
    fprintf('Pause = OFF\n');
end

%% Посылка "Стоп" на всех роботов.
if (RP.Pause==1)
    Rules(1,:)=[2,1,0,0,0,0,0];
    Rules(2,:)=[1,0,0,0,0,0,0];
    Rules(3,:)=[1,0,0,0,0,0,0];
    Rules(4,:)=[1,0,0,0,0,0,0];
    pause(0.1);
    Rules(1,:)=[2,1,0,0,0,0,0];
    Rules(2,:)=[1,0,0,0,0,0,0];
    Rules(3,:)=[1,0,0,0,0,0,0];
    Rules(4,:)=[1,0,0,0,0,0,0];
else
    Rules(1,:)=[2,1,0,0,0,0,0];
end

%% 