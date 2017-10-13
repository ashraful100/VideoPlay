#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QMessageBox>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->label_2->setScaledContents(true);
    ui->label_2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );   

    connect(this, SIGNAL(sendCurrentFrame(int&)),ui->spinBox,SLOT(setValue(int)));


    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Browse_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Videos (*.avi)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString videofileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/Users/ASHRAF/Desktop/", tr("Videos (*.avi)"));

    if(!videofileName.isEmpty())
    {
        cv::String videopath;

        videopath = videofileName.toLocal8Bit().constData();

        bool playVideo = true;
        VideoCapture cap(videopath);
        if(!cap.isOpened())
        {
            QMessageBox::warning(this, tr("Warning"),tr("Error loadeing video."));
            exit(0);
        }        
        Mat3b frame1, frame2;
        QImage dest, image;

        while(1)
        {                        
            cap >> frame1;
            int CurrentFrame=cap.get(CV_CAP_PROP_POS_FRAMES);
            int TotalFrame=cap.get(CV_CAP_PROP_FRAME_COUNT);
            ui->spinBox->setMaximum(TotalFrame);                       
            ui->horizontalSlider->setMaximum(ui->spinBox->maximum());

            emit sendCurrentFrame(CurrentFrame);

            dest= Mat3b2QImage(frame1);
            ui->label->setPixmap(QPixmap::fromImage(dest));
            QApplication::processEvents();
            if(CurrentFrame>1)
            {
                cap.set(CV_CAP_PROP_POS_FRAMES, CurrentFrame-1);
                cap >> frame2;
                image= Mat3b2QImage(frame2);
                ui->label_2->setPixmap(QPixmap::fromImage(image));
                QApplication::processEvents();
                cap.set(CV_CAP_PROP_POS_FRAMES, CurrentFrame);
            }

            if(frame1.empty())
            {
                QMessageBox::warning(this, tr("Warning"),tr("Video frame cannot be openned."));
                break;
            }         
        }
    }
}

QImage MainWindow::Mat3b2QImage (Mat3b src)
{
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
            for (int y = 0; y < src.rows; ++y) {
                    const cv::Vec3b *srcrow = src[y];
                    QRgb *destrow = (QRgb*)dest.scanLine(y);
                    for (int x = 0; x < src.cols; ++x) {
                            destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                    }
            }
           return dest;

}

void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}
