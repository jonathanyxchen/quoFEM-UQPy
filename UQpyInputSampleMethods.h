#ifndef UQPY_INPUT_SAMPLE_METHODS_H
#define UQPY_INPUT_SAMPLE_METHODS_H

#include <UQ_Engine.h>

#include <QGroupBox>
#include <QVector>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>

class DakotaSamplingResults;
class DakotaResults;
class QCheckBox;
class RandomVariablesContainer;
class QStackedWidget;
class UQ_MethodInputWidget;

class UQpyInputSampleMethods : public UQ_Engine
{
    Q_OBJECT
public:
    explicit UQpyInputSampleMethods(QWidget *parent = 0);
    ~UQpyInputSampleMethods();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);

    int processResults(QString &filenameResults, QString &filenameTab);

    UQ_Results *getResults(void);
    RandomVariablesContainer  *getParameters();

    int getMaxNumParallelTasks(void);

    QVBoxLayout *mLayout;

signals:

public slots:
   void clear(void);
   void onTextChanged(const QString &arg1);

private:
    QVBoxLayout *layout;
    QWidget     *methodSpecific;
    QComboBox   *samplingMethod;
    QLineEdit   *numSamples;
    QLineEdit   *randomSeed;
    //    QPushButton *run;

    QComboBox   *uqSelection;
    QWidget     *uqSpecific;

    RandomVariablesContainer *theRandomVariables;
    DakotaSamplingResults *results;

    QStackedWidget *theStackedWidget;
    UQ_MethodInputWidget * theCurrentMethod;

    UQ_MethodInputWidget * theMCS;
    UQ_MethodInputWidget * theLHS;
    UQ_MethodInputWidget * theSTS;
    UQ_MethodInputWidget * theStrata;
    UQ_MethodInputWidget * theRSS;
    UQ_MethodInputWidget * theSimplex;
    UQ_MethodInputWidget * theAKMCS;
//    UQ_MethodInputWidget * theMCMC;
    UQ_MethodInputWidget * theIS;
};

#endif
