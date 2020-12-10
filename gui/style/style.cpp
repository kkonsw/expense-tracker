#include "style.h"

#include <QCalendarWidget>
#include <QTextCharFormat>

void Style::changeQDateEditStyleSheet(QDateEdit *dateEdit)
{
    QString style_sheet = "QCalendarWidget QTableView"
                          "{"
                          "alternate-background-color: grey;"
                          "color: white;"
                          "selection-background-color: grey;"
                          "selection-color: white"
                          "}"
                          "QDateEdit"
                          "{"
                          "color: white;"
                          "selection-background-color: white;"
                          "}"
                          "QDateEdit QAbstractItemView::disabled"
                          "{"
                          "color: grey;"
                          "}";

    dateEdit->setStyleSheet(style_sheet);

    dateEdit->setCalendarPopup(true);
    dateEdit->calendarWidget()->setFirstDayOfWeek(Qt::DayOfWeek::Monday);

    QTextCharFormat weekendFormat;
    weekendFormat.setForeground(QBrush(Qt::white, Qt::SolidPattern));
    dateEdit->calendarWidget()->setWeekdayTextFormat(Qt::Saturday,
                                                         weekendFormat);
    dateEdit->calendarWidget()->setWeekdayTextFormat(Qt::Sunday,
                                                         weekendFormat);
    dateEdit->setDisplayFormat("dd/MM/yyyy");
}
