// cv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>  
#include<string>
using namespace cv;  
using namespace std;  
  
const int kvalue = 15;//双边滤波邻域大小  
  string s1="C:\\Users\\jin\\pictures\\";
  string s2=".jpg";
  //输入形参为pass by conference-const，保证输入的图像不会被修改，并且为传递引用
  
  bool istrue(uchar a[],int x,int y){
  for(int i=x;i<x+10;i++)
	  if((int)a[i]!=0)return false;
	  
  
  return true;
  
  }
 
  bool istrue2(Mat result,int x,int y,int nc){
  
  
    for(int j=x; j<x+100 ;++j)  
    {  
       uchar *data = result.ptr<uchar>(j);  
         
            
			if((int)data[nc/2]!=0){
				return false;
			
       
    }  
  
	}
  
  return true;
  }

int main()  
 { 
	 
    Mat  img = imread(s1+"head3d.jpg");//读取原彩色图  
	

	
	Mat After(img.rows, img.cols, CV_8UC4);//这里是更改图片背景，统一颜色，以后的图片叠加好去色  
	
    for (int i = 0; i < img.rows; i++)  
    {  
        for (int j = 0; j < img.cols; j++)  
        {   
            After.at<Vec4b>(i, j)[0] = img.at<Vec3b>(i, j)[0];
            After.at<Vec4b>(i, j)[1] = img.at<Vec3b>(i, j)[1] ;  
            After.at<Vec4b>(i, j)[2] = img.at<Vec3b>(i, j)[2];  
			After.at<Vec4b>(i, j)[3] = 255;
		
        }  
    }
	img=After;
	int c=img.cols/5;
	int r=img.rows/5;
	
	cout<<img.rows<<" "<<img.cols<<" "<<img.channels()<<endl;
	
	namedWindow("原始图像",0);
	resizeWindow("原始图像",c,r);
	 imshow("原始图像", img);
	
	   //创建与src同类型和同大小的矩阵
	 Mat bf,result;
   

    //将原始图转化为灰度图
    cvtColor(img, bf, COLOR_BGR2GRAY);
    threshold(bf, result, 0, 255, CV_THRESH_BINARY);  

	namedWindow("d",0);
	resizeWindow("d",c,r);
    imshow("d", result);
	
	cout<<result.rows<<" "<<result.cols<<" "<<result.channels()<<endl;

	 int nl = result.rows;  
    int nc = result.cols * result.channels();  
      int l1=0,l2=0;
	  int f=0;
	 


	  uchar *data = result.ptr<uchar>(nl/2);  
 
    for(int j=0; j<nc ;++j)  
    {  
       
         
            if((int)data[j]&&!f)
			{l1=j;f=1;}
			if(f&&istrue(data,j,nc)){
				
				
			l2=j;break;}
       
    }  
	int r1=0,r2=0;
	  f=0;
	  
 
    for(int j=0; j<nl ;++j)  
    {  
       uchar *data = result.ptr<uchar>(j);  
         
            if((int)data[nc/2]&&!f)
			{r1=j;f=1;break;}
			
       
    }  

	cout<<l1<<" "<<l2<<" "<<r1<<" "<<r2<<endl;
	for(int x=r1;x<nl/2;x++){
		  uchar *data = result.ptr<uchar>(x);
		  
		for (int y=l1;y<l2;y++)
		{  
			if((int)data[y]==0)data[y]=255;
		
		
		}
	
	}
	
	
	namedWindow("dd",0);
	resizeWindow("dd",c,r);
    imshow("dd", result);
	
	for(int x=0;x<result.rows;x++){
		
		
		 uchar *data = result.ptr<uchar>(x);
		
		for(int y=0;y<result.cols;y++)
		{
			
			if((int)data[y]==0){
		
    img.at<Vec4b>(x,y)[3]=0;
	
		}
		
		
		
		}
	}

	imwrite(s1+"head3dafter.png",img);
	

	
  
    waitKey();  
}  