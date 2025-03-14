#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) override;
    void GenerateImage(long double x1, long double y1, long double x2, long double y2);
    void keyPressEvent(QKeyEvent *event) override;
    QImage image;
    bool saveImg = false;

private:
    Ui::MainWindow *ui;
    QImage randomImage;
    void generateRandomImage();
};

#endif // MAINWINDOW_H
