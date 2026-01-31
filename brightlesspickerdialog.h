#ifndef BRIGHTLESSPICKERDIALOG_H
#define BRIGHTLESSPICKERDIALOG_H

#include <QDialog>

namespace Ui {
class BrightlessPickerDialog;
}

class BrightlessPickerDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Class ctor.
    /// @param brightness initial brightness value.
    explicit BrightlessPickerDialog(QWidget *parent = nullptr, int brightless=0);
    ~BrightlessPickerDialog();

signals:
    /// @brief Signal on brightness change.
    void brightlessValueChanged(int value);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::BrightlessPickerDialog *ui;
};

#endif // BRIGHTLESSPICKERDIALOG_H
