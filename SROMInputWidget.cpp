#include <SROMInputWidget.h>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

SROMInputWidget::SROMInputWidget(QWidget *parent) 
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    // create layout label and entry for # samples
    numSamples = new QLineEdit();
    numSamples->setText(tr("500"));
    numSamples->setValidator(new QIntValidator);
    numSamples->setToolTip("Specify the number of samples");

    layout->addWidget(new QLabel("# Samples"), 0, 0);
    layout->addWidget(numSamples, 0, 1);

    // create label and entry for seed to layout
    srand(time(NULL));
    int randomNumber = rand() % 1000 + 1;
    randomSeed = new QLineEdit();
    randomSeed->setText(QString::number(randomNumber));
    randomSeed->setValidator(new QIntValidator);
    randomSeed->setToolTip("Set the seed");

    layout->addWidget(new QLabel("Seed"), 1, 0);
    layout->addWidget(randomSeed, 1, 1);

    layout->setRowStretch(2, 1);
    layout->setColumnStretch(2, 1);
    this->setLayout(layout);
}

SROMInputWidget::~SROMInputWidget()
{

}

bool
SROMInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
    jsonObj["samples"]=numSamples->text().toInt();
    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;    
}

bool
SROMInputWidget::inputFromJSON(QJsonObject &jsonObject){

  bool result = false;
  if (jsonObject.contains("samples") && jsonObject.contains("seed")) {
    int samples=jsonObject["samples"].toInt();
    double seed=jsonObject["seed"].toDouble();
    numSamples->setText(QString::number(samples));
    randomSeed->setText(QString::number(seed));
    result = true;
  }

  return result;
}

void
SROMInputWidget::clear(void)
{

}


int
SROMInputWidget::getNumberTasks()
{
  return numSamples->text().toInt();
}