#include "calcthread.h"

long double MandelTest(long double x0, long double y0){
    int maxIter = 1000;
    int maxBaseIter = 10;
    int iter = 0;
    long double x = 0;
    long double y = 0;
    long double tempX;

    while(iter < maxBaseIter && x * x + y * y < 4.0) {
        tempX = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = tempX;
        iter++;
    }

    if(x * x + y * y >= 4.0) {
        return 0;
    }

    while(iter < maxIter && x * x + y * y < 4.0) {
        tempX = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = tempX;
        iter++;
    }

    // return (iter - maxBaseIter) / (long double)(maxIter - maxBaseIter);
    return iter / (long double)maxIter;
}

QColor colors[1000];

void colors_doer() {
    // int rs[7] = {10, 50, 100, 150, 200, 1000};
    // int rs[] = {10, 15, 20, 25, 30, 35};
    int rs[] = {20, 25, 30, 35, 40, 45};

    int r = 0, g = 0, b = 0;

    for(int i = rs[0]; i < rs[1]; i++) {
        colors[i + rs[0]] = QColor(r, g, b);
        r += 255 / (rs[1] - rs[0]);
    }
    r = 255;

    for(int i = rs[1]; i < rs[2]; i++) {
        colors[i] = QColor(r, g, b);
        g += 165 / (rs[2] - rs[1]);
    }
    g = 165;

    for(int i = rs[2]; i < rs[3]; i++) {
        colors[i] = QColor(r, g, b);
        g += 90 / (rs[3] - rs[2]);
    }
    g = 255;

    for(int i = rs[3]; i < rs[4]; i++) {
        colors[i] = QColor(r, g, b);
        g -= 255 / (rs[4] - rs[3]);
    }
    r = 0;

    for(int i = rs[4]; i < rs[5]; i++) {
        colors[i] = QColor(r, g, b);
        g -= 255 / (rs[5] - rs[4]);
        b += 255 / (rs[5] - rs[4]);
    }
    g = 0;
    b = 255;

    for(int i = rs[4]; i < rs[5]; i++) {
        colors[i] = QColor(r, g, b);
        r += 75 / (rs[5] - rs[4]);
        b -= 125 / (rs[5] - rs[4]);
    }
    r = 75;
    b = 130;
    colors[rs[5] - 1] = QColor(r, g, b);

    for(int i = rs[5]; i < 1000; i++) {
        colors[i] = QColor(0, 0, 0);
    }
}

void colors_doer2() {
    // int rs[7] = {10, 50, 100, 150, 200, 1000};
    // int rs[] = {10, 15, 20, 25, 30, 35};
    int rs[] = {20, 25, 30, 35};

    int r = 0, g = 0, b = 0;

    for(int i = 0; i < rs[0]; i++) {
        colors[i + rs[0]] = QColor(r, g, b);
    }

    for(int i = rs[0]; i < rs[1]; i++) {
        colors[i + rs[0]] = QColor(r, g, b);
        r += 255 / (rs[1] - rs[0]);
    }
    r = 255;

    for(int i = rs[1]; i < rs[2]; i++) {
        colors[i] = QColor(r, g, b);
        g += 165 / (rs[2] - rs[1]);
    }
    g = 165;

    for(int i = rs[2]; i < rs[3]; i++) {
        colors[i] = QColor(r, g, b);
        g += 90 / (rs[3] - rs[2]);
    }
    g = 255;
    colors[rs[3] - 1] = QColor(r, g, b);

    for(int i = rs[3]; i < 1000; i++) {
        colors[i] = QColor(0, 0, 0);
    }
}

CalcThread::CalcThread(QObject *parent, MainWindow *mainWindow, int n, int i, long double rx,long double ry,
                       long double x1, long double y1, long double x2, long double y2, int width, int height) : QThread(parent) {
    this->mainWindow = mainWindow;
    this->n = n;
    this->ii = i;
    this->rx = rx;
    this->ry = ry;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->width = width;
    this->height = height;
    colors_doer();
}

void CalcThread::run() {
    int nrx = width / n;
    int nry = height / n;
    long double number;
    for(int i = nrx * ii; i < nrx * (ii + 1); i++) {
        for(int j = 0; j < height; ++j) {
            if((number = MandelTest(x1 + i * rx, y1 + j * ry)) != 0){
                if(number != 1) {
                    // if(number < 1) {
                    //     mainWindow->image.setPixel(i, j, qRgb(colors[(int)(number * 1000)].red(), colors[(int)(number * 1000)].green(), colors[(int)(number * 1000)].blue()));
                    // }


                    number = 255 * number * 2;
                    if(number > 255) {
                        number = 255;
                    }

                    mainWindow->image.setPixel(i, j, qRgb(number, 0, 0));

                }
                // mainWindow->image.setPixel(i, j, qRgb(255 * (1 - number) * 25, 255 * (1 - number) * 25, 255 * (1 - number)));
            }
        }
    }

}
