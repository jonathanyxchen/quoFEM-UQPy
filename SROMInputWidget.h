#ifndef SROM_H
#define SROM_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;

class SROMInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit SROMInputWidget(QWidget *parent = 0);
    ~SROMInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *randomSeed;
    QLineEdit *numSamples;
};

#endif