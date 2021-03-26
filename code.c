#include <iostream>
#include<math.h>
using namespace std;



int data[50],r,temp[50];
int power(int h)
{
	int i,p=1;
	for(i=1;i<=h;i++)
	{
		p=p*2;
	}
	return(p);
}



int calc_paritybits(int k, int r)
{
	int n=1,i,cnt_ones;
	int j=1,errSum = 0;


	while(n<power(r))
	{
		i=n;
		cnt_ones=0;
		while(i<=(k+r))
		{
			for(j=0;j<n;j++)
			{
				if(temp[i+j]==1)
					cnt_ones++;
			}
			i=i+2*n;
		}
		if((cnt_ones%2)!=0)
		{
			temp[n]=1;
			errSum += n ;
		}

		else
			temp[n]=0;
	       n=n*2;
	}
      return errSum;
}

void hammingcode(int k)
{
      int i,j,d=0;
       r=1;

      while(k > (power(r)-r-1))
		r++;

     j = k;
     for(i=1;i<=(k+r);i++)
	{
		if(i==power(d))
		  {
		    temp[i]=0;
		    d++;
		  }
		else
		  temp[i]=data[j--];
	}

	cout<< "\n no. of parity bits r = "<< r;
	calc_paritybits(k,r);
}

main()
{

	int k,i,p;
	int flg =0,errPos =0 ;

	cout<<"no of databits\n";
	cin>>k;
	cout<<"enter the data to be transmitted\n";
	for(i=k;i>=1;i--)

		cin>>data[i];
	hammingcode(k);

	cout<<"\nthe hamming code for data is\n";

	for(i=1;i<=(k+r);i++)
		cout<<temp[i];



     cout<<"\n enter the recieved  data:\n";

	for (i=1; i <= k+r; i++)
		cin>>temp[i];

	errPos =  calc_paritybits(k,r); ;

	if (errPos != 0)
	{

		for(i=1;i < power(r) ; i = i * 2)
		{
		       if(errPos == i)
			{
				flg = 1;
				break;
			 }

		}

		if(flg == 1)

			cout<<" Parity bit P%d  is corrupted, data is fine"<< errPos;
		else
		{
		    cout<<"Data bit is corrupted. pos = D"<< errPos;

		temp[errPos] = !(temp[errPos]);

		cout<<"\nCorrected data with parity bits\n";
           for(i=1;i<=(k+r);i++)
			cout<<temp[i];

 		}
	 }

	 else
	     cout<<"No error";
return 0;
}




