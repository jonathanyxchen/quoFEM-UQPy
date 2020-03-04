#include <RSSInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

RSSInputWidget::RSSInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    sample_object = new QLineEdit();

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

    max_train_size = new QLineEdit();

    layout->addWidget(new QLabel("max_train_size"), 4, 0);
    layout->addWidget(max_train_size, 4, 1);

    step_size = new QLineEdit();
    step_size->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("step_size"), 5, 0);
    layout->addWidget(step_size, 5, 1);

    qoi_name = new QLineEdit();

    layout->addWidget(new QLabel("qoi_name"), 6, 0);
    layout->addWidget(qoi_name, 6, 1);

    local = new QLineEdit();
    local->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("local"), 7, 0);
    layout->addWidget(local, 7, 1);

    verbose = new QComboBox();
    verbose->addItem(tr("True"));
    verbose->addItem(tr("False"));

    layout->addWidget(new QLabel("Verbose"), 8, 0);
    layout->addWidget(verbose, 8, 1);

    layout->setRowStretch(9, 1);
    layout->setColumnStretch(9, 1);
    this->setLayout(layout);
}

RSSInputWidget::~RSSInputWidget()
{

}

bool
RSSInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
    jsonObj["samples"]=nsamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
RSSInputWidget::inputFromJSON(QJsonObject &jsonObject){

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
RSSInputWidget::clear(void)
{

}


int
RSSInputWidget::getNumberTasks()
{
  return nsamples->text().toInt();
}
