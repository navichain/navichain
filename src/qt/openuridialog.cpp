// Copyright (c) 2011-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/openuridialog.h>
#include <qt/forms/ui_openuridialog.h>

#include <qt/guiutil.h>
#include <qt/walletmodel.h>
#include <qt/styleSheet.h>

#include <QUrl>

OpenURIDialog::OpenURIDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenURIDialog)
{
    ui->setupUi(this);

    SetObjectStyleSheet(ui->buttonBox->button(QDialogButtonBox::Cancel), StyleSheetNames::ButtonWhite);
    SetObjectStyleSheet(ui->buttonBox->button(QDialogButtonBox::Ok), StyleSheetNames::ButtonBlue);

#if QT_VERSION >= 0x040700
    ui->uriEdit->setPlaceholderText("nc:");
#endif
}

OpenURIDialog::~OpenURIDialog()
{
    delete ui;
}

QString OpenURIDialog::getURI()
{
    return ui->uriEdit->text();
}

void OpenURIDialog::accept()
{
    SendCoinsRecipient rcp;
    if(GUIUtil::parseBitcoinURI(getURI(), &rcp))
    {
        /* Only accept value URIs */
        QDialog::accept();
    } else {
        ui->uriEdit->setValid(false);
    }
}

void OpenURIDialog::on_selectFileButton_clicked()
{
    QString filename = GUIUtil::getOpenFileName(this, tr("Select payment request file to open"), "", "", nullptr);
    if(filename.isEmpty())
        return;
    QUrl fileUri = QUrl::fromLocalFile(filename);
    ui->uriEdit->setText("nc:?r=" + QUrl::toPercentEncoding(fileUri.toString()));
}