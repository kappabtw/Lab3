#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FiniteAutomaton {
private:
    vector<string> states;
    vector<string> alphabet;
    vector<vector<string>> transitionMatrix;
    string startState;

public:
    FiniteAutomaton(const vector<string>& states, const vector<string>& alphabet,
                    const vector<vector<string>>& transitionMatrix, const string& startState)
        : states(states), alphabet(alphabet), transitionMatrix(transitionMatrix), startState(startState) {}

    void isReachable(const string& inputString, const vector<string>& targetStates) {
        vector<string> lexemes;
        size_t stringIndex = 0;

        while (stringIndex < inputString.length()) {
            bool isSymbolFound = false;

            for (const auto& symbol : alphabet) {
                if (inputString.compare(stringIndex, symbol.length(), symbol) == 0) {
                    lexemes.push_back(symbol);
                    stringIndex += symbol.length();
                    isSymbolFound = true;
                    break;
                }
            }

            if (!isSymbolFound) {
                cerr << "Error: Invalid input string" << endl;
                return;
            }
        }

        string currentState = startState;

        for (const auto& lexeme : lexemes) {
            auto stateIterator = find(states.begin(), states.end(), currentState);
            auto symbolIterator = find(alphabet.begin(), alphabet.end(), lexeme);

            if (stateIterator == states.end() || symbolIterator == alphabet.end()) {
                cerr << "Error: Invalid state or symbol" << endl;
                return;
            }

            auto stateIndex = distance(states.begin(), stateIterator);
            auto symbolIndex = distance(alphabet.begin(), symbolIterator);

            currentState = transitionMatrix[stateIndex][symbolIndex];

            stateIterator = find(states.begin(), states.end(), currentState);
            if (stateIterator == states.end()) {
                cerr << "Error: Invalid state" << endl;
                return;
            }
        }

        if (find(targetStates.begin(), targetStates.end(), currentState) != targetStates.end())
            cout << "Target state reached!" << endl;
        else
            cout << "Target state not reached." << endl;
    }
};

int main() {
    vector<string> states = {"S0", "S1", "S2"};
    vector<string> alphabet = {"A", "B"};
    vector<vector<string>> transitionMatrix = {{"S1", "S0"}, {"S2", "S1"}, {"S0", "S2"}};
    string startState = "S0";
    vector<string> targetStates = {"S2"};

    FiniteAutomaton autom(states, alphabet, transitionMatrix, startState);
    autom.isReachable("AAB", targetStates);
    autom.isReachable("BA", targetStates);
    autom.isReachable("BAA", targetStates);
    autom.isReachable("AB", targetStates);
    return 0;
}
