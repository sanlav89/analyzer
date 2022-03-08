function [sp, ENERGY, FWHM, PEAKSHAPE, EFFICIENCY, lib_energies, ... 
          Activity, start_channel, smooth_span, stop_condition, delim_counts, ...
          factor, preSpSmoothWin, thres, minValuesUnderThres, ... 
          centOfMassWindowLen, minNetCountsForMaxDetect, ... 
          nIters, boost, nBoostIters, title_msg, minFilterOrder, maxFilterOrder, ...
          filename] = ... 
          LOAD_data_NaI(numberOfSpectrum)

filenames = [
"d:/Workspace/Gammatech/database/Ti-44   A=72400 Bq.dat" 
"d:/Workspace/Gammatech/database/Eu-152  A=243600 Bq.dat" 
"d:/Workspace/Gammatech/database/Cs-137  A=74800 Bq.dat" 
"d:/Workspace/Gammatech/database/Cs-134   A=95100 Bq.dat" 
"d:/Workspace/Gammatech/database/Co-60   A=197600 Bq.dat" 
"d:/Workspace/Gammatech/database/Background140207.dat" 
"d:/Workspace/Gammatech/database/Ba-133   A=813600 Bq.dat" 
"d:/Workspace/Gammatech/database/Am-241  A=321200 Bq.dat" 
];
sizeofFile = 4096;

filename = filenames(numberOfSpectrum);

sp = f_LoadLsrmSpeFile(filenames(numberOfSpectrum), sizeofFile);

% ENERGY = [-0.763608 2.997121 0.000000 0.000000 0.000000 0.000000 0.000000 ];
ENERGY = [27.37 0.5147 0.003878];
FWHM = [-8.208433 2.090497 0.009513 0.000000 0.000000 0.000000 0.000000];

PEAKSHAPE = [
503.12, 0.555190, 1.000000, 1.006037, 1.002926, 232.951598, 6.430240, 23774.830178
658.02, 0.661282, 1.000000, 1.018221, 0.991077, 284.598755, 7.551050, 9321.417306
1168.89, 0.522584, 1.000000, 1.042052, 0.980464, 454.237319, 8.830402, 10153.968206
1330.44, 1.000000, 1.000000, 1.022500, 1.011996, 508.104551, 9.686833, 9168.630253
];

EFFICIENCY = [-9.873462 8.017599 -2.745777 0.258087 ];

lib_Am_241 = [
26.345 2.270000
59.541 35.900000
];
lib_Ba_133 = [
53.162 2.140730
79.614 2.649540
80.998 32.948500
160.612 0.637874
276.399 7.160570
302.851 18.335800
356.013 62.050000
383.849 8.941400
];
lib_Co_60 = [
1173.230 99.850000
1332.490 99.982600
];
lib_Cs_134 = [
475.365 1.477000
563.246 8.337980
569.331 15.373000
604.721 97.619700
795.864 85.459700
801.953 8.687970
1038.610 0.989997
1167.970 1.790000
1365.180 3.016990
];
lib_Cs_137 = [
661.657 89.900000
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
lib_K_40 = [
1460.820 10.662200
];
lib_Ra_226 = [
295.223 18.420100
296.000 79.168500
304.896 25.152300
351.932 35.600200
609.320 45.490300
799.600 98.960700
1070.000 11.875300
1120.290 14.920100
1210.000 16.823300
1316.000 20.781700
1764.490 15.300100
];
lib_Th_232 = [
238.632 43.600000
338.320 11.270000
510.770 22.600000
583.187 85.000000
860.557 12.500000
911.204 25.800000
968.971 15.800000
2614.510 99.754000
];
lib_Ti_44 = [
67.868 93.026000
78.323 96.400000
1157.020 99.900000
1499.460 0.908091
];

% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
% Библиотека
lib_energies = zeros(1, 2);
% TODO ... 
% "c:/Workspace/_Gammatech/database/Ti-44   A=72400 Bq.dat" 
% "c:/Workspace/_Gammatech/database/Eu-152  A=243600 Bq.dat" 
% "c:/Workspace/_Gammatech/database/Cs-137  A=74800 Bq.dat" 
% "c:/Workspace/_Gammatech/database/Cs-134   A=95100 Bq.dat" 
% "c:/Workspace/_Gammatech/database/Co-60   A=197600 Bq.dat" 
% "c:/Workspace/_Gammatech/database/Background140207.dat" 
% "c:/Workspace/_Gammatech/database/Ba-133   A=813600 Bq.dat" 
% "c:/Workspace/_Gammatech/database/Am-241  A=321200 Bq.dat" 
if (numberOfSpectrum == 1) lib_energies = lib_Ti_44; title_msg = 'NaI-Ti-44   A=72400 Bq';
elseif (numberOfSpectrum == 2) lib_energies = lib_Eu_152; title_msg = 'NaI-Eu-152  A=243600 Bq';
elseif (numberOfSpectrum == 3) lib_energies = lib_Cs_137; title_msg = 'NaI-Cs-137  A=74800 Bq';
elseif (numberOfSpectrum == 4) lib_energies = lib_Cs_134; title_msg = 'NaI-Cs-134   A=95100 Bq';
elseif (numberOfSpectrum == 5) lib_energies = lib_Co_60; title_msg = 'NaI-Co-60   A=197600 Bq';
elseif (numberOfSpectrum == 6) title_msg = 'NaI-Background140207';
elseif (numberOfSpectrum == 7) lib_energies = lib_Ba_133; title_msg = 'NaI-Ba-133   A=813600 Bq';
elseif (numberOfSpectrum == 8) lib_energies = lib_Am_241; title_msg = 'NaI-Am-241  A=321200 Bq';
% elseif (numberOfSpectrum == 9) lib_energies = ;
% elseif (numberOfSpectrum == 10) lib_energies = ;
end
% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Activity = 500; % Подобрано вручную

% Параметры алгоритма SASNIP
start_channel = 10;         % Номер канала, от которого начинать обработку
smooth_span = 0.015;        % Размер окна сглаживания
stop_condition = 2.2;       % Условие остановки процесса вычисления (в %)
delim_counts = 40;                % Номер канала, до которого фоновая подложка
                            % обязательно должна быть ниже спектра

% Параметры сглаживания спектра регрессионным методом
minFilterOrder = 5;
maxFilterOrder = 85;
                            
% Параметры для определения границ
factor = 0.1;              % Критерий близости, максимальная разница в логарифмических единицах

% Параметры для определения максимумов
centOfMassWindowLen = 3;    % Размер окна для формулы ЦМ при уточнении положения максимума
minNetCountsForMaxDetect = 5; % Порог детектирования локального максимума (по "чистому" спектру)

% Устаревший параметр
preSpSmoothWin = 5;         % Размер фильтра предварительного сглаживания спектра

% GOLD
minValuesUnderThres = 5;
thres = 200;
nIters = 1000;              % Gold : количество итераций
boost = 5;                  % Gold : boost
nBoostIters = 50;           % Golt : repetitions


end
