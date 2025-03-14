#ifndef CALCTHREAD_H
#define CALCTHREAD_H

#include "mainwindow.h"
#include <QImage>
#include <QtWidgets>
#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QDebug>
#include <QRandomGenerator>

class CalcThread : public QThread {
    Q_OBJECT

    MainWindow *mainWindow;
    int n;
    int ii;
    long double rx;
    long double ry;
    long double x1;
    long double y1;
    long double x2;
    long double y2;
    int width;
    int height;

public:
    CalcThread(QObject *parent = nullptr, MainWindow *mainWindow = nullptr, int n = 2, int i = 0, long double rx = 0,long double ry = 0,
               long double x1 = 0, long double y1 = 0, long double x2 = 0, long double y2 = 0, int width = 0, int height = 0);

    void run() override;
};

#endif // CALCTHREAD_H
