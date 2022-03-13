function [sp, ENERGY, FWHM, PEAKSHAPE, EFFICIENCY, lib_energies, ... 
          Activity, start_channel, smooth_span, stop_condition, delim_counts, ...
          factor, preSpSmoothWin, thres, minValuesUnderThres, ... 
          centOfMassWindowLen, minNetCountsForMaxDetect, ... 
          nIters, boost, nBoostIters, title_msg, minFilterOrder, maxFilterOrder, ...
          filename] = ... 
          LOAD_data_OSGI(numberOfSpectrum)

filenames = [
"d:/WORK/_Gammatech/database/LSRM_S_Th228_15_OSGI.dat" 
"d:/WORK/_Gammatech/database/LSRM_S_Eu152_15_OSGI.dat" 
"d:/WORK/_Gammatech/database/LSRM_S_Cs137_15_OSGI.dat" 
"d:/WORK/_Gammatech/database/LSRM_S_Co60_15_OSGI.dat" 
"d:/WORK/_Gammatech/database/LSRM_S_Ba133_15_OSGI.dat" 
"d:/WORK/_Gammatech/database/LSRM_S_Am241_15_OSGI.dat" 
];
sizeofFile = 4092;

filename = filenames(numberOfSpectrum);

sp = f_LoadLsrmSpeFile(filenames(numberOfSpectrum), sizeofFile);

ENERGY = [-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10];

FWHM = [0.3180643473,1.2086508047,0.0274012077];

PEAKSHAPE = [
341.74, 1.000000, 1.000000, 0.988270, 1.054396, 134.402502, 4.987201, 351764.831581
];

EFFICIENCY = [-19.424696 20.563331 -7.695772 0.906304 ];
lib_Th_228 = [
39.857 1.063820
84.373 1.220000
115.183 0.596448
238.632 43.600000
240.986 4.100000
252.610 0.780000
277.371 6.600000
300.087 3.300520
510.770 22.600000
583.187 85.000000
727.330 6.668650
763.130 1.790000
785.370 1.101830
860.557 12.500000
1078.620 0.563728
1620.500 1.466970
2614.510 99.754000
];
lib_Eu_152 = [
121.782 28.531400
244.697 7.548990
344.279 26.591000
367.789 0.859421
411.116 2.237100
443.961 2.826550
688.670 0.856474
778.904 12.928500
867.380 4.227860
964.057 14.510300
1005.270 0.659440
1085.840 10.115000
1089.740 1.733730
1112.080 13.667400
1212.950 1.414600
1299.140 1.632690
1408.010 20.868100
];
lib_Co_60 = [
1173.230 99.850000
1332.490 99.982600
];
lib_Cs_137 = [
283.500 0.000580
661.657 89.900000
];
lib_Ba_133 = [
53.163 2.199000
79.614 2.620000
80.997 34.060000
160.611 0.645000
223.237 0.450000
276.400 7.164000
302.851 18.330000
356.013 62.050000
383.848 8.940000
];
lib_Ba_137m = [
661.657 89.900000
];
lib_Am_241 = [
26.345 2.270000
59.541 35.900000
];

% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
% Библиотека
lib_energies = zeros(1, 2);
% TODO ... 
% "d:/WORK/_Gammatech/database/LSRM_S_Th228_15_OSGI.dat" 
% "d:/WORK/_Gammatech/database/LSRM_S_Eu152_15_OSGI.dat" 
% "d:/WORK/_Gammatech/database/LSRM_S_Cs137_15_OSGI.dat" 
% "d:/WORK/_Gammatech/database/LSRM_S_Co60_15_OSGI.dat" 
% "d:/WORK/_Gammatech/database/LSRM_S_Ba133_15_OSGI.dat" 
% "d:/WORK/_Gammatech/database/LSRM_S_Am241_15_OSGI.dat" 
if (numberOfSpectrum == 1) lib_energies = lib_Th_228;title_msg = 'LSRM-S-Th228-15-OSGI';
elseif (numberOfSpectrum == 2) lib_energies = lib_Eu_152; title_msg = 'LSRM-S-Eu152-15-OSGI';
elseif (numberOfSpectrum == 3) lib_energies = lib_Cs_137; title_msg = 'LSRM-S-Cs137-15-OSGI';
elseif (numberOfSpectrum == 4) lib_energies = lib_Co_60; title_msg = 'LSRM-S-Co60-15-OSGI';
elseif (numberOfSpectrum == 5) lib_energies = lib_Ba_133; title_msg = 'LSRM-S-Ba133-15-OSGI';
elseif (numberOfSpectrum == 6) lib_energies = lib_Am_241;title_msg = 'LSRM-S-Am241-15-OSGI';
% elseif (numberOfSpectrum == 7) lib_energies = ;
% elseif (numberOfSpectrum == 8) lib_energies = ;
% elseif (numberOfSpectrum == 9) lib_energies = ;
% elseif (numberOfSpectrum == 10) lib_energies = ;
end
% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Activity = 500; % Подобрано вручную

% Параметры алгоритма SASNIP
start_channel = 10;         % Номер канала, от которого начинать обработку
smooth_span = 0.015;        % Размер окна сглаживания
stop_condition = 0.8;       % Условие остановки процесса вычисления (в %)
delim_counts = 40;          % Номер канала, до которого фоновая подложка
                            % обязательно должна быть ниже спектра

% Параметры сглаживания спектра регрессионным методом
minFilterOrder = 5;
maxFilterOrder = 85;
                            
% Параметры для определения границ
factor = 0.15;              % Критерий близости, максимальная разница в логарифмических единицах

% Параметры для определения максимумов
centOfMassWindowLen = 3;    % Размер окна для формулы ЦМ при уточнении положения максимума
minNetCountsForMaxDetect = 3; % Порог детектирования локального максимума (по "чистому" спектру)

% Устаревший параметр
preSpSmoothWin = 5;         % Размер фильтра предварительного сглаживания спектра

% GOLD
minValuesUnderThres = 5;
thres = 200;
nIters = 1000;              % Gold : количество итераций
boost = 5;                  % Gold : boost
nBoostIters = 50;           % Golt : repetitions

end
