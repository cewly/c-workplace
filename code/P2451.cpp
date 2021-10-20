#include<iostream>
using namespace std;
int main()
{
    int n,l[1005],r[1005];
    int tl[1005],tr[1005];
    int sum;
    cin>>n;
    for (int i=1;i<=1005;i++)
    {
        tl[i]=0;
        tr[i]=0;
    }
    for (int i=1;i<=n;i++)
    {
        cin>>l[i]>>r[i];
        tr[r[i]]++;
        tl[l[i]]++;
    }
    sum=0;
    for (int i=1;i<=1000+1;i++)
	{
		if (tr[i]>tl[i])
		{
			sum+=tr[i]-tl[i];
		}
	}
	cout<<sum+n;
	return 0;
}