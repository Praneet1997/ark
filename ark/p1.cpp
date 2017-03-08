
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#define PI 3.14159265
#include<stdio.h>
#include<string.h>
using namespace std;
using namespace cv;
#define MAXA 400
#define INFINITY 9999
#define IN 9999
 int puka[50]={0};
int * dijkstra(int G[MAXA][MAXA],int n,int startnode);
int main(){
  
  Mat img1=imread("pic-1.jpg",0);                                                                 //READING A BLACK AND WHITE VERSION OF IMAGE
	Mat img2=Mat(img1.rows,img1.cols,CV_8UC1,Scalar(0));
	Mat img3=Mat(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));                                  //DECLARING TWO IMAGES
	Mat img4=imread("pic-1.jpg",1);                                                           //READING COLORED IMAGE

                                                                                                  //APPLYING SOBEL FILTER
	
	int i, j, k, l, th = 0, gx = 0, gy = 0, c = 0;
	double g = 0.0;
	int kernel = 3;
	int arr1[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };                                          
	int arr2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

      		namedWindow("Original", WINDOW_AUTOSIZE);
		namedWindow("filter - SOBEL", WINDOW_AUTOSIZE);
		imshow("Original", img4);
		for (i = 1; i < img1.rows - 1; i++)
		{
			for (j = 1; j < img1.cols - 1; j++)
			{
				gx = 0; c = 0, gy = 0;
				for (k = 2 - kernel; k < kernel - 1; k++)
				{
					for (l = 2 - kernel; l < kernel - 1; l++)
					{
						gx += (img1.at<uchar>(i + k, j + l)*arr1[c]);
						gy += (img1.at<uchar>(i + k, j + l)*arr2[c]);

						c++;

					}
					gx = abs(gx);
					gy = abs(gy);
					g = sqrt(gx*gx + gy*gy);
					if (g < 256)
						img2.at<uchar>(i, j) = 0;
					else
						img2.at<uchar>(i, j) = 255;

				}
			}
		}
		 
		  imshow("filter - SOBEL",img2);

                                                                                                  /*NOW COMPARISON OF TWO IMAGES*/
   
   cvtColor(img2,img3,CV_GRAY2BGR);                                                               //CONVERTED SOBEL GRAYSCALE IMAGE TO COLORED IMAGE
   int p=60;
  	for(int i=0;i<img1.rows;i++)
	  for(int j=0;j<img1.cols;j++)
	    for(int k=0;k<3;k++)
	      {
		if(((img4.at<Vec3b>(i,j)[0]>p) &&
		  (img4.at<Vec3b>(i,j)[1]>p)   &&
		  (img4.at<Vec3b>(i,j)[2]>p))  ||
		  ((img4.at<Vec3b>(i,j)[0]>p)  &&
		  (img4.at<Vec3b>(i,j)[1]>p))  ||
		  ((img4.at<Vec3b>(i,j)[0]>p)) ||                                                 //COMPARING BOTH IMAGES
		  ((img4.at<Vec3b>(i,j)[1]>p)  &&
		  (img4.at<Vec3b>(i,j)[2]>p))  ||                                                 // TO GET A COLORED IMAGE 
		  ((img4.at<Vec3b>(i,j)[0]>p)  &&
		  (img4.at<Vec3b>(i,j)[2]>p))  ||
		  (img4.at<Vec3b>(i,j)[1]>p)   ||
		  (img4.at<Vec3b>(i,j)[2]>p)) 
	
		  img3.at<Vec3b>(i,j)[k]=img4.at<Vec3b>(i,j)[k];
	     }
	      namedWindow("noiseless image",WINDOW_AUTOSIZE);                                    //imshow("filter2",img3);
              imshow("noiseless image",img3);
	                                                                                         //NOW SETTING THE CENTRE PIXEL VALUES OF ALL POINTS
	
   int z=0;
       	for(int i=100;i<img3.rows;i+=99)
	  {
	    for(int j=100;j<img3.cols;j+=99)
	      {
		printf("\n %d ",z);
		z++;
		for(int k=0;k<3;k++)
		  {
		    if(((img3.at<Vec3b>(i,j)[0]>110)&& (img3.at<Vec3b>(i,j)[0]<140)) &&
		       ((img3.at<Vec3b>(i,j)[1]>110)&& (img3.at<Vec3b>(i,j)[1]<140)) &&
		       (img3.at<Vec3b>(i,j)[2]<40))
		       
		      {
		      img3.at<Vec3b>(i,j)[0]=128;
		      img3.at<Vec3b>(i,j)[1]=128;
		      img3.at<Vec3b>(i,j)[2]=0;
		      }
		    else   if(((img3.at<Vec3b>(i,j)[2]>110)&& (img3.at<Vec3b>(i,j)[2]<140)) &&
		             ((img3.at<Vec3b>(i,j)[1]>110)&& (img3.at<Vec3b>(i,j)[1]<140))  &&
			     (img3.at<Vec3b>(i,j)[0]<20))
		      {
		      img3.at<Vec3b>(i,j)[0]=0;
		      img3.at<Vec3b>(i,j)[1]=128;
		      img3.at<Vec3b>(i,j)[2]=128;
		      }
		    else   if((img3.at<Vec3b>(i,j)[0]>148) && (img3.at<Vec3b>(i,j)[1]<50) &&
			     ((img3.at<Vec3b>(i,j)[2]<50)))
		      {
		      img3.at<Vec3b>(i,j)[0]=255;
		      img3.at<Vec3b>(i,j)[1]=0;
		      img3.at<Vec3b>(i,j)[2]=0;
		      }
		    else    if((img3.at<Vec3b>(i,j)[1]>170)&& (img3.at<Vec3b>(i,j)[2]<65) &&
			      (img3.at<Vec3b>(i,j)[0]<65))
		      {
		      img3.at<Vec3b>(i,j)[0]=0;
		      img3.at<Vec3b>(i,j)[1]=255;
		      img3.at<Vec3b>(i,j)[2]=0;
		      }
		    else      if((img3.at<Vec3b>(i,j)[2]>170)&& (img3.at<Vec3b>(i,j)[1]<60) &&
			 ((img3.at<Vec3b>(i,j)[0]<60)))
		      {
		      img3.at<Vec3b>(i,j)[0]=0;
		    img3.at<Vec3b>(i,j)[1]=0;
		    img3.at<Vec3b>(i,j)[2]=255;
		      }
		    else if((img3.at<Vec3b>(i,j)[0]<50)&& (img3.at<Vec3b>(i,j)[1]<60) &&
			 ((img3.at<Vec3b>(i,j)[2]<50)))
		      {
		      img3.at<Vec3b>(i,j)[0]=0;
		      img3.at<Vec3b>(i,j)[1]=0;
		      img3.at<Vec3b>(i,j)[2]=0;
		      }
       
	  else	 if((img3.at<Vec3b>(i,j)[0]==0)  &&
		    (img3.at<Vec3b>(i,j)[1]==0)  &&
		    (img3.at<Vec3b>(i,j)[2]==83))
		   {
		   img3.at<Vec3b>(i,j)[0]=0;
		   img3.at<Vec3b>(i,j)[1]=0;
		   img3.at<Vec3b>(i,j)[2]=255;
		   }
     	  else   if((img3.at<Vec3b>(i,j)[0]==0)  &&
		    (img3.at<Vec3b>(i,j)[1]==0)  &&
		    (img3.at<Vec3b>(i,j)[2]==86))
	           {
		   img3.at<Vec3b>(i,j)[0]=0;
		   img3.at<Vec3b>(i,j)[1]=0;
		   img3.at<Vec3b>(i,j)[2]=255;
	           }
          else	 if((img3.at<Vec3b>(i,j)[0]==0)  &&
		    (img3.at<Vec3b>(i,j)[1]==0)  &&
		    (img3.at<Vec3b>(i,j)[2]==83))
		   {
		   img3.at<Vec3b>(i,j)[0]=0;
		   img3.at<Vec3b>(i,j)[1]=0;
		   img3.at<Vec3b>(i,j)[2]=255;
		   }
		   
	  else	 if((img3.at<Vec3b>(i,j)[0]==133)&&
		    (img3.at<Vec3b>(i,j)[1]==0)  &&
		    (img3.at<Vec3b>(i,j)[2]==0))
		   {
		   img3.at<Vec3b>(i,j)[0]=255;
		   img3.at<Vec3b>(i,j)[1]=0;
		   img3.at<Vec3b>(i,j)[2]=0;
		   }
	  else	 if((img3.at<Vec3b>(i,j)[0]==142)&&
		    (img3.at<Vec3b>(i,j)[1]==0)  &&
		    (img3.at<Vec3b>(i,j)[2]==0))
		   {
		   img3.at<Vec3b>(i,j)[0]=255;
		   img3.at<Vec3b>(i,j)[1]=0;
		   img3.at<Vec3b>(i,j)[2]=0;
		   }
	  else	 if((img3.at<Vec3b>(i,j)[0]==0) &&
		    (img3.at<Vec3b>(i,j)[1]==0) &&
		    (img3.at<Vec3b>(i,j)[2]==105))
		 {
		 img3.at<Vec3b>(i,j)[0]=0;
		 img3.at<Vec3b>(i,j)[1]=0;
		 img3.at<Vec3b>(i,j)[2]=255;
		 }
		   
	     //  printf( "  %d ",img3.at<Vec3b>(i,j)[k]);                                     FOR PRINTING THE BGR VALUES OF CENTRE OF COLORED IMAGE
		 }
	      }
	  }
		                                                                                //now we will make cost matrix
  int cost[20][20];
  int m=0,n=0;
  for(int i=100;i<img3.rows&&m<20;i+=99)
     {
         //  printf("\n");                                                                     //IF WANT TO SEE ACTUAL COST MATRIX
	 for(int j=100,n=0;j<img3.cols&&n<20;j+=99)
	  {
	    cost[m][n]=0;
	        if((img3.at<Vec3b>(i,j)[0]==0)  &&
		   (img3.at<Vec3b>(i,j)[1]==0)  &&
		   (img3.at<Vec3b>(i,j)[2]==0))
		cost[m][n]=0;
		if((img3.at<Vec3b>(i,j)[0]==255)&&
		   (img3.at<Vec3b>(i,j)[1]==0)  &&
		   (img3.at<Vec3b>(i,j)[2]==0))
		cost[m][n]=20;
		if((img3.at<Vec3b>(i,j)[0]==0)  &&
		   (img3.at<Vec3b>(i,j)[1]==255)&&
		   (img3.at<Vec3b>(i,j)[2]==0))
		cost[m][n]=15;
		if((img3.at<Vec3b>(i,j)[0]==0)  &&
		   (img3.at<Vec3b>(i,j)[1]==0)  &&
		   (img3.at<Vec3b>(i,j)[2]==255))
		cost[m][n]=12;
		if((img3.at<Vec3b>(i,j)[0]==128)&&
		   (img3.at<Vec3b>(i,j)[1]==128)&&
		   (img3.at<Vec3b>(i,j)[2]==0))
		cost[m][n]=10;
		if((img3.at<Vec3b>(i,j)[0]==0)  &&
		   (img3.at<Vec3b>(i,j)[1]==128)&&
		   (img3.at<Vec3b>(i,j)[2]==128))
		cost[m][n]=9;
	   //  printf("%d ",cost[m][n]);		      
       n++;
	  }
       m++;
	  }
	                                                                                    /*now we will apply djikstra BT BEFORE THAT
	                                                                                    MAKING THE A COST MATRIX WHICH
	                                                                                    IS TO BE USED IN DJIKSTRA*/
		
   int	acost[400][400];
     for(int i=0;i<400;i++)
       for(int j=0;j<400;j++)                                                               //FIRSTLY SETTING ALL THE VALUES TO INFINITY
	  {
	  acost[i][j]=INFINITY;  
	  }
     for(int m=0;m<20;m++)
	  {
       for(int n=0;n<20;n++)	    
	 {if(m!=0 && n!=0)
	     {
	      i=20*m+n-1;
	      j=20*m+n;
	      acost[i][j]=acost[j][i]=cost[m][n];
	     }
	      if(m!=0)
		{
	      i=20*m+n-20;
	      j=20*m+n;
	      acost[i][j]=acost[j][i]=cost[m][n];
		}                                 
	    }
          }
     /*  for (int i=0;i<400;i++)
	  {
	      printf("\n");
	                                                                                   // IF WANT TO PRINT THE ACOST MATRIX
	      for(int j=0;j<400;j++)
		{                                                                 
		  printf("%d  ",acost[i][j]);
		}
		}*/
	
	                                                                                   /* Dijkstra's Algorithm in C */
  int u=0;
  n=378; 
  int *ll= dijkstra(acost,n,u);  
   i=36;
   while(puka[i]!=378)
     {
     
       Point pt1,pt2;
       pt1.y=100+99*(puka[i]/20);
       pt1.x=100+99*(puka[i]%20);                                                          //MAKING THE PATH IN GRAPH
       pt2.y=100+99*(puka[i-1]/20);
       pt2.x=100+99*(puka[i-1]%20);
       line( img3,Point (pt1.x,pt1.y),Point (pt2.x,pt2.y),Scalar(0,0,255),2,8,0);
       i--;
     }
     namedWindow("pathjpg",WINDOW_NORMAL);
     imshow("pathjpg",img3);
     waitKey(0);
}
 
int * dijkstra(int cost[MAXA][MAXA],int n,int startnode)
{
 
    int distance[MAXA],pred[MAXA];
    int visited[MAXA],count,mindistance,nextnode,i,j ;                                                                                                                                                                                          //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
      mindistance=INFINITY;
        
                                                                                          //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }                                                                             //check if a better path exists through nextnode           
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }
   int m=2;
    puka[0]=378;
    puka[1]=377;
                                                                                          //print the path and distance of each node
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
            printf("\nDistance of node%d=%d",i,distance[i]);
            printf("\nPath=%d",i);
            int  j=i;
            do
            {
                j=pred[j];
                printf("<-%d",j);
		if(i==377)
		  {
		  
		  puka[m]=j;
		  m++;
	          }
            }while(j!=startnode);
        }
    /* for(j=0;j<40;j++)                                                             //FOR PRINTING THE PATH AND DISTANCE
       printf(" %d   ",puka[j]);*/
    return puka;
}	    

