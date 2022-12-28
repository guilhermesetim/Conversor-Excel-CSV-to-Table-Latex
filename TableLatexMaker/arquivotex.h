#ifndef ARQUIVOTEX_H
#define ARQUIVOTEX_H

#include <QString>

class ArquivoTex
{  
private:
    QString caminhoArquivo;

    QString nomeArquivoTex();
public:
    ArquivoTex(QString);
    void gravar(QString);
};

#endif // ARQUIVOTEX_H
