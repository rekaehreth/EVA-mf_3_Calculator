#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->resultLineEdit->setReadOnly( true );

    connect( ui->additionRadioButton, SIGNAL( clicked() ), this, SLOT( on_operatorChanged() ) );
    connect( ui->subtractionRadioButton, SIGNAL( clicked() ), this, SLOT( on_operatorChanged() ) );
    connect( ui->multiplicationRadioButton, SIGNAL( clicked() ), this, SLOT( on_operatorChanged() ) );
    connect( ui->divisionRadioButton, SIGNAL( clicked() ), this, SLOT( on_operatorChanged() ) );

    connect( ui->controlPushButton, SIGNAL( clicked() ), this, SLOT( on_controlPushButton_clicked() ) );
    connect(ui->resultLineEdit, SIGNAL( returnPressed()), this, SLOT( on_controlPushButton_clicked() ) );
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_controlPushButton_clicked()
{
    if ( ui->controlPushButton->text() == "Generate" ) {
        ui->lineEditOp1->setText( QString::number( QRandomGenerator::global()->generate() % 101 ) );
        ui->lineEditOp2->setText( QString::number( QRandomGenerator::global()->generate() % 101 ) );
        ui->opsGroupBox->setEnabled( false );
        ui->resultLineEdit->setReadOnly( false );
        ui->controlPushButton->setText( "Check" );
    
    }
    else if ( ui->controlPushButton->text() == "Check" ) {
        bool ok;
        int c = ui->resultLineEdit->text().toInt( &ok );
        if ( ok ) {
            // válasz összevetése a helyes eredménnyel
            int result = 0;
            if      ( ui->opLabel->text() == "+" )  result = ui->lineEditOp1->text().toInt() + ui->lineEditOp2->text().toInt();
            else if ( ui->opLabel->text() == "-" )  result = ui->lineEditOp1->text().toInt() - ui->lineEditOp2->text().toInt();
            else if ( ui->opLabel->text() == "*" )  result = ui->lineEditOp1->text().toInt() * ui->lineEditOp2->text().toInt();
            else if ( ui->opLabel->text() == "/" )  result = ui->lineEditOp1->text().toInt() / ui->lineEditOp2->text().toInt();
            
            // az értékelés hozzáírása a listadoboz tartalmához
            if ( result == c ) {
                ui->resultListWidget->addItem( "CORRECT " + ui->lineEditOp1->text() + " " + ui->opLabel->text() + " " + ui->lineEditOp2->text() );
            } else {
                ui->resultListWidget->addItem( "WRONG " + ui->lineEditOp1->text() + " " + ui->opLabel->text() + " " + ui->lineEditOp2->text() );
            }
            // felkészülés a következő feladvány generálására
            ui->opsGroupBox->setEnabled( true );
            ui->resultLineEdit->setReadOnly( true );
            ui->lineEditOp1->setText( "" );
            ui->lineEditOp2->setText( "" );
            ui->controlPushButton->setText( "Generate" );
        } 
        else {
            QMessageBox error;
            error.setText( "Imput format is incorrect" );
            error.exec();
        }

    }
}

void Calculator::on_operatorChanged()
{
    if ( sender()->objectName()=="additionRadioButton" )            ui->opLabel->setText( "+" );
    else if( sender()->objectName()=="subtractionRadioButton" )     ui->opLabel->setText( "-" );
    else if( sender()->objectName()=="multiplicationRadioButton" )  ui->opLabel->setText( "*" );
    else if( sender()->objectName()=="divisionRadioButton" )        ui->opLabel->setText( "/" );
}

