#include "sensors.h"
#include "qdebug.h"
#include "qthread.h"
#define Nbuttons 10
#define Noutputs 10

static const int buttons[] = {2,3,4,17,27,22,10,9,11,0};



Sensor::Sensor() { // Constructor
    if (gpioInitialise() < 0)
    {
        qDebug()<<"pigpio initialisation failed.";
        exit(1);
    }
    else
    {
        qDebug()<<"pigpio initialised okay.";
    }


    for (int i= 0;i<Nbuttons;i++)
    {
        gpioSetMode(buttons[i], PI_INPUT);
        gpioSetPullUpDown(buttons[i], PI_PUD_UP);

    }
    for (int i= 0;i<Noutputs;i++)
    {
        gpioSetMode(outputs[i], PI_OUTPUT);


    }


}

Sensor::~Sensor() { // Destructor
    // free resources
}



void Sensor::startProcess()
{
    process();

}


void Sensor::process() { // Process. Start processing data.
    bool state;
    active = true;
    buttonStates.resize(Nbuttons,true);
    while(active)
    {
        for (int i= 0;i<Nbuttons;i++)
        {
            state = gpioRead(buttons[i]);
            if(state!=buttonStates.at(i))
            {

                buttonStates[i] =state;
                if(state == false)
                {
                    qDebug()<<i+1<<" on";
                    emit pushButton(i+1);
                }
                else
                {
                    qDebug()<<i+1<<" off";
                    emit releaseButton(i+1);

                }

            }



        }




        QObject().thread()->usleep(1000*20);
    }



}


void Sensor::stop()
{

    active = false;
}
