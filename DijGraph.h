#pragma once
#include <iostream>
//Random Number Generator
#include<stdlib.h>
#include<time.h>

//Needed for Writing/Creating File
#include <ostream>
#include <fstream>

static int hops = 0;
static int distancetotal = 0;

class DijGraph {
protected:
	int vertices; //# of Vertices in Graph

	int **adjMatrix; //adjacency matrix of graph

	int *distancesArray;

	bool *visitedVertices;

	const int startSource = 0;

	const int endSource = vertices-1;

public:
	//Constructor
	DijGraph(int vertices);

	//Destructor
	~DijGraph();

	//Print Matrix for Testing
	void printMatrix();

	//Dijkstra's Algorithm
	void dijShortestPath();

	//Create 100 Graphs with 64-8192 Vertices and Find Shortest Path
	int dijRandomGraphs();

	//Upload Data to File
	void uploadFileDijkstras(int shortestDistance);

};

void DijGraph::uploadFileDijkstras(int shortestDistance) {
	std::ofstream myfile;
	myfile.open("data64.txt", std::ios_base::app);

	if (myfile) {
		myfile << shortestDistance;
		myfile << "\n";
	}
	else {
		std::cout << "File Failed to Open!\n";
	}
}

int DijGraph::dijRandomGraphs() {
	int averageHops = 0;

	for (int i = 1; i <= 100; i++) {
		//Create a Graph with 64-8192 vertices
		DijGraph* graphD = new DijGraph(64);

		//Use Dijkstra's Algorithm
		graphD->dijShortestPath();

		//Delete Graph
		delete graphD;
	}

	std::cout << "Number of hops: " << hops << "\n";
	std::cout << "Total distance after 100 tests: " << distancetotal << "\n";
	int avgDist = distancetotal / 100;

	std::cout << "Average Distance from Source to Target = " << avgDist << "\n";
	averageHops = hops / 100;

	distancetotal = 0;
	hops = 0;
	return averageHops;
}

DijGraph::DijGraph(int vertices) {
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

DijGraph::~DijGraph() {
	//Deallocate pointers in matrix
	for (int i = 0; i < vertices; i++) {
		delete[] adjMatrix[i];
	}

	delete[] adjMatrix;

	//Deallocate Visited Vertices, Distances Array
	delete[] visitedVertices;
	delete[] distancesArray;
}

void DijGraph::printMatrix() {
	std::cout << "Printing Matrix: \n";

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			std::cout << adjMatrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void printPath(int parent[], int j) {
	int inf = 2000000;

	// Base Case : If j is source
	if (parent[j] == inf)
		return;


	printPath(parent, parent[j]);

	//std::cout << j << " ";
	hops++;
}

void DijGraph::dijShortestPath() {

	//Distances array = first row of adjacency matrix
	int inf = 2000000;
	for (int i = 0; i < vertices; i++) {
		distancesArray[i] = inf;
		visitedVertices[i] = false;
	}

	//Source is 0
	distancesArray[0] = 0;

	//Hop counter
	int hopsToTarget = 0;
	int *parent = new int[vertices];
	parent[0] = inf;

	for (int i = 0; i < vertices; i++) {
		//For loop that exits with the smallest weight 
		int smallIndex;
		int minDistance = INT_MAX, minIndex;

		for (int j = 0; j < vertices; j++) {
			if (visitedVertices[j] == false && distancesArray[j] <= minDistance) {
				minIndex = j;
				minDistance = distancesArray[j];
				//std::cout << minDistance << "\n";
			}
		}

		int u = minIndex;
		//std::cout << "min index: " << u << "\n";
		visitedVertices[u] = true;

		//Add smallindex(the index of the
		//shortest distance), to the vertex 
		//set.

		//Check the weight for vertices
		//Not in the vertex set

		for (int v = 0; v < vertices; v++) {
			if ((!visitedVertices[v]) && (adjMatrix[u][v]) && (distancesArray[u] != inf)
				&& (distancesArray[u] + adjMatrix[u][v] < distancesArray[v])) {

				parent[v] = u;
				distancesArray[v] = distancesArray[u] + adjMatrix[u][v];
			}
		}
	}

	int sourceToEnd = distancesArray[vertices - 1];

	//uploadFileDijkstras(sourceToEnd);

	//Find total number of hops
	printPath(parent, vertices - 1);
	//std::cout << "Number of Hops from Source " << 0 << " to Target " << vertices - 1 << " = " << hops - 1 << "\n";

	//Find average distance
	distancetotal += distancesArray[vertices - 1];


	/*
	for (int i = 0; i < vertices; i++) {
		std::cout << "Vertex " << i << " distance from source vertex 0: " << distancesArray[i];
		std::cout << "\n";
	}
	*/
}