#include <LHSInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

LHSInputWidget::LHSInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    criteria = new QComboBox();
    criteria->addItem(tr("random"));
    criteria->addItem(tr("centered"));
    criteria->addItem(tr("maxmin"));
    criteria->addItem(tr("correlate"));

    layout->addWidget(new QLabel("lhs_criteria"), 0, 0);
    layout->addWidget(criteria, 0, 1);

    metric = new QComboBox();
    metric->addItem(tr("braycurtis"));
    metric->addItem(tr("canberra"));
    metric->addItem(tr("chebyshev"));
    metric->addItem(tr("cityblock"));
    metric->addItem(tr("correlation"));
    metric->addItem(tr("cosine"));
    metric->addItem(tr("dice"));
    metric->addItem(tr("euclidean"));
    metric->addItem(tr("hamming"));
    metric->addItem(tr("jaccard"));
    metric->addItem(tr("kulsinski"));
    metric->addItem(tr("mahalanobis"));
    metric->addItem(tr("minkowski"));
    metric->addItem(tr("rogerstanimoto"));
    metric->addItem(tr("russellrao"));
    metric->addItem(tr("seuclidean"));
    metric->addItem(tr("sokalmichener"));
    metric->addItem(tr("sokalsneath"));
    metric->addItem(tr("sqeuclidean"));

    layout->addWidget(new QLabel("lhs_metric"), 1, 0);
    layout->addWidget(metric, 1, 1);

    iter = new QLineEdit();
    iter->setValidator(new QIntValidator);
    iter->setToolTip("Specify the number of samples");

    layout->addWidget(new QLabel("lhs_iter"), 2, 0);
    layout->addWidget(iter, 2, 1);

    // create layout label and entry for # samples
    numSamples = new QLineEdit();
    numSamples->setValidator(new QIntValidator);
    numSamples->setToolTip("Specify the number of samples");

    layout->addWidget(new QLabel("nsamples"), 3, 0);
    layout->addWidget(numSamples, 3, 1);

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

    layout->addWidget(new QLabel("Verbose"), 4, 0);
    layout->addWidget(verbose, 4, 1);

    layout->setRowStretch(5, 1);
    layout->setColumnStretch(5, 1);
    this->setLayout(layout);
}

LHSInputWidget::~LHSInputWidget()
{

}

bool
LHSInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
    jsonObj["samples"]=numSamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
LHSInputWidget::inputFromJSON(QJsonObject &jsonObject){

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
LHSInputWidget::clear(void)
{

}


int
LHSInputWidget::getNumberTasks()
{
  return numSamples->text().toInt();
}
