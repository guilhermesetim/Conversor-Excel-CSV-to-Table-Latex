#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_arqCSV_clicked();

    void on_arqxlsx_clicked();

private:
    Ui::MainWindow *ui;

    void msgSucesso();
    bool quadriculado();
    QString titulo();
    QString leituraExcel(QString);
};
#endif // MAINWINDOW_H
