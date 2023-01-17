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
#ifndef QtTerminal_H
#define QtTerminal_H

#include <QMainWindow>
#include <QPointer>
#include <QStringList>

class QProcess;

namespace Ui {
class QtTerminal;
}

class QtTerminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtTerminal(QWidget *parent = NULL);
    ~QtTerminal();

private Q_SLOTS:
    void onExecute(const QString &s);
    void onAskCompletion(const QString &cmd, int cursorPos);
    void onEscape();

    void readBashStandardOutputInfo();
    void readBashStandardErrorInfo();

private:
    Ui::QtTerminal * ui;
    QStringList m_ls_history;
    QStringList m_ls_predefine;

    QPointer<QProcess> m_proces;
};

#endif // QtTerminal_H
