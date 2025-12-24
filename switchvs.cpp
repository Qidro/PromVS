#include "switchvs.h"
#include <QTimer>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

switchVS::switchVS(QObject *parent)
    : QObject{parent}
{

}

int extractNumber(const char* str) {
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

void startStatic()
{

    QSerialPort serial;
    serial.setPortName("ttyr00"); // или "/dev/ttyUSB0" на Linux
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.open(QIODevice::ReadWrite)) {
        // порт успешно открыт
                qDebug() << "Мы здесь";
                QTimer::singleShot(100, []() {
                        qDebug() << "Задержка завершена";
                     // Завершение приложения
                    });

            QObject::connect(&serial, &QSerialPort::readyRead, [&serial]() {
                    QByteArray data = serial.readAll();
                    while (serial.waitForReadyRead(100))
                            data += serial.readAll();
                    QString readableData = QString::fromUtf8(data);


                        // Выводим данные в читаемом формате
                        qDebug() << "Полученные данныеt:" << readableData;
                    //qDebug() << "Полученные данные:" << data;
                           int number = extractNumber(data);
                           number = number / 10;
                              qDebug() << "Данные в формате int :" << number;
                    // Обработка данных
                });


}

