#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
    void mathButtonPressed();
    void EqualButton();
    void ClearButton();
    void ChangeNumberSign();
    void ResetButton();
    void PCButton();
    void decButton();
    void overXButton();
    void sqrt();
    void factorial();
    void pi();
};
#endif // CALCULATOR_H
