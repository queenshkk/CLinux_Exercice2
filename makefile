.SILENT:


CLINUX_Exercice2 : main.o mywindow.o moc_mywindow.o FichierUtilisateur.o
	echo Création compilation de CLINUX_Exercice2
	g++  -o CLINUX_Exercice2 main.o mywindow.o moc_mywindow.o FichierUtilisateur.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

main.o : main.cpp
	echo Création de compilation main.o
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

mywindow.o : mywindow.cpp 
	echo Création de compilation mywindow.o
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o mywindow.o mywindow.cpp 

moc_mywindow.o : moc_mywindow.cpp
	echo Création de compilation moc_mywindow.o
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_mywindow.o moc_mywindow.cpp

FichierUtilisateur.o : FichierUtilisateur.cpp
	echo Création de compilation Fichier Utilisateur
	g++ FichierUtilisateur.cpp -c

clean :
	rm -f *.o

clobber : clean
	rm -f CLINUX_Exercice2