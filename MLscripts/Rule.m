%Rule(Nom,Left,Right,Kick,Sound,Sensor)
%Rule(Nom,Agent) - recommended
%Размещение нового управления в массиве Rules
%Добавление 1ого елемента   [1,*,*,...]

function Rule(Nom,Left,Right,Kick,Sound,Sensor)
global RP;
if (nargin==2)
    Agent=Left;
    Left=Agent.rul.left;
    Right=Agent.rul.right;
    Kick=Agent.rul.kick;    
    Sound=Agent.rul.sound;
    Sensor=Agent.rul.sensor;
else
    warning('<RP>: old definition Rule(Nom,Left,Right,Kick,Sound,Sensor), not recommended');
end

global Rules;
RulesI=1;
Rules_length=size(Rules,1);

%% Поиск свободной строки
while ((RulesI<=Rules_length)&&((Rules(RulesI,1)>0)||((Rules(RulesI,1)==1)&&(Rules(RulesI,2)~=Nom))))
    RulesI=RulesI+1;
end

%% Проверки управления.
% <100
if (abs(Right)>100) 
    Right=sign(Right)*100; 
end
if (abs(Left)>100) 
    Left=sign(Left)*100;  
end
% Округление
Right=fix(Right);
Left=fix(Left);
% ПОМЕХИ
% Right=Right-15*sign(Right);
% Right(abs(Right)<15)=0;
% Left=Left-10*sign(Left);
% Left(abs(Left)<10)=0;
%

%% Передача управления
if (RP.Pause~=1)
    Rules(RulesI,1)=1;
    Rules(RulesI,2)=Nom;
    Rules(RulesI,3)=Left;
    Rules(RulesI,4)=Right;
    Rules(RulesI,5)=Kick;
    Rules(RulesI,6)=Sound;
    Rules(RulesI,7)=Sensor;
end
 