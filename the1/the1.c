#include <stdio.h>
#define W_INDEX 0
#define H_INDEX 1
#define T_INDEX 2
#define P_INDEX 3
#define S_INDEX 4
#define A_INDEX 5
#define N_INDEX 6


int wall[100000];

void attack(int length, int w, int h, int t, int p, int s, int in, int no )
{
    
    int j=0;
    int pos=p;

    for (j=0;j<no;j++)/*number of attack*/
    {
        if (p>=0 && p+w<= length)
        {
            for (pos=p;pos<p+w;pos++)/*increase wall to h */
            {
                if(wall[pos]<h)
                    wall[pos]=h; 
            }
        }

        else if(p<0 && p+w>=0) 
        {
            for (pos=0;pos<p+w;pos++)
            {
                if(wall[pos]<h)
                     wall[pos]=h; 
            }
                
        }

        else if(p+w>length && p<=length)
        {
            for (pos=p;pos<length+1;pos++)
            {
                if(wall[pos]<h)
                     wall[pos]=h; 
            }
                
        }

        p=p+in*s;
    }
      

}

int main() {

    int r,k,width, height, time, position, speed, interval, number,i;
    
    scanf("%d", &r);
    scanf("%d", &k);
   
    for (i=0;i<r+1;i++)
        wall[i]=1;
        
    for (i=0;i<k;i++)
    {
        scanf("%d %d %d %d %d %d %d", &width, &height, &time, &position, &speed, &interval, &number);
        attack(r, width, height, time, position, speed, interval, number);
    }
    
    for (i=0;i<r;i++)
        printf("%d ", wall[i]);
    
    printf("%d\n", wall[r]);
    return 0;
}
