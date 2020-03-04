#include <StrataInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

StrataInputWidget::StrataInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    nstrata = new QLineEdit();

    layout->addWidget(new QLabel("nstrata"), 0, 0);
    layout->addWidget(nstrata, 0, 1);

    inputFile = new QLineEdit();

    layout->addWidget(new QLabel("input file"), 1, 0);
    layout->addWidget(inputFile, 1, 1);

    origins = new QLineEdit();

    layout->addWidget(new QLabel("origins"), 2, 0);
    layout->addWidget(origins, 2, 1);

    widths = new QLineEdit();

    layout->addWidget(new QLabel("widths"), 3, 0);
    layout->addWidget(widths, 3, 1);

    weights = new QLineEdit();

    layout->addWidget(new QLabel("weights"), 4, 0);
    layout->addWidget(weights, 4, 1);

    layout->setRowStretch(5, 1);
    layout->setColumnStretch(5, 1);
    this->setLayout(layout);
}

StrataInputWidget::~StrataInputWidget()
{

}

bool
StrataInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
//    jsonObj["samples"]=numSamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
StrataInputWidget::inputFromJSON(QJsonObject &jsonObject){

  bool result = false;
  if (jsonObject.contains("samples") && jsonObject.contains("seed")) {
//    int samples=jsonObject["samples"].toInt();
//    double seed=jsonObject["seed"].toDouble();
//    numSamples->setText(QString::number(samples));
//    randomSeed->setText(QString::number(seed));
    result = true;
  }

  return result;
}

void
StrataInputWidget::clear(void)
{

}


int
StrataInputWidget::getNumberTasks()
{
//  return numSamples->text().toInt();
}
