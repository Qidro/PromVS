#ifndef WEIGHINGSTATIC_H
#define WEIGHINGSTATIC_H
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QDialog>

namespace Ui {
class WeighingStatic;
}

class WeighingStatic : public QDialog
{
    Q_OBJECT

public:
    explicit WeighingStatic(QWidget *parent = nullptr);
    ~WeighingStatic();

private slots:
    void on_pushButton_clicked();
    void readData();
    int extractNumber(const char* str);

private:
    Ui::WeighingStatic *ui;
     QSerialPort *serial;
};

#endif // WEIGHINGSTATIC_H
