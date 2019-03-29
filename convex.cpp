#include <bits/stdc++.h>
using namespace std;

/*! Class for creating points */

class Point
{
	public:
		double x; 
		double y;
		Point(double x, double y);
		Point();
		bool NotEquals(Point);
		double distance(Point);
};

Point::Point(double x_coordinate, double y_coordinate)
{
	x = x_coordinate;
	y = y_coordinate;
}

Point::Point()
{
	x=0;
	y=0;
}

bool Point::NotEquals(const Point p)
{
	return (x==p.x && y==p.y);
}

double Point::distance(Point p)
{
	return (pow(p.x-x,2)+pow(p.y-y,2));
}

Point left_most_point;

double slope(Point p, Point q)
{
	return (q.y-p.y)/(q.x-p.x);
}

int orientation(Point a, Point b, Point c)
{
	/**
	*returns:-
	*	0 : Collinear
	*	1 : clockwise
	*	2 : anti-clockwise
	*/

	double orient = (b.y - a.y)*(c.x - b.x) - (c.y - b.y)*(b.x-a.x);

	if(orient==0)
		return 0;
	else if(orient>0)
		return 1;
	else
		return 2;
}

int get_left_most_point(vector<Point> points)
{
	int left_most = 0;
	for(int i=1; i<points.size(); i++)
		if((points[i].x < points[left_most].x) || (points[i].x == points[left_most].x && points[i].y<points[left_most].y))
			left_most = i;

	return left_most;
}

vector<Point> jarvis_march(vector<Point> points)
{
	vector<Point> answer;
	
	if(points.size()<3)
		return answer;

	int left_most = get_left_most_point(points);
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

bool comparator(Point p, Point q)
{
	int orient = orientation(left_most_point,p,q);
	if(orient==0)
		return p.distance(left_most_point)<q.distance(left_most_point);
	return orient==2;
}

vector<Point> graham_scan(vector<Point> points)
{
	vector<Point> answer;
	
	if(points.size()<3)
		return answer;

	int size = points.size();
	int left_most = get_left_most_point(points);
	left_most_point.x = points[left_most].x;
	left_most_point.y = points[left_most].y;
	sort(points.begin(),points.end(),comparator);

	int p = 1;
	for(int i=1; i<size-1; i++)
		if(orientation(points[0],points[i],points[i+1])!=0)
			points[p++]=points[i];
	points[p++] = points[size-1];

	size = p;
	answer.push_back(points[0]);
	answer.push_back(points[1]);
	answer.push_back(points[2]);

	for(int i=3; i<size; i++)
	{
		int answer_size = answer.size();
		while(answer_size>1 && orientation(points[i], answer[answer_size-1], answer[answer_size-2])==2 )
		{
			answer.pop_back();
			answer_size--;
		}
		answer.push_back(points[i]);
	}

	return answer;
}

int main()
{
	vector<Point> points;
	int n;
	cin>>n;
	while(n--)
	{
		double p,q;
		cin>>p>>q;
		Point po(p,q);
		points.push_back(po);
	}
	// vector<Point> answer = graham_scan(points);
	vector<Point> answer = jarvis_march(points);
	// cout<<answer.size()<<endl;
	// cout<<answer2.size()<<endl;
	// assert(answer.size()==answer2.size());
	// for(int i=0; i<answer2.size(); i++)
	// {
	// 	assert(answer2[i].x==answer[i].x);
	// 	assert(answer2[i].y==answer[i].y);
	// }

	// cout<<endl;
	// for(Point p : answer)
	// 	cout<<p.x<<" "<<p.y<<endl;
	// cout<<endl;
	for(Point p : answer)
		cout<<p.x<<" "<<p.y<<endl;
	return 0;
}