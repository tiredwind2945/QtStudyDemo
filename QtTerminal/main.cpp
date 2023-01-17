#include "QtTerminal.h"
#include <QApplication>
#include <QDebug>

#include "qcommandtokenizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if defined(TEST_SIMPLE_TOKENIZER)
    QString cmd = "  foo bar  baz";
    QSimpleCommandTokenizer t;
    t.setCommand(cmd);
    qDebug() << "command: " << cmd;
    for(const QCommandTokenizer::Token &tok : t.getTokens())
        qDebug() << tok.token_ << tok.start_ << tok.end_;
    qDebug() << "token at 9: " << t.getTokenAtCharPos(9).token_;
    return 0;
#else
    QtTerminal w;
    w.show();

    return a.exec();
#endif
}
