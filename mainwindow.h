#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <opencv/highgui.h>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage Mat3b2QImage (Mat3b src);
    ~MainWindow();

private slots:
    void on_Browse_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;    
//    QMediaPlayer *player;
//    QVideoWidget *vw;
signals:
    void sendCurrentFrame(int&);
};

#endif // MAINWINDOW_H
