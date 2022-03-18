clc;
clear;

ENERGY = [-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10];
FWHM = [0.3180643473,1.2086508047,0.0274012077];
EFFICIENCY = [-19.424696 20.563331 -7.695772 0.906304 ];

x0 = 100;
[en0, ~, fwhm0] = f_calcEnergyFwhm(x0, ENERGY, FWHM);

en1 = 500;
eff0 = f_calcEfficiency(en1, EFFICIENCY);

[en, ~, ~] = f_calcEnergyFwhm(1:1:1024, ENERGY, FWHM);

g = f_gaussian(en, 500, 20, 100);

tlive = 3600.0;
a = 5 * tlive;
b = -0.003;
c = 0.5 * tlive;
d = -0.002;

N = length(en);
substrate = f_substrateModel(en, a, b, c, d);



