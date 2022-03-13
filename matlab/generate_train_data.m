clc;
clear;
close all;

library;
ENERGY = [-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10];
FWHM = [0.3180643473,1.2086508047,0.0274012077];
EFFICIENCY = [-19.424696 20.563331 -7.695772 0.906304];

N = 1024;
[en, fwx, fwe] = f_calcEnergyFwhm(1:1:N, ENERGY, FWHM);

num_classes = length(lib);
% lib_Am_241 = 0
% lib_Ba_133 = 1
% lib_Co_57 = 2
% lib_Co_60 = 3
% lib_Cs_137 = 4
% lib_Eu_152 = 5
% lib_Ra_226 = 6
% lib_Th_228 = 7
% lib_Th_232 = 8
% lib_Ti_44 = 9

% w = ones(1, num_classes);
% a = ones(1, num_classes);

w = [0 0 0 0 0 1 0 0 0 0];
a = [0 0 0 0 0 1 0 0 0 0];

possible_w = [0.025 0.05 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0];
possible_a = [0.025 0.05 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0];
possible_n = [1 2 3 4 5 6];

cnt = 0;

fileID = fopen('data.csv','w');
% fprintf(fileID,'%6s %12s\n','x','exp(x)');
% fprintf(fileID,'%6.2f %12.8f\n',A);
fprintf(fileID,'label');
for i = 1:1:N
    fprintf(fileID, ',ch%d',i);
end
fprintf(fileID,'\n');

for ipn = 1:1:length(possible_n)

for ipw = 1:1:length(possible_w)
    
for ipa = 1:1:length(possible_a)

for id1 = 1:1:num_classes
    
% for id2 = 1:1:num_classes

    w = zeros(1, num_classes);
    a = zeros(1, num_classes);

    w(id1) = possible_w(ipw);
    a(id1) = possible_a(ipa);
    
%     w(id2) = possible_w(ipw);
%     a(id2) = possible_a(ipa);
   
    Anoise = possible_n(ipn);
    y_train = zeros(1, N);
    for i = 1:1:num_classes
        lib_energies = cell2mat(lib(i));
        eff = f_calcEfficiency(lib_energies(:,1)', EFFICIENCY);
        tlive = w(i) * 3600;
        Activity = a(i) * 500;
        m = f_simulateSpectrum(tlive, Anoise, Activity, eff, lib_energies, en, ENERGY, FWHM);
        y_train = y_train + m;
    end
    
    fprintf(fileID,'%d',id1-1);
    for i = 1:1:N
        value = y_train(i);
        if (value < 1)
            value = 1;
        end
        fprintf(fileID, ',%d', round(value));
    end
    fprintf(fileID,'\n');
    
    cnt = cnt + 1;
% end

end

end

end
display([num2str(ipn) ' / ' num2str(max(possible_n))]);
end

fclose(fileID);

figure;
subplot(211);
% semilogy(en, sp, 'Linewidth', 1); grid on; hold on;
semilogy(en, y_train); grid on; hold on;
sz = size(lib_energies);
for i = 1:1:sz(1)
    semilogy([lib_energies(i,1) lib_energies(i,1)],[1 1e6], 'k');
end
xlim([en(1) en(end)]);
ylim([1 1e6]);
xlabel('Energy [keV]');

subplot(212);
plot(en, log10(y_train)); grid on; hold on;
xlim([en(1) en(end)]);
