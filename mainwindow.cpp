#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sensors.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    installEventFilter(this);

    ui->setupUi(this);

    lights.resize(10,false);



    getParams(QCoreApplication::arguments());
    readParamFile();


    initGpios();

    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
    }


    setWindowState(Qt::WindowFullScreen);

}




void MainWindow::getParams(QStringList params)
{
    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;
}

void MainWindow::readParamFile()
{
    QFile file(PATH+"config.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no config file";
        return;
    }

    QTextStream in(&file);

    int fontsize = 12;
    int buttonWidth = BUTTON_WIDTH_DEFAULT;

    QString  line;
    QString paramName,paramValue;
    QStringList params;
    int buttonNb;
    bool test;
    QString font = "";

    QStringList buttonNames;
    std::vector<int> buttonValues;

    while(!in.atEnd()) {
        line = in.readLine();
        line = (line.split("#"))[0];
        params = line.split("=");

        if(params.size()>=2)
        {
            paramName = params[0];
            paramValue = params[1];

            if(paramName.mid(0,6)=="BUTTON")
            {
                buttonNb = paramName.mid(6).toInt(&test);
                if((test)&&(buttonNb<=10)&&(buttonNb>0))
                {
                    //qDebug()<<"button: "<<buttonNb<<" : "<<paramValue;
                    buttonValues.push_back(buttonNb);
                    buttonNames.push_back(paramValue);
                }
            }
            else if (paramName.mid(0,6)=="CURSOR")
            {
                HIDE_CURSOR = (paramValue=="NO");

            }
            else if (paramName.mid(0,4)=="FONT")
            {

                font = paramValue;


            }
            else if (paramName.mid(0,5)=="FSIZE")
            {

                int nufontsize = paramValue.toInt(&test);
                if((test)&&(nufontsize>0))
                {
                    fontsize = nufontsize;
                }
            }
            else if (paramName.mid(0,6)=="BWIDTH")
            {

                int nuButtonWidth = paramValue.toInt(&test);
                if((test)&&(nuButtonWidth>0))
                {
                    buttonWidth = nuButtonWidth;
                }
            }
            else
            {
                qDebug()<<paramName<<" - "<<paramValue;
            }
        }

    }

    file.close();


    qDebug()<<font;

    for(int i = 0;i<buttonValues.size();i++)
    {
        qDebug()<<"button: "<<buttonValues[i]<<" : "<<buttonNames[i];

        button * b = new button(this,buttonValues[i],buttonWidth,"buttonOn.png","buttonOff.png",false,font,PATH,buttonNames[i],fontsize);
        buttonList.push_back(b);
        connect(b,SIGNAL(clicked(int)),this,SLOT(onButtonPressed(int)));
        connect(b,SIGNAL(released(int)),this,SLOT(onButtonReleased(int)));
        b->show();
    }

    arrangeButtons();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        QResizeEvent* resizeEv = static_cast<QResizeEvent*>(event);



        arrangeButtons();
    }

}

void MainWindow::arrangeButtons()
{


    QPixmap bkgnd(PATH+"background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    int nbButton = buttonList.size();



    if(width()>height())
    {

        if(nbButton<=5)
        {
            for (int i = 0;i<nbButton;i++)
            {
                button *b = buttonList[i];
                int offset = (width()-nbButton*b->width())/(nbButton+1);
                b->move(offset*(1+i)+b->width()*i,height()/2-b->height()/2);

            }
        }
        else
        {


            int nbButton1 = nbButton/2;
            int nbButton2 = nbButton/2;

            if(nbButton1+nbButton2<nbButton)
                nbButton1++;


            for (int i = 0;i<nbButton1;i++)
            {
                button *b = buttonList[i];
                int offsetY = (height()-2*b->height())/(2+1);
                int offset = (width()-nbButton1*b->width())/(nbButton1+1);
                b->move(offset*(1+i)+b->width()*i,offsetY);


            }
            for(int i = nbButton1;i<nbButton1+nbButton2;i++)
            {
                button *b = buttonList[i];
                int j = i-nbButton1;
                int offsetY = (height()-2*b->height())/(2+1);
                int offset = (width()-nbButton2*b->width())/(nbButton2+1);
                b->move(offset*(1+j)+b->width()*j,offsetY*2+b->height());


            }


        }
    }
    else
    {
        if(nbButton<=5)
        {
            for (int i = 0;i<nbButton;i++)
            {
                button *b = buttonList[i];
                int offsetX = (width()-b->width())/2;
                int offsetY = (height()-nbButton*b->height())/(nbButton+1);
                b->move(offsetX,offsetY*(1+i)+b->height()*i);

            }
        }
        else
        {


            int nbButton1 = nbButton/2;
            int nbButton2 = nbButton/2;

            if(nbButton1+nbButton2<nbButton)
                nbButton1++;


            for (int i = 0;i<nbButton1;i++)
            {
                button *b = buttonList[i];
                int offsetX = (width()-2*b->width())/(2+1);
                int offsetY = (height()-nbButton1*b->height())/(nbButton1+1);
                b->move(offsetX,offsetY*(1+i)+b->height()*i);


            }
            for(int i = nbButton1;i<nbButton1+nbButton2;i++)
            {
                button *b = buttonList[i];
                int j = i-nbButton1;
                int offsetX = (width()-2*b->width())/(2+1);
                int offsetY = (height()-nbButton2*b->height())/(nbButton2+1);
                b->move(offsetX*2+b->width(),offsetY*(1+j)+b->height()*j);


            }


        }

    }

}




void MainWindow::onButtonPressed(int id)
{
    qDebug()<<"pressed "<<id;
    turnLightOn(id);
    fadeDmx2();

}

void MainWindow::onButtonReleased(int id)
{
    qDebug()<<"released "<<id;
    turnLightOff(id);
    resetDmx2();
}




void MainWindow::initGpios()
{


    QThread* thread = new QThread;
    sensor = new Sensor();

    sensor->moveToThread(thread);


    connect(sensor,SIGNAL(pushButton(int)),this,SLOT(onButtonPressed(int)));
    connect(sensor,SIGNAL(releaseSensor(int)),this,SLOT(onButtonReleased(int)));
    connect(this,SIGNAL(startSensor()),sensor,SLOT(startProcess()));
    thread->start();

    emit startSensor();








}

MainWindow::~MainWindow()
{
    gpioTerminate();
    delete ui;

}
