function simSp = f_simulateSpectrum(tlive, Anoise, Activity, eff, energies, intensities, en, ENERGY, FWHM)

areas = eff .* intensities * Activity * tlive;
% areas = 1e-3 * lib_energies(:, 2)' * Activity * tlive;

a = 5 * tlive;
b = -0.003;
c = 0.5 * tlive;
d = -0.0025;
% a = 0;
% b = 0;
% c = 5 * tlive;
% d = -0.0035;
substrate = f_substrateModel(en, a, b, c, d);
N = length(en);
y = zeros(1, N);
for i = 1:1:length(areas)
    en0 = energies(i);
    x0 = f_channelByEnergy(en, en0);
    [~, ~, fwhm] = f_calcEnergyFwhm(x0, ENERGY, FWHM);
    sigma = fwhm / (2*sqrt(2*log(2)));
    g = f_gaussian(en, en0, sigma, areas(i));
    y = y + g;
end
noise = randn(1, N) * Anoise;
simSp = substrate + y + noise;

end

