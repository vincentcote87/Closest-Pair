#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    vector<int> points;
    ofstream outFile;

    int numberOfPoints;

    for (int i = 1; i < argc; ++i) {
        numberOfPoints = atoi(argv[i]);
        outFile.open("./pointsData/Output" + to_string(numberOfPoints) + ".txt");

        srand(std::time(nullptr));
        for (int i = 0; i < numberOfPoints; i++) {
            outFile << rand() % 20000 - 10000 << "," << rand() % 20000 - 10000 << endl;
        }
        outFile.close();
    }
    return 0;
}
