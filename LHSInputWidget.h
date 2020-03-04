#ifndef LHS_H
#define LHS_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class LHSInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit LHSInputWidget(QWidget *parent = 0);
    ~LHSInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QComboBox *criteria;
    QComboBox *metric;
    QLineEdit *iter;
    QLineEdit *numSamples;
    QComboBox *verbose;
};

#endif
