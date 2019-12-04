#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cmath>
#include <cfloat>

using namespace std;

struct Point {
    int id = -1;
    int x = INT32_MAX;
    int y = INT32_MAX;
};

struct Pair {
    Point p1;
    Point p2;
    double dist = FLT_MAX;
};

Pair closestPair(vector<Point> points);
Pair closest(vector<Point> points);
Pair bruteforce(vector<Point> points);
double distance(Point a, Point b);
int partition(vector<Point> &points, int low, int high, char direction);
void quickSort(vector<Point> &points, int low, int high, char direction);
void sortPoints(vector<Point> &points, char direction);


int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout<<"Please pass in an input size ie. ./divideconquer 100"<<endl;
        return 0;
    }

    vector<Point> allPoints;
    string line;
    Point p;
    int index = 0;

    // Read from file and push onto points vector
    ifstream myFile ("./pointsData/Output" + to_string(atoi(argv[1])) + ".txt");
    if (myFile.is_open()) {
        while (getline (myFile,line)) {
            int i = 0;
            string s1, s2 = "";
            while (line[i] != ',') {
                s1 += line[i];
                i++;
            }
            i++; // Skip the ','
            while (i < line.length()) {
                s2 += line[i];
                i++;
            }
            if (s1.length() > 0 && s2.length() > 0) {
                p.id = index;
                p.x = stoi(s1);
                p.y = stoi(s2);
                allPoints.push_back(p);
                index++;
            }
        }
        myFile.close();
    } else {
        cout<<"File not found, did you run ./create <number>?"<<endl;
        return 0;
    }

    Pair closestPointsPair;
    if (allPoints.size() > 1) {
        closestPointsPair = closestPair(allPoints);
        cout<<"The closest pairs are points:"<<endl;
        cout<<"  P1 = ("<<closestPointsPair.p1.x<<","<<closestPointsPair.p1.y<<")"<<endl;
        cout<<"  P2 = ("<<closestPointsPair.p2.x<<","<<closestPointsPair.p2.y<<")"<<endl;
        cout<<"They are "<<closestPointsPair.dist<<" appart"<<endl;
    } else {
        cout<<"The file was read but not data was extracted"<<endl;
    }

    return 0;
};

Pair closestPair(vector<Point> points) {
    sortPoints(points, 'x');
    return closest(points);
};

Pair closest(vector<Point> points) {
    if (points.size() <= 3)
        return bruteforce(points);

    int half = points.size()/2;
    int c = (points[half - 1].x + points[half].x)/2;
    vector<Point> left(points.begin(), points.begin() + half);
    vector<Point> right(points.begin() + half, points.end());
    Pair dLeft;
    dLeft = closest(left);
    Pair dRight;
    dRight = closest(right);
    Pair min;
    min = dLeft.dist < dRight.dist ? dLeft : dRight;

    vector<Point> borderPoints;
    for (int i = 0; i < points.size(); i++) {
        if (abs(points[i].x - c) < min.dist)
            borderPoints.push_back(points[i]);
    }

    sortPoints(borderPoints, 'y');
    for (int i = 0; i < borderPoints.size(); i++) {
        for (int j = i+1; j < borderPoints.size() && (borderPoints[j].y - borderPoints[i].y) < min.dist; j++) {
            if (distance(borderPoints[i], borderPoints[j]) <= min.dist) {
                min.p1 = borderPoints[i];
                min.p2 = borderPoints[j];
                min.dist = distance(borderPoints[i], borderPoints[j]);
            }
        }
    }

    return min;
};

Pair bruteforce(vector<Point> points) {
    double shortestDist = FLT_MAX;
    double dist;
    Pair shortestPair;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i+1; j < points.size(); j++) {
            dist = distance(points[i], points[j]);
            if (dist < shortestDist) {
                shortestDist = dist;
                shortestPair.p1 = points[i];
                shortestPair.p2 = points[j];
                shortestPair.dist = dist;
            }
        }
    }
    return shortestPair;
};

double distance(Point a, Point b) {
    int x = a.x - b.x;
    int y = a.y - b.y;
    return sqrt((x*x) + (y*y));
};

int partition(vector<Point> &points, int low, int high, char direction) {
    int i = low - 1;
    Point tmp;
    int pivot = tolower(direction) == 'y' ? points[high].y:points[high].x;
    for (int j = low; j <= high - 1; j++) {
        if ((tolower(direction) == 'y' ? points[j].y:points[j].x) <= pivot) {
            i++;
            tmp = points[i];
            points[i] = points[j];
            points[j] = tmp;
        }
    }
    tmp = points[i+1];
    points[i+1] = points[high];
    points[high] = tmp;
    return (i+1);
}

void quickSort(vector<Point> &points, int low, int high, char direction) {
    if (low < high) {
        int partIndex = partition(points, low, high, direction);
        quickSort(points, low, partIndex - 1, direction);
        quickSort(points, partIndex + 1, high, direction);
    }
}

void sortPoints(vector<Point> &points, char direction) {
    int low = 0;
    int high = points.size() - 1;
    quickSort(points, low, high, direction);
};
