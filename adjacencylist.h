#ifndef PROJECT2_PAGERANK_ADJACENCYLIST_H
#define PROJECT2_PAGERANK_ADJACENCYLIST_H

using namespace std;

class AdjacencyList {
private:
    unordered_map<string, vector<string>> inDegreeMap;
    // Using a map to have alphabetical sorted output.
    map<string, pair<double, vector<string>>> pagesOut;

public:
    AdjacencyList() {};
    ~AdjacencyList() {};
    void insert(string from, string to);
    void PageRank(int n);
    void print();
};

void AdjacencyList::insert(string from, string to) {
    // Credit to the Module 8a slide 56, adjacency list implementation
    inDegreeMap[to].push_back(from);
    if (inDegreeMap.find(from) == inDegreeMap.end())
        inDegreeMap[from] = {};
    // Same process for outDegree storage as the inDegree storage
    pagesOut[from].second.push_back(to);
    if (pagesOut.find(to) == pagesOut.end())
        pagesOut[to] = {};
}

void AdjacencyList::PageRank(int n){
    //establish initial rank
    for (auto & it : inDegreeMap) {
        pagesOut[it.first].first = 1.0 / (double)pagesOut.size();
    }

    for (int i = 1; i < n; i++) {
        // use a temp map for storing all final results.
        // rank that are stored in pagesOut are used within the below for loop
        // temp insures that the ranks aren't meddled in intermediate calculations
        unordered_map<string, double> temp;
        // For loop to find the rank of each page.
        for (auto & it : pagesOut) {
            string curr = it.first;

            //calculate ranks

            // using the map that stores the incoming vertices for the associated index
            vector<string> incomingVertices = inDegreeMap[curr];
            double currRank = 0.0;
            for (string incomingVertex : incomingVertices) {
                // formula from the Project 2 overview slideshow, rank(vertex V) = sum(rank(vertex i)/outdegree(node i))
                currRank += pagesOut[incomingVertex].first * (1.0 / (double)pagesOut[incomingVertex].second.size());
            }
            temp[curr] = currRank;
        }
        // Populate the rank map with the final ranks after all iterations of the above for loop
        for (auto & it : temp) {
            pagesOut[it.first].first = it.second;
        }
    }
}

void AdjacencyList::print() {
    // Sets precision to two fixed decimal positions
    for (auto & it : pagesOut) {
        cout << it.first << " ";
        cout << setprecision(2) << fixed << pagesOut[it.first].first << endl;
    }
}

#endif //PROJECT2_PAGERANK_ADJACENCYLIST_H
