#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagefileiterator.h"
#include "imagefilemanipulator.h"

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_gallery_triggered();

    void on_actionChoose_folder_triggered();

    void on_actionNext_image_triggered();

    void on_actionPrevious_image_triggered();

    void on_actionBrightness_triggered();

    void brightnessChanged(int value);

private:
    // Search image files in folder.
    void searchFiles(const QString& folder);

    // Read current image file.
    void readImage();

    // Redraw image.
    void redrawImage();

private:
    Ui::MainWindow *ui;

    ImageFileIterator files_{""};     ///< iterates over image files in folder
    ImageFileManipulator image_{""};  ///< image content manipulator
};
#endif // MAINWINDOW_H
