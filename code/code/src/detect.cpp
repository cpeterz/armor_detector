//注释代码全为调试时使用

#include"detect.h"
using namespace std;
using namespace cv;

void detect::function()
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy; 
    VideoCapture capture(filename);
    while (capture.isOpened()) {
        Mat frame;
        capture>>frame;
        if(frame.empty())
            {
                cout<<"no picture now"<<endl;
                break;
            }

        Mat hsvimg;
        cvtColor(frame,hsvimg,COLOR_BGR2HSV);

        /*vector<Mat> hsvsplit;

        split(hsvimg,hsvsplit);
        equalizeHist(hsvsplit[2],hsvsplit[2]);
        merge(hsvsplit,hsvimg);
        */

        Mat thresholdimg,blurimg,Gaussian;
        inRange(hsvimg,Scalar(LowH,LowS,LowV),Scalar(HighH,HighS,HighV),thresholdimg);
        //medianBlur(thresholdimg,blurimg,3);
        GaussianBlur(thresholdimg,Gaussian,Size(3,3),0);      //对二值图像采用高斯平滑
        //imshow("out",Gaussian);
        findContours(Gaussian,contours,hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
       
        /*Rect boundRect;
        findContours(Gaussian,contours,hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
        
        for(int i=0;i<contours.size();i++){
            boundRect = boundingRect(Mat(contours[i]));
            rectangle(frame,boundRect.tl(),boundRect.br(),Scalar(0,255,0),2,8);
            cout<<boundRect.width<<"#####"<<boundRect.height<<endl;
        }

        imshow("out1",frame);
        */
        int index=0;
        Rect point_array[1000],boundRect;
        for(int i=0;i<contours.size();i++){                //筛选轮廓
            boundRect = boundingRect(Mat(contours[i]));
            //rectangle(frame,boundRect.tl(),boundRect.br(),Scalar(0,255,0),2,8);
            try
            {
                if(double(boundRect.height/boundRect.width) >= 1.7 && boundRect.width>8 ) {
                    point_array[index] = boundRect;
                    index++;
                    //cout<<index<<endl;
                }
            }
            catch(const char *msg)
            {
                cout<<msg<<endl;
            }
        }
        int point_near[2];   //找出大小最接近的两个轮廓
        int min = 99999;
        for(int i=0; i<index-1 ;i++){
            for(int j=i+1; j < index; j++){
                int value = abs(point_array[i].area() - point_array[j].area() );
                if(value < min){
                    min = value;
                    point_near[0]=i;
                    point_near[1]=j;
                }
                
            }
        }
        
        try        //根据找到的轮廓作出四边形包围
        {
           Rect recttangle_0 =  point_array[point_near[0]];
           Rect recttangle_1 =  point_array[point_near[1]];
           Point point1 =   Point(recttangle_0.x + recttangle_0.width/2,recttangle_0.y);
           Point point2 =   Point(recttangle_0.x + recttangle_0.width/2,recttangle_0.y+recttangle_0.height);
           Point point4 =   Point(recttangle_1.x + recttangle_1.width/2,recttangle_1.y);
           Point point3 =   Point(recttangle_1.x + recttangle_1.width/2,recttangle_1.y+recttangle_1.height);
           Point p[4]={point1,point2,point3,point4};
          // cout<<p[0]<<p[1]<<p[2]<<p[3]<<endl;
           for(int i = 0;i < 4;i++){
               line(frame,p[i],p[(i+1)%4],Scalar(0,255,0),2);
           }
           
           Point point;                        //在图像固定位置根据hsv和height描述出其颜色和大小           
            if(point1.x>point3.x){
                point.x=point3.x;
            }else{
                point.x=point1.x;
            }
            if(point2.y>point4.y){
                point.y=point2.y;
            }else{
                point.y=point4.y;
            }            
            int height=recttangle_0.height;

            if(HighH<125 && HighH>100){
              if(height > 100){
                putText(frame,"big,blue",point,FONT_HERSHEY_SIMPLEX,2,Scalar(255,0,0),2);
              }else if(height > 60 && height<=100){
                 putText(frame,"medium,blue",point,FONT_HERSHEY_COMPLEX,2,Scalar(255,0,0),2);
              }else{
                putText(frame,"small,blue",point,FONT_HERSHEY_SIMPLEX,2,Scalar(255,0,0),2);
              }
            }
            if((HighH>0 && HighH<10)||(HighH>156 && HighH<180)){
                if(height > 100){
                putText(frame,"big,red",point,FONT_HERSHEY_SIMPLEX,2,Scalar(255,0,0),2);
            }else if(height > 60 && height<=100){
                putText(frame,"medium,red",point,FONT_HERSHEY_COMPLEX,2,Scalar(255,0,0),2);
            }else{
                putText(frame,"small,red",point,FONT_HERSHEY_SIMPLEX,2,Scalar(255,0,0),2);
            }
            }
        }
        catch(const char* msg){
            cout<<msg<<endl;
        }
        imshow("out",frame);
        int key=waitKey(10);
        if(key == 27){
            break;
        }
    }
}