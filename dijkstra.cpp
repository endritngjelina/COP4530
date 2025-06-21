

/*
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to implement Dijkstra's algorithm
vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        // Find the node with the minimum distance
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        // Update the distances of the neighbors
        for (auto neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (!visited[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

int main() {
    // Define the graph and source node
    int n = 6, source = 0;
    vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 1}, {4, 3}},
        {{2, 2}, {3, 5}, {5, 1}},
        {{3, 1}, {4, 4}, {5, 3}},
        {{4, 2}, {5, 1}},
        {{5, 2}},
        {}
    };

    // Call the Dijkstra's algorithm function to find the shortest distances
    vector<int> distances = dijkstra(graph, source);

    // Print the shortest distances from the source node to all other nodes
    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << (distances[i] == INT_MAX ? "Infinity" : to_string(distances[i])) << "\n";
    }

    return 0;
}
*/
//improved dijkstra

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_map>

// using namespace std;

// #define INF 1e9

// // Function to implement Dijkstra's algorithm
// vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int source) {
//     int n = graph.size();
//     vector<int> dist(n, INF);  // Initialize distances with infinity
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  // Create a min-heap

//     // Set the distance of the source node to 0 and add it to the heap
//     dist[source] = 0;
//     pq.push({0, source});

//     while (!pq.empty()) {
//         // Get the node with the minimum distance from the heap
//         int u = pq.top().second;
//         int d = pq.top().first;
//         pq.pop();

//         // If we've already found a better path, skip this node
//         if (d > dist[u]) continue;

//         // Iterate through the neighbors of the current node
//         for (auto neighbor : graph[u]) {
//             int v = neighbor.first;
//             int weight = neighbor.second;

//             // Check if a shorter path to the neighbor node is found
//             if (dist[v] > dist[u] + weight) {
//                 dist[v] = dist[u] + weight;
//                 pq.push({dist[v], v});
//             }
//         }
//     }

//     return dist;
// }

// int main() {
//     // Define the graph and source node
//     int n = 6, source = 0;
//     vector<vector<pair<int, int>>> graph = {
//         {{1, 4}, {2, 1}, {4, 3}},
//         {{2, 2}, {3, 5}, {5, 1}},
//         {{3, 1}, {4, 4}, {5, 3}},
//         {{4, 2}, {5, 1}},
//         {{5, 2}},
//         {}
//     };

//     // Call the Dijkstra's algorithm function to find the shortest distances
//     vector<int> distances = dijkstra(graph, source);

//     // Print the shortest distances from the source node to all other nodes
//     cout << "Shortest distances from source " << source << ":\n";
//     for (int i = 0; i < n; i++) {
//         cout << "Node " << i << ": " << (distances[i] == INF ? "Infinity" : to_string(distances[i])) << "\n";
//     }

//     return 0;
// }

/*
priority_queue
    pair<int, int>,                 // Type of elements
    vector<pair<int, int>>,         // Container type
    greater<pair<int, int>>         // Comparison function
> pq;*/
// #include <vector>
// #include <iostream>
// #include <queue>
// using namespace std;

// int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
//     // Create the adjacency list
//     vector<vector<pair<int, int>>> graph(n);
//     for (auto& flight : flights) {
//         graph[flight[0]].emplace_back(flight[1], flight[2]);
//     }

//     // Perform modified Dijkstra's algorithm
//     priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
//     vector<vector<int>> dist(n, vector<int>(k + 2, INT_MAX));

//     dist[src][0] = 0;
//     pq.emplace(0, src, 0);

//     while (!pq.empty()) {
//         int d, u, stops;
//         tie(d, u, stops) = pq.top();
//         pq.pop();

//         if (u == dst)
//             return d;

//         if (stops > k + 1)
//             continue;

//         for (auto& neighbor : graph[u]) {
//             int v = neighbor.first;
//             int w = neighbor.second;

//             if (dist[v][stops + 1] > dist[u][stops] + w) {
//                 dist[v][stops + 1] = dist[u][stops] + w;
//                 pq.emplace(dist[v][stops + 1], v, stops + 1);
//             }
//         }
//     }

//     return -1;
// }

// int main() {
//     int n = 4;
//     vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
//     int src = 0, dst = 3, k = 1;

//     int result = findCheapestPrice(n, flights, src, dst, k);
//     cout << "Cheapest Price: " << result << endl;

//     return 0;
// }

/*
Explanation:
Cheapest Flights Within K Stops-
We first create the adjacency list graph to represent the weighted, directed graph of flights.
We then perform a modified version of Dijkstra's algorithm using a priority queue pq. Instead of just keeping 
track of the distance to each node, we also keep track of the number of stops in the current path.
The priority queue stores tuples (d, u, stops), where d is the total cost of the path, 
u is the current node, and stops is the number of stops in the current path.
We initialize the distance dist[src][0] to 0 and add the source node to the priority queue.
In the main loop, we pop the tuple with the minimum total cost from the priority queue.
 If the current node is the destination node, we return the total cost.
If the number of stops in the current path is greater than k + 1, 
we skip the current node as we are not interested in paths with more than k stops.
For each neighbor of the current node, we update the distance dist[v][stops + 1] 
if the new path is cheaper than the current path, and add the new path to the priority queue.
If the priority queue becomes empty and we haven't found the destination node, 
we return -1 to indicate that no path within k stops exists.
In the main() function, we provide an example input and call the findCheapestPrice() function to get the result.
*/




vector<int> shortestPath(vector<vector<int>>& edges, int n, int source, int target) {
    // Create the adjacency list
    vector<vector<pair<int, int>>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].emplace_back(edge[1], edge[2]);//more efficient version of push_back
        graph[edge[1]].emplace_back(edge[0], edge[2]);
    }

    // Perform Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);

    dist[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue;

        if (u == target)
            break;

        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int curr = target;
    while (curr != -1) {
        path.push_back(curr);
        curr = prev[curr];
    }
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    vector<vector<int>> edges = {{0, 1, 5}, {1, 2, 5}, {0, 3, 2}, {3, 2, 1}, {3, 4, 3}, {4, 2, 1}};
    int n = 5;
    int source = 0;
    int target = 2;

    vector<int> result = shortestPath(edges, n, source, target);
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
/*
Explanation:
Shortest Path in a Weighted, Undirected Graph given source and destination-
We first create the adjacency list graph to represent the weighted, undirected graph.
We then perform Dijkstra's algorithm using a priority queue pq. The priority queue stores pairs (d, u), where d is the total cost of the path and u is the current node.
We initialize the distance dist[source] to 0 and add the source node to the priority queue.
In the main loop, we pop the pair with the minimum total cost from the priority queue. If the total cost of the current path is greater than the distance to the current node, we skip the current node as it cannot be part of the shortest path.
If the current node is the target node, we break out of the loop.
For each neighbor of the current node, we update the distance dist[v] if the new path is shorter than the current path, and add the new path to the priority queue.
After the loop, we reconstruct the shortest path by tracing back from the target node using the prev vector, which stores the previous node in the shortest path.
Finally, we return the path vector containing the nodes in the shortest path.
*/
