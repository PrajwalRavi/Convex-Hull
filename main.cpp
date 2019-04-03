#include<bits/stdc++.h>
#include "convex.h"
using namespace std;
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
	ConvexHull ch;


	 // vector<Point> answer = ch.graham_scan(points);
	 // vector<Point> answer = ch.jarvis_march(points);
	 vector<Point> answer = ch.kirk(points);
	 for(Point p : answer)
	 	cout<<p.x<<" "<<p.y<<endl;
	return 0;
}