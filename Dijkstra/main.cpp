#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<ctime>

std::vector<int> dijkstra(std::vector<std::vector<int>> &distanceTable)
{
    int at;
    std::vector<int> prev(distanceTable.size());
    std::map<int,int> ensemble;
    
    
    for(int i=0;i<distanceTable.size();i++){
        ensemble.insert(std::pair<int,int>(i, 1e5));
    }
    ensemble[0]=0;
    while(ensemble.size()!=0){
        auto nodeItr = min_element(ensemble.begin(),ensemble.end(),[&](std::pair<int, int> lhs,std::pair<int, int> rhs){
            return lhs.second < rhs.second;
        });
        at = nodeItr->first;
        for(int i=0;i<distanceTable[at].size();i++){
            if(ensemble.find(i)!=ensemble.end() && distanceTable[at][i]!=0){
                if(ensemble[i] > ensemble[at]+distanceTable[at][i]){
                    ensemble[i] = ensemble[at]+distanceTable[at][i];
                    prev[i] = at;
                }
            }
        }
        ensemble.erase(nodeItr);
    }
    return prev;
}

std::vector<int> dijkstra_withPriority(std::vector<std::vector<int>> &distanceTable)
{
    int at;
    std::vector<int> prev(distanceTable.size());
    std::priority_queue<std::pair<int,int>> ensemble;
    std::map<int,int> graph;
    
    for(int i=0;i<distanceTable.size();i++){
        graph.insert(std::pair<int,int>(i, 1e5));
    }
    
    graph[0]=0;
    
    ensemble.push(std::pair<int,int>(0,0));
    
    while(ensemble.size()!=0){
        at = ensemble.top().first;
        ensemble.pop();
        for(int i=0;i<distanceTable[at].size();i++){
            if(distanceTable[at][i]!=0){
                if(graph[i] > graph[at] + distanceTable[at][i]){
                    graph[i] = graph[at] + distanceTable[at][i];
                    prev[i] = at;
                    ensemble.push(std::pair<int,int>(i,graph[i]));
                }
            }
        }
    }
    return prev;
}

int main(){
    const int node_num=11;
    const int target = 10;
    std::vector<int> prev;
    std::vector<std::vector<int>> distanceTable(node_num,std::vector<int>(node_num));
    distanceTable[0]={0,7,6,0,0,0,0,0,0,0,0};
    distanceTable[1]={7,0,0,5,0,0,0,0,0,0,0};
    distanceTable[2]={6,0,0,2,3,0,1,0,15,0,0};
    distanceTable[3]={0,5,2,0,5,0,0,0,0,24,0};
    distanceTable[4]={0,0,3,5,0,8,0,0,0,0,0};
    distanceTable[5]={0,0,0,0,8,0,2,7,0,0,0};
    distanceTable[6]={0,0,1,0,0,2,0,0,9,0,0};
    distanceTable[7]={0,0,0,0,0,7,0,0,0,5,0};
    distanceTable[8]={0,0,15,0,0,0,9,0,0,5,0};
    distanceTable[9]={0,0,0,24,0,0,0,5,5,0,1};
    distanceTable[10]={0,0,0,0,0,0,0,0,0,1,0};
    
    std::clock_t time = std::clock();
    prev = dijkstra(distanceTable);
    std::cout << "Dijkstra " << static_cast<double>( std::clock() - time )/1e3 << "[ms]" << std::endl;
    time = std::clock();
    prev = dijkstra_withPriority(distanceTable);
    std::cout << "Dijkstra with Priority_queue " << static_cast<double>( std::clock() - time )/1e3 << "[ms]" << std::endl;
    
    int at=target;
    while(true){
        std::cout << at << ' ';
        if(at==0)break;
        at = prev[at];
    }
    
}
