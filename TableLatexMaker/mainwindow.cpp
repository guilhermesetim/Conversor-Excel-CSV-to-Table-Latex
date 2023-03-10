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
    /*      Abertura do arquivo     */
    QString filtro = "Todos os arquivos (*.*) ;; Arquivos CSV (*.csv)";
    QString abrirArquivo = QFileDialog::getOpenFileName(this, "Selecionar Arquivos", QDir::homePath(), filtro);
    QFile arquivo(abrirArquivo);
    if(!arquivo.open(QFile::ReadOnly|QFile::Text)) {
        QMessageBox::warning(this, "ERRO","Erro ao abrir o arquivo !");
    }
    QTextStream entrada(&arquivo);
    QString texto=entrada.readAll();
     arquivo.close();


    /*      Informações de inputs da interface     */
    QString titulo = this->titulo();
    bool quadriculado = this->quadriculado();


    /*      Formatar o conteudo para formato LaTex     */
    FormatoTex formatoTex(texto, titulo,quadriculado);
    QString conteudoLatex = formatoTex.getConteudoFormatado();

     /*      Imprimir informações na interface     */
    ui->arqSelect->setPlainText(abrirArquivo);
    ui->tabConvert->setPlainText(conteudoLatex);

     /*      Criar e gravar em um arquivo     */
    ArquivoTex arquivoLatex(abrirArquivo);
    arquivoLatex.gravar(conteudoLatex);

    // messagem de sucesso
    msgSucesso();


}


void MainWindow::on_arqxlsx_clicked()
{
    /*      Abertura do arquivo     */
    QString filtro = "Todos os arquivos (*.*) ;; Arquivos xlsx (*.xlsx)";
    QString abrirArquivo = QFileDialog::getOpenFileName(this, "Selecionar Arquivos", QDir::homePath(), filtro);


    /*      Informações de inputs da interface     */
    QString titulo = this->titulo();
    bool quadriculado = this->quadriculado();
    QString dadosPlanilha = this->leituraExcel(abrirArquivo);


    /*      Formatar o conteudo para formato LaTex     */
    FormatoTex formatoTex(dadosPlanilha, titulo,quadriculado);
    QString conteudoLatex = formatoTex.getConteudoFormatado();

    /*      Imprimir informações na interface     */
    ui->arqSelect->setPlainText(abrirArquivo);
    ui->tabConvert->setPlainText(conteudoLatex);

    /*      Criar e gravar em um arquivo     */
    ArquivoTex arquivoLatex(abrirArquivo);
    arquivoLatex.gravar(conteudoLatex);

    // messagem de sucesso
    msgSucesso();
}


QString MainWindow::leituraExcel(QString abrirArquivo) {

    QString dadosPlanilha;
    QXlsx::Document planilha(abrirArquivo);
    QString colunas[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M",
                        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};


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

    return dadosPlanilha;
}


void MainWindow::msgSucesso() {
    QMessageBox msgBox;
    msgBox.setText("A tabela foi convertida para latex com sucesso.");
    msgBox.exec();
}

bool MainWindow::quadriculado() {
    bool quadriculado;
    if(ui->radio_tab->isChecked()) {
        quadriculado = false;
    }
    else {
        quadriculado = true;
    }

    return quadriculado;
}

QString MainWindow::titulo() {
    QString titulo = ui->titulo->text();
    ui->titulo->clear();
    return titulo;
}
