n = 9;

cmd = sprintf("./main %d", n);

A = full(sprandsym(n,0.4));

in = fopen('data.in', 'wb');
fwrite(in, A, 'double');
fclose(in);

system(cmd);

out = fopen('data.out', 'rb');
r = fread(in, 'int');
fclose(out);

r = r' + 1;

p = symrcm(A);

subplot(1,2,1), spy(A), title('A');
subplot(1,2,2), spy(A(r,r)), title('A(r,r)');
%subplot(1,2,1), spy(A(p,p)), title('A(p,p)');