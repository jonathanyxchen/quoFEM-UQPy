#ifndef MCS_H
#define MCS_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class MCSInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit MCSInputWidget(QWidget *parent = 0);
    ~MCSInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *numSamples;
    QComboBox *verbose;
};

#endif
