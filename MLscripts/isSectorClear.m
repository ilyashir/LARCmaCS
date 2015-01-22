%re=isSectorClear(X,B,Bang,Opponents,L) 
%re=isSectorClear(X,B,Bang,Opponents) L=0;
%re=isSectorClear(X,B,Opponents) Bang=angV(B-X); L=200;
% Функция проверяет, попадают ли агенты из массива Opponents в сектор 
% захода на мячь перед агентом X. L - размер робота, который можно указать
% в качестве дополнительной толщины сектора.
function re=isSectorClear(X,B,Bang,Opponents,L)
if (nargin==4)
    L=0;
end
if (nargin==3)
    L=200;
    ML=-10;
    Opponents=Bang;
    Bang=angV(B-X);
else
ML=L;
end
X=X-B;
T=[cos(Bang),sin(Bang);-sin(Bang),cos(Bang)];
X=(T*[X(1);X(2)])';

MysteryValue=150;

if( (X(1)>0) || ( abs(angV(-X+[MysteryValue,0]))>pi/6))
    re=0;
    return
end

for i=1:size(Opponents,1)
    C=Opponents(i,:);
    C=C-B;
    C=(T*[C(1);C(2)])';
    if X(2)<0
        C(2)=-C(2);
    end
    if ((C(2)>-L) && (C(1)<0) && (C(1)>X(1)-ML) && ((C(2)-L)*-X(1)<(-C(1)+L)*abs(X(2))))
        re=0;
        return
    end
end
re=1;
end