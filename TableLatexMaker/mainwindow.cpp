#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "xlsxdocument.h"
#include "arquivotex.h"
#include "formatotex.h"

#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include <QStack>


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

void MainWindow::on_arqCSV_clicked()
{
    QString filtro = "Todos os arquivos (*.*) ;; Arquivos CSV (*.csv)";
    QString abrirArquivo = QFileDialog::getOpenFileName(this, "Selecionar Arquivos", QDir::homePath(), filtro);
    QFile arquivo(abrirArquivo);
    if(!arquivo.open(QFile::ReadOnly|QFile::Text)) {
        QMessageBox::warning(this, "ERRO","Erro ao abrir o arquivo !");
    }
    QTextStream entrada(&arquivo);
    QString texto=entrada.readAll();

    QString titulo = ui->titulo->text();
    ui->titulo->clear();

    bool quadriculado;
    if(ui->radio_tab->isChecked()) {
        quadriculado = false;
    }
    else {
        quadriculado = true;
    }

    //QString conteudoLatex = this->arquivoCSV(texto, titulo, quadriculado);
    FormatoTex formatoTex(texto, titulo,quadriculado);
    QString conteudoLatex = formatoTex.getConteudoFormatado();

    ui->arqSelect->setPlainText(abrirArquivo);
    ui->tabConvert->setPlainText(conteudoLatex);

    arquivo.close();


    ArquivoTex arquivoLatex(abrirArquivo);
    arquivoLatex.gravar(conteudoLatex);


    QMessageBox msgBox;
    msgBox.setText("A tabela foi convertida para latex com sucesso.");
    msgBox.exec();


}


void MainWindow::on_arqxlsx_clicked()
{
    QString filtro = "Todos os arquivos (*.*) ;; Arquivos CSV (*.csx)";
    QString abrirArquivo = QFileDialog::getOpenFileName(this, "Selecionar Arquivos", QDir::homePath(), filtro);

    QString titulo = ui->titulo->text();
    ui->titulo->clear();

    bool quadriculado;
    if(ui->radio_tab->isChecked()) {
        quadriculado = false;
    }
    else {
        quadriculado = true;
    }

    QString dadosPlanilha;
    QXlsx::Document planilha(abrirArquivo);
    QString colunas[] = {"A","B","C","D","E","F"};


    QString celulaTopo;
    int qtdColunas = 0;
    do {
        celulaTopo = planilha.read(colunas[qtdColunas]+"1").toString();
        qtdColunas++;
    } while(celulaTopo != "");
    qtdColunas--;


    int l = 1;
    while (true) {

        for(int c = 0; c < qtdColunas; c++) {
            dadosPlanilha+=planilha.read(colunas[c]+QString::number(l)).toString();
            if(c < qtdColunas-1){
                dadosPlanilha+=",";
            }
        }
        ++l;
        if(planilha.read("A"+QString::number(l)).toString() == ""){
            break;
        }
        dadosPlanilha+="\n";
     }


    FormatoTex formatoTex(dadosPlanilha, titulo,quadriculado);
    QString conteudoLatex = formatoTex.getConteudoFormatado();

    ui->arqSelect->setPlainText(abrirArquivo);
    ui->tabConvert->setPlainText(conteudoLatex);




    ArquivoTex arquivoLatex(abrirArquivo);
    arquivoLatex.gravar(conteudoLatex);


    QMessageBox msgBox;
    msgBox.setText("A tabela foi convertida para latex com sucesso.");
    msgBox.exec();


}

