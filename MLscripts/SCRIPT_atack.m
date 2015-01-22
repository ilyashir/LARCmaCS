%Описание скрипта 
function SCRIPT_atack(N,X,B,G,ST,Opponent,Opponent2)
global Balls;
global PAR;
if  ((Balls(1)==0)||(abs(B(1))>PAR.MAP_X/2-300)||(abs(B(2))>PAR.MAP_Y/2-300)) %Если мячь не в играбетельной зоне
    if (norm(ST-X(1:2))>300) %Если расстояния до точки ожидания больше 300
        [Left,Right]=TrackAvoidance(X(1:2),X(3),ST,angV(B-ST),12,Opponent,0,0); %Обходим препятствия и едем к ST
    else
        Left=0; Right=0;        %Остановились.
    end
    Kick=0;
else
    if (norm(B-X(1:2))<700 && isSectorClear(X(1:2),B,angV(G-B),Opponent,100)) %Если мы близки к мячу и сектор для захода свободен
        [Left,Right,Kick]=GOSlide(X(1:2),X(3),B,angV(G-B));       %Заход на мячь
    else
        Kick=0;
        [Left,Right]=TrackAvoidance(X(1:2),X(3),B,angV(G-B),2,Opponent);  %Обходим препятствия и едем к B
    end
end
[Left,Right]=ReactAvoidance(Left,Right,X(1:2),X(3),Opponent2); %Реактивные обход препятствий (не врезаться в своих).

Rule(N,Left,Right,-Kick,0,0); 
end