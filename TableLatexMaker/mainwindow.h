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
    void on_importarArq_clicked();

private:
    Ui::MainWindow *ui;
    void conversor(QString argv);
    QString headerTable(QString nomeArquivo);
    QString arquivoCSV(QString nomeArquivo, QString titulo, QString caminho, bool quadriculado);
};
#endif // MAINWINDOW_H
