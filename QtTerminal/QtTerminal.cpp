/* QCommandEdit - a widget for entering commands, with completion and history
 * Copyright (C) 2018 Federico Ferri
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "QtTerminal.h"
#include "ui_QtTerminal.h"
#include "qcommandtokenizer.h"

#include <QProcess>
#include <QDebug>


QtTerminal::QtTerminal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtTerminal)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("NARI终端"));

    m_ls_history << "break if x == 1"
             << "lambda x: try import foo else return"
             << "local y"
             << "raise Exception(...)"
             << "return 0"
             << "while x > 0: print(x); x += 1"
             << "for i in range(100): print(i)";
    ui->commandEdit->setHistory(m_ls_history);
    ui->commandEdit->setShowMatchingHistory(true);
    for(int i = 0; i < m_ls_history.size(); i++)
        ui->textCmdLog->append(m_ls_history[i]);

    m_ls_predefine << "查看文件夹下所有文件: ls -a" << "查看磁盘使用情况: df -h" << "查看内存占用信息: free -m" << "打印当前目录: pwd"
           << "打开ns2000系统: cd ~/ ; ./START" << "关闭ns2000系统: cd ~/ ; ./STOP" << "弹出插入U盘: umount /mnt/";
    ui->listWords->addItems(m_ls_predefine);
    ui->commandEdit->setFocus();

    // QProcess to call linux instruction
    m_proces = new QProcess();
    m_proces->start("bash");
    m_proces->waitForStarted();

    // signals and slots
    connect(m_proces, SIGNAL(readyReadStandardOutput()), this, SLOT(readBashStandardOutputInfo()));
    connect(m_proces, SIGNAL(readyReadStandardError()), this, SLOT(readBashStandardErrorInfo()));
    connect(ui->commandEdit, SIGNAL(execute(const QString &)), this, SLOT(onExecute(const QString &)));
    connect(ui->commandEdit, SIGNAL(askCompletion(const QString &, int)), this, SLOT(onAskCompletion(const QString &, int)));
    connect(ui->commandEdit, SIGNAL(escape()), this, SLOT(onEscape()));
}

QtTerminal::~QtTerminal()
{
    delete ui;
}

void QtTerminal::onExecute(const QString &s)
{
    m_ls_history.append(s);
    ui->textCmdLog->append(s);
    ui->commandEdit->clear();
    ui->commandEdit->setHistory(m_ls_history);

    // for terminal
    ui->txb_output->append("Linux:~$ "+s);
    if(s.contains(":"))
    {
        int _index = s.indexOf(":");
        QString _s = s.mid(_index + 1);
        m_proces->write(_s.toLocal8Bit() + '\n');
        return;
    }
    m_proces->write(s.toLocal8Bit() + '\n');
}

void QtTerminal::onAskCompletion(const QString &cmd, int cursorPos)
{
    QSimpleCommandTokenizer t;
    t.setCommand(cmd);
    try
    {
        QCommandTokenizer::Token tok = t.getTokenAtCharPos(cursorPos);

        if(cursorPos != tok.end_)
            throw "Not completing at middle of token";

        QStringList comp;
        for(int i = 0; i < m_ls_predefine.size(); i++)
            if(m_ls_predefine[i].startsWith(tok.token_))
                comp << m_ls_predefine[i].mid(tok.token_.length());

        ui->commandEdit->setCompletion(comp);
        // qDebug() << "Completion:" << comp;
    }
    catch(const char *ex)
    {
        qDebug() << ex;
        return;
    }
}

void QtTerminal::onEscape()
{
    qDebug() << "Escape!";
}

void QtTerminal::readBashStandardOutputInfo()
{
    QByteArray cmdout = m_proces->readAllStandardOutput();
    if(!cmdout.isEmpty()){
        ui->txb_output->append(QString::fromLocal8Bit(cmdout));
    }
}

void QtTerminal::readBashStandardErrorInfo()
{
    QByteArray cmdout = m_proces->readAllStandardError();
    if(!cmdout.isEmpty()){
        ui->txb_output->append(QString::fromLocal8Bit(cmdout));
    }
}
