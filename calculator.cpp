#include "calculator.h"
#include "./ui_calculator.h"

int contor = 0;
double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool decTrigger = false;
bool powTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10;i++){
        QString butName = "Button_" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Button_plus, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Button_multy, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Button_div, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Button_sub, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Button_pow, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->Button_equal, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->Button_AC, SIGNAL(released()), this, SLOT(ClearButton()));
    connect(ui->Button_sign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Button_C,SIGNAL(released()), this, SLOT(ResetButton()));
    connect(ui->Button_pc,SIGNAL(released()), this, SLOT(PCButton()));
    connect(ui->Button_dec,SIGNAL(released()), this, SLOT(decButton()));
    connect(ui->Button_overX,SIGNAL(released()), this, SLOT(overXButton()));
    connect(ui->Button_sqrt,SIGNAL(released()),this ,SLOT(sqrt()));
    connect(ui->Button_factorial,SIGNAL(released()),this,SLOT(factorial()));
    connect(ui->Button_Pi,SIGNAL(released()),this,SLOT(pi()));
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::NumPressed(){

    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->Display->text();

    if(displayVal.toDouble() == 0 && !decTrigger ){ // && !decTrigger
        ui->Display->setText(butval);
    } else if(decTrigger && contor == 0){

        QString newVal = displayVal +"."+butval;
        ui->Display->setText(newVal);
        contor++;


    } else if(contor == 1 && displayVal.toDouble() == 0.0 && decTrigger){

        QString newVal = displayVal + butval;
        ui->Display->setText(newVal);

    } else {

        QString newVal = displayVal + butval;      
        ui->Display->setText(newVal);

    }
    //decTrigger = false;
}


void Calculator::mathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    decTrigger = false;
    powTrigger = false;
    contor = 0;
    QString displayVal= ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"/",Qt::CaseInsensitive) == 0){
        divTrigger = true;

    } else if(QString::compare(butVal,"X",Qt::CaseInsensitive) == 0){
        multTrigger = true;

    } else if(QString::compare(butVal,"+",Qt::CaseInsensitive) == 0){
        addTrigger = true;

    } else if(QString::compare(butVal,"-",Qt::CaseInsensitive) == 0){
        subTrigger = true;

    } else{
        powTrigger = true;
    }
    ui->Display->setText("");
}



void Calculator::EqualButton(){

    double solution =0.0;
    QString displayval = ui->Display->text();
    double dbldispval = displayval.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger || powTrigger){
        if(addTrigger){
            solution = calcVal + dbldispval;
            addTrigger = false;
        } else if(subTrigger){
            solution = calcVal - dbldispval;
            subTrigger = false;
        }else  if(multTrigger){
            solution = calcVal * dbldispval;
            multTrigger = false;
        } else if(divTrigger){
            solution = calcVal / dbldispval;
            divTrigger = false;
        } else {
            solution = calcVal;

            for(double i = dbldispval-1; i > 0; i--){
                solution = solution*calcVal;
            }
            powTrigger = false;
        }

    }
    contor = 0;
    ui->Display->setText(QString::number(solution));
}

void Calculator::ClearButton(){

    ui->Display->setText("0");
    decTrigger = false;
    contor = 0;

}




void Calculator::ChangeNumberSign() {

    QString displayVal = ui->Display->text();
    double dbldisplayval = displayVal.toDouble()*-1;
    ui->Display->setText(QString::number(dbldisplayval));

}


void Calculator::ResetButton(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    decTrigger = false;
    calcVal = 0;
    contor = 0;

    ui->Display->setText("0");

}

void Calculator::PCButton(){

    QString displayVal = ui->Display->text();
    double dbldisplayVal = displayVal.toDouble()/100;
    ui->Display->setText(QString::number(dbldisplayVal));


}


void Calculator::decButton(){
    QString displayVal = ui->Display->text();
    double dbldisplayVal = displayVal.toDouble();

   // ui->Display->setText(QString::number((int)dbldisplayVal));
    if((int)dbldisplayVal == dbldisplayVal){
        decTrigger = true;
    }

}

void Calculator::overXButton(){
    QString displayVal = ui->Display->text();
    double dbldisplayVal = displayVal.toDouble();
    if (dbldisplayVal != 0){
        dbldisplayVal = 1.0/dbldisplayVal;
        ui->Display->setText(QString::number(dbldisplayVal));
    }   else ui->Display->setText("Error");


}

void Calculator::sqrt(){
    QString displayVal = ui->Display->text();
    double dbldisplayVal = displayVal.toDouble();
    double sqrt = dbldisplayVal/2;
    double temp = 0;
    while(sqrt != temp){
        temp  = sqrt;
        sqrt = (dbldisplayVal/temp + temp)/2;
    }
    ui->Display->setText(QString::number(sqrt));

}

void Calculator::factorial(){
    QString displayVal = ui->Display->text();
    double dbldisplayVal = displayVal.toDouble();
    if(dbldisplayVal == (int)dbldisplayVal){
        if(dbldisplayVal != 0){
            if(dbldisplayVal > 0){
                for(double i = dbldisplayVal-1; i>=1; i--)
                    dbldisplayVal = dbldisplayVal * i;
            } else for(double i = dbldisplayVal+1; i<=-1; i++)
                        dbldisplayVal = dbldisplayVal * i;
        } else dbldisplayVal = 1;
    ui->Display->setText(QString::number(dbldisplayVal));
    }
    else  ui->Display->setText("Expected int");

}

void Calculator::pi(){

    ui->Display->setText(QString::number(3.14159265358979323846));

}

