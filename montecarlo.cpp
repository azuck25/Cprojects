#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <cmath>
using namespace std;

//This program is a multithreaded estimate of PI using the Monte Carlo Method
//First we define 1000 random points of (x,y) within a range of -1 to 1 as an array type data structure in the global block
//Next using the Pathagorean Theorem we find the distance from the center point (0,0)
//If the distance from the center is less than the radius the point lies within the circle
//To estimate PI we use the formula PI = 4 * (Number of points in Circle / Number of points outside of Circle)

//Thread Parameters defined as a data structure to pass into the threaded functions 
struct ThreadParam{
    int count_inCircle = 0;
    float radius = 1.0;
    const int totalPoints = 1000;
};

//An array of points defined using a constructor
struct Point{
    float x;
    float y;

    Point(float x_value = 0, float y_value = 0) : x(x_value), y(y_value) {}
};
//Points array with a size of 1000
Point points_array[1000];


//This function generates the random points between -1 and 1 and calculates the distance of the set from the center
void* generateRandom(void* param){
    //Because threaded functions assume the data type of void we pass the ThreadedParameters to function with a pointer to the address space of the data structure
    //The param arguement is casted to the data structure ThreadParam
    //The arrow notation to point back to the data structures members 
    ThreadParam* parameter = (ThreadParam*) param;
    //We then seed the random number generator with the current time to get a quality set of random numbers
    srand((unsigned int)time(NULL));
    for(int i = 0; i < parameter->totalPoints; i++){
        //To create a decimal we represent the random number generated as a percentage of the max possible number generated
        //The formula decimal = 2 * x - 1 is used to restrict the range of the random number generator between -1 to 1
        points_array[i].x = 2.0f * ((float) rand()) / (float) RAND_MAX - 1.0f;
        points_array[i].y = 2.0f * ((float) rand()) / (float) RAND_MAX - 1.0f;
    }
    
    for(int i = 0; i < parameter->totalPoints; i++){
        //The Pathegorean Theorem is represented below to compare the distance from the center of the circle to the radius of the circle
        if(sqrtf32(powf32(points_array[i].x,2.00) + powf32(points_array[i].y,2.0)) < parameter->radius){
            parameter->count_inCircle++;
            //Below lines were used to debug
            float c_squared = sqrtf32(powf32(points_array[i].x,2.0) + powf32(points_array[i].y,2.0));
            cout << i + 1 << "  C^2 = " << c_squared <<" : TRUE : (" << points_array[i].x << "," << points_array[i].y << ")" << endl;
        }
    }
    //Used to exit the thread
    pthread_exit(0);
}

void* calculatePI(void *param){
    ThreadParam* parameter = (ThreadParam*) param;
    
    cout << "Count of points within circles radius range[-1.0, 1.0]  :  " << parameter->count_inCircle << endl;

    //We then use the formula PI = 4 * (Number of points in Circle / total number of points)
    float pi_esitmate = (float)4.0 *  ((float)parameter->count_inCircle / (float) parameter->totalPoints);

    cout << "PI Estimate : " << pi_esitmate << endl;


    pthread_exit(0);
}

int main(){
    ThreadParam parameter;
    //Thread ID creation
    pthread_t tid;
    pthread_t tid1;
    //Setting the attributes of the threads to the default settings
    pthread_attr_t attr;
    //Initializing the attributes
    pthread_attr_init(&attr);
    //We pass the data structure parameters as void data type pointing to the memory address of the datastructure holding the variables
    pthread_create(&tid, &attr,generateRandom,(void*)&parameter);
    pthread_join(tid,NULL);
    pthread_create(&tid1,&attr,calculatePI,(void*)&parameter);
    pthread_join(tid1,NULL);
    
    return 0;
};