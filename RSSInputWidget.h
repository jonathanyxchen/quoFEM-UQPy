#ifndef RSS_H
#define RSS_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class RSSInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit RSSInputWidget(QWidget *parent = 0);
    ~RSSInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *sample_object;
    QComboBox *run_model_object;
    QComboBox *krig_object;
    QLineEdit *nsamples;
    QLineEdit *max_train_size;
    QLineEdit *step_size;
    QLineEdit *qoi_name;
    QLineEdit *local;
    QComboBox *verbose;
};

#endif
