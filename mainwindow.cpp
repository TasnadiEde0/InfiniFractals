#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QtWidgets>
#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QDebug>
#include <QRandomGenerator>
#include <pthread.h>
#include "calcthread.h"

using namespace std;

long double ox1 = -2, ox2 = 1, oy1 = 1, oy2 = -1;

static QTextStream ts(stdout);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int h = 1040;
    setFixedSize(h / 2 * 3, h);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        long double mx = (ox1 + ox2) / 2;
        long double my = (oy1 + oy2) / 2;

        long double nx = abs(ox2 - ox1) * 2;
        long double ny = abs(oy2 - oy1) * 2;

        ox1 = mx - nx/2;
        ox2 = mx + nx/2;
        oy1 = my + ny/2;
        oy2 = my - ny/2;

        repaint();
    }
    if(event->key() == Qt::Key_Down)
    {
        long double mx = (ox1 + ox2) / 2;
        long double my = (oy1 + oy2) / 2;

        long double nx = abs(ox2 - ox1) / 2;
        long double ny = abs(oy2 - oy1) / 2;

        ox1 = mx - nx/2;
        ox2 = mx + nx/2;
        oy1 = my + ny/2;
        oy2 = my - ny/2;

        repaint();

        // ts << to_string(mx).c_str() << " " << to_string(my).c_str() << " " << to_string(nx).c_str() << " " << to_string(ny).c_str() << "\n";
        // ts << to_string(ox1).c_str() << " " << to_string(ox2).c_str() << " " << to_string(oy1).c_str() << " " << to_string(oy2).c_str() << "\n";
    }
    if(event->key()== Qt::Key_A){
        long double r = abs(ox2 - ox1) / 10;
        ox1 -= r;
        ox2 -= r;
        repaint();
    }
    if(event->key()== Qt::Key_W){
        long double r = abs(oy2 - oy1) / 10;
        oy1 += r;
        oy2 += r;
        repaint();
    }
    if(event->key()== Qt::Key_S){
        long double r = abs(oy2 - oy1) / 10;
        oy1 -= r;
        oy2 -= r;
        repaint();
    }
    if(event->key()== Qt::Key_D){
        long double r = abs(ox2 - ox1) / 10;
        ox1 += r;
        ox2 += r;
        repaint();
    }
    if(event->key()== Qt::Key_P){
        saveImg = true;
    }

}



void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    GenerateImage(ox1, oy1, ox2, oy2);
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void MainWindow::GenerateImage(long double x1, long double y1, long double x2, long double y2) {
    image = QImage(width(), height(), QImage::Format_RGB32);
    image.fill(QColor(0, 0, 0));
    // image.fill(QColor(255, 255, 255));

    long double rx = (x2 - x1) / width();
    long double ry = (y2 - y1) / height();

    int n = 12;

    CalcThread **threads = new CalcThread*[n];

    for(int i = 0; i < n; i++) {
        threads[i] = new CalcThread(nullptr, this, n, i, rx, ry, x1, y1, x2, y2, width(), height());

        threads[i] -> start();
    }

    for(int i = 0; i < n; i++) {
        threads[i] -> wait();
        delete threads[i];
    }

    delete[] threads;

    if(saveImg){
        image.save((to_string(QRandomGenerator().generate()) + ".png").c_str());
        saveImg = false;
    }

    // for(int i = 0; i < image.width(); ++i) {
    //     for(int j = 0; j < image.height(); ++j) {
    //         if(MandelTest(x1 + i * rx, y1 + j * ry)){
    //             image.setPixel(i, j, qRgb(0, 0, 0));
    //         }
    //     }
    // }

}

