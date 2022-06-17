#include <QApplication>
#include "view.h"

#include <QFile>
#include <QTextStream>
void messageHander(QtMsgType type,
                   const QMessageLogContext& context,
                   const QString& message) {
    QString levelText;
    switch (type) {
    case QtDebugMsg:
        levelText = "Debug";
        break;
    case QtInfoMsg:
        levelText = "Info";
        break;
    case QtWarningMsg:
        levelText = "Warning";
        break;
    case QtCriticalMsg:
        levelText = "Critical";
        break;
    case QtFatalMsg:
        levelText = "Fatal";
        break;
    }
    QString text = QString("[%1] %2")
            .arg(levelText)
            .arg(message);
    QFile file("app.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << text << "\r\n";
}

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    qInstallMessageHandler(messageHander);

    View v;
    v.show();

    a.exec();
}
