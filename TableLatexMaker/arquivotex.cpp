#include "arquivotex.h"
#include <QFile>
#include <QTextStream>


ArquivoTex::ArquivoTex(QString caminho)
{
    this->caminhoArquivo = caminho;
}



QString ArquivoTex::nomeArquivoTex(){
    QString nomeTex = "";
    nomeTex += this->caminhoArquivo;
    nomeTex += ".tex";

    return nomeTex;
}

void ArquivoTex::gravar(QString conteudoEnviar){

    QFile arquivoLatex(this->nomeArquivoTex());
    arquivoLatex.open(QFile::WriteOnly|QFile::Text);
    QTextStream saida(&arquivoLatex);
    saida << conteudoEnviar;

    arquivoLatex.flush();
    arquivoLatex.close();
}

