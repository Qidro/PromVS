#ifndef WEIGHINGSTATIC_H
#define WEIGHINGSTATIC_H

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

private:
    Ui::WeighingStatic *ui;
};

#endif // WEIGHINGSTATIC_H
