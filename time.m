I = 10:15
N = pow2(I);
T = zeros(size(I));

for i=1:length(I)
    n = N(i);
    A = full(sprandsym(n,1/n));
    fin = fopen('data.in', 'wb');
    fwrite(fin, A,'double');
    fclose(fin);
    
    cmd = sprintf("./time %d", n);
    system(cmd);
    
    fout = fopen('data.out', 'rb');
    t = fread(fout, 'double');
    fclose(fout);
    
    T(i) = t;
end