#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "QTimer"
#include "qthread.h"






void MainWindow::turnLightOff(int n)
{
    if(n>10) return;
    if(n<1) return;

    lights[n-1] = false;

    sendDmx();


}


void MainWindow::turnLightOn(int n)
{
    if(n>10) return;
    if(n<1) return;
    lights[n-1] = true;
    sendDmx();
}





void MainWindow::sendDmx()
{
    unsigned long m = 1;
    unsigned long msg = 0;
    for (int i = 0;i<10;i++)
    {

        msg += lights[i] *m;
        m*=2;

    }
    QString txt = "/usr/bin/python "+PATH+"setDmx.py "+QString::number(msg)+" &";
    system(txt.toStdString().c_str());



}


void MainWindow::fadeDmx2()
{

    QString txt = "/usr/bin/python "+PATH+"fadeDmx.py &";
    system(txt.toStdString().c_str());

}

void MainWindow::resetDmx2()
{

    QString txt = "/usr/bin/python "+PATH+"resetDmx.py &";
    system(txt.toStdString().c_str());



}





