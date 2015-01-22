%[Left,Right,Kick]=Goeiler(X,Xang,B,Bang) 
function [Left,Right,kick]=GOeiler(X,Xang,B,Bang)
Cang=Bang;

l=130;
%R=l+100;
R=l*2;
R2=l*3;

wV=0;

Kw=1;

KSpeed=1;
K=1;
kick=0;


B_SaveDist=200;
C_SaveDist=100;
C=B-B_SaveDist*[cos(Cang),sin(Cang)];
C2=C-C_SaveDist*[cos(Cang),sin(Cang)];
%% AL 1 Невязка окружности.
%Cang=angV(C-X);
%Bang=angV(B-X);

%DB=azi(Bang-Xang);
%DC=azi(Cang-Xang);


Cc=0;
% if (sin(DC)==0)
%     SecC=norm(X-C);
%     rC=inf;
% else
%     rC=(norm(X-C)/2)/abs(sin(DC));
%     SecC=abs(DC)*2*rC;
% end
% 
% %plot(C(1)+r*sin(0:0.1:2*pi),r+C(2)+r*cos(0:0.1:2*pi),'b');
% 
% if (sin(DB)==0)
%     SecB=norm(X-B);
%     rB=inf;
% else
%     rB=(norm(X-B)/2)/abs(sin(DB));
%     SecB=abs(DB)*2*rB;
% end



%% AL 3 касательная
% Cc=C-sign(DC)*[cos(Cang+pi/2),sin(Cang+pi/2)]*R;
% 
% if (norm(X-Cc)>=R) 
%     DCc=azi(angV(Cc-X)-Xang+sign(DC)*asin(R/norm(X-Cc)));
% else
%     DCc=sign(DC)*asin(norm(X-Cc)/R)/2;
% end

%% Выбор алгоритма
% ALGORITM=0;
% Pz=dot(C-B,X-B)/norm(C-B);
% Pzt=sqrt(norm(X-B)^2-(Pz)^2);
% l_k=l/4;
% 
% 
%     KwA1=1;
%     KwA3=1;
%     KwA4=1;
% if (Pzt<l)&&(Pz>0)&&(Pz<drr+R)%&&((abs(Cang-Xang)<pi/8)||(Pz<drr))%)||(Pzt<l_k))%(((SecB<drr+200)&&(abs(DB)<pi/4)))%(abs(Cang-Xang)<pi/8)||
%     %Ты достиг уровня точки Pzt=0;
%     ALGORITM=4;
%     w=2*azi(Cang-Xang);
%     %KSpeed=((Pz)/(drr+R));
%     Kw=KwA4%*(1/KSpeed);
%     if ((abs(azi(Cang-Xang)))<10*pi/180)&&(Pz<400)
%     
%         ALGORITM=5;   
%         KSpeed=1;
%         kick=1;
%     else
%         kick=0;
%     end 
% else
% eee=(l/(rC+l))*pi*(1-abs(2*azi(DCA+DC)/pi))-sign(DC)*KwA3*azi(DCA+DC);
%     if ((norm(X-Cc)<R2)&&(eee>0))||(norm(X-Cc)<R)
%         w=azi(DCA+DC); 
%         wV=-sign(DC)*l/(rC+l);
%         %V=[R+l*sign(DC),R-l*sign(DC)];
% 
%        % V=[rC+l*sign(DC),rC-l*sign(DC)];
% %        wv=(l/R+l)*pi;
%         Kw=KwA3;
%         ALGORITM=3;  
%     else
%         V=[1,1];
%         Kw=KwA1;  
%         ALGORITM=1;
%         w=DCc;
%     end
% end




%if al0>0 al0=al0-pi*2; end

%Integ2=sign(al0)*sqrt(pi/2/al0)*mfun('FresnelS',(sqrt(al0*2/pi)))

%QQ3=@(w0_)(-Dist+100*(1-cos(al0))-al0*200/w0_*Integ);
%QQ3(w0)

% global TTR;
% TTR=TTR+1;
% global Kwal;
% global w0w;
% if TTR==1
%     w0w=w0;
%     Kwal=-S*w0^2/(2*(Xang));
% end
tBCX=dot(B-C,B-X)/norm(B-C)^2;
DistX=dot(B-C,B-X)/norm(B-C);
DistY=sqrt(norm(X-B)^2-(DistX)^2)*sign(azi(angV(B-X)-angV(B-C)));


    global S_ALGORITM;
    global S_t;
DDDX=0;
DDDY=0;

        ALGORITM=1;
        w=azi(angV(C2-X)-Xang)/pi;
%        w=sqrt(abs(w))*sign(w);
if (DistX>0)
    al0=-Cang+Xang;
    
    DistY2=DistY;
    DistX2=DistX;    
    
    DAl=l;    
    if (sign(al0*DistY2)<=0)
        al0=al0+2*pi*sign(DistY2);
    end
        
    IntegS=quad(@(t)sin(((1-t)).^2*al0),0,1);
    IntegC=quad(@(t)cos(((1-t)).^2*al0),0,1);

    w_=-2*al0*IntegS/(DistY2/DAl+sign(DistY)*(1-cos(al0)));                           
    DDDX=DAl*(-sign(DistY2)*( sin(al0) )-2*al0/w_*IntegC);
    DDDY=DAl*(-sign(DistY2)*(1-cos(al0))-2*al0/w_*IntegS);
    
    if ( (DDDX<DistX2) || ( (norm(size(S_t))>0) && (S_t~=0) && (S_ALGORITM{S_t}==6) ) )
        ALGORITM=6;
        w=w_;
        %ALGORITM=1;
        %DCc=angV(B-[500,00]-X);
        %w=azi(DCc-Xang)/pi;
    end

    if (DistX>0)&&(abs(DistY)<=100)&&((abs(al0)>pi/2)||(ALGORITM~=6))
        ALGORITM=7;
        if (DistX<B_SaveDist)
            KSpeed=((DistX+100)/(B_SaveDist+100));
        end
        w=azi(Cang-Xang)/pi;
        %w=sqrt(abs(w))*size(w);
    end

    
%D=100*sin(al0)-2*al0*100/w*IntegC;
  %  Kwal=-w^2/(2*(al0));
    %w=w%w-TTR*Kwal;
    %DDD=100*(1-w)*S
%    if w<0 w=0; end
   %w=%azi(Cang-Xang); 
   %V=[1,1];
%    Kw=1;
end

kick=0;
if (DistX<B_SaveDist)&&(DistX>0)&&(abs(DistY)<100)
    if (abs(azi(Cang-Xang))<pi/16)
        ALGORITM=9;
        kick=1;
        w=0;
        KSpeed=1;
    else
        ALGORITM=8;
        KSpeed=((DistX+100)/(B_SaveDist+100));
        w=azi(Cang-Xang)/pi;%/KSpeed;
        %w=sqrt(abs(w))*sign(w);
        
        %KSpeed=azi(Bang-Xang)/pi;
        %w=sign(azi(Bang-Xang)/pi);
        %w=azi(Bang-Xang)/pi;
    end
end

ALGORITM
%% ПРОПОРЦИАНАЛЬНЫЙ РЕГУЛЯТОР


if(abs(w)>1)
    wP=sign(w);
else
    wP=w;
end

if (KSpeed>1)
    KSpeed=1;
end
RS=100*KSpeed;

Left =RS*(1-abs(wP)-wP);
Right=RS*(1-abs(wP)+wP);

%% SAVE
% if (SAVE_it())
%    % global S_t;
%     %global S_ALGORITM;
%     global S_Dang;
%     global S_w;
%     
%     global S_REALw;
%     global S_SR;
%     global S_SL;
%     
%     global S_DDDX;
%     S_DDDX{S_t}=DDDX;
%     global S_DDDY;
%     S_DDDY{S_t}=DDDY;
%     
%     S_Cc{S_t}=Cc;
%     S_R{S_t}=R;
%     S_R2{S_t}=R2;
%     S_ALGORITM{S_t}=ALGORITM;
%     S_Dang{S_t}=azi(Cang-Xang);
%     S_w{S_t}=wP;
%     S_REALw{S_t}=((Right-Left)/(2*RS));%норм. угловая скорость
%     S_SR{S_t}=Right;
%     S_SL{S_t}=Left;
%     global S_X; S_X{S_t}=X;
%     global S_Xang;      S_Xang{S_t}=Xang;
% end
%% end
kick
re=[Left,Right,kick,0];
end