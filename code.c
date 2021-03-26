
#include<stdio.h>
#include<math.h>

int input[50],temp[50];
int r,m;

int power(int a)
{
	int j,x=1;
	if(a==0)
		return 1;
	for(j=1;j<=a;j++)
		x*=2;
	return x;
}


void markChkBits()
{
	int j,k,l;
	// mark check bits positions with 0's
	k=0;
	l=m-1;
	for(j=1;j<=(m+r);j++)
	{
		if(power(k)==j)
		{
			temp[j]=0;
			k++;
		}
		else
			temp[j]=input[l--]; // LSB to MSB
	}
}


int  calXor()
{
	int i = 1,t = 0;
	while(i <= (r + m))
	{
		if(temp[i] == 1)
			t = t ^ i;
		i++;
	}

       return t;
}


void  calChkBits()
{
       int t = 0,i,j;
       int cb[25];

       t = calXor();

       i = 0;
       while(i < r)
       {
		cb[i++] = t % 2;
		t = t/2;
       }

      // place check bits in the data
      i = 0;
      while(i < r)
      {
	j = power(i);
	temp[j] = cb[i++];
      }
}


void  main()
{
	int i,k;
	int errPos=0,flag;

	printf("\nEnter the number of bits in the input:\n");
	scanf("%d",&m);

	// find the number of check bits r
	i = 1;
	while ((power(i) -1)  < (m+i))
		i++;
	r = i;

       //input the data bits
	printf("\nEnter the bits:\n");
	for(i=0;i<m;i++)
		scanf("%d",&input[i]);

	//mark check bits
	markChkBits();

	// claculate check bits
	calChkBits();


	printf("\n\n\n=====At Sender=====\n\nThe message transmitted is:\n");
	for(i=m+r;i>0;i--)
		printf("%d ",temp[i]);

	printf("\n\n\n=====At receiver=====\n\n");

	printf("\nEnter the recived bits(only single bit error): \n");

	for(i = m+r; i > 0; i--)
		scanf("%d",&temp[i]);

	if((errPos = calXor()) != 0)
	{
		flag = 0;
		for(i=r-1;i>=0;i--)
		{
			if(power(i) ==errPos)
				{flag = 1; break;}
		}
		if(flag == 0)
		{
			printf("\nError in data \n");
			printf("Error position is :%d\n", errPos);
			printf("\nCorrected data : \n");
			temp[errPos] = !(temp[errPos]);
			for(i=m+r;i>0;i--)
				printf("%d ",temp[i]);
		}
		else
		{
			printf("Error in check bits. Data is fine.\n");
		}
	}
	else
		printf("\n No error\n");

	printf("\nThe data :\n");
	k = r - 1;
	for(i= m + r; i > 0 ; i--)
	{
		if(power(k) == i)
			k--;
		else
			printf("%d ", temp[i]);
	}

     }




