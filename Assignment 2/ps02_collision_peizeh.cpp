/*  
Course name: Engineering Computation
Created by Peize Hong on 9/12/2022
This program takes user's estimation of final velocity Vax, VAy, VBx, VBy and compare with correct answer and come out percentage error
*/
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;

void userinput(double &velAx2, double &velAy2, double &velBx2, double &velBy2){
    cout << "Enter your final velocity of object A in x-direction>> ";
    cin >> velAx2;
    cout << "Enter your final velocity of object A in y-direction>> ";
    cin >> velAy2;
    cout << "Enter your final velocity of object B in x-direction>> ";
    cin >> velBx2;
    cout << "Enter your final velocity of object B in y-direction>> ";
    cin >> velBy2;
}

int main(void){

    //Generate random parameters
    srand(time(NULL)); 
    double massA = (5 + (rand() % 36))/10.0;
    double massB = (5 + (rand() % 36))/10.0;
    double thetaA1 = -60 + (rand() % 121);
    double thetaB1 = -60 + (rand() % 121);
    double velA1 = (0.0 + (rand() % 51))/10.0;
    double velB1 = (0.0 + (rand() % 51))/10.0; 
    double eRes = (60 + (rand() % 31))/100.0;
    // print out random parameters
    cout << "←: -x direction, →: +x direction" << endl;
    cout << "Mass A: " << massA << "kg, Mass B: " << massB << "kg" << endl;
    cout << "Theta A: " << thetaA1 << "deg, Theta B: " << thetaB1 << "deg" << endl;
    cout << "Velocity A: " << velA1 << "m/s →, Velocity B: " << velB1 << "m/s ←" << endl;
    cout << "Restitution: " << eRes << endl;

    velB1 = -velB1; //consider directions
    //take user's input
    double velAx2, velAy2, velBx2, velBy2;
    userinput(velAx2, velAy2, velBx2, velBy2);

    //Start to calculate actual final velocity
    double Vel_A1_x = velA1 * cos(M_PI*thetaA1/180.0), Vel_A1_y = velA1 * sin(M_PI*thetaA1/180.0),
    Vel_B1_x = velB1 * cos(M_PI*thetaB1/180.0), Vel_B1_y = velB1 * sin(M_PI*thetaB1/180.0);

    // Solve A&B final velocity magnitude in x direction
    double res1 = massA * Vel_A1_x + massB * Vel_B1_x;
    double res2 = eRes * (Vel_A1_x - Vel_B1_x);
    double determinant = massA*1.0 - massB*-1.0;
    double analytical_velAx2 = (res1*1.0 - massB*res2)/determinant;
    double analytical_velBx2 = (massA*res2 - res1*-1.0)/determinant;
    // Solve A&B final velocity magnitude in y direction
    double analytical_velAy2 = Vel_A1_y;
    double analytical_velBy2 = Vel_B1_y;
    //cout << res1 << " " << res2 << " " << determinant << endl;
    cout << "Correct V_Ax2: " << analytical_velAx2 << "m/s, Correct V_Ay2: " << analytical_velAy2 << "m/s, Correct V_Bx2: " << analytical_velBx2  << "m/s, Correct V_By2: " << analytical_velBy2 << "m/s" << endl;

    //compare the error
    double error_Ax = (analytical_velAx2 - velAx2)*100.0/analytical_velAx2, error_Ay = (analytical_velAy2 - velAy2)*100.0/analytical_velAy2, 
    error_Bx = (analytical_velBx2 - velBx2)*100.0/analytical_velBx2, error_By = (analytical_velBy2 - velBy2)*100.0/analytical_velBy2;
    // print out result
    cout << "Error Ax: " << error_Ax << "%, Error Ay: " <<  error_Ay << "%, Error Bx: " << error_Bx << "%, Error By: " << error_By << "%" << endl;
    return 0;
}