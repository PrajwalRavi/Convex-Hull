#include <bits/stdc++.h>
using namespace std;

class Point
{
	public:
		double x;
		double y;
		Point(double x, double y);
		bool NotEquals(Point);
};

bool Point::NotEquals(const Point p)
{
	return (x==p.x && y==p.y);
}

Point::Point(double x_coordinate, double y_coordinate)
{
	x = x_coordinate;
	y = y_coordinate;
}

double slope(Point p, Point q)
{
	return (q.y-p.y)/(q.x-p.x);
}

int orientataion(Point a, Point b, Point c)
{
	/*
	returns:-
		0 : Collinear
		1 : clockwise
		2 : anti-clockwise
	*/
	double slope_ab = slope(a,b);
	double slope_bc = slope(b,c);

	if(slope_ab == slope_bc)
		return 0;
	else if(slope_ab < slope_bc)
		return 2;
	else
		return 1;
}

vector<Point> jarvis_march(vector<Point> points)
{
	vector<Point> answer;
	int left_most = 0;
	for(int i=1; i<points.size(); i++)
		if(points[i].x < points[left_most].x)
			left_most = i;
	int p = left_most;
	do
	{
		answer.push_back(points[p]);
		int q = (p+1)%points.size();

		for(int i=0; i<points.size(); i++)
			if(orientataion(points[p],points[q],points[i])==2)
				q=i;

		p=q;

	}while(p!=left_most);

	return answer;
}

int main()
{
	vector<Point> points;
	points.push_back(new Point(0,3));
	points.push_back(new Point(2,2));
	points.push_back(new Point());
	points.push_back(new Point(0,3));
	points.push_back(new Point(0,3));
	return 0;
}




















// bool check_intersection(Point p1, Point q1, Point p2, Point q2)
// {
// 	if(orientataion(p1,q1,p2) != orientataion(p1,q1,q2)
// 		&& orientataion(p2,q2,p1) != orientataion(p2,q2,q1))
// 		return true;

// 	if(orientataion(p1,q1,p2)==0 orientataion(p1,q1,q2)==0
// 		&& orientataion(p2,q2,p1)==0 orientataion(p2,q2,q1)==0)
// }