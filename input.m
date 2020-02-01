A = load('A.mat')

f = fopen('data.in', 'wb');

fwrite(f, A, 'double');

fclose(f);

G = graph(A);

plot(G);

pause;
