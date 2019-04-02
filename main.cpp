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


	// cout<<"-----------------GRAHAM---------------------";
	 vector<Point> answer1 = ch.graham_scan(points);
	 vector<Point> answer2 = ch.jarvis_march(points);
	 vector<Point> answer3 = ch.kirk(points);
	 for(Point p : answer3)
	 	cout<<p.x<<" "<<p.y<<endl;
	// cout<<"--------------------JARVIS------------------";
	// for(Point p : answer2)
	// 	cout<<p.x<<" "<<p.y<<endl;
	// cout<<"------------------KPS--------------------";
	// for(Point p : answer3)
	//  	cout<<p.x<<" "<<p.y<<endl;
	return 0;
}