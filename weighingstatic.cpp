#include "weighingstatic.h"
#include "ui_weighingstatic.h"
#include "switchvs.h"
#include <QMessageBox>
#include <QDebug>
WeighingStatic::WeighingStatic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeighingStatic)


{
    ui->setupUi(this);
    //for (int i = 0; i < 4; ++i) {
     //       serial[i] = new QSerialPort(this);
            // Дополнительные настройки для каждого порта можно добавить здесь
     //   }
    for (int i = 0; i < 4; ++i) {
            serial[i] = new QSerialPort(this);
            // Дополнительные настройки для каждого порта можно добавить здесь
            // Установка параметров порта
            serial[i]->setPortName("ttyr0"+QString::number(i)); // Измените на "/dev/ttyUSB0" на Linux
            serial[i]->setBaudRate(QSerialPort::Baud9600);
            serial[i]->setDataBits(QSerialPort::Data8);
            serial[i]->setParity(QSerialPort::NoParity);
            serial[i]->setStopBits(QSerialPort::OneStop);
            serial[i]->setFlowControl(QSerialPort::NoFlowControl);

            // Подключение сигнала readyRead к слоту readData
            connect(serial[i], &QSerialPort::readyRead, this, &WeighingStatic::readData);
        }

}

WeighingStatic::~WeighingStatic()
{
    delete ui;
}

int WeighingStatic::extractNumber(const char* str) {
    const char* p = str;
    // Сначала пропускаем все ненумерующие символы (можно также искать первый знак минуса)
    while (*p && !isdigit(*p) && *p != '-' && *p != '+') {
        p++;
    }

    // Теперь p указывает на начало потенциального числа
    char numberBuffer[50]; // Буфер для числа
    int index = 0;

    // Копируем число, включая знак минуса, если есть
    if (*p == '-' || *p == '+') {
        numberBuffer[index++] = *p;
        p++;
    }

    while (*p && isdigit(*p)) {
        if (index < (int)sizeof(numberBuffer) - 1)
            numberBuffer[index++] = *p;
        p++;
    }
    numberBuffer[index] = '0';

    // Преобразуем в int
    return atoi(numberBuffer);
}

void WeighingStatic::on_pushButton_clicked()
{
    if (serial[0]->open(QIODevice::ReadWrite)) {
            QMessageBox::information(this, "Success", "Connected to the port!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to open the port!");
        }
}

void WeighingStatic::readData()
{
    int dataGlobalInt = 0;
    int result=0;
    for (int i = 0; i < 4; ++i)
    {

        QByteArray data = serial[i]->readAll();
         while (serial[i]->waitForReadyRead(10))
                data += serial[i]->readAll();
        // Обработка полученных данных
        QString receivedData = QString::fromUtf8(data);
        int dataInt = extractNumber(data);
        dataGlobalInt += dataInt/10;
        // Здесь можно обновить интерфейс или вывести данные в консоль
        qDebug() << "Received data:" << dataGlobalInt;
    }


    ui->label->setText("Вес вагона: " +QString::number(dataGlobalInt) + "кг" );
    //dataGlobalInt = 0;
}

