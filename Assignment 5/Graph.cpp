#include "Graph.h"
#include "heap.h"

// This is 2^31 -1

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}

Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}


int Graph::shortestDistance(int s, int d)
{
	// Dijkstra, using min heap to store the unvisited nodes
	int INFIN = 2147483647;
	Heap<nodeWeightPair> queue;

	// Initialise all the arrays
	int* dist = new int [_nv];
	bool* visited = new bool [_nv];
	int* parent = new int [_nv];
	int* son = new int [_nv];
	for(int i = 0; i < _nv; i++){
		dist[i] = INFIN;
		visited[i] = false;
		parent[i] = -1;
		son[i] = -1;
	}
	dist[s] = 0;
	queue.insert(nodeWeightPair(s,0));

	while(!queue.empty()) {
		// Process the current vertex
		int v_index = queue.extractMax().nodeIndex(); // index of current vertex
		if(visited[v_index]) {continue;} // Try again if node is visited
		visited[v_index] = true;

		// Relax its neighbours O(E)
		for(_al[v_index].start(); !_al[v_index].end(); _al[v_index].next()) {
			int neighbour_index = _al[v_index].current().nodeIndex();		
			// List<nodeWeightPair> vertex = _al[v_index]; // vertex = current vertex which is a linked list
			// for some reason ^this breaks the code idk why
			// maybe because the List = operator is undefined?
			int temp_dist = _al[v_index].current().weight() + dist[v_index]; // dist to given neighbour
			if(dist[neighbour_index] > temp_dist) { // if smaller, relax
				dist[neighbour_index] = temp_dist;
				if(!visited[neighbour_index]) {
					queue.insert(nodeWeightPair(neighbour_index, -dist[neighbour_index]));
					// 2040C SPECIFIC CHEAT METHOD
					// Since we check visited anyw, can just add a new, shorter distance nodeweightpair vs decreasekey
					// This is because our decreasekey kind of sucks asymptotically
					// because we only have max heap, have to use negative dist
					parent[neighbour_index] = v_index;
				}
			}
		}
	}

	if(dist[d] == INFIN)
		return -1;
	int result = dist[d];
	// Print the path in a "stack" (using son[])
	// using son from the start doesn't work because it won't be shortest
	std::cout << "Path:";
	for(int i = d; i != -1; i = parent[i])
		if(parent[i] != -1){son[parent[i]] = i;}
	for(int i = s; i != -1; i = son[i])
		std::cout << " " << i;
	std::cout << endl;
	
	delete[] dist;
	delete[] visited;
	delete[] parent;
	delete[] son;

	return result;
}

void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}
Graph::~Graph()
{

	delete[] _al;

}