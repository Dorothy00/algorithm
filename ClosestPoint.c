#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

typedef struct P
{
    int x;
    int y;
}Point;

float ClosestPoint(Point x[], Point y[], int n);
void QuickSort(Point a[], int p, int r, bool isx);
int partition(Point a[], int p, int r, bool isx);
float _distance(Point p1, Point p2);


int main()
{

    int n = 15;
    Point px[15];
    Point py[15];
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; i++)
    {
        int x = rand() % 50;
        int y = rand() % 50;
        px[i].x = x;
        px[i].y = y;
        py[i].x = x;
        py[i].y = y;
        printf("point: %d, %d\n", x, y);
    }
    QuickSort(px, 0, n - 1, true);
    QuickSort(py, 0, n - 1, false);
    float dis = ClosestPoint(px, py, n);
    printf("Closest distance is: %f\n", dis);
    return 0;
}

float _distance(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float ClosestPoint(Point x[], Point y[], int n)
{
    if(n == 1)
    {
        return INT_MAX;
    }
    if(n == 2)
    {
        return _distance(x[0], x[1]);
    }
    
    Point xL[n];
    Point xR[n];
    Point yL[n];
    Point yR[n];
    int xl_size = 0;
    int xr_size = 0;
    int yl_size = 0;
    int yr_size = 0;
    int mid_x = (x[0].x + x[n - 1].x) / 2;
    for(int i = 0; i < n; i++)
    {
        if(x[i].x < mid_x)
        {
            xL[xl_size++] = x[i];
        }else
        {
            xR[xr_size++] = x[i];
        }
        if(y[i].x < mid_x)
        {
            yL[yl_size++] = y[i];
        }else
        {
            yR[yr_size++] = y[i];
        }
    }
    
    float distance_l = ClosestPoint(xL, yL, xl_size);
    float distance_r = ClosestPoint(xR, yR, xr_size);
    float distance = distance_l > distance_r ? distance_r : distance_l;
    
    Point yyL[yl_size];
    Point yyR[yr_size];
    int yyl_size = 0;
    int yyr_size = 0;
    for(int i = 0; i < yl_size; i++)
    {
        if(mid_x - y[i].x < distance)
        {
            yyL[yyl_size++] = yL[i];
        }
    }
    for(int i = 0; i < yr_size; i++)
    {
        if(y[i].x - mid_x < distance)
        {
            yyR[yyr_size++] = yR[i];
        }
    }
    float dis = 0;
    for(int i = 0; i < yyl_size; i++)
    {
        for(int j = 0; j < yyr_size; j++)
        {
            dis = _distance(yL[i], yR[j]);
            distance = distance > dis ? dis : distance;
        }
    }
    return distance;
}

void QuickSort(Point a[], int p, int r, bool isx)
{
    if(p < r)
    {
        int q = partition(a, p, r, isx);
        QuickSort(a, p, q - 1, isx);
        QuickSort(a, q + 1, r, isx);
    }
}

int partition(Point a[], int p, int r, bool isx)
{
    if(p == r)
    {
        return p;
    }
    if(p > r)
    {
        return -1;
    }
    
    int i = p - 1;
    int data = isx ? a[r].x : a[r].y;
    for(int j = p; j < r; j++)
    {
        int cmp_data = isx ? a[j].x : a[j].y;
        if(cmp_data <= data)
        {
            i ++;
            Point tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    Point tmp = a[i + 1];
    a[i + 1] = a[r];
    a[r] = tmp;
    
    return i + 1;
}

