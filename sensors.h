#ifndef SENSORS_H
#define SENSORS_H
#include "QObject"
#include "/home/fred/PIGPIO/pigpio.h"





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
