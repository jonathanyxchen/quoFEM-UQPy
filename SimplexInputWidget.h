#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class SimplexInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit SimplexInputWidget(QWidget *parent = 0);
    ~SimplexInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *nodes;
    QLineEdit *nsamples;
};

#endif
