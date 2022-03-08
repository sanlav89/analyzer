function [x] = f_channelByEnergy(en, en0)

N = length(en);
% Осноной цикл 
e = 1;
a = 1;
b = N;
while abs(b - a) > e
    c = round((b + a) / 2);
    if sign(en(c) - en0) == sign(en(a) - en0)
        a = c;
    else
        b = c;
    end
end

kk = (b - a) / (en(b) - en(a));
bb = b - kk * en(b);
x = kk * en0 + bb;

end

