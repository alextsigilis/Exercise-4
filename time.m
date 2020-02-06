clear; hold off;

I = 1:13;
N = pow2(I);
T_1 = zeros(size(I));
T_2 = zeros(size(I));
T_3 = zeros(size(I));
T_4 = zeros(size(I));

for i=1:length(I)
    disp(N(i));
    n = N(i);
    d = 0.05
    A = full(sprandsym(n,d));
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
    d = 0.1;
    A = full(sprandsym(n,d));
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

for i=1:length(I)
    disp(N(i));
    n = N(i);
    d = 0.5;
    A = full(sprandsym(n,d));
    fin = fopen('data.in', 'wb');
    fwrite(fin, A,'double');
    fclose(fin);
    
    cmd = sprintf("./time %d", n);
    system(cmd);
    
    fout = fopen('data.out', 'rb');
    t = fread(fout, 'double');
    fclose(fout);
    
    T_3(i) = t;
end

for i=1:length(I)
    disp(N(i));
    n = N(i);
    d = 0.8;
    A = full(sprandsym(n,d));
    fin = fopen('data.in', 'wb');
    fwrite(fin, A,'double');
    fclose(fin);
    
    cmd = sprintf("./time %d", n);
    system(cmd);
    
    fout = fopen('data.out', 'rb');
    t = fread(fout, 'double');
    fclose(fout);
    
    T_4(i) = t;
end

hold on;

plot(N,log(T_1),'o-');
plot(N,log(T_2), 'o-');
plot(N,log(T_3), 'o-');
plot(N,log(T_4), 'o-');

xlabel('Matrix size n')
ylabel('Log of execution time')

legend('density=0.05', 'density=0.1', 'density=0.5', 'density=0.8');

title('Logarithmic plot of execution time with various densities');

grid on;