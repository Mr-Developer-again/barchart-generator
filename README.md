# barchart-generator
- this program takes a csv file and then create a barchart and table from columns of the csv file (columns' values)

- this project has been written by 5.15 version of Qt

- the inner project (inside project.tar.gz compressed file) has been implemented on git

- probable error:
    if you encounter with "qcustomplot.h" file not found, to fix this error, you must
    go to "ui_mainwindow.h" file (or double click on the error if you are on qtcreator) and
    do this:
    
        #include <qcustomplot.h> -> #include <../include/qcustomplot.h>

        
- some examples of running of the program:

![image](https://user-images.githubusercontent.com/112639283/214506736-0e53ef2b-4574-4f9c-b46b-363a7168571b.png)

![image](https://user-images.githubusercontent.com/112639283/214507129-f7b7a06f-9842-42c9-83f7-0850213a70c6.png)
