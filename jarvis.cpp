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

int orientation(Point a, Point b, Point c)
{
	/*
	returns:-
		0 : Collinear
		1 : clockwise
		2 : anti-clockwise
	*/

	double test = (b.y - a.y)*(c.x - b.x) - (c.y - b.y)*(b.x-a.x);

	if(test==0)
		return 0;
	else if(test>0)
		return 1;
	else
		return 2;
}

vector<Point> jarvis_march(vector<Point> points)
{
	vector<Point> answer;
	int left_most = 0;
	for(int i=1; i<points.size(); i++)
		if(points[i].x < points[left_most].x)
			left_most = i;
	int p = left_most,q;
	do
	{
		answer.push_back(points[p]);
		q = (p+1)%points.size();

		for(int i=0; i<points.size(); i++)
			if(orientation(points[p],points[i],points[q])==2)
				q=i;

		p=q;
	}while(p!=left_most);

	return answer;
}

int main()
{
	vector<Point> points;
	int n;
	cin>>n;
	while(n--)
	{
		int p,q;
		cin>>p>>q;
		Point po(p,q);
		points.push_back(po);
	}
	vector<Point> answer = jarvis_march(points);
	for(Point p : answer)
		cout<<p.x<<" "<<p.y<<endl;
	return 0;
}