#include "weighingstatic.h"
#include "ui_weighingstatic.h"
#include "switchvs.h"
#include <QMessageBox>
#include <QDebug>
WeighingStatic::WeighingStatic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeighingStatic)
  , serial(new QSerialPort(this))

{
    ui->setupUi(this);

    // Установка параметров порта
    serial->setPortName("ttyr00"); // Измените на "/dev/ttyUSB0" на Linux
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Подключение сигнала readyRead к слоту readData
    connect(serial, &QSerialPort::readyRead, this, &WeighingStatic::readData);
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
    if (serial->open(QIODevice::ReadWrite)) {
            QMessageBox::information(this, "Success", "Connected to the port!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to open the port!");
        }
}

void WeighingStatic::readData()
{
    QByteArray data = serial->readAll();
     while (serial->waitForReadyRead(100))
            data += serial->readAll();
    // Обработка полученных данных
    QString receivedData = QString::fromUtf8(data);
    int dataInt = extractNumber(data);
    dataInt = dataInt/10;
    // Здесь можно обновить интерфейс или вывести данные в консоль
    qDebug() << "Received data:" << dataInt;
}

