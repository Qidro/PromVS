#ifndef SWITCHVS_H
#define SWITCHVS_H

#include <QObject>

class switchVS : public QObject
{
    Q_OBJECT
public:
    explicit switchVS(QObject *parent = nullptr);
void startStatic();
int extractNumber(const char* str);



signals:

};

#endif // SWITCHVS_H
