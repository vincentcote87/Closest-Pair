#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cmath>

using namespace std;

struct Point {
    int id;
    int x;
    int y;
};

void create(int n) {
    vector<int> points;
    ofstream outFile;
    outFile.open("./Output" + to_string(n) + ".txt");

    srand(std::time(nullptr));
    for (int i = 0; i < n; i++) {
        outFile << rand() % 20000 - 10000 << "," << rand() % 20000 - 10000 << endl;
    }
    outFile.close();
}

// Brute force approach
vector<Point> closestPair(vector<Point> points) {
    double shortestDist = 250000.0;
    int closestPair[2] = {-1,-1};
    for (int i = 0; i < points.size() - 1; i++) {
        for (int j = i + 1; j < points.size(); j++) {
            int x = points[i].x - points[j].x;
            int y = points[i].y - points[j].y;
            double dist = sqrt((x*x) + (y*y));
            if (dist < shortestDist) {
                shortestDist = dist;
                closestPair[0] = points[i].id;
                closestPair[1] = points[j].id;
            }
        }
    }
    vector<Point> closest;
    closest.push_back(points[closestPair[0]]);
    closest.push_back(points[closestPair[1]]);
    return closest;
}

int main() {

    // TODO pull points from file
    // TODO reconsider how things are passed around
    // TODO add testing
    Point p1;
    p1.id = 0;
    p1.x = 12;
    p1.y = 6;

    Point p2;
    p2.id = 1;
    p2.x = 14;
    p2.y = 12;

    Point p3;
    p3.id = 2;
    p3.x = 8;
    p3.y = 4;

    vector<Point> allPoints;
    allPoints.push_back(p1);
    allPoints.push_back(p2);
    allPoints.push_back(p3);

    vector<Point> closest = closestPair(allPoints);
    cout<<closest[0].id<<", "<<closest[1].id<<endl;
//    create(100);
    return 0;
}