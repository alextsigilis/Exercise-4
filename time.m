clear; hold off;

I = 1:13;
N = pow2(I);
T_1 = zeros(size(I));
T_2 = zeros(size(I));

for i=1:length(I)
    disp(N(i));
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
    
    T_1(i) = t;
end

for i=1:length(I)
    disp(N(i));
    n = N(i);
    A = full(sprandsym(n,0.8));
    fin = fopen('data.in', 'wb');
    fwrite(fin, A,'double');
    fclose(fin);
    
    cmd = sprintf("./time %d", n);
    system(cmd);
    
    fout = fopen('data.out', 'rb');
    t = fread(fout, 'double');
    fclose(fout);
    
    T_2(i) = t;
end

plot(N,log(T_1),'o-')
hold on;
plot(N,log(T_2), 'o-');

xlabel('Matrix size n')
ylabel('Log of execution time')

legend('density=1/n', 'density=0.8');

title('Logarithmic plot of execution time with various densities');