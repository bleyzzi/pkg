#include "widget.h"
#include "QtWidgets/qapplication.h"
#include "QtGui/qguiapplication.h"
#include "QtCore/qcoreapplication.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    resize(400,400);

    color_converter = new QColor();
    space_id = space_name::rgb;
    spaces = {space_name::rgb, space_name::cmyk, space_name::hsv, space_name::hls, space_name::xyz};


    GradientLabel = new QLabel(this);

    backgr= new QGridLayout;
    backgr->setAlignment(Qt::AlignLeft);
    sliders= new QGridLayout;
    sliders->setAlignment(Qt::AlignRight);

    backgr->addLayout(sliders,0,0,4,4);

    LeftCB = new QComboBox;
    CentralCB = new QComboBox;
    RightCB = new QComboBox();


    Slider1 = new QSlider;
    Slider1->setRange(0,255);
    Slider1->setOrientation(Qt::Horizontal);
    SliderLabel1 = new QLabel;
    SliderLabel1->setMaximumSize(30,30);
    SliderLabel1->setAlignment(Qt::AlignRight);


    Slider2 = new QSlider;
    Slider2->setRange(0,255);
    Slider2->setOrientation(Qt::Horizontal);
    SliderLabel2 = new QLabel;
    SliderLabel2->setMaximumSize(30,30);
    SliderLabel2->setAlignment(Qt::AlignRight);

    Slider3 = new QSlider;
    Slider3->setRange(0,255);
    Slider3->setOrientation(Qt::Horizontal);
    SliderLabel3 = new QLabel;
    SliderLabel3->setMaximumSize(30,30);
    SliderLabel3->setAlignment(Qt::AlignRight);

    Slider4 = nullptr;
    SliderLabel4 = new QLabel;
    SliderLabel4->setMaximumSize(30,30);
    SliderLabel4->setAlignment(Qt::AlignRight);

    ColorRect = new QLabel(this);
    ColorRect->setMaximumSize(700,30);
    ColorRect->setMinimumSize(700,30);
    ColorRect->setStyleSheet("QLabel{background-color:rgb(0,0,0);border:2px solid black;}");


    connect(Slider1, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));
    connect(Slider2, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));
    connect(Slider3, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));



    Left1 = new QSpinBox;
    Left2 = new QSpinBox;
    Left3 = new QSpinBox;
    Left4 = nullptr;
    Left1->setMinimumSize(200,20);

    Left1->setRange(0, 255);
    Left2->setRange(0, 255);
    Left3->setRange(0, 255);

    connect(Left1, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));
    connect(Left2, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));
    connect(Left3, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));

    Mid1 = new QSpinBox;
    Mid2 = new QSpinBox;
    Mid3 = new QSpinBox;
    Mid4 = new QSpinBox;
    Mid1->setMinimumSize(200,20);

    Mid1->setReadOnly(true);
    Mid2->setReadOnly(true);
    Mid3->setReadOnly(true);

    Mid1->setRange(0, 255);
    Mid2->setRange(0, 255);
    Mid3->setRange(0, 255);

    Right1 = new QSpinBox;
    Right2 = new QSpinBox;
    Right3 = new QSpinBox;
    Right4 = nullptr;
    Right1->setMinimumSize(200,20);

    Right1->setReadOnly(true);
    Right2->setReadOnly(true);
    Right3->setReadOnly(true);

    Right1->setRange(0, 359);
    Right2->setRange(0, 255);
    Right3->setRange(0, 255);

    LLabel1 = new QLabel("R:");
    LLabel2 = new QLabel("G:");
    LLabel3 = new QLabel("B:");
    LLabel4 = new QLabel;

    MLabel1 = new QLabel("C:");
    MLabel2 = new QLabel("M:");
    MLabel3 = new QLabel("Y:");
    MLabel4 = new QLabel("K:");

    RLabel1 = new QLabel("H:");
    RLabel2 = new QLabel("S:");
    RLabel3 = new QLabel("V:");
    RLabel4 = new QLabel;

    Names_For_LeftLabels("RGB");


    backgr->addWidget(GradientLabel, 0,4,1,2);
    backgr->addWidget(ColorRect, 4,0,1,6);

    sliders->addWidget(SliderLabel1,0,0,1,1);
    sliders->addWidget(SliderLabel2,1,0,1,1);
    sliders->addWidget(SliderLabel3,2,0,1,1);
    sliders->addWidget(SliderLabel4,3,0,1,1);

    sliders->addWidget(Slider1,0,1,1,3);
    sliders->addWidget(Slider2,1,1,1,3);
    sliders->addWidget(Slider3,2,1,1,3);

    backgr->addWidget(LeftCB, 5,0,1,2);
    backgr->addWidget(CentralCB,5,2,1,2);
    backgr->addWidget(RightCB, 5,4,1,2);

    backgr->addWidget(Left1, 7,1);
    backgr->addWidget(Left2, 8,1);
    backgr->addWidget(Left3, 9,1);

    backgr->addWidget(LLabel1,7,0);
    backgr->addWidget(LLabel2,8,0);
    backgr->addWidget(LLabel3,9,0);
    backgr->addWidget(LLabel4,10,0);

    backgr->addWidget(Mid1, 7,3);
    backgr->addWidget(Mid2, 8,3);
    backgr->addWidget(Mid3, 9,3);
    backgr->addWidget(Mid4, 10,3);

    backgr->addWidget(MLabel1,7,2);
    backgr->addWidget(MLabel2,8,2);
    backgr->addWidget(MLabel3,9,2);
    backgr->addWidget(MLabel4,10,2);

    backgr->addWidget(Right1, 7,5);
    backgr->addWidget(Right2, 8,5);
    backgr->addWidget(Right3, 9,5);
    backgr->addWidget(Right4, 10,5);

    backgr->addWidget(RLabel1,7,4);
    backgr->addWidget(RLabel2,8,4);
    backgr->addWidget(RLabel3,9,4);
    backgr->addWidget(RLabel4,10,4);

    LeftCB->addItem("RGB");
    LeftCB->addItem("CMYK");
    LeftCB->addItem("HSV");
    LeftCB->addItem("HLS");
    LeftCB->addItem("XYZ");

    CentralCB->addItem("CMYK");
    CentralCB->addItem("HSV");
    CentralCB->addItem("RGB");
    CentralCB->addItem("HLS");
    CentralCB->addItem("LAB");
    CentralCB->addItem("HLS");
    CentralCB->addItem("XYZ");

    RightCB->addItem("HSV");
    RightCB->addItem("CMYK");
    RightCB->addItem("HLS");
    RightCB->addItem("RGB");
    RightCB->addItem("XYZ");
    RightCB->addItem("LAB");

    connect(LeftCB,SIGNAL(currentTextChanged(QString)),this,SLOT(Names_For_LeftLabels(QString)));
    connect(CentralCB,SIGNAL(currentTextChanged(QString)),this,SLOT(Names_For_MidLabels(QString)));
    connect(RightCB,SIGNAL(currentTextChanged(QString)),this,SLOT(Names_For_RightLabels(QString)));

    this->setLayout(backgr);

}
double Widget::From_RGB_To_XYZ(double a)
{
    double x=a;
    if(x>= 0.04045)
    {
        return pow((x+0.055)/1.055,2.4);
    }
    else return (x/12.92);
}

double Widget::From_XYZ_To_LAB(double a)
{
    double x=a;
    if(x>= 0.008856)
    {
        return pow(x,1.0/3.0);
    }
    else return (7.787*x + 16.0/116.0);
}


QVector<int> Widget::getValues(space_name value_id)
{
    QVector<int> values;
    switch(value_id)
    {
    case space_name::rgb:
       values.push_back(color_converter->red());
       values.push_back(color_converter->green());
       values.push_back(color_converter->blue());
        break;
    case space_name::cmyk:
        int c,m,y,k;
        color_converter->getCmyk(&c,&m,&y,&k);
        values= {c,m,y,k};
        break;
    case space_name::hsv:
       int h,s,v;
       color_converter->getHsv(&h,&s,&v);
       values= {h,s,v};
        break;

    case space_name::hls:
        int h_,l_,s_;
        color_converter->getHsl(&h_,&s_,&l_);
        values= {h_,l_,s_};
        break;
    case space_name::xyz:
    {
        double X,Y,Z;
        double r = color_converter->red();
        double g = color_converter->green();
        double b = color_converter->blue();

        double Rn, Gn, Bn;
        Rn = qMin(qMax(0.0, From_RGB_To_XYZ (r / 255.0) *100.0), 100.0);
        Gn = qMin(qMax(0.0, From_RGB_To_XYZ (g / 255.0) *100.0), 100.0);
        Bn = qMin(qMax(0.0, From_RGB_To_XYZ (b / 255.0) *100.0), 100.0);

        X = 0.412453*Rn + 0.357580*Gn + 0.180423* Bn;
        Y = 0.212671*Rn + 0.715160*Gn + 0.072169*Bn;
        Z = 0.019334*Rn + 0.119193*Gn + 0.950227*Bn;

        values= {int(X),int(Y),int(Z)};
    }
        break;

    case space_name::lab:
    {
        double L,A,B;
        double X,Y,Z;
        double r = color_converter->red();
        double g = color_converter->green();
        double b = color_converter->blue();

        double Rn, Gn, Bn;
        Rn = From_RGB_To_XYZ (r / 255.0) *100.0;
        Gn = From_RGB_To_XYZ (g / 255.0) *100.0;
        Bn = From_RGB_To_XYZ (b / 255.0) *100.0;

        X= 0.412453*Rn + 0.357580*Gn + 0.18042* Bn;
        Y= 0.212671*Rn + 0.715160*Gn + 0.072169*Bn;
        Z= 0.019334*Rn + 0.119193*Gn + 0.950227*Bn;

        double Xw = 95.047;
        double Yw = 100.0;
        double Zw = 108.883;

        L = 116.0 * From_XYZ_To_LAB(Y/Yw) -16.0;
        A = 500.0 *(From_XYZ_To_LAB(X/Xw) - From_XYZ_To_LAB(Y/Yw));
        B = 200.0 *(From_XYZ_To_LAB(Y/Yw) - From_XYZ_To_LAB(Z/Zw));

        values= {int(L),int(A), int (B)};
    }
        break;
    }

    return values;
}



double Widget::From_LAB_To_XYZ(double a)
{
    double x = a;
    if(pow(x,3)>= 0.008856)
    {
        return pow(x,3);
    }
    else return (x-16.0/116.0)/7.787;
}

double Widget::From_XYZ_To_RGB(double a)
{
    double x=a;
    if(x >= 0.0031308)
    {
        return (1.055*pow(x,1.0/2.4)-0.055);
    }
    else return 12.92*x;
}


void Widget::SetColor(space_name value_id, int a, int b, int c, int d)
{
    switch(value_id)
    {
    case space_name::rgb:
        color_converter->setRed(a);
        color_converter->setGreen(b);
        color_converter->setBlue(c);
        break;
    case space_name::cmyk:
        color_converter->setCmyk(a,b,c,d);
        break;
    case space_name::hsv:
        color_converter->setHsv(a,b,c);
        break;

    case space_name::hls:
        color_converter->setHsl(a,c,b);
        break;
    case space_name::xyz:
    {
        double x = a;
        double y_ = b;
        double z = c;
        double Rn = 0.032406 *x - 0.015372*y_ -0.004986* z;
        double Gn = -0.009689 *x + 0.018758 *y_ + 0.000415 * z;
        double Bn= 0.000557 *x - 0.002040 *y_ + 0.010570 * z;


        double R= qMin(qMax(0.0,From_XYZ_To_RGB(Rn)*255), 255.0);
        double G= qMin(qMax(0.0, From_XYZ_To_RGB(Gn)*255), 255.0);
        double B= qMin(qMax(0.0, From_XYZ_To_RGB(Bn)*255), 255.0);

        color_converter->setRed(R);
        color_converter->setGreen(G);
        color_converter->setBlue(B);
    }
        break;
    case space_name::lab:
    {
        double Xw = 95.047;
        double Yw = 100.0;
        double Zw = 108.883;
        double L=a;
        double A=b;
        double B=c;
        double Y = From_LAB_To_XYZ((L+16.0)/116.0)*Yw;
        double X = From_LAB_To_XYZ(A/500.0 + (L+16.0)/116.0)*Xw;
        double Z = From_LAB_To_XYZ((L+16.0)/116.0 - B/200.0)*Zw;

        double Rn = 0.032406 *X - 0.015372*Y -0.004986* Z;
        double Gn = -0.009689 *X + 0.018758 *Y + 0.000415 * Z;
        double Bn = 0.000557 *X - 0.002040 *Y + 0.010570 * Z;

        double R= From_XYZ_To_RGB(Rn)*255;
        double G= From_XYZ_To_RGB(Gn)*255;
        double B_= From_XYZ_To_RGB(Bn)*255;
        color_converter->setRed(R);
        color_converter->setGreen(G);
        color_converter->setBlue(B_);
    }
        break;
    }
}


void Widget::Names_For_LeftLabels(QString text)
{
    Slider2->setMaximum(255);
    Slider3->setMaximum(255);
    if(text=="RGB")
    {
        space_id = space_name::rgb;
        spaces[0]=space_name::rgb;

        LLabel1->setText("R:");
        LLabel2->setText("G:");
        LLabel3->setText("B:");
        LLabel4->setText("");

        SliderLabel1->setText("R:");
        SliderLabel2->setText("G:");
        SliderLabel3->setText("B:");
        SliderLabel4->setText("");

        FirstSliderSetRange();
        FirstSpinSetRange(Left1);

        if(Left4)
        {
            delete Left4;
            Left4=nullptr;
        }

        if(Slider4)
        {
            delete Slider4;
            Slider4=nullptr;
        }


    }
    if(text=="CMYK")
    {
        space_id = space_name::cmyk;
        spaces[0]=space_name::cmyk;
        FirstSliderSetRange();
        FirstSpinSetRange(Left1);
        Left4 = new QSpinBox;
        Left4->setRange(0, 255);
        connect(Left4, SIGNAL(valueChanged(int)), this, SLOT(spinsChanged(int)));
        backgr->addWidget(Left4, 10,1);
        LLabel1->setText("C:");
        LLabel2->setText("M:");
        LLabel3->setText("Y:");
        LLabel4->setText("K:");

        SliderLabel1->setText("C:");
        SliderLabel2->setText("M:");
        SliderLabel3->setText("Y:");
        SliderLabel4->setText("K:");

        Slider4 = new QSlider;
        Slider4->setRange(0,255);
        Slider4->setOrientation(Qt::Horizontal);
        connect(Slider4, SIGNAL(sliderMoved(int)), this, SLOT(slidersMoved(int)));
        sliders->addWidget(Slider4,3,1,1,3);

    }
    if(text=="HSV")
    {
        space_id = space_name::hsv;
        spaces[0]=space_name::hsv;
        FirstSliderSetRange(true);
        FirstSpinSetRange(Left1, true);
        LLabel1->setText("H:");
        LLabel2->setText("S:");
        LLabel3->setText("V:");
        LLabel4->setText("");

        SliderLabel1->setText("H:");
        SliderLabel2->setText("S:");
        SliderLabel3->setText("V:");
        SliderLabel4->setText("");

        if(Left4)
        {
           delete Left4;
           Left4=nullptr;
        }

        if(Slider4)
        {
            delete Slider4;
            Slider4=nullptr;
        }
    }
    if(text=="HLS")
    {
        space_id = space_name::hls;
        spaces[0]=space_name::hls;
        FirstSliderSetRange(true);
        FirstSpinSetRange(Left1, true);
        LLabel1->setText("H:");
        LLabel2->setText("L:");
        LLabel3->setText("S:");
        LLabel4->setText("");

        SliderLabel1->setText("H:");
        SliderLabel2->setText("L:");
        SliderLabel3->setText("S:");
        SliderLabel4->setText("");

        if(Left4)
        {
           delete Left4;
           Left4=nullptr;
        }

        if(Slider4)
        {
            delete Slider4;
            Slider4=nullptr;
        }
    }
    if(text=="XYZ")
    {
        space_id = space_name::xyz;
        spaces[0]=space_name::xyz;
        Left1->setMaximum(95);
        Slider1->setMaximum(95);
        Slider2->setMaximum(100);
        Slider3->setMaximum(108);
        LLabel1->setText("X:");
        LLabel2->setText("Y:");
        LLabel3->setText("Z:");
        LLabel4->setText("");

        SliderLabel1->setText("X:");
        SliderLabel2->setText("Y:");
        SliderLabel3->setText("Z:");
        SliderLabel4->setText("");

        if(Left4)
        {
           delete Left4;
           Left4=nullptr;
        }

        if(Slider4)
        {
            delete Slider4;
            Slider4=nullptr;
        }
    }
    setSliders(getValues(space_id));
    QVector<int> empty;
    setSpinBoxes(getValues(space_id),empty,empty);
}



void Widget::Names_For_MidLabels(QString text)
{
    Mid2->setRange(0,255);
    Mid3->setRange(0,255);
    if(text=="LAB")
    {
        Mid2->setRange(-128,127);
        Mid3->setRange(-128,127);
        spaces[1]= space_name::lab;
        MLabel1->setText("L:");
        MLabel2->setText("A:");
        MLabel3->setText("B:");
        MLabel4->setText("");
        if(Mid4)
        {
           delete Mid4;
           Mid4=nullptr;
        }

    }

    if(text=="RGB")
    {
        spaces[1] = space_name::rgb;
        FirstSpinSetRange(Mid1);
        MLabel1->setText("R:");
        MLabel2->setText("G:");
        MLabel3->setText("B:");
        MLabel4->setText("");
        if(Mid4)
        {
           delete Mid4;
           Mid4=nullptr;
        }
    }
    if(text=="CMYK")
    {
        spaces[1]= space_name::cmyk;
        FirstSpinSetRange(Mid1);
        Mid4 = new QSpinBox;
        Mid4->setRange(0, 255);
        Mid4->setReadOnly(true);
        backgr->addWidget(Mid4, 10,3);
        MLabel1->setText("C:");
        MLabel2->setText("M:");
        MLabel3->setText("Y:");
        MLabel4->setText("K:");
    }
    if(text=="HSV")
    {
        spaces[1] = space_name::hsv;
        FirstSpinSetRange(Mid1, true);
        MLabel1->setText("H:");
        MLabel2->setText("S:");
        MLabel3->setText("V:");
        MLabel4->setText("");
        if(Mid4)
        {
           delete Mid4;
           Mid4=nullptr;
        }
    }
    if(text=="XYZ")
    {
        spaces[1]= space_name::xyz;
        MLabel1->setText("X:");
        MLabel2->setText("Y:");
        MLabel3->setText("Z:");
        MLabel4->setText("");
        if(Mid4)
        {
           delete Mid4;
           Mid4=nullptr;
        }
    }
    if(text=="HLS")
    {
        spaces[1] = space_name::hls;
        FirstSpinSetRange(Mid1, true);
        MLabel1->setText("H:");
        MLabel2->setText("L:");
        MLabel3->setText("S:");
        MLabel4->setText("");
        if(Mid4)
        {
           delete Mid4;
           Mid4=nullptr;
        }
    }
}

void Widget::Names_For_RightLabels(QString text)
{
    Right2->setRange(0,255);
    Right3->setRange(0,255);
    if(text=="LAB")
    {
        Right2->setRange(-128,127);
        Right3->setRange(-128,127);
        spaces[2] = space_name::lab;
        RLabel1->setText("L:");
        RLabel2->setText("A:");
        RLabel3->setText("B:");
        RLabel4->setText("");
        if(Right4)
        {
           delete Right4;
           Right4=nullptr;
        }
    }

    if(text=="RGB")
    {
        spaces[2] = space_name::rgb;
        FirstSpinSetRange(Right1);
        RLabel1->setText("R:");
        RLabel2->setText("G:");
        RLabel3->setText("B:");
        RLabel4->setText("");
        if(Right4)
        {
           delete Right4;
           Right4=nullptr;
        }
    }
    if(text=="CMYK")
    {
        spaces[2]= space_name::cmyk;
        FirstSpinSetRange(Right1);
        Right4 = new QSpinBox;
        Right4->setRange(0, 255);
        Right4->setReadOnly(true);
        backgr->addWidget(Right4, 10,5);
        RLabel1->setText("C:");
        RLabel2->setText("M:");
        RLabel3->setText("Y:");
        RLabel4->setText("K:");
    }
    if(text=="HSV")
    {
        spaces[2] = space_name::hsv;
        FirstSpinSetRange(Right1, true);
        RLabel1->setText("H:");
        RLabel2->setText("S:");
        RLabel3->setText("V:");
        RLabel4->setText("");
        if(Right4)
        {
           delete Right4;
           Right4=nullptr;
        }
    }
    if(text=="XYZ")
    {
        spaces[2] = space_name::xyz;
        RLabel1->setText("X:");
        RLabel2->setText("Y:");
        RLabel3->setText("Z:");
        RLabel4->setText("");
        if(Right4)
        {
           delete Right4;
           Right4=nullptr;
        }
    }
    if(text=="HLS")
    {
        spaces[2] = space_name::hls;
        FirstSpinSetRange(Right1, true);
        RLabel1->setText("H:");
        RLabel2->setText("L:");
        RLabel3->setText("S:");
        RLabel4->setText("");
        if(Right4)
        {
           delete Right4;
           Right4=nullptr;
        }
    }
}


void Widget::mousePressEvent(QMouseEvent *e)
{
    double mouseX = e->pos().x();
    double mouseY = e->pos().y();
    if(mouseX < GradientLabel->x() || mouseX > GradientLabel->x() + GradientLabel->width()) return;
    if(mouseY < GradientLabel->y() || mouseY > GradientLabel->y() + GradientLabel->height()) return;

    QColor temp = grab(QRect(mouseX, mouseY, 1, 1)).toImage().pixelColor(0,0);
    SetColor(space_name::rgb, temp.red(), temp.green(), temp.blue());
    setSpacesAndLabel();
}

void Widget::FirstSliderSetRange(bool hueSpace)
{
    int max = 255;
    if(hueSpace) max = 359;
    Slider1->setMaximum(max);
}

void Widget::FirstSpinSetRange(QSpinBox* spin, bool hueSpace)
{
    int max = 255;
    if(hueSpace) max = 359;
    spin->setMaximum(max);
}


void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPixmap Grad(GradientLabel->width(), GradientLabel->height());
    QPainter paint(&Grad);
    double radius =200;
    QLinearGradient linearGradient(0,0, radius,0);
    linearGradient.setColorAt(0.0, Qt::red);
    linearGradient.setColorAt(0.35, Qt::yellow);
    linearGradient.setColorAt(0.5, Qt::green);
    linearGradient.setColorAt(0.65, Qt::cyan);
    linearGradient.setColorAt(0.8, Qt::blue);
    linearGradient.setColorAt(1.0, Qt::magenta);
    GradientLabel->setPixmap(Grad);
    GradientLabel->setMinimumSize(200,200);
    GradientLabel->setMaximumSize(200,200);
    paint.setBrush(linearGradient);
    paint.drawRect(0,0,GradientLabel->width()-1,GradientLabel->height()-1);
    GradientLabel->update();
}

void Widget::setSpacesAndLabel()
{
    QVector<int> valuesLeft=getValues(spaces[0]);
    QVector<int> valuesMid=getValues(spaces[1]);
    QVector<int> valuesRight=getValues(spaces[2]);

    setSpinBoxes(valuesLeft, valuesMid, valuesRight);
    setColorLabel();
}

void Widget::setSpinsAndLabel()
{
        QVector<int> valuesLeft;
        QVector<int> valuesMid=getValues(spaces[1]);
        QVector<int> valuesRight=getValues(spaces[2]);

        setSpinBoxes(valuesLeft, valuesMid, valuesRight);
        setColorLabel();
}

void Widget::setColorLabel()
{
    r = QString::number(color_converter->red());
    g = QString::number(color_converter->green());
    b = QString::number(color_converter->blue());

    ColorRect->setStyleSheet("QLabel{"
                             "background-color:rgb("+r+","+g+","+b+");"
                                                                   "}");
}

void Widget::setSpinBoxes(QVector<int> valuesLeft, QVector<int> valuesMid, QVector<int> valuesRight) {
    if(!valuesLeft.empty())
    {
        spin_changed_manual = true;
        Left1->setValue((valuesLeft[0]));
        spin_changed_manual = true;
        Left2->setValue((valuesLeft[1]));
        spin_changed_manual = true;
        Left3->setValue((valuesLeft[2]));
        if(Left4 != nullptr)
        {
            spin_changed_manual = true;
            Left4->setValue((valuesLeft[3]));
        }
    }

    if(valuesMid.empty()) return;
    spin_changed_manual = true;
    Mid1->setValue((valuesMid[0]));
    spin_changed_manual = true;
    Mid2->setValue((valuesMid[1]));
    spin_changed_manual = true;
    Mid3->setValue((valuesMid[2]));
    if(Mid4 != nullptr)
    {
        spin_changed_manual = true;
        Mid4->setValue((valuesMid[3]));
    }

    if(valuesRight.empty()) return;
    spin_changed_manual = true;
    Right1->setValue((valuesRight[0]));
    spin_changed_manual = true;
    Right2->setValue((valuesRight[1]));
    spin_changed_manual = true;
    Right3->setValue((valuesRight[2]));
    if(Right4 != nullptr)
    {
        spin_changed_manual = true;
        Right4->setValue((valuesRight[3]));
    }
}

void Widget::setSliders(QVector<int> valuesLeft)
{
    slider_changed_manual = true;
    Slider1->setValue((valuesLeft[0]));
    slider_changed_manual = true;
    Slider2->setValue((valuesLeft[1]));
    slider_changed_manual = true;
    Slider3->setValue((valuesLeft[2]));
    if(Slider4 != nullptr)
    {
        slider_changed_manual = true;
        Slider4->setValue((valuesLeft[3]));
    }
}


void Widget::slidersMoved(int a)
{
    if(slider_changed_manual)
    {
        slider_changed_manual=false;
        return;
    }
    int val1= Slider1->value();
    int val2= Slider2->value();
    int val3= Slider3->value();
    int val4=-1;
    if(Slider4 != nullptr)
    {
        val4=Slider4->value();
    }

    SetColor(space_id, val1, val2, val3, val4);
    setSpacesAndLabel();
}

void Widget::spinsChanged(int a)
{
    if(spin_changed_manual)
    {
        spin_changed_manual=false;
        return;
    }
    int val1= Left1->value();
    int val2= Left2->value();
    int val3= Left3->value();
    int val4=-1;
    if(Left4 != nullptr)
    {
        val4=Left4->value();
    }


    SetColor(space_id, val1, val2, val3, val4);
    setSpinsAndLabel();
    QVector<int> values = {val1, val2, val3, val4};
    setSliders(values);
}


Widget::~Widget()
{
}
