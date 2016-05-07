#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>

QT_FORWARD_DECLARE_CLASS(PrinterSettingDlg)

class PrinterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterWidget(QWidget *parent = 0);

signals:

public slots:
    void onPrintButtonClicked();
    void onSaveButtonClicked();
    void onOpenButtonClicked();
    void onSetButtonClicked();

private:
    void initLayout();
    void initSignalSlots();

private:
    PrinterSettingDlg *setting_dlg_;
    QLabel *tip_label_, *arrow_label_;
    QPushButton *print_button_, *save_button_, *open_button_, *set_button_;
    QTextEdit *content_txtedit_;
    QComboBox *lpt_cmb_;
};

#endif // PRINTERWIDGET_H
