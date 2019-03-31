#include <bits/stdc++.h>
using namespace std;

class Point
{
	public:
		double x; 
		double y;
		Point(double x_coordinate, double y_coordinate)
		{
			x = x_coordinate;
			y = y_coordinate;
		}
		Point()
		{
			x=0;
			y=0;
		}
		bool NotEquals(Point p)
		{
			return (x==p.x && y==p.y);
		}
		double distance(Point p)
		{
			return (pow(p.x-x,2)+pow(p.y-y,2));
		}
};

int orientation(Point p1, Point p2, Point p3) 
{ 
    // See 10th slides from following link for derivation 
    // of the formula 
    int val = (p2.y - p1.y) * (p3.x - p2.x) - 
              (p2.x - p1.x) * (p3.y - p2.y); 
  
    if (val == 0) return 0;  // colinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

bool comparator(Point p, Point q)
{
	return p.x<q.x;
}

pair<Point,Point> upper_bridge(vector<Point> points, double median_x)
{
	vector<Point> candidates;
	if(points.size()==2)
	{
		if(points[0].x<points[1].x)
			return {points[0],points[1]};
		else
			return {points[1],points[0]};
	}

	if(points.size()%2)
		candidates.push_back(points[points.size()-1]);

	vector<pair<Point,Point>> point_pairs;
	for(int i=0; i<points.size()-1; i+=2)
	{
		if(points[i].x<=points[i+1].x)
			point_pairs.push_back({points[i],points[i+1]});
		else
			point_pairs.push_back({points[i+1],points[i]});
	}
	vector<double> k;

	for(auto point_pair : point_pairs)
	{
		if(abs(point_pair.first.x - point_pair.second.x) < 1e-8 )
		{
			if(point_pair.first.y > point_pair.second.y)
				candidates.push_back(point_pair.first);
			else
				candidates.push_back(point_pair.second);
		}
		else
			k.push_back((point_pair.second.y - point_pair.first.y)/(point_pair.second.x - point_pair.first.x));
	}
	if(k.size()==0)
		return upper_bridge(candidates,median_x);
	sort(k.begin(),k.end());

	double K = k[k.size()/2];

	vector<pair<Point,Point>> small,equal,large;

	for(auto point_pair : point_pairs)
		if(abs(point_pair.first.x - point_pair.second.x) > 1e-8)
		{
			double slope = (point_pair.second.y - point_pair.first.y)/(point_pair.second.x - point_pair.first.x);			
			if(abs(slope-K)<1e-8)
				equal.push_back(point_pair);
			else if(slope<K)
				small.push_back(point_pair);
			else
				large.push_back(point_pair);
		}

	double max_y = points[0].y - K*points[0].x;
	std::vector<Point> max_y_pts = {points[0]};
	for(int i=1; i<points.size(); i++)
	{
		double y_int = points[i].y - K * points[i].x;
		if(y_int > max_y)
			max_y_pts.clear();
		if(y_int > max_y || abs(y_int - max_y)<1e-8)
		{
			max_y_pts.push_back(points[i]);
			max_y = y_int;
		}
	}
	sort(max_y_pts.begin(), max_y_pts.end(), [](Point p, Point q)
			{
				return p.x<q.x;
			}
		);

	Point pm = max_y_pts[max_y_pts.size()-1];
	Point pk = max_y_pts[0];

	if(max_y_pts.size()>=2 && (pk.x<median_x || abs(pk.x - median_x)<1e-8) && pm.x>median_x)
		return {pk,pm};	

	if(pm.x < median_x || abs(pm.x - median_x) < 1e-8)
	{
		for(auto point_pair : large)
			candidates.push_back(point_pair.second);
		for(auto point_pair : equal)
			candidates.push_back(point_pair.second);
		for(auto point_pair : small)
		{
			candidates.push_back(point_pair.second);
			candidates.push_back(point_pair.first);			
		}
	}

	if(pk.x > median_x)
	{
		for(auto point_pair : small)
			candidates.push_back(point_pair.first);
		for(auto point_pair : equal)
			candidates.push_back(point_pair.first);
		for(auto point_pair : large)
		{
			candidates.push_back(point_pair.second);
			candidates.push_back(point_pair.first);			
		}
	}

	return upper_bridge(candidates,median_x);
}

pair<Point,Point> lower_bridge(vector<Point> points, double median_x)
{

	vector<Point> candidates;
	if(points.size()==2)
	{
		if(points[0].x<points[1].x)
			return {points[0],points[1]};
		else
			return {points[1],points[0]};
	}

	if(points.size()%2)
		candidates.push_back(points[points.size()-1]);

	vector<pair<Point,Point>> point_pairs;
	for(int i=0; i<points.size()-1; i+=2)
	{
		if(points[i].x<=points[i+1].x)
			point_pairs.push_back({points[i],points[i+1]});
		else
			point_pairs.push_back({points[i+1],points[i]});
	}
	vector<double> k;

	for(auto point_pair : point_pairs)
	{
		if(abs(point_pair.first.x - point_pair.second.x) < 1e-8 )
		{
			if(point_pair.first.y < point_pair.second.y)
				candidates.push_back(point_pair.first);
			else
				candidates.push_back(point_pair.second);
		}
		else
			k.push_back((point_pair.second.y - point_pair.first.y)/(point_pair.second.x - point_pair.first.x));
	}
	if(k.size()==0)
		return lower_bridge(candidates,median_x);
	sort(k.begin(),k.end());

	double K = k[k.size()/2];

	vector<pair<Point,Point>> small,equal,large;

	for(auto point_pair : point_pairs)
		if(abs(point_pair.first.x - point_pair.second.x) > 1e-8)
		{
			double slope = (point_pair.second.y - point_pair.first.y)/(point_pair.second.x - point_pair.first.x);			
			if(abs(slope-K)<1e-8)
				equal.push_back(point_pair);
			else if(slope<K)
				small.push_back(point_pair);
			else
				large.push_back(point_pair);
		}

	double max_y = points[0].y - K*points[0].x;
	std::vector<Point> max_y_pts = {points[0]};
	for(int i=1; i<points.size(); i++)
	{
		double y_int = points[i].y - K * points[i].x;
		if(y_int < max_y)
			max_y_pts.clear();
		if(y_int < max_y || abs(y_int - max_y)<1e-8)
		{
			max_y_pts.push_back(points[i]);
			max_y = y_int;
		}
	}
	sort(max_y_pts.begin(), max_y_pts.end(), [](Point p, Point q)
			{
				return p.x<q.x;
			}
		);

	Point pm = max_y_pts[max_y_pts.size()-1];
	Point pk = max_y_pts[0];

	if(max_y_pts.size()>=2 && (pk.x<median_x || abs(pk.x - median_x)<1e-8) && pm.x>median_x)
		return {pk,pm};	

	if(pm.x < median_x || abs(pm.x - median_x) < 1e-8)
	{
		for(auto point_pair : small)
			candidates.push_back(point_pair.second);
		for(auto point_pair : equal)
			candidates.push_back(point_pair.second);
		for(auto point_pair : large)
		{
			candidates.push_back(point_pair.second);
			candidates.push_back(point_pair.first);			
		}
	}

	if(pk.x > median_x)
	{
		for(auto point_pair : large)
			candidates.push_back(point_pair.first);
		for(auto point_pair : equal)
			candidates.push_back(point_pair.first);
		for(auto point_pair : small)
		{
			candidates.push_back(point_pair.second);
			candidates.push_back(point_pair.first);			
		}
	}

	return lower_bridge(candidates,median_x);
}

vector<Point> upper_hull(Point pmin, Point pmax, vector<Point> points)
{
	// cout<<points.size()<<endl;
	vector<Point> answer;
	if(abs(pmin.x-pmax.x)<=1e-8 && abs(pmin.y-pmax.y)<=1e-8)
	{
		answer.push_back(pmin);
		return answer;
	}

	sort(points.begin(),points.end(),comparator);
	double median_x = points[points.size()/2].x;
	
	vector<Point> Tleft, Tright;
	for(Point p:points)
	{
		if(p.x< median_x || abs(p.x - median_x)<1e-8)
			Tleft.push_back(p);
		else
			Tright.push_back(p);
	}

	pair<Point,Point> bridge_pts = upper_bridge(points,median_x);

	vector<Point> newTleft = {bridge_pts.first,pmin};
	vector<Point> newTright = {bridge_pts.second,pmax};

	for(Point p: Tleft)
		if(orientation(pmin,bridge_pts.first,p)==2)
			newTleft.push_back(p);
	
	for(Point p:Tright)
		if(orientation(bridge_pts.second,pmax,p)==2)
			newTright.push_back(p);

	vector<Point> left_upper = upper_hull(pmin,bridge_pts.first,newTleft);
	vector<Point> right_upper = upper_hull(bridge_pts.second,pmax,newTright);
	left_upper.insert(left_upper.end(),right_upper.begin(),right_upper.end());
	return left_upper;
}

vector<Point> lower_hull(Point pmin, Point pmax, vector<Point> points)
{
	// cout<<points.size()<<endl;
	vector<Point> answer;
	if(abs(pmin.x-pmax.x)<=1e-8 && abs(pmin.y-pmax.y)<=1e-8)
	{
		answer.push_back(pmin);
		return answer;
	}

	sort(points.begin(),points.end(),comparator);
	double median_x = points[points.size()/2].x;
	
	vector<Point> Tleft, Tright;
	for(Point p:points)
	{
		if(p.x< median_x || abs(p.x - median_x)<1e-8)
			Tleft.push_back(p);
		else
			Tright.push_back(p);
	}

	pair<Point,Point> bridge_pts = lower_bridge(points,median_x);

	vector<Point> newTleft = {bridge_pts.first,pmin};
	vector<Point> newTright = {bridge_pts.second,pmax};

	for(Point p: Tleft)
		if(orientation(pmin,bridge_pts.first,p)==1)
			newTleft.push_back(p);
	
	for(Point p:Tright)
		if(orientation(bridge_pts.second,pmax,p)==1)
			newTright.push_back(p);

	vector<Point> left_lower = lower_hull(pmin,bridge_pts.first,newTleft);
	vector<Point> right_lower = lower_hull(bridge_pts.second,pmax,newTright);
	left_lower.insert(left_lower.end(),right_lower.begin(),right_lower.end());
	return left_lower;
}

vector<Point> kirk(vector<Point> points)
{
	Point pmin=points[0],pmax=points[0],pumin,pumax,plmin,plmax;
	set<pair<double,double>> s1,s2;
	for(Point po : points)
	{
		if(po.x<pmin.x)
		{
			pmin=po;
			s1.clear();
			s1.insert({po.x,po.y});
		}
		else if(po.x==pmin.x)
			s1.insert({po.x,po.y});
		if(po.x>pmax.x)
		{
			pmax=po;
			s2.clear();
			s2.insert({po.x,po.y});
		}
		else if(po.x==pmax.x)
			s2.insert({po.x,po.y});
	}
	if(s1.size()==1)
	{
		pumin=Point(s1.begin()->first,s1.begin()->second);
		plmin=pumin;
	}
	else
	{
		plmin=Point(s1.begin()->first,s1.begin()->second);
		auto it = s1.end();
		it--;
		pumin=Point(it->first,it->second);
	}
	if(s2.size()==1)
	{
		pumax=Point(s2.begin()->first,s2.begin()->second);
		plmax=pumax;
	}
	else
	{
		plmax=Point(s2.begin()->first,s2.begin()->second);
		auto it = s2.end();
		it--;
		pumax=Point(it->first,it->second);
	}
	vector<Point> upper_hull_points =  upper_hull(pumin,pumax,points);
	vector<Point> lower_hull_points = lower_hull(plmin,plmax,points);
	reverse(lower_hull_points.begin(),lower_hull_points.end());
	if(s1.size()==1)
		lower_hull_points.erase(lower_hull_points.begin());
	if(s2.size()==1)
		lower_hull_points.erase(--lower_hull_points.end());
	upper_hull_points.insert(upper_hull_points.end(),lower_hull_points.begin(),lower_hull_points.end());

	return upper_hull_points;
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
	// ConvexHull ch;
	// vector<Point> answer = ch.graham_scan(points);
	vector<Point> answer = kirk(points);
	for(Point p : answer)
		cout<<p.x<<" "<<p.y<<endl;
	return 0;
}