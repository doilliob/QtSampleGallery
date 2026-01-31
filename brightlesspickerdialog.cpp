#include "brightlesspickerdialog.h"
#include "ui_brightlesspickerdialog.h"

BrightlessPickerDialog::BrightlessPickerDialog(QWidget *parent, int brightless)
    : QDialog(parent)
    , ui(new Ui::BrightlessPickerDialog)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(brightless);
}

BrightlessPickerDialog::~BrightlessPickerDialog()
{
    delete ui;
}

void BrightlessPickerDialog::on_horizontalSlider_valueChanged(int value)
{
    emit BrightlessPickerDialog::brightlessValueChanged(value);
}


void BrightlessPickerDialog::on_pushButton_clicked()
{
    ui->horizontalSlider->setValue(0);
}

