#include "algorithm"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"
#include "QFont"
#include "qfontdatabase.h"
#include "qpalette.h"
#include "qtextdocument.h"
#include "qstatictext.h"
#include "button.h"



button::button(QWidget* parent , int id, int w, QString on, QString off,bool ignoreEmptySpace,QString fontName,QString PATH,QString txt,int fontsize)
    : QLabel(parent),id(id),ignoreEmptySpace(ignoreEmptySpace),fontName(fontName),PATH(PATH),txt(txt),fontsize(fontsize)
{

    hide();

    offPix = new QImage(PATH+off); //preload image
    onPix = new QImage(PATH+on); //preload image

    ratio = (double)(offPix->width())/(offPix->height());

    setWidth(w);



    //this->setStyleSheet("border: 1px solid black");


    drawState(false);

}


void button::setWidth(int w)
{
    int h = offPix->height()*w/offPix->width();
    this->resize(w,h);
}




void button::drawState(bool state)
{
    QPixmap pix;

    if(state)
        pix = QPixmap::fromImage((*onPix).scaled(width(),height()));
    else
        pix = QPixmap::fromImage((*offPix).scaled(width(),height()));


    int id = QFontDatabase::addApplicationFont(PATH+fontName);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family,fontsize);



    QPainter painter( &pix);
    painter.setFont( font );
    painter.setPen(Qt::white);

    painter.drawText(QRectF(0,0,width(),height()),Qt::AlignCenter,txt);

    setPixmap(pix);
}


void button::mousePressEvent( QMouseEvent* ev )
{
    QImage image(pixmap()->toImage());
    QColor color(image.pixel(ev->pos()));



    if((color.black()==255)&(color.hslHue()==-1)&(color.hslSaturation()==0)&(ignoreEmptySpace))//transparent area
        return;

    drawState(true);
  emit clicked(id);
}


void button::mouseReleaseEvent(QMouseEvent * ev)
{
    drawState(false);
     emit released(id);
}


button::~button()
{


}

