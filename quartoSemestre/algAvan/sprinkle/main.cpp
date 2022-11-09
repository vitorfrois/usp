#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

double computateDelta(double d, double r, double y){
    return pow(2*d, 2.0) - 4*(pow(d, 2.0) + pow(y, 2.0) - pow(r, 2.0));
}

double computateX1(double d, double r, double y){
    double delta = computateDelta(d, r, y);
    if(delta < 0) return -1;
    return ((2*d) - sqrt(delta))/2;
}

double computateX2(double d, double r, double y){
    double delta = computateDelta(d, r, y);
    if(delta < 0) return -1;
    return ((2*d) + sqrt(computateDelta(d, r, y)))/2;
}

typedef struct circle{
    double position;
    double radius;
    double x1;
    double x2;
}Circle;

Circle newCircle(double position, double radius, int width){
    Circle c;
    c.position = position;
    c.radius = radius;
    c.x1 = computateX1(position, radius, (double) width);
    c.x2 = computateX2(position, radius, (double) width); 
    return c;
}

bool compareX(const Circle &a, const Circle &b){
    return a.x2 < b.x2;
}

typedef struct point{
    double x;
    double y;
}Point;


bool checkPoint(Circle c, Point p){
    return (pow(p.x - c.position, 2.0) + pow(p.y, 2.0)) < pow(c.radius, 2.0);
}

int main(){
    int nSprinklers, lenght;
    double width;
    while(cin >> nSprinklers >> lenght >> width){
        double position, radius;
        vector<Circle> vec;
        for(int i = 0; i < nSprinklers; i++){
            cin >> position >> radius;
            if(radius > width/2){
                Circle c = newCircle(position, radius, width/2);
                vec.push_back(c);
            }
        }

        sort(vec.begin(), vec.end(), compareX);
    
        Circle currentCircle;
        Point p; 
        int count;
        int i = vec.size() - 1;
        if(vec.size() > 0){
            currentCircle = vec.back();
            count = 1;
            p.x = lenght; p.y = width/2;
            while(!checkPoint(currentCircle, p) && !vec.empty()){
                vec.pop_back();
                currentCircle = vec.back();
            }
            Point q; q.x = 0; q.y = width/2;
            if(checkPoint(currentCircle, q))
                i = 0;
            if(i == 0 && !checkPoint(currentCircle, q))
                count = -1;
            while(i > 0 && checkPoint(vec[i-1], p)){
                i--;
                if(checkPoint(vec[i-1], p) && checkPoint(vec[i-1], q))
                    i = 0;
            }
            if(vec.empty()) count = -1;            

        }else{  
            count = -1;
        }

        
        while(i > 0){
            if(!checkPoint(currentCircle, p) && currentCircle.position < lenght){
                count = -1;
                break;
            }
            while(i > 0 && vec[i-1].x2 > currentCircle.x1) i--;
            if(i != 0) currentCircle = vec[i];
            p.x = currentCircle.x2;
            count++;
        }   
        cout << count << endl;
    }
    return 0;
}