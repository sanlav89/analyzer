function [en, fwx, fwe] = f_calcEnergyFwhm(x, polyEnergy, polyFwhm)
% Энергия
en = zeros(1, length(x));
for j = 1:1:length(polyEnergy)
    en = en + polyEnergy(j) * x.^(j - 1);
end

% ПШПВ в энергиях
en1 = en;
for i = 1:1:length(en1)
    if (en1(i) < 0)
        en1(i) = 0;
    end
end
fwe = zeros(1, length(x));
for j = 1:1:length(polyFwhm)
    fwe = fwe + polyFwhm(j) * en1.^((j - 1) / 2);
end
% en = abs(en);

% ПШПВ в каналах
fwx = zeros(1, length(x));
for i = 1:1:length(x)
    xl = f_channelByEnergy(en, en(i) - fwe(i) * 0.5);
    xr = f_channelByEnergy(en, en(i) + fwe(i) * 0.5);
    x0 = i;
    if i < length(x) / 2
        fwx(i) = (xr - x0) * 2;
    else
        fwx(i) = (x0 - xl) * 2;
    end
    if (fwx(i) < 0)
        fwx(i) = 0;
    end
end

end
