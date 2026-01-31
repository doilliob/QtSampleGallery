#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "brightlesspickerdialog.h"

#include <QFileDialog>
#include <QMessageBox>

#include <exception>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_gallery_triggered()
{
    QApplication::quit();
}

void MainWindow::searchFiles(const QString& folder) {
    try
    {
        files_ = ImageFileIterator{folder};
    }
    catch (const std::runtime_error& err)
    {
        std::ostringstream ss;
        ss << "Failed to read files in the folder: " << folder.toStdString() << std::endl
           << "Details: " << err.what();

        QMessageBox::critical(this, "Error", QString::fromStdString(ss.str()));
        files_ = ImageFileIterator{""};
    }
}

void MainWindow::readImage() {
    try
    {
        image_ = ImageFileManipulator{ files_.GetFilePath() };
    }
    catch (const std::runtime_error& err)
    {
        std::ostringstream ss;
        ss << "Failed to read image file: " << files_.GetFilePath() << std::endl
           << "Details: " << err.what();

        QMessageBox::critical(this, "Error", QString::fromStdString(ss.str()));
        image_ = ImageFileManipulator{""};
    }
}

void MainWindow::on_actionChoose_folder_triggered()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Choose folder", QDir::currentPath());
    if (!directoryPath.isEmpty()) {
        searchFiles(directoryPath);
        readImage();
        redrawImage();
    }
}

void MainWindow::redrawImage() {
    const auto& pixmap = image_.GetImage();
    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents(true);

    const auto status = files_.Empty() ? "No image files" : files_.GetFilePath();
    ui->statusbar->showMessage(QString::fromStdString(status));
}

void MainWindow::on_actionNext_image_triggered()
{
    if (files_.Next()) {
        readImage();
        redrawImage();
    }
}

void MainWindow::on_actionPrevious_image_triggered()
{
    if (files_.Previous()) {
        readImage();
        redrawImage();
    }
}


void MainWindow::on_actionBrightness_triggered()
{
    if (image_.Empty()) {
        // no current image
        return;
    }

    BrightlessPickerDialog *dlg = new BrightlessPickerDialog(this, image_.GetBrightness());
    dlg->setModal(true);
    dlg->show();

    connect(dlg, SIGNAL(brightlessValueChanged(int)), this, SLOT(brightnessChanged(int)));
}

void MainWindow::brightnessChanged(int value) {
    image_.SetBrightness(value);
    redrawImage();
}

