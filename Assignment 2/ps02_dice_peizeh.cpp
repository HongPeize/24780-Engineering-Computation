/*  
Course name: Engineering Computation
Created by Peize Hong on 9/9/2022
This program takes user's input (number of rolls they want to model) and simulate the dice rolling. Each time will come out 2 value (1<=x<=6,1<=y<=6) and we need to add them together. The program will calculate the frequcney of each occurance and calculate the possibility of each occurance.
*/

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>

using namespace std;

int userinput(){ //take user's input
    int roll_time;
    cout << "Enter number of rolls >> ";
    cin >> roll_time;
    return roll_time;
}

void result(){
    int dice1, dice2, res, roll_time; 
    roll_time = userinput(); //get how many time should roll
    
    // get a full rolling result: freq dictionary
    map<int,int> freq;
    for (int i=2; i<13;i++){ //initialize the dictionary
        freq[i]=0;
    }
    int i;
    srand(time(NULL)); //generate seed
    while (i < roll_time){
        dice1=rand()%6+1;
        dice2=rand()%6+1;
        res = dice1 + dice2; //combine result
        freq[res]++;
        i++;
    }

    printf("Frequency of each number:\n");
    for (int k=2; k < 13; k++){
        cout << k << ": ";
        int a = 0;
        for (a; a < freq[k]; a++){
            cout <<  "o";
        }
        cout << endl;
    }
}

int main(void){
    
    result();
    
}