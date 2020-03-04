#ifndef MCMC_H
#define MCMC_H

#include <UQ_MethodInputWidget.h>
class QLineEdit;
class QComboBox;

class MCMCInputWidget : public UQ_MethodInputWidget
{
    Q_OBJECT
public:
    explicit MCMCInputWidget(QWidget *parent = 0);
    ~MCMCInputWidget();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    int getNumberTasks(void);

private:
    QLineEdit *dimension;
    QLineEdit *pdf_target1;
    QLineEdit *pdf_target2;
    QLineEdit *log_pdf_target1;
    QLineEdit *log_pdf_target2;
    QLineEdit *args_target;
    QComboBox *algorithm;
    QLineEdit *seed;
    QLineEdit *nsamples;
    QLineEdit *nsamples_per_chain;
    QLineEdit *nburn;
    QLineEdit *jump;
    QComboBox *save_log_pdf;
    QComboBox *concat_chains_;
    QComboBox *verbose;
};

#endif
