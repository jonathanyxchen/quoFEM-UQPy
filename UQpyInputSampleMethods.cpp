#include "UQpyInputSampleMethods.h"
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

#include <MCSInputWidget.h>
#include <LHSInputWidget.h>
#include <STSInputWidget.h>
#include <StrataInputWidget.h>
#include <RSSInputWidget.h>
#include <SimplexInputWidget.h>
#include <AKMCSInputWidget.h>
//#include <MCMCInputWidget.h>
#include <ISInputWidget.h>

UQpyInputSampleMethods::UQpyInputSampleMethods(QWidget *parent)
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
    samplingMethod->addItem(tr("MCS"));
    samplingMethod->addItem(tr("LHS"));
    samplingMethod->addItem(tr("STS"));
    samplingMethod->addItem(tr("Strata"));
    samplingMethod->addItem(tr("RSS"));
    samplingMethod->addItem(tr("Simplex"));
    samplingMethod->addItem(tr("AKMCS"));
    samplingMethod->addItem(tr("MCMC"));
    samplingMethod->addItem(tr("IS"));

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

    theMCS = new MCSInputWidget();
    theLHS = new LHSInputWidget();
    theSTS = new STSInputWidget();
    theStrata = new StrataInputWidget();
    theRSS = new RSSInputWidget();
    theSimplex = new SimplexInputWidget();
    theAKMCS = new AKMCSInputWidget();
//    theMCMC = new MCMCInputWidget();
    theIS = new ISInputWidget();

    theStackedWidget->addWidget(theMCS);
    theStackedWidget->addWidget(theLHS);
    theStackedWidget->addWidget(theSTS);
    theStackedWidget->addWidget(theStrata);
    theStackedWidget->addWidget(theRSS);
    theStackedWidget->addWidget(theSimplex);
    theStackedWidget->addWidget(theAKMCS);
//    theStackedWidget->addWidget(theMCMC);
    theStackedWidget->addWidget(theIS);

    // set current widget to index 0
    theCurrentMethod = theMCS;

    mLayout->addWidget(theStackedWidget);
    layout->addLayout(mLayout);

    this->setLayout(layout);

    connect(samplingMethod, SIGNAL(currentTextChanged(QString)), this, SLOT(onTextChanged(QString)));

}

void UQpyInputSampleMethods::onTextChanged(const QString &text)
{
  if (text=="MCS") {
    theStackedWidget->setCurrentIndex(0);
    theCurrentMethod = theMCS;
  }
  else if (text=="LHS") {
    theStackedWidget->setCurrentIndex(1);
    theCurrentMethod = theLHS;
  }
  else if (text=="STS") {
    theStackedWidget->setCurrentIndex(2);
    theCurrentMethod = theSTS;
  }
  else if (text=="Strata") {
    theStackedWidget->setCurrentIndex(3);
    theCurrentMethod = theStrata;
  }
  else if (text=="RSS") {
    theStackedWidget->setCurrentIndex(4);
    theCurrentMethod = theRSS;
  }
  else if (text=="Simplex") {
    theStackedWidget->setCurrentIndex(5);
    theCurrentMethod = theSimplex;
  }
  else if (text=="AKMCS") {
    theStackedWidget->setCurrentIndex(6);
    theCurrentMethod = theAKMCS;
  }
//  else if (text=="MCMC") {
//    theStackedWidget->setCurrentIndex(7);
//    theCurrentMethod = theMCMC;
//  }
  else if (text=="IS") {
    theStackedWidget->setCurrentIndex(7);
    theCurrentMethod = theIS;
  }
}

UQpyInputSampleMethods::~UQpyInputSampleMethods()
{

}

int
UQpyInputSampleMethods::getMaxNumParallelTasks(void){
  return theCurrentMethod->getNumberTasks();
}

void UQpyInputSampleMethods::clear(void)
{

}


bool
UQpyInputSampleMethods::outputToJSON(QJsonObject &jsonObject)
{
    bool result = true;

    QJsonObject uq;
    uq["method"]=samplingMethod->currentText();
    theCurrentMethod->outputToJSON(uq);

    jsonObject["samplingMethodData"]=uq;

    return result;
}


bool
UQpyInputSampleMethods::inputFromJSON(QJsonObject &jsonObject)
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


int UQpyInputSampleMethods::processResults(QString &filenameResults, QString &filenameTab) {

    return 0;
}

UQ_Results *
UQpyInputSampleMethods::getResults(void) {
    qDebug() << "RETURNED DAKOTARESULTSSAMPLING";
    return new DakotaResultsSampling(theRandomVariables);
}

RandomVariablesContainer *
UQpyInputSampleMethods::getParameters(void) {
  QString classType("Uncertain");
  theRandomVariables =  new RandomVariablesContainer(classType);
  return theRandomVariables;
}
