/*
Finding the shortest path
*/

#include <iostream>
#include <vector>

using namespace std;



int main(){

    //first - number, second - length
    vector<vector<pair<int, int>>> graph(5);

    graph[0].push_back(make_pair(1, 5));
    graph[0].push_back(make_pair(2, 30));
    graph[0].push_back(make_pair(4, 100));
    graph[1].push_back(make_pair(2, 20));
    graph[2].push_back(make_pair(3, 20));
    graph[3].push_back(make_pair(4, 8));
    graph[4].push_back(make_pair(0, 100));
    

    int colors[5] {};
    int lengths[5] {};
    for (int i = 1; i < 5; i++) lengths[i] = INT16_MAX;
    
    vector<int> queue;

    //adding starting point
    queue.push_back(0);
    

    int queueLen = queue.size();
    for (int i = 0; i < queueLen; i++){
                
        colors[queue[i]] = 2;
        for (int j = 0; j < graph[queue[i]].size(); j++){
            
            lengths[graph[queue[i]][j].first] = min(lengths[graph[queue[i]][j].first], lengths[queue[i]] + graph[queue[i]][j].second);
            if (colors[graph[queue[i]][j].first] == 0){
                colors[graph[queue[i]][j].first] = 1;
                queue.push_back(graph[queue[i]][j].first);
            }
                   
        }

        if (i + 1 == queueLen){
            for (int x = 0; x < queueLen; x++){
                queue.erase(queue.begin());
            }

            for (auto x: queue){
                cout << x << " ";
            }
            cout << endl;   
            i = -1;
            queueLen = queue.size();
        }
    }

    //printing minimal possible distance from starter point to each point
    for (auto i : lengths){
        cout << i << " ";
    }
    
    
    

    return 0;
}