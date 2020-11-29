#ifndef MESSAGE_DIALOG_H
#define MESSAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QWidget *parent = nullptr, const QString &text = "");
    ~MessageDialog();

    static int information(QWidget *parent = nullptr, const QString &text = "");

private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGE_DIALOG_H
