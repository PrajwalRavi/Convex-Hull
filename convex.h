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
		/*!Partition array around the pivot element 'x' and returns index of the pivot
		in the array
		*/
		int partition(std::vector<double>& arr, int l, int r, int x);
		/*! Finds the median element of an array (array size < 5)*/
		double findMedian(std::vector<double>& arr, int start, int n);
		/*! Finds median element of an array using medians of medians algorithm*/
		double nth_elemnt(std::vector<double>& arr, int l, int r, int k);

		///Returns slope of straight line passing through Point 'p' and 'q'
		double slope(Point p, Point q);
		/**Returns circular orientation of three points 'a','b' and 'c'
		
			*Returns:-
			*	0 : Collinear
			*	1 : clockwise
			*	2 : anti-clockwise
			*/
		int orientation(Point a, Point b, Point c);
		/**Returns point with least x coordinate */
		int get_left_most_point(vector<Point> points);
		/** Function that returns upper bridge of the set of points */
		pair<Point,Point> upper_bridge(vector<Point> points, double median_x);
		/** Function that returns lower bridge of the set of points */
		pair<Point,Point> lower_bridge(vector<Point> points, double median_x);
		/**Returns set of points in the upper hull in clockwise order */
		vector<Point> upper_hull(Point pmin, Point pmax, vector<Point> points);
		
		/** Returns the set of points in lower hull in anticlockwise order */
		vector<Point> lower_hull(Point pmin, Point pmax, vector<Point> points);

		public:
			/// Returns the set of points in the convex hull in clockwise order
			///Algorithm: Graham Scan
			vector<Point> graham_scan(vector<Point> points);
			/// Returns the set of points in the convex hull in clockwise order
			///Algorithm: Jarvis' March
			vector<Point> jarvis_march(vector<Point> points);
			/// Returns the set of points in the convex hull in clockwise order
			///Algorithm: Kirkpatrik siedel
			vector<Point> kirk(vector<Point> points);
		

};

