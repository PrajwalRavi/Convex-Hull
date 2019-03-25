#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	ofstream f;
	// f.open("inp_1000_gen.txt", ios::out);
	f.open("inp_"+to_string(n)+"_gen.txt", ios::out);
	f<<n<<"\n";
	int y=1,x=1;
	for(;x<=(n-2)/2; x++)
		f<<x<<" 0\n";
	f<<--x<<" 1\n";
	for(; x>=1; x--)
		f<<x<<" 2\n";
	f<<"1 1\n";
	return 0;
}