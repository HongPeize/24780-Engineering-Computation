//  Course name: Engineering Computation
//
//  Created by Peize Hong on 1/9/2022.
//this program can approximate the Pi value by using square addition
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main() {
    double x = 0.0;
    double dx_list[3] = {0.001, 0.0001, 0.00001}; //a list of dx
    double y = 0.0;
    double dx;
    double radius = 1.0;
    double area;
    double pi;
    double diff;

    for (int i = 0; i < 3; i++){
        dx = dx_list[i]; //dx will not change in loop
        while (sqrt(x*x+y*y) < radius){ //float/double comparision is not trustworthy
            while (sqrt(x*x+y*y) < radius){ 
                area += 1;
                x += dx; //x direction increment
            }
            x = 0.0;
            y += dx; //y direction increment
        }
        /*if (i==1){
            area -= 4;
        }
        */
        pi = 4*area*dx*dx/radius/radius;
        diff = (M_PI - pi)/M_PI * 100;
        cout << "Pi: " << setprecision(10) << pi << endl;
        cout << "Percentage Error: " << setprecision(10) << diff << "%" << endl;
        area = 0.0;
        y = 0.0;
    }
    return 0;
}
