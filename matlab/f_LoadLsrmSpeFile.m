function [N] = f_LoadLsrmSpeFile(filename, size)
N_COLS = size / 4;
fid = fopen(filename, 'r');
N = double(fread(fid,[N_COLS,Inf],'uint32'))';
fclose(fid);
end

