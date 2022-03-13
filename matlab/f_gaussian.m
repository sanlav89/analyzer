function [y] = f_gaussian(x, x0, sigma, S)

y = S / (sigma * sqrt(2 * pi)) * exp(-(x - x0).^2 / (2 * sigma^2));

end

