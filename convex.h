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

		int partition(std::vector<double>& arr, int l, int r, int x);

		double findMedian(std::vector<double>& arr, int start, int n);

		double nth_elemnt(std::vector<double>& arr, int l, int r, int k);

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

