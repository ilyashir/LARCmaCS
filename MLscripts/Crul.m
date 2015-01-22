% rul= Crul(Left,Right,Kick,Sound,Sensor)
% Функция компонует управления для передачи её в поле робота.
% RP.Blue[N].rul=rul
function rul= Crul(Left,Right,Kick,Sound,Sensor)
rul=struct();
rul.sound=Sound;
rul.sensor=Sensor;
rul.left=Left;
rul.right=Right;
rul.kick=Kick;
end

