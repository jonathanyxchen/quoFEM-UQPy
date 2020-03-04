#ifndef STRATA_H
#define STRATA_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class StrataInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit StrataInputWidget(QWidget *parent = 0);
    ~StrataInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *nstrata;
    QLineEdit *inputFile;
    QLineEdit *origins;
    QLineEdit *widths;
    QLineEdit *weights;
};

#endif
