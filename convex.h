#include <bits/stdc++.h>
using namespace std;

/*! Class for creating points */

class Point
{
	public:
		/*!
		* x : x coordinate of point
		* y : y coordinate of point
		*/
		double x; 
		double y;
		Point(double x_coordinate, double y_coordinate);
		Point();
		bool NotEquals(Point p);
		double distance(Point p);
};
/*! Class for creating an object of convex hull that computes the set of points on the convex hull */
class ConvexHull
{
	private:
		/// left_most_point : point with least x coordinate in given set of points
		Point left_most_point;

		// void swap_elements(double *a, double *b); 

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
		// bool comparator(Point p, Point q);

		///returns slope of straight line passing through Point 'p' and 'q'
		double slope(Point p, Point q);
		/**returns circular orientation of three points 'a','b' and 'c'
		
			*returns:-
			*	0 : Collinear
			*	1 : clockwise
			*	2 : anti-clockwise
			*/
		int orientation(Point a, Point b, Point c);
		/**returns point with least x coordinate */
		int get_left_most_point(vector<Point> points);
		/** function that returns upper bridge of the set of points */
		pair<Point,Point> upper_bridge(vector<Point> points, double median_x);
		/** function that returns lower bridge of the set of points */
		pair<Point,Point> lower_bridge(vector<Point> points, double median_x);
		/**returns set of points in the upper hull in clockwise order */
		vector<Point> upper_hull(Point pmin, Point pmax, vector<Point> points);
		
		/** returns the set of points in lower hull in anticlockwise order */
		vector<Point> lower_hull(Point pmin, Point pmax, vector<Point> points);

		public:
			/// returns the set of points in the convex hull in clockwise order
			///Algorithm: Graham Scan
			vector<Point> graham_scan(vector<Point> points);
			/// returns the set of points in the convex hull in clockwise order
			///Algorithm: Jarvis' March
			vector<Point> jarvis_march(vector<Point> points);
			/// returns the set of points in the convex hull in clockwise order
			///Algorithm: Kirkpatrik siedel
			vector<Point> kirk(vector<Point> points);
		

};

