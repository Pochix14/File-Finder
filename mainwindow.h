#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void buscarPDF ();

private slots:
    void on_buscar_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
