#include "macrostrings.h"
#include "printersettingdlg.h"
#include "printerhandler.h"

#include <QLabel>
#include <QSpinBox>
#include <QRadioButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QButtonGroup>

PrinterSettingDlg::PrinterSettingDlg(QWidget *parent) : QDialog(parent)
{
    handler_ = PrinterHandler::GetInstance();
    InitLayout();
    InitParam();
    InitSignalSlots();
}

void PrinterSettingDlg::InitParam()
{
    PrinterParam param;
    param.is_bold_ = false;
    param.is_widen_ = false;
    param.low_byte_ = 0;
//    param.high_byte_ = 0;
    param.char_spacing_ = 0;
    param.feedinches_ = 0;
    param.rowspacing_120_ = 0;
    handler_->SetPrinterParam(param);
    UpdateUI(param);
}

void PrinterSettingDlg::onOKButtonClicked()
{
    PrinterParam param;
    param.is_bold_ = bold_yes_rbt_->isChecked();
    param.is_widen_ = widen_yes_rbt_->isChecked();
//    param.high_byte_ = left_high_spb_->value();
    param.low_byte_ = left_low_spb_->value();
    param.char_spacing_ = char_space_spb_->value();
    param.feedinches_ = feedinches_spb_->value();
    param.rowspacing_120_ = rowspacing_120_spb_->value();
    handler_->SetPrinterParam(param);
    this->accept();
}

void PrinterSettingDlg::onResetButtonClicked()
{
    UpdateUI(handler_->GetPrinterParam());
}

void PrinterSettingDlg::InitLayout()
{
    setObjectName("PrinterSettingDlg");
    setWindowTitle(STRING_SET);
    bold_label_ = new QLabel(STRING_BOLD_CHAR);
    horizon_label_ = new QLabel(STRING_WIDE_CHAR);
    left_border_label_ = new QLabel(STRING_LEFT_BORDER);
    char_spacing_label_ = new QLabel(STRING_CHAR_SPACE);
    low_label_  = new QLabel(STRING_LOW_BYTE);

    bold_yes_rbt_ = new QRadioButton(STRING_YES,this);
    bold_no_rbt_ = new QRadioButton(STRING_NO,this);

    QButtonGroup *bold_bgrp = new QButtonGroup(this);
    bold_bgrp->addButton(bold_yes_rbt_);
    bold_bgrp->addButton(bold_no_rbt_);

    widen_yes_rbt_ = new QRadioButton(STRING_YES,this);
    widen_no_rbt_ = new QRadioButton(STRING_NO,this);

    QButtonGroup *widen_bgrp = new QButtonGroup(this);
    widen_bgrp->addButton(widen_yes_rbt_);
    widen_bgrp->addButton(widen_no_rbt_);

    left_low_spb_ = new QSpinBox(this);
    char_space_spb_ = new QSpinBox(this);

    left_low_spb_->setRange(0, 999);
    char_space_spb_->setRange(0, 180);

    feedinches_spb_ = new QSpinBox(this);
    feedinches_spb_->setRange(0, 255);
    rowspacing_120_spb_ = new QSpinBox(this);
    rowspacing_120_spb_->setRange(0, 255);

    QLabel *rowspacing_label = new QLabel(STRING_CUSTOM+STRING_ROW_SPACING, this);

    ok_button_ = new QPushButton(STRING_OK);
    reset_button_ = new QPushButton(STRING_RESET);

    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(bold_label_, 0, 0, 1, 1, Qt::AlignRight);
    glayout->addWidget(bold_yes_rbt_, 0, 1, 1, 1, Qt::AlignLeft);
    glayout->addWidget(bold_no_rbt_, 0, 2, 1, 1, Qt::AlignLeft);

    glayout->addWidget(horizon_label_, 1, 0, 1, 1, Qt::AlignRight);
    glayout->addWidget(widen_yes_rbt_, 1, 1, 1, 1, Qt::AlignLeft);
    glayout->addWidget(widen_no_rbt_, 1, 2, 1, 1, Qt::AlignLeft);

    glayout->addWidget(rowspacing_label, 2, 0, 1, 2, Qt::AlignRight);
    glayout->addWidget(rowspacing_120_spb_, 2, 2, 1, 1, Qt::AlignLeft);

    glayout->addWidget(char_spacing_label_, 3, 0, 1, 2, Qt::AlignRight);
    glayout->addWidget(char_space_spb_, 3, 2, 1, 1, Qt::AlignLeft);

    glayout->addWidget(left_border_label_, 4, 0, 1, 2, Qt::AlignRight);
    glayout->addWidget(left_low_spb_, 4, 2, 1, 1, Qt::AlignLeft);

    glayout->addWidget(new QLabel(STRING_FEEDINCH, this), 5, 0, 1, 2, Qt::AlignRight);
    glayout->addWidget(feedinches_spb_, 5, 2, 1, 1, Qt::AlignLeft);

    QGroupBox *grp = new QGroupBox(STRING_SET);
    QVBoxLayout *grp_vlayout = new QVBoxLayout();
    grp_vlayout->addLayout(glayout);
    grp->setLayout(grp_vlayout);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch(1);
    btnLayout->addWidget(ok_button_);
    btnLayout->addStretch(1);
    btnLayout->addWidget(reset_button_);
    btnLayout->addStretch(1);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(grp);
    vlayout->addLayout(btnLayout);
    setLayout(vlayout);

    QString qss(
            "QComboBox { "
                "background-color: rgb(233,246,254);"
                "border:1px solid rgb(128,171,224);"
                "border-radius:3px;"
                "min-width: 80px;}"
            "QComboBox QAbstractItemView {"
                "selection-background-color:rgb(128,171,224); }"
            "QComboBox::item {"
                "background-color: transparent;"
                "color: #000000;}"
            "QComboBox::item:selected {"
                "background-color: #83c8f9; }"
            "QPushButton {"
                "border: 1px solid #dcdcdc; border-radius: 4px;"
                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #cef3ff, stop: 1 #fffafa);"
                "min-width: 60px; min-height: 20px; }"
            "QPushButton:hover {"
                "border: 1px solid #f8f8ff; border-radius: 4px;"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #ceffff, stop: 1 #ffffff); }"
            "QPushButton:pressed {"
                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #e9f6fe); }"
            "QPushButton:checked {"
                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #bebebe, stop: 1 #f6f7fa); }"
            "QPushButton:flat {"
                "border: none; }"
            "QPushButton:default {"
                 "border-color: navy; }"
            "QWidget#PrinterSettingDlg {"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff); }"
             "QGroupBox {border-width:1px;border-style:solid;border-color:LightSkyBlue;margin-top: 1ex;"
                         "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff);}"
             "QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;left:10px;margin-left:0px;padding:0px}"
            "QTextEdit {"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff); }"
                );
    setStyleSheet(qss);
}

void PrinterSettingDlg::InitSignalSlots()
{
    connect(ok_button_, &QPushButton::clicked, this, &PrinterSettingDlg::onOKButtonClicked);
    connect(reset_button_, &QPushButton::clicked, this, &PrinterSettingDlg::onResetButtonClicked);
}

void PrinterSettingDlg::UpdateUI(const PrinterParam &param)
{
    bold_yes_rbt_->setChecked(param.is_bold_);
    bold_no_rbt_->setChecked(!param.is_bold_);
    widen_yes_rbt_->setChecked(param.is_widen_);
    widen_no_rbt_->setChecked(!param.is_widen_);
//    left_high_spb_->setValue(param.high_byte_);
    left_low_spb_->setValue(param.low_byte_);
    char_space_spb_->setValue(param.char_spacing_);
}
