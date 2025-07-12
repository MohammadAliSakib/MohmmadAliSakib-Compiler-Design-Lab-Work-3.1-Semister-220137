//session 6
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

// Define grammar
unordered_map<string, vector<string>> grammar = {
    {"E", {"T", "E'"}},
    {"E'", {"+T", "ε"}},
    {"T", {"F", "T'"}},
    {"T'", {"*F", "ε"}},
    {"F", {"(E)", "id"}}
};

// Define FIRST and FOLLOW sets
unordered_map<string, unordered_set<string>> first;
unordered_map<string, unordered_set<string>> follow;

// Function to compute FIRST sets
void computeFirst() {
    first["E"].insert("id");
    first["E'"].insert("+");
    first["T"].insert("id");
    first["T'"].insert("*");
    first["F"].insert("(");
    first["F"].insert("id");
}

// Function to compute FOLLOW sets
void computeFollow() {
    follow["E"].insert("$");  // Start symbol follow set
    follow["E'"].insert("$");
    follow["T"].insert(")");
    follow["F"].insert(")", "*");
}

// Function to print FIRST and FOLLOW sets
void printFirstFollow() {
    cout << "FIRST sets:" << endl;
    for (const auto& entry : first) {
        cout << entry.first << ": ";
        for (const auto& symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << endl;
    }

    cout << "FOLLOW sets:" << endl;
    for (const auto& entry : follow) {
        cout << entry.first << ": ";
        for (const auto& symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << endl;
    }
}

int main() {
    computeFirst();  // Compute FIRST sets
    computeFollow(); // Compute FOLLOW sets

    printFirstFollow();  // Print the sets

    // You can implement the LL(1) parsing table here and start parsing.

    return 0;
}
