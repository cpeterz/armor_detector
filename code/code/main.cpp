#include"detect.h"
using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    char filename_[] = "res/video.avi";
    detect mydetect(filename_);   //函数接口，即传入视频文件的位置
    FileStorage fs_read("config/test.yaml",FileStorage::READ);
    char key[]="blue";           //key可赋值为blue,red1,red2,green调用参数文件
    vector<int> parameter;
    FileNode seq=fs_read[key];
    FileNodeIterator it = seq.begin();
    FileNodeIterator it_end=seq.end();
    for( ; it!=it_end;it++ )
    {
       parameter.push_back((int)(*it));       
    }
    fs_read.release();
    
    mydetect.parame(parameter[0],parameter[1],parameter[2],parameter[3],parameter[4],parameter[5]);   //可通过调制参数筛选颜色范围，默认范围是蓝色范围
    mydetect.function();            //调用函数功能：识别并追踪视频中指定颜色的装甲板，并输出其相对大小和颜色
    return 0;
}