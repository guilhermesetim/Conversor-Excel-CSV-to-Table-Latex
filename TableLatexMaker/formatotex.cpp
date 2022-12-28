#include "formatotex.h"

#include <QStack>

FormatoTex::FormatoTex(QString nomeArquivo, QString titulo, bool quadriculado)
{

    this->body(nomeArquivo, quadriculado);
    this->setFormatoTabular(quadriculado);
    this->header(titulo);
    this->final();
    this->setConteudoFormatado();
}

void FormatoTex::setFormatoTabular(bool quadriculado) {
    QString _formatoTabular = "";

    // formatação
    for (int c = 0; c <= this->larguraTabela; c++) {
        if(quadriculado)
            _formatoTabular+='|';

        _formatoTabular+= "c";
    }
    if(quadriculado)
        _formatoTabular+='|';

    this->formatoTabular = _formatoTabular;
}

void FormatoTex::header(QString titulo)
{
    QString header = "";
    header += "\\begin{table}[h]\n";
    header += "\\centering\n";
    header += "\\caption{"+ titulo +"}\n";
    header += "\\begin{tabular}{"+this->formatoTabular+"}\n";
    header+= "\\hline\n";

    QStack<QChar> inverte;

    for(QChar letraHeader : header) {
        inverte.push(letraHeader);
    }
    while (!inverte.isEmpty()) {
        tabela.push_front(inverte.top());
        inverte.pop();
    }
}


void FormatoTex::body(QString nomeArquivo, bool quadriculado)
{
    bool conteudoCelula = false;
    bool linhaHorizontal = true;
    int larguraTabela = 0;

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
        if(larguraTabela > this->larguraTabela){
            this->larguraTabela = larguraTabela;
        }
      }
      else
        tabela.push_back(cadaLetra);
    }

}


void FormatoTex::final()
{
    QString final = "";
    final += "\\\\ \n\\hline\n";
    final += "\\end{tabular}\n";
    final += "\\end{table}\n";

    for(QChar letraFinal : final) {
        tabela.push_back(letraFinal);
    }

}

void FormatoTex::setConteudoFormatado() {
   QString formatoString = "";
   for(QChar caracter : tabela) {
     formatoString+= caracter;
   }

   this->conteudoFormatado = formatoString;
}

QString FormatoTex::getConteudoFormatado() {
    return this->conteudoFormatado;
}
