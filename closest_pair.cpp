// Tyler Price
// Project 1
// ITEC 360
//
#include<stdlib.h> 
#include<stdio.h>
#include <iostream>
#include <math.h>
#include <float.h>
#include <iomanip>
#include <limits.h>
#include <ctime>
#include <cstring>
#include <algorithm>

	struct point{// point struct containing an X and Y coordinate
	long long int x;
	long long int y;
};

point bPoint1, bPoint2;
point dPoint1, dPoint2;
int dCalcs = 0; // number of distance calculations
int calls = 0; // number of calls to the divide and conquer method
int depth = 0; // How Many times the array was divided in divide and conquer

void merge(point arr[], int l, int m, int r, bool sortx);
void mergeSort(point arr[], int l, int r, bool sortx);
void printArray(point A[], int size);
void fillArray(point P[],point Q[],int n);
double dist(point p1, point p2);
double bruteForce(point P[], int n);
double closest(point P[],point Q[],int n);
double stripClosest(point strip[], int size, long int d);

	using namespace std;

int main(int argc, char **argv){
	int n; //length of the array
	double sDist;
	cin >> n;
	point P[n];
	point Q[n];
	fillArray(P,Q,n);// fills the array with data given via command line
	string input;
	if(argv[1] != NULL)//check if given command line arguement
		input = argv[1];

	transform(input.begin(), input.end(), input.begin(), ::tolower);//make command line input case sensitive

	cout << "\nN: " << n <<  endl;
		

	if(input == "brute" || input == "both"){
		sDist = bruteForce(P,n);
		cout << "-------------------BRUTE FORCE--------------------" << endl;//call brute
		cout << setprecision(5) << fixed << "\nPoint 1: (" 
		<< bPoint1.x << ", " << bPoint1.y << ")"
		<< " \nPoint 2: " << "(" << bPoint2.x << ", " << bPoint2.y << ")"
		<< " \n\nDistance:  " << sDist << endl;

		cout << "Number of distance calcs: " << dCalcs << endl << endl;
		dCalcs = 0;
	}
	if(input == "divide" || input == "both"){

		cout << "-------------------DIVIDE AND CONQUER--------------------" << endl;//call DAC
		mergeSort(P,0,n-1,true);
		mergeSort(Q,0,n-1,false);
		sDist = closest(P,Q,n);
		
		cout << setprecision(5) << fixed << "\nPoint 1: (" 
		<< dPoint1.x << ", " << dPoint1.y << ")"
		<< " \nPoint 2: " << "(" << dPoint2.x << ", " << dPoint2.y << ")"
		<< " \n\nDistance:  " << sDist << endl;

		cout << "Number of distance calcs: " << dCalcs << endl;
		cout << "Number of calls: " << calls << endl << endl;
	}else
		cout << "Please Run with brute | divide | both arguements" << endl;
	

}
/*
 * Fills up two arrays based upon input sent into std::in
 * takes in two array pointers and an int for their length
 */
void fillArray(point* P,point* Q,int n){
	long long int cx;
	long long int cy;
	int c;
	
	for(int i = 0; i < n; i++){
		cin >> cx;
		cin >> cy;
		P[i].x = cx;
		P[i].y = cy;
		Q[i].x = cx;
		Q[i].y = cy;
	}

}
/*
 * main part of the mereg sort that does the sorting
 * takes in an array
 * it's leftmost index
 * it's middle point
 * it's rightmost index
 * and a boolean to used to determine to sort by x-cord or y-cord
 */
void merge(point arr[], int l, int m, int r, bool sortx) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    // create temp arrays 
    point L[n1], R[n2]; 
  
    // Copy data to arrays L[] and R[] 

		for (i = 0; i < n1; i++) 
       		 L[i] = arr[l + i]; 
    	for (j = 0; j < n2; j++) 
       		R[j] = arr[m + 1+ j]; 
  
    
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
	// 
	if(sortx){
    while (i < n1 && j < n2) 
    { 
        if (L[i].x <= R[j].x) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    }
	}else{
 	 while (i < n1 && j < n2) 
   	 { 
     	   if (L[i].y <= R[j].y) 
     	  	 { 
        	    arr[k] = L[i]; 
            	i++; 
        	} 
       	 else
       	 	{ 
        	    arr[k] = R[j]; 
           		 j++; 
       		 } 
       		 k++; 
   	 } 
	}
  
    // Copy the remaining elements of L[]
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of R[]
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

  
/* 
 * Driver of the merge method 
 * takes in an array
 * it's leftmost index
 * it's rightmost index
 * and a boolean to used to determine to sort by x-cord or y-cord
 * */
void mergeSort(point arr[], int l, int r,bool sortx) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2;
        mergeSort(arr, l, m,sortx); 
        mergeSort(arr, m+1, r,sortx);

		merge(arr, l, m, r,sortx);
	        
	}
}
/*
 * Prints the contents of an array to std::out
 * Takes in a pointer to an array and it's size
 */
void printArray(point* A, int size)
{
    int i;
    for (i=0; i < size; i++){
        cout << (A + i)->x  << " " <<  (A + i)->y  << endl;	
	}
}
/*
 * returns the distance between two given points using the distance formula
 * Takes in two points
 */
double dist(point p1, point p2) 
{ 
	dCalcs++;
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + 
                 (p1.y - p2.y)*(p1.y - p2.y) 
				 ); 
} 
/*
 * Brute Force Method
 * compares each point in the array with the other n-1 points of the array
 * returns the shortest distance found between all points
 *
 * takes in an array of points
 * an int representing it's size
 * and a bool of whether to print the results or not
 */
double bruteForce(point P[], int n) 
{ 
    double min = LONG_MAX;
	double cDist;
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j){//compares all points to eachother
			cDist = dist(P[i], P[j]);
				if (cDist < min) {
                min = cDist;	
				bPoint2 = P[i];
				bPoint1 = P[j];
		
				}
		}
	}
		
	return min;
} 
/*
 * Takes in the array representing the points in  middle strip 
 * of the array
 *
 * then compares them to the shortest distance between points
 * found in the left and right arrays
 *
 * returns the shortest distance 
 * 
 * takes in the array representing the strip
 * the size of the array
 * and the current smallest distance from left and right arrays
 *
 */
double stripClosest(point strip[], int size, double d) 
{ 
    double min = d; 
    double cDist;

    for (int i = 0; i < size; i++) { //Nested Loop iterates over all the points on the strip and compares them
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
			cDist = dist(strip[i],strip[j]);
				if (cDist < min) {
                min = cDist;
				dPoint1 = strip[i];
				dPoint2 = strip[j];
				}
		}
	}
  
    return min; 
} 
  
// A recursive function to find the smallest distance. The array P contains 
// all points sorted according to x coordinate 
double closest(point P[],point Q[] ,int n) 
{

	calls++;
	int i;
	int j;
	int k;
     
    if (n <= 3){ 
        return bruteForce(P, n); 
	}else{
     
	int mid = n/2;

	point PL[mid], PR[n-(mid+1)];
	point QL[mid], QR[n-(mid+1)];

	point midPoint = P[mid]; 
  	
		for (i = 0; i < mid; i++){
       		PL[i] = P[0 + i]; 
			QL[i] = Q[0 + i];
		}
		
    	for (j = 0; j < n - mid; j++) {
       		PR[j] = P[n-mid + j]; 
			QR[j] = Q[n-mid  + j];			
		}

    double dl = closest(PL,QL, mid);	
	double dr = closest(PR,QR, n-mid);    
    double d = min(dl, dr);

    point strip[n]; 
   	k = 0; 
    for (int i = 0; i < n; i++){//finds what points are in the strip and adds them 
		
        if (abs(P[i].x - midPoint.x) <= d) {
            strip[k] = Q[i]; 
			k++;
		}
	}
 	
	return stripClosest(strip, k, d); 
	}
} 
  
 

