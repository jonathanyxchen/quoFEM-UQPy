#include <ISInputWidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QValidator>
#include <QJsonObject>

ISInputWidget::ISInputWidget(QWidget *parent)
: UQ_MethodInputWidget(parent)
{
    auto layout = new QGridLayout();

    pdf_target1 = new QLineEdit();
    pdf_target2 = new QLineEdit();

    layout->addWidget(new QLabel("pdf_target"), 0, 0);
    layout->addWidget(pdf_target1, 0, 1);
    layout->addWidget(pdf_target2, 0, 2);

    log_pdf_target1 = new QLineEdit();
    log_pdf_target2 = new QLineEdit();

    layout->addWidget(new QLabel("log_pdf_target"), 1, 0);
    layout->addWidget(log_pdf_target1, 1, 1);
    layout->addWidget(log_pdf_target2, 1, 2);

    args_target = new QLineEdit();

    layout->addWidget(new QLabel("args_target"), 2, 0);
    layout->addWidget(args_target, 2, 1);

    verbose = new QComboBox();
    verbose->addItem(tr("True"));
    verbose->addItem(tr("False"));

    layout->addWidget(new QLabel("Verbose"), 3, 0);
    layout->addWidget(verbose, 3, 1);

    layout->setRowStretch(4, 1);
    layout->setColumnStretch(4, 1);
    this->setLayout(layout);
}

ISInputWidget::~ISInputWidget()
{

}

bool
ISInputWidget::outputToJSON(QJsonObject &jsonObj){

    bool result = true;
//    jsonObj["samples"]=nsamples->text().toInt();
//    jsonObj["seed"]=randomSeed->text().toDouble();
    return result;
}

bool
ISInputWidget::inputFromJSON(QJsonObject &jsonObject){

  bool result = false;
  if (jsonObject.contains("samples") && jsonObject.contains("seed")) {
//    int samples=jsonObject["samples"].toInt();
//    double seed=jsonObject["seed"].toDouble();
//    nsamples->setText(QString::number(samples));
//    randomSeed->setText(QString::number(seed));
    result = true;
  }

  return result;
}

void
ISInputWidget::clear(void)
{

}


int
ISInputWidget::getNumberTasks()
{
//  return nsamples->text().toInt();
}
