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

#include "DakotaInputBayesianCalibration.h"
#include <DakotaResultsBayesianCalibration.h>
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
#include <InputWidgetEDP.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>


DakotaInputBayesianCalibration::DakotaInputBayesianCalibration(QWidget *parent)
    : UQ_Engine(parent),uqSpecific(0)
{
    layout = new QVBoxLayout();

    QHBoxLayout *methodLayout= new QHBoxLayout;
    QLabel *label1 = new QLabel();
    label1->setText(QString("Method"));
    calibrationMethod = new QComboBox();
    calibrationMethod->addItem(tr("DREAM"));
    calibrationMethod->addItem(tr("QUESO - MCMC w Delayed Rejection"));
    calibrationMethod->addItem(tr("QUESO - Adaptive Metropolis"));
    calibrationMethod->addItem(tr("QUESO - DRAM"));
    calibrationMethod->addItem(tr("QUESO - Metropolis Hastings"));
    
    methodLayout->addWidget(label1);
    methodLayout->addWidget(calibrationMethod,2);
    methodLayout->addStretch(4);
    
    QGridLayout *otherLayout= new QGridLayout;
    QLabel *label2 = new QLabel();
    label2->setText(QString("#Chain Samples"));
    chainSamples = new QLineEdit();
    chainSamples->setText(tr("5000"));
    //chainSamples->setMaximumWidth(100);
    //chainSamples->setMinimumWidth(100);

    otherLayout->addWidget(label2, 0,0);
    otherLayout->addWidget(chainSamples, 0,1);
    
    QLabel *label3 = new QLabel();
    label3->setText(QString("Seed"));
    srand(time(NULL));
    int randomNumber = rand() % 1000 + 1;

    randomSeed = new QLineEdit();
    randomSeed->setText(QString::number(randomNumber));
    //    randomSeed->setMaximumWidth(100);
    //    randomSeed->setMinimumWidth(100);
    otherLayout->addWidget(label3, 1,0);
    otherLayout->addWidget(randomSeed, 1,1);
    
    //Burn In Samples
    QLabel* burnInlabel = new QLabel();
    burnInlabel->setText(QString("Burn In Samples"));
    burnInSamples = new QLineEdit();
    burnInSamples->setText("500");
    otherLayout->addWidget(burnInlabel, 2,0);
    otherLayout->addWidget(burnInSamples, 2,1);
    
    //Emulator
    QLabel* Emulatorlabel = new QLabel();
    Emulatorlabel->setText(QString("Use Emulator"));
    Emulator = new QComboBox();
    Emulator->addItem("No");
    Emulator->addItem("Yes");
    otherLayout->addWidget(Emulatorlabel, 3,0);
    otherLayout->addWidget(Emulator, 3,1);

    //Proposal covariance
    QLabel* covlabel = new QLabel();
    covlabel->setText(QString("Proposal Covariance"));
    propCov = new QComboBox();
    propCov->addItem("Prior");
    propCov->addItem("Values");
    propCov->addItem("Filename");
    otherLayout->addWidget(covlabel, 4,0);
    otherLayout->addWidget(propCov, 4,1);    

    //Adaptive posterior
    QLabel* apostlabel = new QLabel();
    apostlabel->setText(QString("Adaptive Posterior"));
    aPost = new QComboBox();
    aPost->addItem("No");
    aPost->addItem("Yes");
    otherLayout->addWidget(apostlabel, 5,0);
    otherLayout->addWidget(aPost, 5,1);  

    //Logit mapping
    QLabel* logMaplabel = new QLabel();
    logMaplabel->setText(QString("Logit Mapping"));
    logMap = new QComboBox();
    logMap->addItem("No");
    logMap->addItem("Yes");
    otherLayout->addWidget(logMaplabel, 6,0);
    otherLayout->addWidget(logMap, 6,1);  


    otherLayout->setColumnStretch(6,1);
    otherLayout->setRowStretch(7,1);

    layout->addLayout(methodLayout);
    layout->addLayout(otherLayout);

    this->setLayout(layout);
}

DakotaInputBayesianCalibration::~DakotaInputBayesianCalibration()
{

}

int 
DakotaInputBayesianCalibration::getMaxNumParallelTasks(void){
  return 1;
}

void DakotaInputBayesianCalibration::clear(void)
{

}


bool
DakotaInputBayesianCalibration::outputToJSON(QJsonObject &jsonObject)
{
    bool result = true;
    QJsonObject uq;
    uq["method"]=calibrationMethod->currentText();
    uq["chain_samples"]=chainSamples->text().toInt();
    uq["seed"]=randomSeed->text().toDouble();
    uq["burn_in_samples"]=burnInSamples->text().toInt();
    uq["use_emulator"]=Emulator->currentText();
    uq["prop_cov"]=propCov->currentText();
    uq["adaptive_post"]=aPost->currentText();
    uq["logMap"]=logMap->currentText();

    jsonObject["bayesian_calibration_method_data"]=uq;
    return result;

}


bool
DakotaInputBayesianCalibration::inputFromJSON(QJsonObject &jsonObject)
{
    bool result = true;
    this->clear();

    if (jsonObject.contains("bayesian_calibration_method_data")) {
        QJsonObject uq = jsonObject["bayesian_calibration_method_data"].toObject();
        QString method =uq["method"].toString();
        int samples=uq["chain_samples"].toInt();
        double seed=uq["seed"].toDouble();

        chainSamples->setText(QString::number(samples));
        randomSeed->setText(QString::number(seed));

        int index = calibrationMethod->findText(method);
        calibrationMethod->setCurrentIndex(index);

    } else {
        emit sendErrorMessage("ERROR: Bayesian Calibration INput - no \"bayesian_calibration_method\" data");
        return false;
    }

    return true;
}

void DakotaInputBayesianCalibration::uqSelectionChanged(const QString &arg1)
{

}

int DakotaInputBayesianCalibration::processResults(QString &filenameResults, QString &filenameTab) {

    return 0;
}

UQ_Results *
DakotaInputBayesianCalibration::getResults(void) {
  return new DakotaResultsBayesianCalibration();
}

RandomVariablesContainer *
DakotaInputBayesianCalibration::getParameters(void) {
  QString classType("Uncertain");
  return new RandomVariablesContainer(classType);
}
