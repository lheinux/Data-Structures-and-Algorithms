#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<string> ci = {"apples", "bananas", "oranges", "pears"};
    vector<string> shipment = {"kiwis", "bananas", "grapes"};

    auto printVector = [](const vector<string>& vec) {
        cout << "[";
        for (const auto& item : vec) cout << "\"" << item << "\", ";
        cout << "]\n";
    };

    cout << "Current Inventory: ";
    printVector(ci);
    cout << "Shipment: ";
    printVector(shipment);

    vector<string> so;
    for (const auto& item : ci)
        if (find(shipment.begin(), shipment.end(), item) == shipment.end())
            so.push_back(item);

    cout << "Sold-out items: ";
    printVector(so);

    vector<string> updated_in = shipment;
    for (const auto& item : ci)
        if (find(so.begin(), so.end(), item) == so.end())
            updated_in.push_back(item);

    cout << "Updated Inventory: ";
    printVector(updated_in);

    return 0;
}