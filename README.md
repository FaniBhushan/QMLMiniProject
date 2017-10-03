# QMLMiniProject

Purpose:

The task for this challenge is to read the Linux CPU information from /proc/cpuinfo and display it using QML.
The solution must run on a standard Linux system, preferably Ubuntu, and should be written using Qt C++ to read the system information 
and Qt Quick (not QWidget) to display the data.Qt version should be at least Qt 5.4.

Solution Approach:

I have created an application using integrated approach with interaction between C++ code and QML code.
I have used a list View to display the "roc/cpuinfo" file's content by adding custom formatting to each line of the file and displayig as a part of the list view.
ListView is defined in Main.qml file.
The model used here is QStringList. It is supplied by the C++ code by
- reading the file
- formatting the content
- populating the string list
- set this list as a model for the listview using 'istView->setProperty()'

