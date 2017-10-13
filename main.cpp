#include <iostream>
#include <fstream>
#include <string>
#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    bool playVideo = true;
//    VideoCapture cap(argv[1]);
//    if(!cap.isOpened())
//    {
//        cout<<"Unable to open video "<<argv[1]<<"\n";
//        return 0;
//    }
//    vector<Mat>src;
//    Mat frame, img;
//    namedWindow("Video",CV_WINDOW_FREERATIO);
//    namedWindow("Vdo",CV_WINDOW_FREERATIO);

//    while(1)
//    {
//        if(playVideo)
//            cap >> frame;

//        int CurrentFrame=cap.get(CV_CAP_PROP_POS_FRAMES);
//        int TotalFrame=cap.get(CV_CAP_PROP_FRAME_COUNT);


//        cout<<TotalFrame<<"   "<<CurrentFrame<<"    ";

//        if(frame.empty())
//        {
//            cout<<"Empty Frame\n";
//            return 0;
//        }
//        imshow("Video",frame);
//        if(CurrentFrame>6)
//        {
//            cap.set(CV_CAP_PROP_POS_FRAMES,CurrentFrame-6);
//            cap>>img;
//            imshow("Vdo",img);
//            cap.set(CV_CAP_PROP_POS_FRAMES,CurrentFrame);
//        }

//        char key = waitKey(1);
//        if(key == 'p')
//            playVideo = !playVideo;
//        if(key == 'q')
//            break;
//    }
//    return 0;

    return a.exec();
}
