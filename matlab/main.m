clc;
clear;

% close all;

[sp, ENERGY, FWHM, PEAKSHAPE, EFFICIENCY, lib_energies, ... 
          Activity, start_channel, smooth_span, stop_condition, delim_counts, ...
          factor, preSpSmoothWin, thres, minValuesUnderThres, ... 
          centOfMassWindowLen, minNetCountsForMaxDetect, ... 
          nIters, boost, nBoostIters, title_msg, minFilterOrder, maxFilterOrder, ...
          filename] = ... 
          LOAD_data_LaBr3(4);

% Предварительны расчет некоторых параметров
N = length(sp);
[en, fwx, fwe] = f_calcEnergyFwhm(1:1:N, ENERGY, FWHM);
roi = ones(1, N); % Области интереса SASNIP

% Вычисление теоретических площадей пиков
eff = f_calcEfficiency(lib_energies(:,1)', EFFICIENCY);
tlive = 3600;
areas = eff .* lib_energies(:, 2)' * Activity * tlive;

figure;
% subplot(211);
semilogy(en, sp, 'Linewidth', 1); grid on; hold on;
sz = size(lib_energies);
for i = 1:1:sz(1)
    semilogy([lib_energies(i,1) lib_energies(i,1)],[1 1e5], 'k');
end
xlim([en(1) en(end)]);
ylim([1 1e5]);
xlabel('Energy [keV]');
% subplot(212);
% semilogy(sp, 'Linewidth', 1); grid on; hold on;

x = en;
y = sp;

%%
calibrdata = [
14.7 26.34
22.3 59.54
25.7 67.87
29.4 78.32
32 84.37
44.7 121.8
86 238.6
87 241.4
88.5 244.7
100 287.2
108 300.8
124 344.3
183 510.8
208.2 583.2
259 727.3
309 867.4
343.5 964.1
394 1112
411 1157
416 1173
461 1299
473 1332
500 1408
521 1499
564 1621
913 2615
];
x = calibrdata(:,1);
y = calibrdata(:,2);


