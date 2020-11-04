#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QRandomGenerator>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void on_controlPushButton_clicked();
    void on_operatorChanged();
};
#endif // CALCULATOR_H
