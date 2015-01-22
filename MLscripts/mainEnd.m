%Функция завершающая основную "main" функцию.
%Обязательная для функционирования структуры RP .
function zMain_End = mainEnd()
global RP;
RP.zMain_End=true;
RP.WorkTime=toc(RP.T_timerH);
if isfield(RP,'WorkTimeMax');
    RP.WorkTimeMax=max(RP.WorkTimeMax,RP.WorkTime);
else
    RP.WorkTimeMax=RP.WorkTime;
end
zMain_End=RP.zMain_End;
end

