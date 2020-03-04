#include <SimplexInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

SimplexInputWidget::SimplexInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    nodes = new QLineEdit();

    layout->addWidget(new QLabel("nodes"), 0, 0);
    layout->addWidget(nodes, 0, 1);

    nsamples = new QLineEdit();
    nsamples->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("nsamples"), 1, 0);
    layout->addWidget(nsamples, 1, 1);

    layout->setRowStretch(2, 1);
    layout->setColumnStretch(2, 1);
    this->setLayout(layout);
}

SimplexInputWidget::~SimplexInputWidget()
{

}

bool
SimplexInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
//    jsonObj["samples"]=numSamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
SimplexInputWidget::inputFromJSON(QJsonObject &jsonObject){

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
SimplexInputWidget::clear(void)
{

}


int
SimplexInputWidget::getNumberTasks()
{
//  return numSamples->text().toInt();
}
