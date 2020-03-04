#ifndef IS_H
#define IS_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class ISInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit ISInputWidget(QWidget *parent = 0);
    ~ISInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *pdf_target1;
    QLineEdit *pdf_target2;
    QLineEdit *log_pdf_target1;
    QLineEdit *log_pdf_target2;
    QLineEdit *args_target;
    QComboBox *verbose;
};

#endif
