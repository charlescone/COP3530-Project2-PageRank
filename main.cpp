#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "adjacencylist.h"

int main() {
    AdjacencyList pages;
    int num, power;
    string from, to;

    cin >> num >> power;
    for (int i = 0; i < num; i++) {
        cin >> from >> to;
        pages.insert(from, to);
    }

    pages.PageRank(power);
    pages.print();

    return 0;
}
