#include "printerwidget.h"
#include "macrostrings.h"
#include "printersettingdlg.h"
#include "printerhandler.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QLineEdit>
#include <QDebug>
#include <QGroupBox>
#include <QFileDialog>
#include <QApplication>

PrinterWidget::PrinterWidget(QWidget *parent) :
    QWidget(parent)
{
    initLayout();
    setting_dlg_ = new PrinterSettingDlg(this);
    initSignalSlots();
    setWindowIcon(QIcon(":/printer.png"));
    setWindowTitle(STRING_TITLE);
    resize(600,400);
}

void PrinterWidget::onPrintButtonClicked()
{
    QString content = content_txtedit_->toPlainText();
    QString lpt = lpt_cmb_->currentText().trimmed();
    FILE* fp = fopen(lpt.toUtf8().data(), "r+");
    if (fp == nullptr)
    {
        QMessageBox::warning(this, STRING_WARNING, STRING_OPEN_LPT_FAILED);
        return;
    }
    else
    {
        QFile file;
        file.open(fp, QFile::ReadWrite);

        /*
         * DLE B  // 打印机初始化
         * CEX p  // 设置倍宽字符（汉字）
         * CEX q  // 取消倍宽字符（汉字）
         * ESC i  // 设置加重字符
         * ESC j  // 取消加重字符
         * FF     // 换页
         * ESC b  // 确定打印操作结束
         * ESC ( n1 n2  // 设置打印区域左边界，n1为高位，n2为低位，公式 (n1*256+n2)/180 英寸
         * CEX $ n  // 设置字符间距(以点距为单位)
         * ESC $ @  // 设定汉字模式
         * ESC ( H  // 解除汉字模式
         * ESC VT n1 n2  // 直接进纸若干行
        */

        PrinterHandler *handler = PrinterHandler::GetInstance();
        PrinterParam param(handler->GetPrinterParam());
        QByteArray array;
        // DLE B
        array.append(16);
        array.append(66);

        // ESC $ @
//        array.append(27);
//        array.append('$');
//        array.append('@');

        // CEX $ n
        array.append(28);
        array.append(36);
        array.append(param.char_spacing_);

        // ESC ( n1 n2
        array.append(27);
        array.append(40);
//        unsigned char ch = 0x00;
        array.append(param.high_byte_);
        array.append(param.low_byte_);

        if (param.is_bold_)
        {
            array.append(27);
            array.append('i');
        }
        if (param.is_widen_)
        {
            array.append(28);
            array.append('p');
        }

//        array.append(27);
//        array.append(11);
//        unsigned char ch = NULL;
//        array.append(ch);
//        array.append(4);

        array.append(content.toLocal8Bit());

        if (param.is_widen_)
        {
            array.append(28);
            array.append('q');
        }
        if (param.is_bold_)
        {
            array.append(27);
            array.append('j');
        }

        // ESC ( H
//        array.append(27);
//        array.append('(');
//        array.append('H');

        // FF
        array.append(12);
        // ESC b
        array.append(27);
        array.append(98);

        array.append(16);
        array.append(66);

        file.write(array);
        file.flush();
        fflush(fp);
        file.close();
        fclose(fp);
    }
}

void PrinterWidget::onSaveButtonClicked()
{
    QString content(content_txtedit_->toPlainText().trimmed());
    QString filename = QFileDialog::getSaveFileName(this, STRING_SAVE, QApplication::applicationDirPath(), STRING_TXT_FILTER, 0, 0);
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, STRING_WARNING, "Can not save this file!");
            return;
        }
        QTextStream outStream(&file);
        outStream << content;
        outStream.flush();
        file.close();
    }
}

void PrinterWidget::onOpenButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, STRING_OPEN, QApplication::applicationDirPath(), STRING_TXT_FILTER, 0, 0);
    if (filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, STRING_WARNING, "Can not open file for read !");
        return;
    }
    QTextStream readStream(&file);
    QString content = readStream.readAll();
    readStream.flush();
    content_txtedit_->setPlainText(content);
}

void PrinterWidget::onSetButtonClicked()
{
    if (setting_dlg_ != nullptr)
    {
        setting_dlg_->exec();
    }
}

void PrinterWidget::initLayout()
{
    this->setObjectName("PrinterWidget");
    content_txtedit_ = new QTextEdit;
    content_txtedit_->setFrameShadow(QFrame::Plain);
    tip_label_ = new QLabel("<h4>" + STRING_CHOOSE_PRINTER + "</h4>");
    lpt_cmb_ = new QComboBox;
    lpt_cmb_->addItem("LPT1");
    lpt_cmb_->addItem("LPT2");
    lpt_cmb_->setCurrentIndex(0);
    print_button_ = new QPushButton(STRING_PRINT);
    save_button_ = new QPushButton(STRING_SAVE);
    open_button_ = new QPushButton(STRING_OPEN);
    set_button_ = new QPushButton(STRING_SET);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(tip_label_);
    hlayout->addWidget(lpt_cmb_);
    hlayout->addStretch(2);
    hlayout->addWidget(print_button_);
    hlayout->addStretch(1);
    hlayout->addWidget(open_button_);
    hlayout->addStretch(1);
    hlayout->addWidget(set_button_);
    hlayout->addStretch(1);
    hlayout->addWidget(save_button_);

    QVBoxLayout *vlayout = new QVBoxLayout;
    content_txtedit_->setPlaceholderText(STRING_TIPS);
    vlayout->addWidget(content_txtedit_);

    QLabel *copyright_label = new QLabel(STRING_COPYRIGHT);
    copyright_label->setFrameStyle(QFrame::Sunken);
    QLabel *warning_label = new QLabel(STRING_DECLARE);
    QHBoxLayout *copyright_hlayout = new QHBoxLayout;
    copyright_hlayout->addWidget(copyright_label);
    copyright_hlayout->addStretch();
    copyright_hlayout->addWidget(warning_label);

    QGroupBox *grp = new QGroupBox;
    QVBoxLayout *bottom_vlayout = new QVBoxLayout;
    bottom_vlayout->addLayout(hlayout);
    bottom_vlayout->addSpacerItem(new QSpacerItem(15,20));
    bottom_vlayout->addLayout(copyright_hlayout);
    grp->setLayout(bottom_vlayout);
    vlayout->addWidget(grp);
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
            "QWidget#PrinterWidget {"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff); }"
             "QGroupBox {border-width:1px;border-style:solid;border-color:LightSkyBlue;margin-top: 1ex;"
                         "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff);}"
             "QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;left:10px;margin-left:0px;padding:0px}"
            "QTextEdit {"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff); }"
                );
    setStyleSheet(qss);
    print_button_->setMinimumSize(60,30);
}

void PrinterWidget::initSignalSlots()
{
    connect(print_button_, &QPushButton::clicked, this, &PrinterWidget::onPrintButtonClicked);
    connect(save_button_, &QPushButton::clicked, this, &PrinterWidget::onSaveButtonClicked);
    connect(open_button_, &QPushButton::clicked, this, &PrinterWidget::onOpenButtonClicked);
    connect(set_button_, &QPushButton::clicked, this, &PrinterWidget::onSetButtonClicked);
}
