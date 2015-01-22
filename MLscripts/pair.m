global Blues Yellows Balls Rules RP

if (RP.Pause==0)
    RP.inpair=false;
end
if (RP.inpair==1)
    Rules=zeros(size(Rules));    
    if (RP.pair.N==13)
        fprintf('<RP>: PAIR in END \n');        
    else
        fprintf('<RP>: PAIR in WORK: %f\n',RP.pair.N);
        if (RP.pair.stop)
            Rules(1,:)=[1,0,0,0,0,1,0];
            if (toc(RP.pair.Htime)>2)
                RP.pair.Htime=tic();
                RP.pair.stop=false;
                RP.pair.N=RP.pair.N+1;
            end
        else
            flg=false;
            Rules(1,:)=[1,RP.pair.N,100,-100,0,1,0];
            for i=1:12
                if (abs(RP.Yellow(i).u)>1)
                    RP.Yellow(i).Nrul=RP.pair.N;
                    RP.pair.Yellows(i)=RP.pair.N;
                    flg=true;
                    RP.pair.count=RP.pair.count+1;
                end
                if (abs(RP.Blue(i).u)>1 && flg==false)
                    RP.Blue(i).Nrul=RP.pair.N;
                    RP.pair.Blues(i)=RP.pair.N;
                    flg=true;
                    RP.pair.count=RP.pair.count+1;
                end
            end

            if (toc(RP.pair.Htime)>5 || flg==true)
                RP.pair.Htime=tic();
                RP.pair.stop=true;
            end

        end
    end
end
