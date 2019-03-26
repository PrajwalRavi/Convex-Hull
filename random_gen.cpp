#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	srand( unsigned(time(NULL)));
	cout<<n<<endl;
	while(n--)
	{
		cout<<(double)rand()/(RAND_MAX+1)*(2*n)-n<<" "<<(double)rand()/(RAND_MAX+1)*(2*n)-n; 
		cout<<endl;
	}
	return 0;
}