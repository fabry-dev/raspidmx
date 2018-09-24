#ifndef SENSORS_H
#define SENSORS_H
#include "QObject"
#include "/home/pi/PIGPIO/pigpio.h"
static const int outputs[] = {5,6,13,19,26,21,20,16,12,1};




class Sensor : public QObject {
    Q_OBJECT
public:
    Sensor();
    ~Sensor();
public slots:
    void process();
    void stop();
    void startProcess();
signals:
    void pushButton(int);
    void releaseButton(int);
private:
    bool active;
    std::vector<bool> buttonStates;

};

#endif // SENSORS_H
