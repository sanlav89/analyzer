function [sp, ENERGY, FWHM, PEAKSHAPE, EFFICIENCY, lib_energies, ... 
          Activity, start_channel, smooth_span, stop_condition, delim_counts, ...
          factor, preSpSmoothWin, thres, minValuesUnderThres, ... 
          centOfMassWindowLen, minNetCountsForMaxDetect, ... 
          nIters, boost, nBoostIters, title_msg, minFilterOrder, maxFilterOrder, ...
          filename] = ... 
          LOAD_data_SrI2(numberOfSpectrum)

filenames = [
"d:/WORK/_Gammatech/database/Фон_открытая крышка_16.dat" 
"d:/WORK/_Gammatech/database/Y-88 #174 04.dat" 
"d:/WORK/_Gammatech/database/Ti-44 #171 04.dat" 
"d:/WORK/_Gammatech/database/Th-228 #177 04.dat" 
"d:/WORK/_Gammatech/database/Eu-152 #6649_4.dat" 
"d:/WORK/_Gammatech/database/Cs-137 #6649_Точечная-25см_25cm.dat" 
"d:/WORK/_Gammatech/database/Co-60 #6649_2.dat" 
"d:/WORK/_Gammatech/database/Ba-133 #6649_Точечная-25см_25cm.dat" 
"d:/WORK/_Gammatech/database/Am-241 4213_Точечная-25см_25cm.dat" 
];
sizeofFile = 4096;

filename = filenames(numberOfSpectrum);

sp = f_LoadLsrmSpeFile(filenames(numberOfSpectrum), sizeofFile);

ENERGY = [-24.244712 2.956511 ];

FWHM = [4.103495 0.889421 ];

PEAKSHAPE = [
244.43, 0.727678, 0.659855, 0.997884, 1.027902, 90.981475, 1.630098, 29932.372920
344.99, 1.000000, 0.677640, 0.989376, 1.027417, 124.977625, 2.019576, 77250.392506
778.40, 0.777875, 0.467763, 1.001549, 0.988194, 271.497133, 3.263701, 15028.566663
962.98, 1.000000, 0.542606, 0.964666, 1.053920, 333.898090, 3.821069, 11941.421971
];

EFFICIENCY = [-7.268519 4.109910 -0.924845 -0.011715 ];

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
lib_Th_232 = [
338.320 11.270000
911.204 25.800000
968.971 15.800000
];
lib_Ti_44 = [
67.868 93.026000
78.323 96.400000
1157.020 99.900000
1499.460 0.908091
];
lib_Y_88 = [
898.042 93.682600
1836.060 99.240000
2734.000 0.714528
];

% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
% Библиотека
lib_energies = zeros(1, 2);
% TODO ... 
% "d:/WORK/__Gammatech/database/Фон_открытая крышка_16.dat" 
% "d:/WORK/__Gammatech/database/Y-88 #174 04.dat" 
% "d:/WORK/__Gammatech/database/Ti-44 #171 04.dat" 
% "d:/WORK/__Gammatech/database/Th-228 #177 04.dat" 
% "d:/WORK/__Gammatech/database/Eu-152 #6649_4.dat" 
% "d:/WORK/__Gammatech/database/Cs-137 #6649_Точечная-25см_25cm.dat" 
% "d:/WORK/__Gammatech/database/Co-60 #6649_2.dat" 
% "d:/WORK/__Gammatech/database/Ba-133 #6649_Точечная-25см_25cm.dat" 
% "d:/WORK/__Gammatech/database/Am-241 4213_Точечная-25см_25cm.dat" 
if (numberOfSpectrum == 1) title_msg = 'SrI2-Background.dat';
elseif (numberOfSpectrum == 2) lib_energies = lib_Y_88; title_msg = 'SrI2-Y-88';
elseif (numberOfSpectrum == 3) lib_energies = lib_Ti_44; title_msg = 'SrI2-Ti-44';
elseif (numberOfSpectrum == 4) lib_energies = lib_Th_228; title_msg = 'SrI2-Th-228';
elseif (numberOfSpectrum == 5) lib_energies = lib_Eu_152; title_msg = 'SrI2-Eu-152';
elseif (numberOfSpectrum == 6) lib_energies = lib_Cs_137; title_msg = 'SrI2-Cs-137';
elseif (numberOfSpectrum == 7) lib_energies = lib_Co_60; title_msg = 'SrI2-Co-60';
elseif (numberOfSpectrum == 8) lib_energies = lib_Ba_133; title_msg = 'SrI2-Ba-133';
elseif (numberOfSpectrum == 9) lib_energies = lib_Am_241; title_msg = 'SrI2-Am-241';
% elseif (numberOfSpectrum == 10) lib_energies = ;
end
% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Activity = 500; % Подобрано вручную

% Параметры алгоритма SASNIP
start_channel = 10;         % Номер канала, от которого начинать обработку
smooth_span = 0.015;        % Размер окна сглаживания
stop_condition = 0.5;     % Условие остановки процесса вычисления (в %)
delim_counts = 40;                % Номер канала, до которого фоновая подложка
                            % обязательно должна быть ниже спектра
                            
% Параметры сглаживания спектра регрессионным методом
minFilterOrder = 5;
maxFilterOrder = 45;
                            
% Параметры для определения границ
factor = 0.01;              % Критерий близости, максимальная разница в логарифмических единицах

% Параметры для определения максимумов
centOfMassWindowLen = 3;    % Размер окна для формулы ЦМ при уточнении положения максимума
minNetCountsForMaxDetect = 3; % Порог детектирования локального максимума (по "чистому" спектру)

% Устаревший параметр
preSpSmoothWin = 5;         % Размер фильтра предварительного сглаживания спектра

% GOLD
minValuesUnderThres = 5;
thres = 150;
nIters = 1000;              % Gold : количество итераций
boost = 5;                  % Gold : boost
nBoostIters = 50;           % Golt : repetitions

end
