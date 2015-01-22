%angV = angV(Z)
%angV = angV(re,im)
%Угол направления вектора. 
%Аналог angle(re+i*im) 

function angV = angV(re,im)
if (nargin==1)
    im=re(2);
    re=re(1);
end

angV=angle(re+1i.*im);
end
