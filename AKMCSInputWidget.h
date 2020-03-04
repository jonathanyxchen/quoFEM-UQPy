#ifndef AKMCS_H
#define AKMCS_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class AKMCSInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit AKMCSInputWidget(QWidget *parent = 0);
    ~AKMCSInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QComboBox *sample_object;
    QComboBox *run_model_object;
    QComboBox *krig_object;
    QLineEdit *nsamples;
    QLineEdit *nlearn;
    QLineEdit *nstart;
    QComboBox *If;
    QLineEdit *n_add;
    QLineEdit *min_cov;
    QLineEdit *max_p;
    QLineEdit *qoi_name;
    QLineEdit *kriging;
    QComboBox *verbose;
};

#endif
