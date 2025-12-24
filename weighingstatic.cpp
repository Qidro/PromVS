#include "weighingstatic.h"
#include "ui_weighingstatic.h"

WeighingStatic::WeighingStatic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeighingStatic)
{
    ui->setupUi(this);
}

WeighingStatic::~WeighingStatic()
{
    delete ui;
}

void WeighingStatic::on_pushButton_clicked()
{

}

