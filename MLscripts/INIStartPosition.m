% Инициализация начальных позиций
% [1,(rand(1,3)-0.5).*[PAR.MAP_Y,PAR.MAP_Y,2*pi]]
global Blues Yellows Balls
Balls(:)=[1,1900,00];

Blues(1,:)=[1,(rand(1,3)-0.5).*[PAR.MAP_Y,PAR.MAP_Y,2*pi]];

Blues(10,:)=[1,500,-1000,-pi];
Blues(9,:)=[1,(rand(1,3)-0.5).*[PAR.MAP_Y,PAR.MAP_Y,2*pi]];


Yellows(4,:)=[1,(rand(1,3)-0.5).*[PAR.MAP_Y,PAR.MAP_Y,2*pi]];
Yellows(5,:)=[1,(rand(1,3)-0.5).*[PAR.MAP_Y,PAR.MAP_Y,2*pi]];
Yellows(10,:)=[1,(rand(1,3)-0.5).*[PAR.MAP_Y,PAR.MAP_Y,2*pi]];
