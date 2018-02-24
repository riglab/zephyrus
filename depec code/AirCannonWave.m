function [totalTime,totalDelay1,totalDelay2,totalDelay3] = AirCannonWave(sampleRates)
%sampleRates is a 1xN vector of sample rates
%[totalTime,totalDelay1,totalDelay2,totalDelay3] = AirCannonWave([7 5 3 1])

L=length(sampleRates);
H=[];

colors=['k' 'b' 'r' 'g' 'c' 'm'];

%also cycle through delays?
%change delay2 and delay4?
for j=1:L
[totalTime,sineSamples,totalDelay1,totalDelay2,totalDelay3] = ...
    Samples(sampleRates(j),20,1,10);

plot(1:totalTime,sineSamples,colors(j)) %cycle through colors
if j==1
    str={num2str(sampleRates(j))};
else
    str=[str, num2str(sampleRates(j))];
end
hold on
end

h=legend(str{:});
v = get(h,'title');
set(v,'string','Sample Rates');
xlabel('time (microseconds)')
ylabel('DAC amplitude')
end

%Is 4096 pushing speaker out of cavity? Check speaker slo-mo



function [totalTime,sineSamples,totalDelay1,totalDelay2,totalDelay3] = Samples(sampleRate,mult1,mult2,mult3)
%initially: 
%[totalTime,sineSamples,totalDelay1,totalDelay2,totalDelay3] = AirCannonWave(7,20,1,10)
%delays in ms (1000ms=1s)
%color example: 'k'

numSamples=512;
sineSamples=[];
PI=3.141592653589793;

%ADJUST THESE PARAMETERS
delay1= 100; % mult1*sampleRate;
delay2= 35000; %original 15000. Based on Microsoft 50ms intake
totalDelay1=127*delay1+delay2;
delay3= 4; %mult2*1;%sampleRate;
totalDelay2=255*delay3;
delay4= 75000; %original 50000. Based on Disney 8Hz (125ms total) (not Microsoft 100ms end delay)
delay5= 50; % mult3*sampleRate;
totalDelay3=128*delay5+delay4;

for i=1:numSamples
    sineNow=2048+2048*(sin(2*PI*i/numSamples)); %4096 is max DAC value
    
    if i<(numSamples/4)
        vector=ones(1,delay1);
    elseif i==(numSamples/4)
        vector=ones(1,delay2);
    elseif i<(3*numSamples/4)
        vector=ones(1,delay3);
    elseif i==(3*numSamples/4)
        vector=ones(1,delay4);
    else
        vector=ones(1,delay5);
    end
    
    sineVector=sineNow.*vector;
    sineSamples=[sineSamples sineVector];
end

totalTime=length(sineSamples);
end