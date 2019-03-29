#include<bits/stdc++.h>
using namespace std;

class Point{
	public:
		double x;
		double y;
		Point(double x,double y);
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

int orientation(Point a, Point b, Point c)
{
	/**
	*returns:-
	*	0 : Collinear
	*	1 : clockwise
	*	2 : anti-clockwise
	*/

	double test = (b.y - a.y)*(c.x - b.x) - (c.y - b.y)*(b.x-a.x);

	if(test<=1e-6)
		return 0;
	else if(test>0)
		return 1;
	else
		return 2;
}

class Line{
	public:
		double slope;
		double intercept;
		Line(Point p1,Point p2);
		bool Position(Point p);
};

Line::Line(Point p1, Point p2){
	slope = (double)((p2.y - p1.y)/(p2.x - p1.x));
	intercept = (double)((p1.y*p2.x - p2.y*p1.x) / (p2.x - p1.x));
}

bool Line::Position(Point p){
	// complete function; return true if above it else false
	if(p.y - slope*p.x - intercept >= 0) return true;
	else if (p.y - slope*p.x - intercept < 0 ) return false;
}

double median(vector<double>);
vector<Point> kps_convexhull(vector<Point>);
vector<Point> lower_hull(Point,Point,vector<Point>);
vector<Point> upper_hull(Point,Point,vector<Point>);
pair<Point,Point> upper_bridge(vector<Point>,double);
pair<Point,Point> lower_bridge(vector<Point>,double);


double median(vector<double> xpoints){
	sort(xpoints.begin(),xpoints.end());
	return xpoints[xpoints.size()/2];
}
vector<Point> kps_convexhull(vector<Point> points){
	cout<<"Hey i am over here!!\n";
	vector<Point> answer;
	double max = DBL_MIN;
	double min = DBL_MAX;
	double utemp1 = DBL_MIN; 
	double ltemp1 = DBL_MIN;
	double utemp2 = DBL_MIN;
	double ltemp2 =  DBL_MIN;
	Point umin(0,0);
	Point lmin(0,0);
	Point umax(0,0);
	Point lmax(0,0);
	vector<Point> UH;
	vector<Point> LH;
	
	for(Point p: points){
		if(p.x < min){
			min = p.x;
			umin.x = p.x;
			umin.y = p.y;
			lmin.x = p.x;
			lmin.y = p.y;
			utemp1 = p.y;
			ltemp1 = p.y;
		}
		else if(p.x > max){
		 max = p.x;
		 umax.x = p.x;
		 umax.y = p.y;
		 lmax.x = p.x;
		 lmax.y = p.y;
		 utemp2 = p.y;
		 ltemp2 = p.y;
		} 
		else if(p.x == min && p.y > utemp1){
			umin.y = utemp1 =  p.y;
		}
		else if(p.x == max && p.y > utemp2){
			umax.y = utemp2 =  p.y;
		}
		else if(p.x == min && p.y < ltemp1){
			lmin.y = ltemp1 = p.y;
		}
		else if(p.x == max && p.y < ltemp2){
			lmax.y = ltemp2 =  p.y;
		}
		
	}
	UH.push_back(umin);
	UH.push_back(umax);
	LH.push_back(lmin);
	LH.push_back(lmax);
	// check if this is the right way to split points into UH and LH
	Line l1(umin,umax);
	Line l2(lmin,lmax);
	for(auto k: points){
		if(!l2.Position(k) && lmin.NotEquals(k) && lmax.NotEquals(k)) LH.push_back(k);
		else if(l1.Position(k) && !umin.NotEquals(k) && !umax.NotEquals(k)) UH.push_back(k);
	}
	vector<Point> Ures = upper_hull(umin,umax,UH);
	//vector<Point> Lres = lower_hull(lmin,lmax,LH);
	
	//concatenate Ures and Lres to get final result
	//Ures.insert(Ures.end(),Lres.begin(),Lres.end());	
	return Ures;
	
}
vector<Point> upper_hull(Point umin,Point umax,vector<Point> points){
	// for(int i=0; i<points.size(); i++)
	// 	cout<<points[i].x<<endl;
	cout<<points.size()<<endl;
	vector<Point> result1;
	// Base
	if(umin.x == umax.x && umin.y == umax.y){
		result1.push_back(umin);
		return result1;
	}
	if(points.size()==2)
	{
		if(umin.x<umax.x)
		{
			result1.push_back(umin);
			result1.push_back(umax);
		}
		else
		{
			result1.push_back(umax);
			result1.push_back(umin);
		}
		return result1;
	}
	vector<Point> result2;
	vector<Point> Tright;
	vector<Point> Tleft;
	pair<Point,Point> lower = {umin,umax};
	vector<Point> Tleft_;
	vector<Point> Tright_;

	double L;
	vector<double> xpoints;
	for(auto k : points) xpoints.push_back(k.x);
	L = median(xpoints);// = medOfX write function to compute median of X's
	for(auto k : points){
		if(k.x <= L) Tleft.push_back(k);
		else  Tright.push_back(k);
	}
	
	pair<Point,Point> upper = upper_bridge(points,L);

	Line left = Line(umin,upper.first);
	for(auto k : Tleft){
		if(orientation(umin,upper.first,k)==2){
			Tleft_.push_back(k);
		}
	}
	Tleft_.push_back(umin);
	Tleft_.push_back(upper.first);
	
	for(auto k : Tright){
		if(orientation(upper.second,umax,k)==2){
			Tright_.push_back(k);
		}
	}
	Tright_.push_back(upper.second);
	Tright_.push_back(umax);
	
	result1 = upper_hull(umin,upper.first,Tleft_);
	result2 = upper_hull(upper.second,umax,Tright_);
	result1.insert(result1.end(),result2.begin(),result2.end());
	return result1;
}


pair<Point,Point> upper_bridge(vector<Point> points,double L){
	pair< Point,Point > result = {points[0],points[0]};
	if(points.size() == 2){
		if(points[0].x <= points[1].x){
			result = {points[0],points[1]};
			return result;
		}
		else{
			result = {points[1],points[0]};
			return result;
		}
	}
	
	else{
		vector<pair<Point,Point>> pairs;
		vector<Point> candidates;
		vector<double> slopes;
		vector<pair<Point,Point>> small;
		vector<pair<Point,Point>> equal;
		vector<pair<Point,Point>> large;
		vector<Point> max;
		int i = 0;
		for(i = 0; i < points.size();i += 2){
			if(points[i].x < points[i+1].x)
				pairs.push_back({points[i],points[i+1]});
			else pairs.push_back({points[i+1],points[i]});
			
		}
		if(points.size() % 2){
			candidates.push_back(points[points.size() - 1]);
		}
		vector<pair<Point,Point>> cleaned;
		for(auto k : pairs){
			if(k.first.x == k.second.x){
				if(k.first.y > k.second.y){
					candidates.push_back(k.first);
				}
				else{
					candidates.push_back(k.second);
				}
			}
			else
			{
				slopes.push_back(((k.first.y - k.second.y) / (k.first.x - k.second.x)));
				cleaned.push_back(k);
			}
		}
		double medSlopes = median(slopes);
		  // = findmedSlopes function to find median of slopes
		for(auto k: cleaned){
			double slope = ((k.first.y - k.second.y) / (k.first.x - k.second.x));
			if(slope < medSlopes){
				small.push_back(k);
			}
			else if(slope == medSlopes) equal.push_back(k);
			else large.push_back(k);
		}
		double maximum = points[0].y - (points[0].x * medSlopes);
		max.push_back(points[0]);
		Point pm(0,0);
		pm.x = points[0].x;
		pm.y = points[0].y;
		Point pk(0,0);
		pk.x = points[0].x;
		pk.y = points[0].y;
		for(int i = 1;i < points.size();i++){
			double y_intercept = points[i].y - (points[i].x * medSlopes);
			if(y_intercept > maximum){
				max.clear();
				max.push_back(points[i]);
				pm.x = points[i].x;
				pk.x = pm.x;
				pk.y = points[i].y;
				pm.y = pk.y;
				maximum = y_intercept;
			}
			else if(y_intercept-maximum<10e-5){
				max.push_back(points[i]);
				if(points[i].x < pk.x){
					pk.x = points[i].x;
					pk.y = points[i].y;
				}
				if(points[i].x > pm.x){
					pm.x = points[i].x;
					pm.y = points[i].y;
				};
			} 
		}
		if(pk.x <= L && pm.x > L){
			result = {pk,pm};
			return result;
		}
		else if(pm.x <= L){
			for(auto k : large){
				candidates.push_back(k.second);
			}
			for(auto k : equal){
				candidates.push_back(k.second);
			}
			for(auto k : small){
				candidates.push_back(k.first);
				candidates.push_back(k.second);
			}
		}
		else if(pk.x > L){
			for(auto k : small){
				candidates.push_back(k.first);
			}
			for(auto k : equal){
				candidates.push_back(k.first);
			}
			for(auto k : large){
				candidates.push_back(k.first);
				candidates.push_back(k.second);
			}
		} 
		return upper_bridge(candidates,L);
	}	
}
int main(){
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
	vector<Point> answer = kps_convexhull(points);
	for(Point p : answer)
		cout<<p.x<<" "<<p.y<<endl;
	
	return 0;
}

