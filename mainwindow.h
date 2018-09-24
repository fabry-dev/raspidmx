#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qfile.h"
#include "qdebug.h"
#include "button.h"
#include "sensors.h"
#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/Cassiopee/RaspiDMX/files/"
#define BUTTON_WIDTH_DEFAULT  100


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void getParams(QStringList params);
    QString PATH;
    bool HIDE_CURSOR;
    void readParamFile();
    std::vector<button*> buttonList;
    void arrangeButtons();
    void sendDmx();
    std::vector<bool> lights;
    void turnLightOn(int n);
    void turnLightOff(int n);
    void fadeDmx2();
    void resetDmx2();
    void initGpios();
    Sensor* sensor;

protected:
    bool eventFilter(QObject *obj, QEvent *event);


private slots:
    void onButtonPressed(int id);
    void onButtonReleased(int id);

signals:
    void startSensor();
};

#endif // MAINWINDOW_H
