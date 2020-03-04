#include <MCMCInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

MCMCInputWidget::MCMCInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    dimension = new QLineEdit();
    dimension->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("dimension"), 0, 0);
    layout->addWidget(dimension, 0, 1);

    pdf_target1 = new QLineEdit();
    pdf_target2 = new QLineEdit();

    layout->addWidget(new QLabel("pdf_target"), 1, 0);
    layout->addWidget(pdf_target1, 1, 1);
    layout->addWidget(pdf_target2, 1, 2);

    log_pdf_target1 = new QLineEdit();
    log_pdf_target2 = new QLineEdit();

    layout->addWidget(new QLabel("log_pdf_target"), 2, 0);
    layout->addWidget(log_pdf_target1, 2, 1);
    layout->addWidget(log_pdf_target2, 2, 2);

    args_target = new QLineEdit();

    layout->addWidget(new QLabel("args_target"), 3, 0);
    layout->addWidget(args_target, 3, 1);

    algorithm = new QComboBox();
    algorithm->addItem(tr("MH"));
    algorithm->addItem(tr("MMH"));
    algorithm->addItem(tr("Stretch"));
    algorithm->addItem(tr("DEMC"));
    algorithm->addItem(tr("DRAM"));

    layout->addWidget(new QLabel("algorithm"), 4, 0);
    layout->addWidget(algorithm, 4, 1);

    seed = new QLineEdit();

    layout->addWidget(new QLabel("seed"), 5, 0);
    layout->addWidget(seed, 5, 1);

    nsamples = new QLineEdit();
    nsamples->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("nsamples"), 6, 0);
    layout->addWidget(nsamples, 6, 1);

    nsamples_per_chain = new QLineEdit();
    nsamples_per_chain->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("nsamples_per_chain"), 7, 0);
    layout->addWidget(nsamples_per_chain, 7, 1);

    nburn = new QLineEdit();
    nburn->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("nburn"), 8, 0);
    layout->addWidget(nburn, 8, 1);

    jump = new QLineEdit();
    jump->setValidator(new QIntValidator);

    layout->addWidget(new QLabel("jump"), 9, 0);
    layout->addWidget(jump, 9, 1);

    save_log_pdf = new QComboBox();
    verbose->addItem(tr("True"));
    verbose->addItem(tr("False"));

    layout->addWidget(new QLabel("save_log_pdf"), 10, 0);
    layout->addWidget(save_log_pdf, 10, 1);

    concat_chains_ = new QComboBox();
    concat_chains_->addItem(tr("True"));
    concat_chains_->addItem(tr("False"));

    layout->addWidget(new QLabel("concat_chains_"), 11, 0);
    layout->addWidget(concat_chains_, 11, 1);

    verbose = new QComboBox();
    verbose->addItem(tr("True"));
    verbose->addItem(tr("False"));

    layout->addWidget(new QLabel("Verbose"), 12, 0);
    layout->addWidget(verbose, 12, 1);

    layout->setRowStretch(13, 1);
    layout->setColumnStretch(13, 1);
    this->setLayout(layout);
}

MCMCInputWidget::~MCMCInputWidget()
{

}

bool
MCMCInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
    jsonObj["samples"]=nsamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
MCMCInputWidget::inputFromJSON(QJsonObject &jsonObject){

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
MCMCInputWidget::clear(void)
{

}


int
MCMCInputWidget::getNumberTasks()
{
  return nsamples->text().toInt();
}
