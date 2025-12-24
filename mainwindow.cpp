#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //  weighingStatic = new FORM();
   // weighingStatic->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked()
{
    WeighingStatic *weighingStaticForm = new WeighingStatic();
    // Показываем новую форму
        weighingStaticForm->show();
        //закрывает эту форму
        this->close();
   // weighingStatic->show();

}

