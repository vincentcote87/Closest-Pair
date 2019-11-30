#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <regex>

using namespace std;

struct Point {
    int id;
    int x;
    int y;
};

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
    if (closestPair[0] > -1 && closestPair[1] > -1) {
        vector<Point> closest;
        closest.push_back(points[closestPair[0]]);
        closest.push_back(points[closestPair[1]]);
        return closest;
    } else {
        throw runtime_error("Something went wrong");
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout<<"Please pass in an input size ie. ./bruteforce 100"<<endl;
        return 0;
    }

    vector<Point> allPoints;
    string line;
    regex expression("(.*),(.*)");
    smatch coordinates;
    Point p;
    int index = 0;

    // Read from file and push onto points vector
    ifstream myFile ("./pointsData/Output" + to_string(atoi(argv[1])) + ".txt");
    if (myFile.is_open()) {
        while (getline (myFile,line)) {
            if(regex_search(line, coordinates, expression)) {
                p.id = index;
                p.x = stoi(coordinates[1]);
                p.y = stoi(coordinates[2]);
                allPoints.push_back(p);
            }
            index++;
        }
        myFile.close();
    } else {
        cout<<"File not found"<<endl;
        return 0;
    }

    vector<Point> closest = closestPair(allPoints);
    Point p1 = allPoints[closest[0].id];
    Point p2 = allPoints[closest[1].id];
    cout<<"The two closest points are:"<<endl;
    cout<<"  Point 1 = ("<<p1.x<<","<<p1.y<<")"<<endl;
    cout<<"  Point 2 = ("<<p2.x<<","<<p2.y<<")"<<endl;

    return 0;
}