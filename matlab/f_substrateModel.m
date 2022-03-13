function m = f_substrateModel(en, a, b, c, d)
% a =        3025; %  (2764, 3285)
% b =   -0.002886; %(-0.003242, -0.00253)
% a = 2000;
% b = -0.0035;
% model = a * exp(b * en);
% model = smooth(model, 100);
% Coefficients (with 95% confidence bounds):
%        a =       -6428  (-2.287e+07, 2.286e+07)
%        b =    -0.00245  (-0.2182, 0.2133)
%        c =        9442  (-2.285e+07, 2.287e+07)
%        d =   -0.002576  (-0.1607, 0.1555)
% a = 3000;
% b = -0.003;
% c = 150;
% d = -0.0018;
m = a*exp(b*en).^2 + c*exp(d*en);

end

