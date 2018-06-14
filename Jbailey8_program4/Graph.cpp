#include <iostream>
#include <iomanip>
#include <vector>

struct Node{
	std::string name;
	int row;
	Node(std::string nameIn, int rowIn) : row(rowIn), name(nameIn) {}
};

class Graph{
	public:
		int ** adj_matrix;
		std::vector<Node *> nodes;
		int size;
		std::string nodes_as_inserted;

		Graph(int size){
			this->size = size;
			adj_matrix = new int*[size];
			for(int i = 0; i < size; i++) adj_matrix[i] = new int[size];
			nodes_as_inserted = "";
		}

		void setValueOfRow(Node * node, int row, std::vector<int> values){
			for(int i = 0; i < size; i++) adj_matrix[row][i] = values[i];
			nodes.push_back(node);
		}

		int minDistance(int dist[], bool spSet[]){
			int min = 1000;
			int min_index;
			for(int i = 0; i < size; i++){
				if(spSet[i] == false && dist[i] <= min){
					min = dist[i];
					min_index = i;
				}
			}
			return min_index;
		}

		void djikstra(Node * source){
			std::string s = source->name;
			int dist[size];
			int prev[size];
			bool spSet[size];
			
			for(int i = 0; i < size; i++){
				dist[i] = 1000;
				prev[i] = -1;
				spSet[i] = false;
			}
			dist[source->row] = 0;
			printMatrixHeader();
			for(int i = 0; i < size; i++){
				int u = minDistance(dist, spSet);
				nodes_as_inserted += nodes[u]->name;
				spSet[u] = true;

				for(int j = 0; j < size; j++){
					if(!spSet[j] && adj_matrix[u][j] < 999 && dist[u] + adj_matrix[u][j] < dist[j]){
						prev[j] = u;
						dist[j] = dist[u] + adj_matrix[u][j];
					}
				}
				printDistTable(i, dist, prev, spSet);
			}
		}

		void printMatrixHeader(){
			std::cout << "Step";
			std::cout << std::setw(size+4) << "NodeList";
			for(int i = 0; i < size; i++) std::cout << std::setw(size+5) << "D(" << nodes[i]->name << "),p(" << nodes[i]->name << ")";
			std::cout << std::endl;
		}

		void printDistTable(int i, int dist[], int prev[], bool spSet[]){
				std::cout << i;
				std::cout << std::setw(size);
				for(int j = 0; j <= size; j++){
					if( j <= i) std::cout << nodes_as_inserted[j];
					else std::cout << ' ';
				}
				for(int j = 0; j < size; j++){
					if(spSet[j]){
						std::cout << std::setw(size+12) << '_';
						continue;
					}
					if(prev[j] != -1 && dist[j] != 1000) std::cout << std::setw(size+10) << dist[j] << ',' << nodes[prev[j]]->name;
					else if(prev[j] != -1 && dist[j] == 1000) std::cout << std::setw(size+13) << "\u221E" << " ";
					else if(dist[j] != 1000) std::cout << std::setw(size+10) << dist[j];
					else std::cout << std::setw(size+13) << "\u221E" << " ";

				}
				std::cout << std::endl;
		}

		~Graph(){
			for(int i = 0; i < size; i++) delete[] adj_matrix[i];
			delete[] adj_matrix;
			for(int i = 0; i < size; i++) delete nodes[i];
		}
	private:
		

};

int main(){
	Graph g(7);

	//tuvwxyz
	std::vector<int> tVals = {0,   2,   4,   999, 999, 7,   999};
	std::vector<int> uVals = {2,   0,   3,   3,   999, 999, 999};
	std::vector<int> vVals = {4,   3,   0,   4,   3,   8,   999};
	std::vector<int> wVals = {999, 3,   4,   0,   6,   999, 999};
	std::vector<int> xVals = {999, 999, 3,   6,   0,   6,   8  };
	std::vector<int> yVals = {7,   999, 8,   999, 6,   0,   12 };
	std::vector<int> zVals = {999, 999, 999, 999, 8,   12,  0  };
	
	Node * t = new Node("t", 0);
	Node * u = new Node("u", 1);
	Node * v = new Node("v", 2);
	Node * w = new Node("w", 3);
	Node * x = new Node("x", 4);
	Node * y = new Node("y", 5);
	Node * z = new Node("z", 6);

	g.setValueOfRow(t, 0, tVals);
	g.setValueOfRow(u, 1, uVals);
	g.setValueOfRow(v, 2, vVals);
	g.setValueOfRow(w, 3, wVals);
	g.setValueOfRow(x, 4, xVals);
	g.setValueOfRow(y, 5, yVals);
	g.setValueOfRow(z, 6, zVals);

	g.djikstra(t);


	Graph g2(6);
	
	//uvwxyz
	std::vector<int> uVals2 = {0,   8,   8,   6,   999, 999};
	std::vector<int> vVals2 = {8,   0,   1,   4,   999, 999};
	std::vector<int> wVals2 = {8,   1,   0,   2,   6,   1  };
	std::vector<int> xVals2 = {6,   4,   2,   0,   9,   999};
	std::vector<int> yVals2 = {999, 999, 6,   9,   0,   9  };
	std::vector<int> zVals2 = {999, 999, 1,   999, 9,   0  };
	
	Node * u2 = new Node("u", 0);
	Node * v2 = new Node("v", 1);
	Node * w2 = new Node("w", 2);
	Node * x2 = new Node("x", 3);
	Node * y2 = new Node("y", 4);
	Node * z2 = new Node("z", 5);

	g2.setValueOfRow(u2, 0, uVals2);
	g2.setValueOfRow(v2, 1, vVals2);
	g2.setValueOfRow(w2, 2, wVals2);
	g2.setValueOfRow(x2, 3, xVals2);
	g2.setValueOfRow(y2, 4, yVals2);
	g2.setValueOfRow(z2, 5, zVals2);

	g2.djikstra(u2);

	Graph g3(6);
	
	//uvwxyz
	std::vector<int> uVals3 = {0,   7,   8,   3,   999, 999};
	std::vector<int> vVals3 = {7,   0,   5,   2,   999, 999};
	std::vector<int> wVals3 = {8,   5,   0,   9,   1,   2  };
	std::vector<int> xVals3 = {3,   2,   9,   0,   8,   999};
	std::vector<int> yVals3 = {999, 999, 1,   8,   0,   6  };
	std::vector<int> zVals3 = {999, 999, 2,   999, 6,   0  };
	
	Node * u3 = new Node("u", 0);
	Node * v3 = new Node("v", 1);
	Node * w3 = new Node("w", 2);
	Node * x3 = new Node("x", 3);
	Node * y3 = new Node("y", 4);
	Node * z3 = new Node("z", 5);

	g3.setValueOfRow(u3, 0, uVals3);
	g3.setValueOfRow(v3, 1, vVals3);
	g3.setValueOfRow(w3, 2, wVals3);
	g3.setValueOfRow(x3, 3, xVals3);
	g3.setValueOfRow(y3, 4, yVals3);
	g3.setValueOfRow(z3, 5, zVals3);

	g3.djikstra(u3);


	
}