#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <utility> 


#define WHITE  0
#define GREY   1
#define BLACK  2
#define INFINITY  -1
 

using namespace std;

map<string, int, std::less<string> > citiesIndexMap;
vector< map<int, int>* > neighboorhood;
	
//implements dijkstra
int getCost(int source, int dest, int numberOfCities) {
	
	vector<int> color(numberOfCities);
	vector<int> costs(numberOfCities);
	vector<int> node2visit;
	
	for (int i = 0; i < numberOfCities; i++) {
		color[i] = WHITE;
		costs[i] = INFINITY;
	}
	
	costs[source] = 0;
	
	node2visit.push_back(source);
	color[source] = GREY;
	
	while (node2visit.size() > 0) {
		
		//get the minimum SLOWLY
		for(int i = 1; i < node2visit.size(); i++) {
			if (costs[node2visit[i-1]] < costs[node2visit[i]]) {
				int temp = node2visit[i-1];
				node2visit[i-1] = node2visit[i];
				node2visit[i] = temp;
			}
		}
		int node = node2visit.back();
		node2visit.pop_back();
		
		if (node == dest){
			//found cheapest path!
			break;
		}
		
		int cost = costs[node];
		
    	map<int,int>::const_iterator end = neighboorhood[node]->end(); 
		for (map<int,int>::const_iterator it = neighboorhood[node]->begin(); it != end; ++it)
		{
			switch (color[it->first]) {
				case BLACK:
					break;
				case WHITE:
					node2visit.push_back(it->first);
					color[it->first] = GREY;
				case GREY:
					//set cost
					costs[it->first] = ( costs[it->first] == INFINITY || costs[it->first] > cost + it->second  ? cost + it->second : costs[it->first]);
			}
		}
		color[node] = BLACK;
	}	
	return costs[dest]; 
}


int main ()
{
	int numberOfTests, numberOfCities, numberOfPaths, numberOfNeighbours, neighbour, cost;
		
	string source, destination;
		
    cin >> numberOfTests;
	
	while (numberOfTests--)
    {
		cin >> numberOfCities;
		
		for( int index = 0; index < numberOfCities; index++){
			
			//store city - index reference
			cin >> source;
			citiesIndexMap.insert( pair<string,int>(source,index) );
		
			//read neighboors
			cin >> numberOfNeighbours;
			
			neighboorhood.push_back(new map<int, int>);
			
			while(numberOfNeighbours--){
				cin >> neighbour >> cost;
				neighboorhood[index]->insert( pair<int, int>(neighbour-1, cost));				
 			}
		}
		
		cin >> numberOfPaths;
		while ( numberOfPaths-- ) {
			cin >> source >> destination;
			printf("%d\n", getCost(citiesIndexMap[source], citiesIndexMap[destination], numberOfCities));
		}
				
		//free memory
		for( int index = 0; index < numberOfCities; index++){
			delete neighboorhood[index];			
		}		
		citiesIndexMap.clear();
		neighboorhood.clear();
		
    }
    return 0;
};