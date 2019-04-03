#include <bits/stdc++.h>
#include "convex.h"
using namespace std;
	
		///Parameterized constructor of Point 
		Point::Point(double x_coordinate, double y_coordinate)
		{
			x = x_coordinate;
			y = y_coordinate;
		}
		///Constructor of Point
		Point::Point()
		{
			x=0;
			y=0;
		}
		/// Returns whether Point 'p' is equal to the current Point object or not
		bool Point::NotEquals(Point p)
		{
			return (x==p.x && y==p.y);
		}
		///Returns euclidian distance between the current Point object and the Point 'p'
		double Point::distance(Point p)
		{
			return (pow(p.x-x,2)+pow(p.y-y,2));
		}

		int ConvexHull::partition(std::vector<double>& arr, int l, int r, int x) 
		{ 
			int i=l; 
			while(i<r) 
			{
				if (!(arr[i] != x)) 
				break; 
				i++;
			}
			swap(arr[i], arr[r]); 

			i = l; 
			int j=l;
			while(j<=r-1) 
			{ 
				if (arr[j] <= x) 
				{ 
					swap(arr[i], arr[j]); 
					i++; 
				} 
				j++;
			} 
			swap(arr[i], arr[r]); 
			return i; 
		}

		double ConvexHull::findMedian(std::vector<double>& arr, int start, int n) 
		{ 
			sort(arr.begin()+start, arr.begin()+start+n); 
			return arr[start + n/2]; 
		} 

		double ConvexHull::nth_elemnt(std::vector<double>& arr, int l, int r, int k) 
		{ 
			if ((k > 0) || (k <= r - l + 1)) 
			{ 
				int n = r-l+1; 

				int i; std::vector<double> median; 
				while(i++<n/5) 
					median.push_back(findMedian(arr,l+i*5, 5)); 
				if (!(i*5 > n)) 
				{ 
					median.push_back(findMedian(arr,l+i*5, n%5)); 
					i++; 
				}	 

				double medOfMed;
				if (i == 1)
					medOfMed = median[i-1];
				else
					medOfMed = nth_elemnt(median, 0, i-1, i/2); 
				int pos = partition(arr, l, r, medOfMed); 

				if (pos == k-1+l) 
					return arr[pos]; 
				if (pos > k-1+l) 
					return nth_elemnt(arr, l, pos-1, k); 

				return nth_elemnt(arr, pos+1, r, k-pos+l-1); 
			} 

			return 999999; 
		}

		double ConvexHull::slope(Point p, Point q)
		{
			return (q.y-p.y)/(q.x-p.x);
		}

		int ConvexHull::orientation(Point a, Point b, Point c)
		{
			

			double orient = (b.y - a.y)*(c.x - b.x) - (c.y - b.y)*(b.x-a.x);

			if(orient==0)
				return 0;
			else if(orient>0)
				return 1;
			else
				return 2;
		} 
		int ConvexHull::get_left_most_point(vector<Point> points)
		{
			int left_most = 0;
			for(int i=1; i<points.size(); i++)
				if((points[i].x < points[left_most].x) || (points[i].x == points[left_most].x && points[i].y<points[left_most].y))
					left_most = i;

			return left_most;
		}
		pair<Point,Point> ConvexHull::upper_bridge(vector<Point> points, double median_x)
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
			// sort(k.begin(),k.end());

			// double K = k[k.size()/2];
			// double K = median_of_medians(k,0,k.size()-1,k.size()/2);
			nth_element(k.begin(),k.begin()+(k.size()/2),k.end());
			double K = k[k.size()/2];
			// cout<<K<<endl;
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

		pair<Point,Point> ConvexHull::lower_bridge(vector<Point> points, double median_x)
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
			// sort(k.begin(),k.end());

			nth_element(k.begin(),k.begin()+(k.size()/2),k.end());			
			double K = k[k.size()/2];
			// double K = medofMedians(k,0,k.size()-1,k.size()/2);

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

		vector<Point> ConvexHull::upper_hull(Point pmin, Point pmax, vector<Point> points)
		{
			// cout<<points.size()<<endl;
			vector<Point> answer;
			if(abs(pmin.x-pmax.x)<=1e-8 && abs(pmin.y-pmax.y)<=1e-8)
			{
				answer.push_back(pmin);
				return answer;
			}

			vector<double> xpoints;
			for(auto k : points){
				xpoints.push_back(k.x);
			}
			// sort(points.begin(), points.end(), [](Point p, Point q)
			// {
			// 	return p.x<q.x;
			// }
			// );
			// sort(points.begin(),points.end(),comparator);
			nth_element(xpoints.begin(),xpoints.begin()+(xpoints.size()/2),xpoints.end());			
			double median_x = xpoints[xpoints.size()/2];
			// double median_x = medofMedians(xpoints,0,points.size()-1,points.size()/2);

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

		vector<Point> ConvexHull::lower_hull(Point pmin, Point pmax, vector<Point> points)
		{
			// cout<<points.size()<<endl;
			vector<Point> answer;
			if(abs(pmin.x-pmax.x)<=1e-8 && abs(pmin.y-pmax.y)<=1e-8)
			{
				answer.push_back(pmin);
				return answer;
			}
			vector<double> xpoints;
			for(auto k : points){
				xpoints.push_back(k.x);
			}
			// sort(points.begin(), points.end(), [](Point p, Point q)
			// {
			// 	return p.x<q.x;
			// }
			// );
			// sort(points.begin(),points.end(),comparator);
			nth_element(xpoints.begin(),xpoints.begin()+(xpoints.size()/2),xpoints.end());						
			double median_x = xpoints[xpoints.size()/2];
			// double median_x = medofMedians(xpoints,0,points.size()-1,points.size()/2);
			
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


		vector<Point> ConvexHull::graham_scan(vector<Point> points)
		{
			vector<Point> answer;
			
			if(points.size()<3)
				return answer;

			int size = points.size();
			int left_most = get_left_most_point(points);
			left_most_point.x = points[left_most].x;
			left_most_point.y = points[left_most].y;
			sort(points.begin(),points.end(),[&](Point p, Point q)
					{
						int orient = orientation(left_most_point,p,q);
						if(orient==0)
							return p.distance(left_most_point)<q.distance(left_most_point);
						return orient==2;
					}
				);

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

		vector<Point> ConvexHull::jarvis_march(vector<Point> points)
		{
			vector<Point> answer;
			
			if(points.size()<3)
				return answer;

			int left_most = get_left_most_point(points);
			int p = left_most,q;
			do
			{
				answer.push_back(points[p]);
				cout<<p<<endl;
				q = (p+1)%points.size();
				cout<<q<<endl;
				for(int i=0; i<points.size(); i++)
					if(orientation(points[p],points[i],points[q])==2){
						q=i;
						cout<<i<<endl;
					}
				cout<<q<<endl;
				cout<<"----"<<endl;

				p=q;
			}while(p!=left_most);

			return answer;
		}

		vector<Point> ConvexHull::kirk(vector<Point> points)
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


