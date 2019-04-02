#include <bits/stdc++.h>
using namespace std;

/*! Class for creating points */

class Point
{
	public:
		double x; 
		double y;
		Point(double x_coordinate, double y_coordinate);
		Point();
		bool NotEquals(Point p);
		double distance(Point p);
};

class ConvexHull
{
	private:
		Point left_most_point;

		void swap_elements(double *a, double *b); 

		// int partition_med(vector<double>& arr,int low,int high,double element){
		// 	int i = low;
		// 	for (i = low; i < high; i++) 
		// 		if (arr[i] == element) 
		// 		   break;
		// 	swap_elements(&arr[i],&arr[high]);
		// 	// swap()		   	
			
		// 	i = low; 
		// 	for (double j = low; j <= high; j++) 
		// 	{ 
		// 		if (arr[j] <= element) 
		// 		{ 
		// 			swap_elements(&arr[i], &arr[j]);
		// 			i++; 
		// 		} 
		// 	} 
		// 	swap_elements(&arr[i], &arr[high]);
		// 	return (i); 
		// }

		// double medofMedians(vector<double> arr,int low,int high,int k)
		// {
		// 	if(high - low+1 <=5)
		// 	{
		// 		int len = high - low + 1;
		// 		sort(arr.begin(), arr.end());
		// 		return arr[len/2];
		// 	}

		// 	int no_medians = 0;
		// 	int size = high - low + 1;
		// 	vector<double> medians;
		// 	for(no_medians = 0; no_medians < size/5 ;no_medians++)
		// 	{
		// 		sort(arr.begin() + low + no_medians * 5 , arr.begin() + low + no_medians * 5 + 5);
		// 		medians.push_back(*(arr.begin() + low + no_medians * 5 + 2));
		// 	}
		// 	if(5 * no_medians < size)
		// 	{
		// 		int len = size - 5*no_medians;
		// 		sort(arr.begin() + low + no_medians * 5 , arr.end());
		// 		if(len%2)
		// 			medians.push_back(*(arr.begin() + low + no_medians * 5 + len/2));
		// 		else
		// 		{
		// 			medians.push_back(*(arr.begin() + low + no_medians * 5 + len/2));			
		// 			medians.push_back(*(arr.begin() + low + no_medians * 5 + len/2-1));			
		// 		}
		// 		no_medians++;
		// 	}
		// 	double medofMed = 0.0;
		// 	if(medians.size() == 1) medofMed =  medians.back();
		// 	else{
		// 		medofMed = medofMedians(medians,0,no_medians - 1,no_medians/2);

		// 	}

		// 	int pos = partition_med(arr,low,high,medofMed);
		// 	if (pos-low == k-1) return arr[pos];
		// 	if (pos-low > k-1)  return medofMedians(arr, low, pos-1, k); 
		// 	return medofMedians(arr, pos+1, high, k-pos+low-1);	
			
		// }
		bool comparator(Point p, Point q);

		double slope(Point p, Point q);

		int orientation(Point a, Point b, Point c);

		int get_left_most_point(vector<Point> points);

		pair<Point,Point> upper_bridge(vector<Point> points, double median_x);
		
		pair<Point,Point> lower_bridge(vector<Point> points, double median_x);

		vector<Point> upper_hull(Point pmin, Point pmax, vector<Point> points);
		

		vector<Point> lower_hull(Point pmin, Point pmax, vector<Point> points);

		public:
			vector<Point> graham_scan(vector<Point> points);
			vector<Point> jarvis_march(vector<Point> points);
			vector<Point> kirk(vector<Point> points);
		

};

