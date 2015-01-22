% MAP
% Отрисовка поля и игроков.
% Создание структуры MAP_PAR и перемещение отрисованного ранее.

%% Было ли создано окно?
global MAP_PAR;
global Blues;
global Yellows;
global Balls;
global PAR;

if (get(0,'CurrentFigure')==100)
%if (isfield(MAP_PAR,'MAP_H') && ishandle(MAP_PAR.MAP_H) && isequal('on',get(MAP_PAR.MAP_H,'Visible')))
%% BEGIN 

Viz_empty=false;
MapModel=[
   -1.0000         0
   -0.7071    0.7071
         0    1.0000
    1.0000    1.0000
    1.0000         0
    2.5000         0
    1.0000         0
    1.0000   -1.0000
         0   -1.0000
   -0.7071   -0.7071
   -1.0000         0];

for MAP_i=1:size(Blues,1)
    if (Blues(MAP_i,1)>0)
        [viz_x,viz_y]=rotV(MapModel(:,1),MapModel(:,2),Blues(MAP_i,4));
        viz_x=PAR.RobotSize/2*viz_x+Blues(MAP_i,2);
        viz_y=PAR.RobotSize/2*viz_y+Blues(MAP_i,3);
        if (isempty(MAP_PAR.viz_Blues{MAP_i}))
            figure(100)
            MAP_PAR.viz_Blues{MAP_i}(1)=plot(viz_x,viz_y,'B-');             
            set(MAP_PAR.viz_Blues{MAP_i}(1),'LineWidth',1.5);
            MAP_PAR.viz_Blues{MAP_i}(3)=text(Blues(MAP_i,2)+PAR.RobotSize/2,Blues(MAP_i,3)+PAR.RobotSize/2,{MAP_i});
        else                        
            set(MAP_PAR.viz_Blues{MAP_i}(1),'xdata',viz_x,'ydata',viz_y);
            set(MAP_PAR.viz_Blues{MAP_i}(3),'Position',[Blues(MAP_i,2)+PAR.RobotSize/2,Blues(MAP_i,3)+PAR.RobotSize/2]);   
        end
    end
end    
for MAP_i=1:size(Yellows,1)
    if (Yellows(MAP_i,1)>0)
        [viz_x,viz_y]=rotV(MapModel(:,1),MapModel(:,2),Yellows(MAP_i,4));
        viz_x=PAR.RobotSize/2*viz_x+Yellows(MAP_i,2);
        viz_y=PAR.RobotSize/2*viz_y+Yellows(MAP_i,3);
        if (isempty(MAP_PAR.viz_Yellows{MAP_i}))
            figure(100)
            MAP_PAR.viz_Yellows{MAP_i}(1)=plot(viz_x,viz_y,'Y-');   
            set(MAP_PAR.viz_Yellows{MAP_i}(1),'LineWidth',1.5);
            MAP_PAR.viz_Yellows{MAP_i}(3)=text(Yellows(MAP_i,2)+PAR.RobotSize/2,Yellows(MAP_i,3)+PAR.RobotSize/2,{MAP_i});
        else                        
            set(MAP_PAR.viz_Yellows{MAP_i}(1),'xdata',viz_x,'ydata',viz_y);
            set(MAP_PAR.viz_Yellows{MAP_i}(3),'Position',[Yellows(MAP_i,2)+PAR.RobotSize/2,Yellows(MAP_i,3)+PAR.RobotSize/2]);   
        end
    end
end
if (Balls(1)>0)
    viz_x=Balls(2);
    viz_y=Balls(3);
    if (isempty(MAP_PAR.viz_Balls))
        figure(100)
        MAP_PAR.viz_Balls=plot(viz_x,viz_y,'Ro');
        set(MAP_PAR.viz_Balls,'ZData',1);
    else
        set(MAP_PAR.viz_Balls,'xdata',viz_x,'ydata',viz_y);
    end
end
drawnow
%% END
end