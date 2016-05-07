#ifndef PRINTERSETTINGDLG_H
#define PRINTERSETTINGDLG_H

#include <QDialog>
#include "printerparam.h"

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSpinBox)
QT_FORWARD_DECLARE_CLASS(QRadioButton)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(PrinterHandler)


class PrinterSettingDlg : public QDialog
{
public:
    PrinterSettingDlg(QWidget *parent = 0);
    void InitParam();

signals:

public slots:
    void onOKButtonClicked();
    void onResetButtonClicked();

private:
    void InitLayout();
    void InitSignalSlots();
    void UpdateUI(const PrinterParam& param);

private:
    PrinterHandler *handler_;

private:
    QLabel *bold_label_, *horizon_label_, *left_border_label_, *char_spacing_label_;
    QLabel *high_label_, *low_label_;
    QRadioButton *bold_yes_rbt_, *bold_no_rbt_;
    QRadioButton *widen_yes_rbt_, *widen_no_rbt_;
    QSpinBox *left_high_spb_, *left_low_spb_, *char_space_spb_;

    QPushButton *ok_button_, *reset_button_;
};

#endif // PRINTERSETTINGDLG_H
