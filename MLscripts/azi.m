%ang = azi(ang)
%Приведение значения угла к [-pi,pi].

function ang = azi(ang)
ang=rem(ang,2*pi);
ang(abs(ang)>pi)=ang(abs(ang)>pi)-sign(ang(abs(ang)>pi))*2*pi;
end
