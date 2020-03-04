#include <AKMCSInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

AKMCSInputWidget::AKMCSInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    sample_object = new QComboBox();
    sample_object->addItem(tr("MCS"));
    sample_object->addItem(tr("STS"));
    sample_object->addItem(tr("LHS"));
    sample_object->addItem(tr("MCMC"));
    sample_object->addItem(tr("IS"));

    layout->addWidget(new QLabel("sample_object"), 0, 0);
    layout->addWidget(sample_object, 0, 1);

    run_model_object = new QComboBox();
    run_model_object->addItem(tr("RunModel"));
    run_model_object->addItem(tr(" "));

    layout->addWidget(new QLabel("run_model_object"), 1, 0);
    layout->addWidget(run_model_object, 1, 1);

    krig_object = new QComboBox();
    krig_object->addItem(tr("Kriging"));
    krig_object->addItem(tr(" "));

    layout->addWidget(new QLabel("krig_object"), 2, 0);
    layout->addWidget(krig_object, 2, 1);

    // create layout label and entry for # samples
    nsamples = new QLineEdit();

    layout->addWidget(new QLabel("nsamples"), 3, 0);
    layout->addWidget(nsamples, 3, 1);

    nlearn = new QLineEdit();
    nlearn->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("nlearn"), 4, 0);
    layout->addWidget(nlearn, 4, 1);

    nstart = new QLineEdit();
    nstart->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("nstart"), 5, 0);
    layout->addWidget(nstart, 5, 1);

    If = new QComboBox();
    If->addItem(tr("U"));
    If->addItem(tr("Weighted-U"));
    If->addItem(tr("EFF"));
    If->addItem(tr("EIF"));
    If->addItem(tr("EIGF"));

    layout->addWidget(new QLabel("If"), 6, 0);
    layout->addWidget(If, 6, 1);

    n_add = new QLineEdit();
    n_add->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("n_add"), 7, 0);
    layout->addWidget(n_add, 7, 1);

    min_cov = new QLineEdit();

    layout->addWidget(new QLabel("min_cov"), 8, 0);
    layout->addWidget(min_cov, 8, 1);

    max_p = new QLineEdit();

    layout->addWidget(new QLabel("max_p"), 9, 0);
    layout->addWidget(max_p, 9, 1);

    qoi_name = new QLineEdit();

    layout->addWidget(new QLabel("qoi_name"), 10, 0);
    layout->addWidget(qoi_name, 10, 1);

    kriging = new QLineEdit();
    kriging->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("kriging"), 11, 0);
    layout->addWidget(kriging, 11, 1);

    verbose = new QComboBox();
    verbose->addItem(tr("True"));
    verbose->addItem(tr("False"));

    layout->addWidget(new QLabel("Verbose"), 12, 0);
    layout->addWidget(verbose, 12, 1);

    layout->setRowStretch(13, 1);
    layout->setColumnStretch(13, 1);
    this->setLayout(layout);
}

AKMCSInputWidget::~AKMCSInputWidget()
{

}

bool
AKMCSInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
    jsonObj["samples"]=nsamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
AKMCSInputWidget::inputFromJSON(QJsonObject &jsonObject){

  bool result = false;
  if (jsonObject.contains("samples") && jsonObject.contains("seed")) {
    int samples=jsonObject["samples"].toInt();
//    double seed=jsonObject["seed"].toDouble();
    nsamples->setText(QString::number(samples));
//    randomSeed->setText(QString::number(seed));
    result = true;
  }

  return result;
}

void
AKMCSInputWidget::clear(void)
{

}


int
AKMCSInputWidget::getNumberTasks()
{
  return nsamples->text().toInt();
}
