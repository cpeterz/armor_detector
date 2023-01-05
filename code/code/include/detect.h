#pragma once
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
#include<string.h>

class detect
{
public:
  char filename[100];
  int LowH = 100;
  int LowS = 100;
  int LowV =150;

  int HighH = 124;
  int HighS = 255;
  int HighV =255;


  detect(char _filename[]){
     strcpy(filename,_filename);
  }
  void parame(int lowh,int lows,int lowv,int highh,int highs,int highv){
      LowH=lowh;
      LowS=lows;
      LowV=lowv;
      HighH=highh;
      HighS=highs;
      HighV=HighV;
      //std::cout<<HighH<<"####"<<LowH<<std::endl;
  }
  
  void function();


};
