#include "UQpyInputSurrogates.h"
#include <DakotaResultsSampling.h>
#include <RandomVariablesContainer.h>

#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <sectiontitle.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>


#include <QStackedWidget>
#include <MonteCarloInputWidget.h>
#include <LatinHypercubeInputWidget.h>
#include <ImportanceSamplingInputWidget.h>
#include <GaussianProcessInputWidget.h>
#include <PCEInputWidget.h>
#include <SROMInputWidget.h>
#include <KRIGInputWidget.h>

UQpyInputSurrogates::UQpyInputSurrogates(QWidget *parent)
: UQ_Engine(parent),uqSpecific(0)
{
    layout = new QVBoxLayout();
    mLayout = new QVBoxLayout();

    //
    // create layout for selection box for method type to layout
    //

    QHBoxLayout *methodLayout= new QHBoxLayout;
    QLabel *label1 = new QLabel();
    label1->setText(QString("UQpy Class"));
    samplingMethod = new QComboBox();
    //samplingMethod->setMaximumWidth(800);
    //samplingMethod->setMinimumWidth(800);
    samplingMethod->addItem(tr("SROM"));
    samplingMethod->addItem(tr("KRIG"));

    /*
    samplingMethod->addItem(tr("Multilevel Monte Carlo"));
    samplingMethod->addItem(tr("Importance Sampling"));
    samplingMethod->addItem(tr("Quadrature"));
    samplingMethod->addItem(tr("Sparse Grid Quadrature"));
    samplingMethod->addItem(tr("Surrogate - Polynomial Chaos"));
    samplingMethod->addItem(tr("Surrogate - Gaussian Process"));
    */

    methodLayout->addWidget(label1);
    methodLayout->addWidget(samplingMethod,2);
    methodLayout->addStretch(4);

    mLayout->addLayout(methodLayout);

    //
    // qstacked widget to hold all widgets
    //

    theStackedWidget = new QStackedWidget();

    theSROM = new SROMInputWidget();
    theKRIG = new KRIGInputWidget();

    theStackedWidget->addWidget(theSROM);
    theStackedWidget->addWidget(theKRIG);

    // set current widget to index 0
    theCurrentMethod = theSROM;


    mLayout->addWidget(theStackedWidget);
    layout->addLayout(mLayout);

    this->setLayout(layout);

    connect(samplingMethod, SIGNAL(currentTextChanged(QString)), this, SLOT(onTextChanged(QString)));

}

void UQpyInputSurrogates::onTextChanged(const QString &text)
{
  if (text=="SROM") {
    theStackedWidget->setCurrentIndex(0);
    theCurrentMethod = theSROM;
  }
  else if (text=="KRIG") {
    theStackedWidget->setCurrentIndex(1);
    theCurrentMethod = theKRIG;
  }
}

UQpyInputSurrogates::~UQpyInputSurrogates()
{

}

int
UQpyInputSurrogates::getMaxNumParallelTasks(void){
  return theCurrentMethod->getNumberTasks();
}

void UQpyInputSurrogates::clear(void)
{

}


bool
UQpyInputSurrogates::outputToJSON(QJsonObject &jsonObject)
{
    bool result = true;

    QJsonObject uq;
    uq["method"]=samplingMethod->currentText();
    theCurrentMethod->outputToJSON(uq);

    jsonObject["samplingMethodData"]=uq;

    return result;
}


bool
UQpyInputSurrogates::inputFromJSON(QJsonObject &jsonObject)
{
  bool result = false;
  this->clear();

  //
  // get sampleingMethodData, if not present it's an error
  //
  
  if (jsonObject.contains("samplingMethodData")) {
      QJsonObject uq = jsonObject["samplingMethodData"].toObject();
      if (uq.contains("method")) {

          QString method =uq["method"].toString();
          int index = samplingMethod->findText(method);
          if (index == -1) {
              return false;
          }
          samplingMethod->setCurrentIndex(index);
          result = theCurrentMethod->inputFromJSON(uq);
          if (result == false)
              return result;

      }
  }
  
  return result;
}


int UQpyInputSurrogates::processResults(QString &filenameResults, QString &filenameTab) {

    return 0;
}

UQ_Results *
UQpyInputSurrogates::getResults(void) {
    qDebug() << "RETURNED DAKOTARESULTSSAMPLING";
    return new DakotaResultsSampling(theRandomVariables);
}

RandomVariablesContainer *
UQpyInputSurrogates::getParameters(void) {
  QString classType("Uncertain");
  theRandomVariables =  new RandomVariablesContainer(classType);
  return theRandomVariables;
}
