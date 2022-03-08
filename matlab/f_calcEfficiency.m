function [eff] = f_calcEfficiency(en, polyEff)

eff = zeros(1, length(en));
for j = 1:1:length(polyEff)
    if (en < 0)
        eff = 0;
    else
        eff = eff + polyEff(j) * (log10(en)).^(j - 1);
    end
end

eff = 10.^eff;

end

