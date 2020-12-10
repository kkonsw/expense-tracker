#ifndef STYLE_H
#define STYLE_H

#include <QDateEdit>

class Style
{
public:
    Style() = delete;

    static void changeQDateEditStyleSheet(QDateEdit *dateEdit);
};

#endif // STYLE_H
