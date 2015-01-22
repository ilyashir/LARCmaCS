% Реактивное обхождение препятствий
function [Left,Right] = ReactAvoidance(Left,Right,X,Xang,Opponent)
    if ~isSectorClear(X,X+300*[cos(Xang),sin(Xang)],Opponent);
        V=(Left+Right)/2;
        Left=Left-V+50*((Left>Right)-0.5);
        Right=Right-V-50*((Left>Right)-0.5);
    end
end

