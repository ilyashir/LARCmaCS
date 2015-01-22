%—имул€ци€ движени€ агентов по их управлению в структуре RP
global RP
if isempty(RP)
    return
end

global Blues;
global Yellows;
global Modul;

for N=1:size(RP.Blue,2)
    if Blues(N,1)
        Blues(N,:)=[Blues(N,1),MOD_GO(Blues(N,2:3),Blues(N,4),[RP.Blue(N).rul.left,RP.Blue(N).rul.right])];
        Modul.BluesKick(N,:)=[RP.Blue(N).rul.kick,Blues(N,4)+RP.Blue(N).KickAng];
    end
end

for N=1:size(RP.Yellow,2)
    if Yellows(N,1)
        Yellows(N,:)=[Yellows(N,1),MOD_GO(Yellows(N,2:3),Yellows(N,4),[RP.Yellow(N).rul.left,RP.Yellow(N).rul.right])];
        Modul.YellowsKick(N,:)=[RP.Yellow(N).rul.kick,Yellows(N,4)+RP.Yellow(N).KickAng];
    end
end
