#pragma once
#include <iostream>
//Random Number Generator
#include<stdlib.h>
#include<time.h>

//Needed for Writing/Creating File
#include <ostream>
#include <fstream>

//Floyd-Warshall Algorithm sourced from 
// http://www.geeksforgeeks.org/dynamic-programming-set-16-floyd-warshall-algorithm/

static int hops1 = 0;
static int distances = 0;

class FWGraph {
protected:
	int vertices; //# of Vertices in Graph

	int **adjMatrix; //adjacency matrix of graph

	int *distancesArray;

	bool *visitedVertices;

	const int startSource = 0;

	const int endSource = vertices - 1;

public:
	//Constructor
	FWGraph(int vertices);

	//Destructor
	~FWGraph();

	//Print Matrix for Testing
	void printMatrix();

	//Floyd-Warshall's Algorithm
	void FWShortestPath();

	//Create 100 Graphs with 64-8192 Vertices and Find Shortest Path
	int fwRandomGraphs();

};

int FWGraph::fwRandomGraphs() {
	int averageHops = 0;

	for (int i = 1; i <= 100; i++) {
		//Create a Graph with 64-8192 vertices
		FWGraph* graphD = new FWGraph(2048);

		//Use Dijkstra's Algorithm
		graphD->FWShortestPath();

		//Delete Graph
		delete graphD;
	}

	std::cout << "Number of hops: " << hops1 << "\n";
	averageHops = hops1 / vertices;
	std::cout << "Total distance after 100 tests: " << distances << "\n";
	int avgDist = distances / 100;


	std::cout << "Average Distance from Source to Target = " << avgDist << "\n";
	std::cout << "Average Number of Hops from Source " << 0 << " to Target Vertices - 1 = " << averageHops << "\n";

	distances = 0;
	hops1 = 0;
	return averageHops;

}

void printPath2(int parent[], int j) {
	int inf = 2000000;

	// Base Case : If j is source
	if (parent[j] == inf)
		return;


	printPath2(parent, parent[j]);

	std::cout << j << " ";
	hops++;
}

FWGraph::FWGraph(int vertices) {
	//Initialize Vertices in Graph
	this->vertices = vertices;

	//Initialize Distances Array
	distancesArray = new int[vertices];

	//Initialize Visited Set Array
	visitedVertices = new bool[vertices];

	//Initialize Matrix of Random Weights
	adjMatrix = new int*[vertices];

	srand(time(NULL));
	int randomWeight = 0;

	for (int i = 0; i < vertices; i++) {
		adjMatrix[i] = new int[vertices];
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			randomWeight = rand() % 5;
			adjMatrix[i][j] = randomWeight;
		}
	}

	for (int i = 0; i < vertices; i++) {
		adjMatrix[i][i] = 0;
	}
}

FWGraph::~FWGraph() {
	//Deallocate pointers in matrix
	for (int i = 0; i < vertices; i++) {
		delete[] adjMatrix[i];
	}

	delete[] adjMatrix;

	//Deallocate Visited Vertices, Distances Array
	delete[] visitedVertices;
	delete[] distancesArray;
}

void FWGraph::printMatrix() {
	std::cout << "Printing Matrix: \n";

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			std::cout << adjMatrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void FWGraph::FWShortestPath() {

	int inf = 2000000;

	/* dist[][] will be the output matrix that will finally have the shortest
	distances between every pair of vertices, but I will print only row 1
	for my project */
	int **dist = new int*[vertices];

	//int **parent = new int*[vertices];
	//parent[0] = inf;

	for (int i = 0; i < vertices; i++) {
		dist[i] = new int[vertices];
	}

	//Initialize the solution matrix with the values of the
	//original graph.
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			dist[i][j] = adjMatrix[i][j];
		}
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
		if(dist[i][j] == 0)
			dist[i][j] = inf;
		}
	}

	int **parent = new int*[vertices];

	for (int i = 0; i < vertices; i++) {
		parent[i] = new int[vertices];
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (dist[i][j] != 0 && dist[i][j] != inf) {
				parent[i][j] = i;
			}
			else {
				parent[i][j] = inf;
			}
		}
	}

	/* Add all vertices one by one to the set of intermediate vertices.
	---> Before start of a iteration, we have shortest distances between all
	pairs of vertices such that the shortest distances consider only the
	vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
	----> After the end of a iteration, vertex no. k is added to the set of
	intermediate vertices and the set becomes {0, 1, 2, .. k} */
	for (int k = 0; k < vertices; k++)
	{
		// Pick all vertices as source one by one
		for (int i = 0; i < vertices; i++)
		{
			// Pick all vertices as destination for the
			// above picked source
			for (int j = 0; j < vertices; j++)
			{
				// If vertex k is on the shortest path from
				// i to j, then update the value of dist[i][j]
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					//distances += dist[0][j];
					//parent[k] = dist[i][j];
					//hops1++;
					parent[i][j] = k;
				}
			}
			//distances += dist[k][i];
			//hops1++;
		}
		//hops1++;
	}

	if (parent[0][vertices - 1] != inf || parent[0][vertices - 1] != 0) {
		hops1++;
		distances += dist[0][vertices - 1];
	}

	/*
	for (int j = 0; j < vertices; j++) {
		if (parent[0][j] != inf) {
			hops1++;
			distances += parent[0][j];
			}
	}
	*/

	/*
	std::cout << "Distances: " << distances << "\n";
	std::cout << "Hops: " << hops1 << "\n";

	std::cout << "Printing Parent Matrix: \n";

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			std::cout << parent[i][j] << " ";
		}
		std::cout << "\n";
	}

	*/






	//printPath2(parent, vertices - 1);

	// Print the shortest distance row from Source Vertex 0 to Vertex V-1
	/*
	for (int i = 0; i < vertices; i++) {
		//std::cout << "Vertex " << i << " distance from source vertex 0: " << dist[0][i];
		//std::cout << "\n";

		distances += dist[0][i];
	}
	*/


	//Deallocate pointers in distance matrix
	for (int i = 0; i < vertices; i++) {
		delete[] dist[i];
		delete[] parent[i];
	}

	delete[] dist;
	delete[] parent;


}
