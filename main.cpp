#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/reverse_graph.hpp"
#include <string>
#include <iostream>


#define N 40000
using namespace std;
using namespace boost;

struct vertex_info;

typedef adjacency_list<vecS, vecS, directedS, vertex_info, double> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_iterator VertexI;
typedef graph_traits<Graph>::edge_iterator EdgeI; 
typedef graph_traits<Graph>::out_edge_iterator EdgeO;

struct vertex_info{
	int tree_id;
	Vertex *bparent;
	double cost;
};

class Forest{
	
	//Creating a boost graph to represent the vertex-disjoint trees 	
	Graph G;
	int num_of_trees;
	public:
	Forest(){
		this->G = G;
		this->num_of_trees = 0;
	}
	
	//Making a new tree and adding it to the forest
	Vertex maketree(){
		Vertex u = add_vertex(G);
		G[u].tree_id = num_of_trees;
		G[u].cost = 0;
		G[u].bparent = NULL;
		num_of_trees++;
		return u;
	}
	//Find root of the tree in which the vertex belongs to
	Vertex findroot(Vertex u){
		Vertex tmp = u;
		while (G[tmp].bparent != NULL){
			tmp = *(G[tmp].bparent);			
		}
		return tmp;
	}
	//Find the vertex with the smallest cost nearest to the root from given vertex 
	Vertex findcost(Vertex u){
		double min = G[u].cost;
		Vertex tmp = u;
		Vertex w = u;
		while (G[tmp].bparent != NULL){
			tmp = *(G[tmp].bparent);
			if(G[tmp].bparent == NULL){
				if(min >= G[tmp].cost){
					min = G[tmp].cost;
					w = tmp;
				}
				break;
			}
			if (min >= G[tmp].cost){
				min = G[tmp].cost;
				w = tmp;
			}
		}
		return w;
	}
	//Add real number x to the cost of every vertex on the tree path from vertex given to root 
	void addcost(Vertex u, double x){
		Vertex tmp = u;
		while (G[tmp].bparent != NULL){
			G[tmp].cost += x;
			tmp = *(G[tmp].bparent); 
		}
		G[tmp].cost += x;
	}
	//Combine 2 trees inside the forest with an edge where u and w are in different trees and u is a root
	void link(Vertex u, Vertex *w){
		if((G[findroot(u)].tree_id != G[findroot(*w)].tree_id)&&(G[u].bparent == NULL)){
			add_edge(u, *w, G);
			G[u].bparent = w;	
		}else{
			cout<<"tried to link non-root with node or root of a tree with one of its nodes"<<endl;
			exit(1);
		}
	}
	//Split 2 trees inside the forest where u is not a tree root.
	void cut(Vertex u){
		if (G[u].bparent != NULL){
			remove_edge(u, *(G[u].bparent), G);
			G[u].bparent = NULL;
		}
	}
	//Display Forest
	void print_forest(){
		for (VertexI i = vertices(G).first; i != vertices(G).second; i++){
			if (G[*i].tree_id == 1){
				cout<<G[*i].tree_id<<" found"<<endl;
			}
			cout<<"Vertex id "<<G[*i].tree_id<<" has cost = "<<G[*i].cost<<endl;
		}
		for(EdgeI y = edges(G).first; y != edges(G).second; y++){
			cout<<"edge "<< *y <<endl;
		}
	}
	//Display the root of the tree given vertex belongs
	void print_root(Vertex u){
		cout<<"MyD: root of "<<G[u].tree_id<<" is "<<G[findroot(u)].tree_id<<endl;
	}
	//Display cost of given vertex
	void print_cost(Vertex u){
		cout<<G[findcost(u)].tree_id<<" with cost= "<<G[findcost(u)].cost <<endl;;
	}
	//Display parent of given vertex
	void print_parent(Vertex u){
		cout<<"Parent of "<<G[u].tree_id<<" is "<<G[*(G[u].bparent)].tree_id<<endl;
	}

};


int main(void){

	//Variables that you will need for the LCT functions
	double x;
	Vertex* my[N];
	Vertex marr[N];
	Vertex* ptrs[N];
	
	//Creating Linking & Cutting trees
	for(int j = 0; j<1000;j++){		
		Forest MyD;
		for (int i = 0; i < N; i++){
			marr[i] = MyD.maketree();
			ptrs[i] = &marr[i];
			my[i] = ptrs[i];
		}
	}
	return 0;
}
