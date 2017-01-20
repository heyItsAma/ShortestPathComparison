/**
@author: Ama Freeman
@date: Dec. 16th 2016
@purpose: To comapre the runtimes and
efficiencies of two shortest path 
algorithms: Dijkstra's and Floyd-Warshall's

*/

#include <iostream>

//Needed for Writing/Creating File
#include <ostream>
#include <fstream>

//Needed for calculating run time
#include <ctime>
#include <cstdio>

//Included header files
#include "DijGraph.h"
#include "FWGraph.h"

int main() {
	//Implementing Test 1 - Creating a Matrix, Printing It
	// and casting Dijkstra's on it.
	int choice;
	int hops;

	do {
		//Prompt user for choice
		std::cout << "What would you like to do? (Enter a number.)\n";
		std::cout << "1. Create and Print Matrix\n";
		std::cout << "2. Create Matrix and Run Dijkstra's Shortest Path Algorithm\n";
		std::cout << "3. Create Matrix and Run Floyd-Warshall's Shortest Path Algorithm\n";
		std::cout << "4. Quit\n";

		std::cin >> choice;

		if (choice == 1) {
			std::cout << "Creating a Matrix and Printing It...\n";

			double duration;
			std::clock_t start;

			start = std::clock();

			DijGraph graph1(6);
			graph1.printMatrix();

			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			std::cout << "Dijkstra's Algorithm finished in " << duration << " seconds.\n";

			choice = 0;
		}
		else if(choice == 2)
		{
			std::cout << "Creating a Matrix and Finding the Shortest Path ";
			std::cout << "using Dijkstra's Algorithm...\n";

			double duration;
			std::clock_t start;

			start = std::clock();

			DijGraph graph2(6);
			hops = graph2.dijRandomGraphs();

			//graph2.printMatrix();
			//graph2.dijShortestPath();

			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			std::cout << "Dijkstra's Algorithm finished in " << duration << " seconds.\n";
			std::cout << "Average Number of Hops from Source " << 0 << " to Target Vertices - 1 = " << hops << "\n";
			choice = 0;
		}
		else if (choice == 3) {

			double duration;
			std::clock_t start;

			start = std::clock();

			std::cout << "Creating a Matrix and Finding the Shortest Path ";
			std::cout << "using Floyd-Warshall's Algorithm...\n";

			FWGraph graph3(6);
			graph3.fwRandomGraphs();

			//graph3.printMatrix();
			//graph3.FWShortestPath();


			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			std::cout << "Floyd-Warshall's Algorithm finished in " << duration << " seconds.\n";
			//std::cout << "Average Number of Hops from Source " << 0 << " to Target Vertices - 1 = " << hops << "\n";

			choice = 0;
		}
		else if (choice == 4) {
			std::cout << "Thank you for using the program!\n";
		}
		else {
			std::cout << "Invalid input. Please choose a number 1 to 4.\n";

			choice = 0;
		}
	} while (choice != 4);

	return 0;
}