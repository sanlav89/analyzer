function [sp, ENERGY, FWHM, PEAKSHAPE, EFFICIENCY, lib_energies, ... 
          Activity, start_channel, smooth_span, stop_condition, delim_counts, ...
          factor, preSpSmoothWin, thres, minValuesUnderThres, ... 
          centOfMassWindowLen, minNetCountsForMaxDetect, ... 
          nIters, boost, nBoostIters, title_msg, minFilterOrder, maxFilterOrder, ...
          filename] = ... 
          LOAD_data_LaBr3(numberOfSpectrum)

%       d:\WORK\_Gammatech\database\
filenames = [
"d:/WORK/_Gammatech/database/Ti44_#250_24sm.dat" 
"d:/WORK/_Gammatech/database/Th228_#3514_24sm.dat" 
"d:/WORK/_Gammatech/database/Eu152_#936_24sm.dat" 
"d:/WORK/_Gammatech/database/Cs137_#936_24sm.dat" 
"d:/WORK/_Gammatech/database/Co60_#936_24sm.dat" 
"d:/WORK/_Gammatech/database/Co57_#478_24sm.dat" 
"d:/WORK/_Gammatech/database/Bckg_10.dat" 
"d:/WORK/_Gammatech/database/Ba133_#936_24sm.dat" 
"d:/WORK/_Gammatech/database/Am241_#14-05_24sm.dat" 
];
sizeofFile = 4096;

filename = filenames(numberOfSpectrum);

sp = f_LoadLsrmSpeFile(filenames(numberOfSpectrum), sizeofFile);

% ENERGY = [-5.170481 2.838536 -0.000047 0.000000 0.000000 0.000000 0.000000 ];
ENERGY = [-12.43, 3.057, -0.0016, 3.543e-06, -2.196e-09];
%        p1 =  -2.196e-09  (-3.372e-09, -1.021e-09)
%        p2 =   3.543e-06  (1.579e-06, 5.507e-06)
%        p3 =     -0.0016  (-0.002604, -0.0005965)
%        p4 =       3.057  (2.878, 3.237)
%        p5 =      -12.43  (-20.53, -4.324)

FWHM = [-2.519034 1.143066 -0.015657 0.000180 0.000000 0.000000 0.000000 ];

PEAKSHAPE = [
120.22, 0.333136, 1.000000, 0.920727, 1.013347, 43.925304, 1.428387, 74624.400770
242.55, 0.479194, 1.000000, 0.952500, 1.047378, 87.480251, 1.945946, 16755.464193
342.47, 0.599200, 0.795078, 0.999184, 1.013630, 122.976465, 2.197386, 43580.678505
778.12, 0.580816, 1.000000, 0.977623, 1.050947, 276.953863, 3.148874, 7989.445582
964.37, 0.423854, 1.000000, 0.929992, 1.056103, 342.394571, 3.413988, 7354.874783
];

EFFICIENCY = [-42.085421 77.053259 -60.786200 24.167924 -4.841784 0.387048];
% EFFICIENCY = [-86.999064 131.322308 -75.421375 19.019057 -1.789179 ];
% EFFICIENCY = [-21.412318 23.485857 -9.350442 1.143476 ];
% EFFICIENCY = [-9.873462 8.017599 -2.745777 0.258087 ];
% EFFICIENCY = [-19.424696 20.563331 -7.695772 0.906304 ];
% EFFICIENCY = [-7.268519 4.109910 -0.924845 -0.011715 ];

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
lib_Co_57 = [
14.413 9.160000
122.061 85.600000
136.474 10.680000
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

% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
% Библиотека
lib_energies = zeros(1, 2);
% TODO ... 
% "c:/WORK/__Gammatech/database/Ti44_#250_24sm.dat" 
% "c:/WORK/__Gammatech/database/Th228_#3514_24sm.dat" 
% "c:/WORK/__Gammatech/database/Eu152_#936_24sm.dat" 
% "c:/WORK/__Gammatech/database/Cs137_#936_24sm.dat" 
% "c:/WORK/__Gammatech/database/Co60_#936_24sm.dat" 
% "c:/WORK/__Gammatech/database/Co57_#478_24sm.dat" 
% "c:/WORK/__Gammatech/database/Bckg_10.dat" 
% "c:/WORK/__Gammatech/database/Ba133_#936_24sm.dat" 
% "c:/WORK/__Gammatech/database/Am241_#14-05_24sm.dat" 
if (numberOfSpectrum == 1) lib_energies = [lib_Ti_44; lib_K_40]; title_msg = 'LaBr3-Ti44-#250-24sm';
elseif (numberOfSpectrum == 2) lib_energies = lib_Th_228; title_msg = 'LaBr3-Th228-#3514-24sm';
elseif (numberOfSpectrum == 3) lib_energies = lib_Eu_152; title_msg = 'LaBr3-Eu152-#936-24sm';
elseif (numberOfSpectrum == 4) lib_energies = lib_Cs_137; title_msg = 'LaBr3-Cs137-#936-24sm';
elseif (numberOfSpectrum == 5) lib_energies = lib_Co_60; title_msg = 'LaBr3-Co60-#936-24sm';
elseif (numberOfSpectrum == 6) lib_energies = lib_Co_57; title_msg = 'LaBr3-Co57-#478-24sm';
elseif (numberOfSpectrum == 7)  title_msg = 'LaBr3-Bckg-10';
elseif (numberOfSpectrum == 8) lib_energies = lib_Ba_133;  title_msg = 'LaBr3-Ba133-#936-24sm';
elseif (numberOfSpectrum == 9) lib_energies = lib_Am_241; title_msg = 'LaBr3-Am241-#14-05-24sm';
% elseif (numberOfSpectrum == 10) lib_energies = ;
end
% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Activity = 500; % Подобрано вручную

% Параметры алгоритма SASNIP
start_channel = 10;         % Номер канала, от которого начинать обработку
smooth_span = 0.015;        % Размер окна сглаживания
stop_condition = 0.8;       % Условие остановки процесса вычисления (в %)
delim_counts = 40;                % Номер канала, до которого фоновая подложка
                            % обязательно должна быть ниже спектра
                            
% Параметры сглаживания спектра регрессионным методом
minFilterOrder = 5;
maxFilterOrder = 41;
                            
% Параметры для определения границ
factor = 0.04;              % Критерий близости, максимальная разница в логарифмических единицах

% Параметры для определения максимумов
centOfMassWindowLen = 3;    % Размер окна для формулы ЦМ при уточнении положения максимума
minNetCountsForMaxDetect = 15; % Порог детектирования локального максимума (по "чистому" спектру)

% Устаревший параметр
preSpSmoothWin = 5;         % Размер фильтра предварительного сглаживания спектра

% GOLD
minValuesUnderThres = 5;
thres = 200;
nIters = 1000;              % Gold : количество итераций
boost = 5;                  % Gold : boost
nBoostIters = 50;           % Golt : repetitions

end
