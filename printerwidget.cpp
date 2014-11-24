#include "printerwidget.h"
#include "macrostrings.h"
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
    if (fp == NULL)
    {
        QMessageBox::warning(this, STRING_WARNING, STRING_OPEN_LPT_FAILED);
        return;
    }
    else
    {
        QFile file;
        file.open(fp, QFile::ReadWrite);
        file.write(content.toLocal8Bit());
        file.close();
        fclose(fp);
    }
}

void PrinterWidget::onSaveButtonClicked()
{
    QString content(content_txtedit_->toPlainText().trimmed());
    qDebug() << content;
    QString filename = QFileDialog::getSaveFileName(this, STRING_SAVE, QApplication::applicationDirPath(), STRING_TXT_FILTER, 0, 0);
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QFile::WriteOnly))
        {
            QMessageBox::warning(this, STRING_WARNING, "Can not save this file!");
            return;
        }
        file.write(content.toUtf8());
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
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, STRING_WARNING, "Can not open file for read !");
        return;
    }
    QByteArray array = file.readAll();
    content_txtedit_->setPlainText(array);
}

void PrinterWidget::initLayout()
{
    this->setObjectName("PrinterWidget");
    content_txtedit_ = new QTextEdit;
    tip_label_ = new QLabel("<h4>" + STRING_CHOOSE_PRINTER + "</h4>");
    lpt_cmb_ = new QComboBox;
    lpt_cmb_->addItem("LPT1");
    lpt_cmb_->addItem("LPT2");
    lpt_cmb_->setCurrentIndex(0);
    print_button_ = new QPushButton(STRING_PRINT);
    save_button_ = new QPushButton(STRING_SAVE);
    open_button_ = new QPushButton(STRING_OPEN);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(tip_label_);
    hlayout->addWidget(lpt_cmb_);
    hlayout->addStretch(2);
    hlayout->addWidget(print_button_);
    hlayout->addStretch(1);
    hlayout->addWidget(open_button_);
    hlayout->addStretch(1);
    hlayout->addWidget(save_button_);

    QVBoxLayout *vlayout = new QVBoxLayout;
    content_txtedit_->setPlaceholderText(STRING_TIPS);
    vlayout->addWidget(content_txtedit_);

    QLabel *copyright_label = new QLabel(STRING_COPYRIGHT+"\t\t"+STRING_DECLARE);
    copyright_label->setFrameStyle(QFrame::Sunken);
    QGroupBox *grp = new QGroupBox;
    QVBoxLayout *bottom_vlayout = new QVBoxLayout;
    bottom_vlayout->addLayout(hlayout);
    bottom_vlayout->addSpacerItem(new QSpacerItem(15,20));
    bottom_vlayout->addWidget(copyright_label);
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
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 rgb(239,247,251), stop: 1 #ffffff); }");
    setStyleSheet(qss);

    print_button_->setMinimumSize(60,30);
}

void PrinterWidget::initSignalSlots()
{
    connect(print_button_, &QPushButton::clicked, this, &PrinterWidget::onPrintButtonClicked);
    connect(save_button_, &QPushButton::clicked, this, &PrinterWidget::onSaveButtonClicked);
    connect(open_button_, &QPushButton::clicked, this, &PrinterWidget::onOpenButtonClicked);
}
