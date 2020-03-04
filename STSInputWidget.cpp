#include <STSInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

STSInputWidget::STSInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    dimension = new QLineEdit();
    dimension->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("dimension"), 0, 0);
    layout->addWidget(dimension, 0, 1);

    // create layout label and entry for # samples
    numSamples = new QLineEdit();
    numSamples->setValidator(new QIntValidator);
    numSamples->setToolTip("Specify the number of samples");

    layout->addWidget(new QLabel("nsamples"), 1, 0);
    layout->addWidget(numSamples, 1, 1);

    criteria = new QComboBox();
    criteria->addItem(tr("random"));
    criteria->addItem(tr("centered"));

    layout->addWidget(new QLabel("sts_criteria"), 2, 0);
    layout->addWidget(criteria, 2, 1);

    stype = new QComboBox();
    stype->addItem(tr("Rectangular"));
    stype->addItem(tr("Voronoi"));

    layout->addWidget(new QLabel("stype"), 3, 0);
    layout->addWidget(stype, 3, 1);

    iter = new QLineEdit();
    iter->setValidator(new QIntValidator);
    iter->setToolTip("Specify the number of iterations");

    layout->addWidget(new QLabel("n_itersr"), 4, 0);
    layout->addWidget(iter, 4, 1);

    design = new QLineEdit();

    layout->addWidget(new QLabel("sts_design"), 5, 0);
    layout->addWidget(design, 5, 1);

    inputFile = new QLineEdit();

    layout->addWidget(new QLabel("input file"), 6, 0);
    layout->addWidget(inputFile, 6, 1);

    // create label and entry for seed to layout
//    srand(time(NULL));
//    int randomNumber = rand() % 1000 + 1;
//    randomSeed = new QLineEdit();
//    randomSeed->setText(QString::number(randomNumber));
//    randomSeed->setValidator(new QIntValidator);
//    randomSeed->setToolTip("Set the seed");

    verbose = new QComboBox();
    verbose->addItem(tr("True"));
    verbose->addItem(tr("False"));

    layout->addWidget(new QLabel("Verbose"), 7, 0);
    layout->addWidget(verbose, 7, 1);

    layout->setRowStretch(8, 1);
    layout->setColumnStretch(8, 1);
    this->setLayout(layout);
}

STSInputWidget::~STSInputWidget()
{

}

bool
STSInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
    jsonObj["samples"]=numSamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
STSInputWidget::inputFromJSON(QJsonObject &jsonObject){

  bool result = false;
  if (jsonObject.contains("samples") && jsonObject.contains("seed")) {
    int samples=jsonObject["samples"].toInt();
//    double seed=jsonObject["seed"].toDouble();
    numSamples->setText(QString::number(samples));
//    randomSeed->setText(QString::number(seed));
    result = true;
  }

  return result;
}

void
STSInputWidget::clear(void)
{

}


int
STSInputWidget::getNumberTasks()
{
  return numSamples->text().toInt();
}
