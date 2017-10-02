#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <qdebug.h>

#define MAXWIDTH 20
QStringList fetchCPUInfo(void);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:///main.qml"));                                               //Loading the QML file

    QList<QObject*> rootItems = engine.rootObjects();

    /*Following code finds the root window from the QML file.
      Then calls the fetchCPUInfo() to get the list of CPU info entries
        and set it as a model for the listview 'cpuInfoList'*/

    for(int i=0;i<rootItems.length();i++)
    {
       if(QString::compare(rootItems[i]->objectName(),"rootWindow") == 0)
        {
            QObject *rootWindow = rootItems[i];
            QStringList listCPUInfo = fetchCPUInfo();
            QQuickItem *listView = rootWindow->findChild<QQuickItem*>("cpuInfoList");
            if(listView)
            {
               listView->setProperty("model",QVariant::fromValue(listCPUInfo));
            }
            else
            {
                qDebug()<<"ListView named cpuInfoList was not found ";
            }
            break;
        }
        else
        {
            qDebug()<<"rootWindow was not found ";
        }
    }
    return app.exec();
}



/**
 * @brief fetchCPUInfo
 * This is a utility function which reads the "/proc/cpuinfo" file line by line, formats it and stores the contents in the return list
 * @return
 * QStringList: list of CPU Info file entries
 */

QStringList fetchCPUInfo(void)
{
    QStringList listCPUInfo;

    QFile procCPUInfo("/proc/cpuinfo");                 //file handle for cpuinfo file

    if(procCPUInfo.open(QIODevice::ReadOnly))
    {
        QTextStream dataStream(&procCPUInfo);

        QString line;
        do
        {
            /*This loop reads each line from cpuinfo file ata a time.
               format it by separating it as property of the CPU vs it's value.
               Once formatted, it stores it in the listCPUInfo*/

            line = dataStream.readLine();                                       //read line

            QStringList lineSplitData = line.split(":");                        //split each line based on ":" into proerty vs value
            QString property,value;

            if(lineSplitData.length() == 2)
            {
                property = lineSplitData[0].trimmed();
                value = lineSplitData[1].trimmed();

            }
            else if(lineSplitData.length() == 1)
            {
                property = lineSplitData[0].trimmed();
                value = "";
            }
            if(!property.isEmpty())
            {
                property.append(QString("").fill(' ',MAXWIDTH-property.length())); //fill the trailing empty spaces for better view
                listCPUInfo << property+"\t"+":"+"\t"+value;                       //Format the display string and insert it in the return list
            }

        }while(!line.isNull());

        procCPUInfo.close();
    }
    else
    {
        qDebug()<<"ERROR IN OPENING FILE" << procCPUInfo.errorString();
    }
    return listCPUInfo;
}
