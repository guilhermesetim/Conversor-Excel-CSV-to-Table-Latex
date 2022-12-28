#ifndef FORMATOTEX_H
#define FORMATOTEX_H

#include <QString>
#include <QVector>

class FormatoTex
{
private:
    QString conteudoFormatado;
    int larguraTabela = 0;
    QString formatoTabular;

public:
    QVector<QChar> tabela;
    FormatoTex(QString, QString, bool);
    void header(QString);
    void setFormatoTabular(bool);
    void body(QString, bool);
    void final();
    void setConteudoFormatado();
    QString getConteudoFormatado();
};

#endif // FORMATOTEX_H
