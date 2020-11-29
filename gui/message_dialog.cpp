#include "message_dialog.h"
#include "ui_message_dialog.h"

MessageDialog::MessageDialog(QWidget *parent, const QString &text) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    this->setFixedSize(350, 200);
    this->setWindowTitle("Message");

    ui->label->setText(text);
    connect(ui->buttonAccept, SIGNAL(clicked()), this, SLOT(accept()));
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

int MessageDialog::information(QWidget *parent, const QString &text)
{
    MessageDialog dialog(parent, text);
    return dialog.exec();
}
