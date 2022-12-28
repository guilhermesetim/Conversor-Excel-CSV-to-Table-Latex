#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "xlsxdocument.h"

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


void MainWindow::on_importarArq_clicked()
{
    QString filtro = "Todos os arquivos (*.*) ;; Arquivos CSV (*.csx)";
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

    QString conteudoLatex = this->arquivoCSV(texto, titulo, abrirArquivo, quadriculado);

    ui->arqSelect->setPlainText(abrirArquivo);
    //ui->tabConvert->setPlainText(conteudoLatex);

    arquivo.close();


    QMessageBox msgBox;
    msgBox.setText("A tabela foi convertida para latex com sucesso.");
    msgBox.exec();

    /* Criaçao de uma planilha
    QXlsx::Document planilha;
    planilha.write("A1", "Teste");
    planilha.saveAs(QDir::currentPath()+"/teste_excel.xlsx");
    */
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
        if(planilha.read("A"+QString::number(l)).toString() == ""){
            break;
        }
        for(int c = 0; c < qtdColunas; c++) {
            dadosPlanilha+=planilha.read(colunas[c]+QString::number(l)).toString();
            if(c < qtdColunas-1){
                dadosPlanilha+=",";
            }
        }
        ++l;
        dadosPlanilha+="\n";
     }



    ui->tabConvert->setPlainText(dadosPlanilha);

}


QString MainWindow::arquivoCSV(QString nomeArquivo, QString titulo, QString caminho, bool quadriculado) {

    QString header = "";
    QString final = "";
    QString formatoTabular = "";


    QVector<QChar> tabela;





    bool conteudoCelula = false;
    bool linhaHorizontal = true;
    int larguraTabela = 0;
    int maiorLargura = 0;

    for(QChar cadaLetra : nomeArquivo) {
      if (cadaLetra == '"')
        conteudoCelula = !conteudoCelula;

      if(cadaLetra == "\n"){

          tabela.push_back(' ');
          tabela.push_back('\\');
          tabela.push_back('\\');

          larguraTabela = 0;

          if(linhaHorizontal) {
              tabela.push_back(' ');
              tabela.push_back('\\');
              tabela.push_back('h');
              tabela.push_back('l');
              tabela.push_back('i');
              tabela.push_back('n');
              tabela.push_back('e');
              linhaHorizontal = quadriculado;
          }
      }

      if(cadaLetra == ',' && !conteudoCelula) {
        tabela.push_back(' ');
        tabela.push_back('&');
        tabela.push_back(' ');

        larguraTabela++;
        if(larguraTabela > maiorLargura){
            maiorLargura = larguraTabela;
        }
      }
      else
        tabela.push_back(cadaLetra);
    }


    for (int c = 0; c <= maiorLargura; c++) {
        if(quadriculado)
            formatoTabular+='|';

        formatoTabular+= "c";
    }
    if(quadriculado)
        formatoTabular+='|';




    header += "\\begin{table}[h]\n";
    header += "\\centering\n";
    header += "\\caption{"+ titulo +"}\n";
    header += "\\begin{tabular}{"+formatoTabular+"}\n";
    header+= "\\hline\n";

    QStack<QChar> inverte;

    for(QChar letraHeader : header) {
        inverte.push(letraHeader);
    }
    while (!inverte.isEmpty()) {
        tabela.push_front(inverte.top());
        inverte.pop();
    }


    final += "\\\\ \n\\hline\n";
    final += "\\end{tabular}\n";
    final += "\\end{table}\n";

    for(QChar letraFinal : final) {
        tabela.push_back(letraFinal);
    }



   QString enviar = "";
   for(QChar caracter : tabela) {
     enviar+= caracter;
   }



   QString nomeTex = "";
   nomeTex += caminho;
   nomeTex += ".tex";

   QFile arquivoLatex(nomeTex);
   arquivoLatex.open(QFile::WriteOnly|QFile::Text);
   QTextStream saida(&arquivoLatex);
   saida << enviar;
   arquivoLatex.flush();
   arquivoLatex.close();

   return enviar;
}
