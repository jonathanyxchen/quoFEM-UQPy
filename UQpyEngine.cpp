// Written: fmckenna

/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: fmckenna

#include "UQpyEngine.h"
#include <QDebug>
#include <QComboBox>
#include <QStackedWidget>
#include <RandomVariablesContainer.h>
#include <UQ_Results.h>

#include <UQpyInputSurrogates.h>
#include <UQpyInputSampleMethods.h>

UQpyEngine::UQpyEngine(QWidget *parent)
    : UQ_Engine(parent), theCurrentEngine(0)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *theSelectionLayout = new QHBoxLayout();
    QLabel *label = new QLabel();
    label->setText(QString("UQpy Module"));
    QComboBox *theEngineSelectionBox = new QComboBox();
    theEngineSelectionBox->addItem(tr("SampleMethods"));
    theEngineSelectionBox->addItem(tr("Reliability"));
    theEngineSelectionBox->addItem(tr("Surrogates"));
    theEngineSelectionBox->addItem(tr("Inference"));
    theEngineSelectionBox->addItem(tr("StochasticProcess"));
    theEngineSelectionBox->setMinimumWidth(600);

    theSelectionLayout->addWidget(label);
    theSelectionLayout->addWidget(theEngineSelectionBox);
    theSelectionLayout->addStretch();
    layout->addLayout(theSelectionLayout);

    theStackedWidget = new QStackedWidget();

    theSampleMethodsEngine = new UQpyInputSampleMethods();
    theSurrogatesEngine = new UQpyInputSurrogates();

    theStackedWidget->addWidget(theSampleMethodsEngine);
    theStackedWidget->addWidget(theSurrogatesEngine);

    layout->addWidget(theStackedWidget);

    this->setLayout(layout);

    theCurrentEngine = theSurrogatesEngine;

    connect(theEngineSelectionBox, SIGNAL(currentIndexChanged(QString)), this,
          SLOT(engineSelectionChanged(QString)));
}

UQpyEngine::~UQpyEngine()
{

}

void UQpyEngine::engineSelectionChanged(const QString &arg1)
{
    if (arg1 == QString("Surrogates")) {
      theStackedWidget->setCurrentIndex(1);
      theCurrentEngine = theSurrogatesEngine;
    } else if ((arg1 == QString("SampleMethods"))) {
      theStackedWidget->setCurrentIndex(0);
      theCurrentEngine = theSampleMethodsEngine;
    } /*else if ((arg1 == QString("Bayesian Calibration")) || (arg1 == QString("Inverse Problem"))) {
      theStackedWidget->setCurrentIndex(2);
      theCurrentEngine = theBayesianCalibrationEngine;
    } else if ((arg1 == QString("Reliability")) || (arg1 == QString("Reliability Analysis"))) {
      theStackedWidget->setCurrentIndex(3);
      theCurrentEngine = theReliabilityEngine;
    } else if ((arg1 == QString("Sensitivity")) || (arg1 == QString("Sensitivity Analysis"))) {
      theStackedWidget->setCurrentIndex(4);
      theCurrentEngine = theSensitivityEngine;
    } */else {
      qDebug() << "ERROR .. DakotaEngine selection .. type unknown: " << arg1;
    }

    // emit signal if engine changed
//    if (theCurrentEngine != theOldEngine)
//        emit onUQ_EngineChanged();
}

int
UQpyEngine::getMaxNumParallelTasks(void) {
    return 1;
}

bool
UQpyEngine::outputToJSON(QJsonObject &rvObject) {
    return true;
}


bool
UQpyEngine::inputFromJSON(QJsonObject &rvObject) {
    return true;
}


int
UQpyEngine::processResults(QString &filenameResults, QString &filenameTab) {
    return 0;
}


RandomVariablesContainer *
UQpyEngine::getParameters() {
  QString classType("Uncertain");
  RandomVariablesContainer *theRV =  new RandomVariablesContainer(classType);
  return theRV;
}

UQ_Results *UQpyEngine::getResults(void) {
  UQ_Results *theRes = new UQ_Results();
  return theRes;
}

void
UQpyEngine::clear(void) {
    return;
}


QString
UQpyEngine::getProcessingScript() {
    return QString("parseUQpy.py");
}




