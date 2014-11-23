#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>

class PrinterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterWidget(QWidget *parent = 0);

signals:

public slots:
    void onPrintButtonClicked();

private:
    void initLayout();
    void initSignalSlots();

private:
    QLabel *tip_label_, *arrow_label_;
    QPushButton *print_button_;
    QTextEdit *content_txtedit_;
    QComboBox *lpt_cmb_;
};

#endif // PRINTERWIDGET_H
