%
%                       test.m
%          ===============================
% 
% This script creates a random n by n sparse metrix with density d,    
% 
% saves that matrix to a binary file named `data.in`,
%
% executes the rcm implementation and get it's output.
%
% Then plots the reordering of my implementation versus matlab's.
%
%               Inputs:
%          ----------------
%  The script needs the followng parametes to be set before run,
%
%   -     n    :   The size of the sparse matrix.
%   -     d    :   The density of the sparce matrix.
%   - nthreads :   The number of threads to execute my implemetation on.
%   - version  :   A string 'S' for running the Sequential version, 'P' for running the parallel one. 
%
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%
n = 10;
d = 0.5;
nthreads = '1';
version = 'S';
%
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%
clear; hold off;

setenv('OMP_NUM_THREADS', nthreads);

cmd = sprintf("./test -%s %d", version, n);

A = full(sprandsym(n,d));

in = fopen('data.in', 'wb');
fwrite(in, A, 'double');
fclose(in);

system(cmd);

out = fopen('data.out', 'rb');
r = fread(in, 'int');
fclose(out);

r = r' + 1;

p = symrcm(A);

subplot(2,2,1), spy(A), title('Original A');
subplot(2,2,2), spy(A(r,r)), title('My RCM implemention');
subplot(2,2,3), spy(A(p,p)), title('Matlabs RCM implementation');
subplot(2,2,4), plot(graph(A));
