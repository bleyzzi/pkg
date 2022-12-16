#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),scale(10)
{

    ui->setupUi(this);

    qApp->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!ready_) return;
    QPainter p;
    QPixmap pix(650,650);
    pix.fill(Qt::white);
    p.begin(&pix);

    Xmin = ui->dsb_Xmin->value();
    Ymin = ui->dsb_Ymin->value();
    Xmax = ui->dsb_Xmax->value();
    Ymax = ui->dsb_Ymax->value();


    double step = 0.9/20;
    double stp = 0.9/(2*scale);

    p.setPen(QPen(Qt::magenta,3));
    p.drawRect(QRect(QPoint(pix.width()*(0.5+stp*Xmin),pix.height()*(0.5-stp*Ymax)),QPoint(pix.width()*(0.5+stp*Xmax),pix.height()*(0.5-stp*Ymin))));

    p.setPen(QPen(Qt::black,3));
    p.drawLine(pix.width()*0.05,pix.height()/2,pix.width()*0.95,pix.height()/2);
    p.drawLine(pix.width()/2,pix.height()*0.95,pix.width()/2,pix.height()*0.05);


    for(int i = 0; i < 20;i++)
    {
       p.setPen(QPen(Qt::black,1));
       p.drawLine(pix.width()*(0.05+step*i),pix.height()*0.05,pix.width()*(0.05+step*i),pix.height()*0.95);
       p.drawLine(pix.width()*0.05,pix.height()*(0.05+step*i),pix.width()*0.95,pix.height()*(0.05+step*i));
       p.drawText(pix.width()*(0.04+step*i),pix.height()/1.90,QString::number(scale/10*(i-10)));
       if(i!=10)
          p.drawText(pix.width()/2.10,pix.height()*(0.955-step*i),QString::number(scale/10*(i-10)));

    }

    QVector<QVector<QPair<QPointF,QPointF>>> clipSegments = cutSegments(segments);
    QVector<QPointF> clipPolygon = cutPolygon(polygon); // here error


   // draw original segments and polygon
    p.setPen(QPen(Qt::black,2,Qt::DashLine));
    for(auto segment:segments)
        p.drawLine(pix.width()*(0.5+stp*segment.first.x()),pix.height()*(0.5-stp*segment.first.y()),pix.width()*(0.5+stp*segment.second.x()),pix.height()*(0.5-stp*segment.second.y()));
    for(int i = 1; i<polygon.size();i++)
        p.drawLine(pix.width()*(0.5+stp*polygon[i-1].x()),pix.height()*(0.5-stp*polygon[i-1].y()),pix.width()*(0.5+stp*polygon[i].x()),pix.height()*(0.5-stp*polygon[i].y()));

    //draw clipped segments and polygon
    p.setPen(QPen(Qt::green,3));
    for(auto otrezok:clipSegments[0])
        p.drawLine(pix.width()*(0.5+stp*otrezok.first.x()),pix.height()*(0.5-stp*otrezok.first.y()),pix.width()*(0.5+stp*otrezok.second.x()),pix.height()*(0.5-stp*otrezok.second.y()));
    p.setPen(QPen(Qt::green,3));
    for(int i = 1; i<clipPolygon.size();i++)
        p.drawLine(pix.width()*(0.5+stp*clipPolygon[i-1].x()),pix.height()*(0.5-stp*clipPolygon[i-1].y()),pix.width()*(0.5+stp*clipPolygon[i].x()),pix.height()*(0.5-stp*clipPolygon[i].y()));


      ui->label->setPixmap(pix);
      p.end();

}
QVector<QVector<QPair<QPointF,QPointF>>> MainWindow::cutSegments(QVector<QPair<QPointF,QPointF>> segments){
    QVector<QVector<QPair<QPointF,QPointF>>> clipSegments(2);
    for(int i=0; i < segments.size();i++){
        QPointF P1 = segments[i].first;
        QPointF P2 = segments[i].second;
        int P1_code = getCode(P1), P2_code = getCode(P2);
        if(sqrt(pow(P1.x() - P2.x(), 2) + pow(P1.y() - P2.y(), 2)) <= 1){
            return clipSegments;
        }
        if((P1_code | P2_code) == 0)
        {
            clipSegments[0].push_back(segments[i]);
        }
        else if((P1_code & P2_code) !=0 )
        {
            clipSegments[1].push_back(segments[i]);
        }
        else
        {
            if(P1_code == 0)
            {
                QPointF tmp = P1;
                P1 = P2;
                P2 = tmp;
            }
            segments[i] = qMakePair(P2,intersectionPoint(P1,P2));
            i--;
        }
    }
    return clipSegments;
}

int MainWindow::getCode(QPointF point)
{
    double x = point.x();
    double y = point.y();

    int code = 0;

    if(x < Xmin)
        code +=1;
    if(x>Xmax)
        code +=2;
    if(y<Ymin)
        code +=4;
    if(y>Ymax)
        code +=8;
    return code;
}


QVector<QPointF> MainWindow::cutPolygon(QVector<QPointF> polygon)
{
    QVector<QPointF> outputList = polygon;

    int borders[]  = {1,2,4,8};

    for(int i = 0; i < 4;i++)
    {
        QVector<QPointF> inputList = outputList;
        inputList.push_back(inputList[0]);
        outputList.clear();

        for(int j = 1;j < inputList.size();j++)
        {
            QPointF currentPoint = inputList[j];
            QPointF prevPoint = inputList[j-1];

            int PrevP_code = getCode(prevPoint), curP_code = getCode(currentPoint);
            if(!(curP_code & borders[i]))
            {
                if(PrevP_code & borders[i])
                    outputList.push_back(intersectionPoint(prevPoint,currentPoint,borders[i]));
                outputList.push_back(currentPoint);
            }
            else if(!(PrevP_code & borders[i]))
                outputList.push_back(intersectionPoint(currentPoint,prevPoint,borders[i]));
        }

    }
    outputList.push_back(outputList[0]);
    return outputList;


}

QPointF MainWindow::intersectionPoint(QPointF P1, QPointF P2, int border){

    int P1_code = getCode(P1);

    QPointF intersectionPoint;
    if ((border ==  8) || ( border == -1 && (P1_code & 8)))
        intersectionPoint = QPointF(P1.x() + (P2.x()- P1.x()) * (Ymax - P1.y()) / (P2.y() - P1.y()),Ymax);
    else if ((border ==  4) || ( border == -1 && (P1_code & 4)))
        intersectionPoint = QPointF(P1.x() + (P2.x()- P1.x()) * (Ymin - P1.y()) / (P2.y() - P1.y()),Ymin);
    else if ((border ==  2) || ( border == -1 && (P1_code & 2)))
        intersectionPoint = QPointF(Xmax,P1.y() + (P2.y()- P1.y()) * (Xmax - P1.x()) / (P2.x() - P1.x()));
    else if ((border ==  1) || ( border == -1 && (P1_code & 1)))
        intersectionPoint = QPointF(Xmin,P1.y() + (P2.y()- P1.y()) * (Xmin - P1.x()) / (P2.x() - P1.x()));


    return intersectionPoint;
}


void MainWindow::on_comboBox_activated(int index)
{
    scale = 10*qPow(2,index);
}


void MainWindow::on_selectDirectoryB_clicked()
{
    QFileDialog* dial = new QFileDialog(this);
      QString path = dial->getOpenFileName(this,tr("Выберите файл"),"/",tr("txt(*.txt)"));
      QFile file(path);
      if (file.open(QIODevice::ReadOnly))
      {

          QTextStream in(&file);
          int segments_number = in.readLine().toInt();
          QStringList line;
          polygon.clear();
          segments.clear();
          for(int i = 0; i< segments_number;i++)
          {
              line = in.readLine().split(" ");
              segments.push_back(qMakePair(QPointF(line[0].toDouble(),line[1].toDouble()),QPointF(line[2].toDouble(),line[3].toDouble())));
          }

          int polygon_number = in.readLine().toInt();
          for(int i = 0;i<polygon_number; i++)
          {
              line = in.readLine().split(" ");
              polygon.push_back(QPointF(line[0].toDouble(),line[1].toDouble()));
          }

          polygon.push_back(polygon[0]);

          ready_ = 1;
      }

}

