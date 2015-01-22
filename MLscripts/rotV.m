%[reX,reY] = rotV(re,im,ang) Z=[re,im]
%reZ = rotV(Z,ang)
%Вращение вектора Z по часовой стрелке на угол ang
function [reX,reY] = rotV(re,im,ang)
if (nargin==2)
    ang=im;
    im=re(2);
    re=re(1);
end

%re=[re,im]*[cos(ang),sin(ang);-sin(ang),cos(ang)];
reX=re*cos(ang)-im*sin(ang);
reY=re*sin(ang)+im*cos(ang);

if (nargin==2)
    reX=[reX,reY];
end
end