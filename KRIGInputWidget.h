#ifndef KRIG_H
#define KRIG_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;

class KRIGInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit KRIGInputWidget(QWidget *parent = 0);
    ~KRIGInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *randomSeed;
    QLineEdit *numSamples;
};

#endif
