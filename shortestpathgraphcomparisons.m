%% Average Run Time Vs. Data Size
n = [64 128 256 512 1024 2048 4096 8192];
avgRunTimeDij = [0.044, 0.175 0.634 2.507 10.425 40.234 170.625 674.231];
avgRunTimeFW = [0.157 1.037 7.286 57.487 450.373 1534.445 12402.581 243001.239];

figure
plot(n, avgRunTimeDij, n, avgRunTimeFW)
title('Run Time Vs. Vertices')
grid on
axis([0 8000 0 500])
legend('Dijkstra','Floyd-Warshall','location','se')
xlabel('Number of Vertices (n)')
ylabel('Run Time (seconds)')
%% Average Disance Vs. Data Size
avgDistDij = [2 2 2 2 1 1 1 1];
avgDistFW = [2 2 1 1 1 1 1 1];

figure
plot(n, avgDistDij, n, avgDistFW)
title('Average Distance Vs. Vertices')
grid on
axis([0 8000 0 3])
legend('Dijkstra','Floyd-Warshall','location','se')
xlabel('Number of Vertices (n)')
ylabel('Average Distance')

%% Average Number of Hops Vs. Data Size

avgHopsDij = [2 2 2 2 1 1 1 1];
avgHopsFW = [11 12 12 11 12 11 11 11];

figure
plot(n, avgHopsDij, n, avgHopsFW)
title('Average Hops Vs. Vertices')
grid on
axis([0 8000 0 15])
legend('Dijkstra','Floyd-Warshall','location','se')
xlabel('Number of Vertices (n)')
ylabel('Average Hops')



