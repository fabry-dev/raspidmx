#ifndef BUTTON_H
#define BUTTON_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "qpushbutton.h"





class button:public QLabel
{
    Q_OBJECT

public:
    button(QWidget* parent = 0, int id=-1, int w=10, QString on="", QString off="", bool ignoreEmptySpace=true, QString fontName="", QString PATH="", QString txt="",int fontsize=12);
    ~button();
    void setWidth(int w);
    double ratio;

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * ev);

private:
    int id;//button identifier
    void drawState(bool activated);
    QImage *onPix,*offPix;


    bool ignoreEmptySpace;
    QString fontName, PATH,txt;
    int fontsize;


signals:
    void clicked(int);
    void released(int);

};








#endif
