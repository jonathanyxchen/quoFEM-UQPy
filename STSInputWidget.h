#ifndef STS_H
#define STS_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class STSInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit STSInputWidget(QWidget *parent = 0);
    ~STSInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *dimension;
    QLineEdit *numSamples;
    QComboBox *criteria;
    QComboBox *stype;
    QLineEdit *iter;
    QLineEdit *design;
    QLineEdit *inputFile;
    QComboBox *verbose;
};

#endif
