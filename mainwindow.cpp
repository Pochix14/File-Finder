#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QStringList>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Etiqueta inicial
    ui->etiqueta->setText("A continuación se le muestra los resultados de la búsqueda.\n\n** Pueden haber resultados que sean correctos, pero aparecen por algún caracter diferente en el nombre del archivo IL.\n\n Puede realizar la búsqueda nuevamente si desea..");

    //Etiqueta logo
    QPixmap logo("\\\\tucan\\varios\\1\\Autoinstalador\\Iconos\\fondo.png");
    logo = logo.scaled(ui->etiquetaLogo->size(), Qt::IgnoreAspectRatio);
    ui->etiquetaLogo->setPixmap(logo);


    QMessageBox * m;
    m->information(this, "Buscando..", "Espere mientras se realiza la busqueda..");

    this->buscarPDF();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::buscarPDF()
{
    QStringList carpetasNoTienen; //Lista que contiene la lista de carpetas que no tienen el .pdf "IL"
    QString path = "\\\\172.31.254.21\\share\\Consultorias SINAC\\MIDEPLAN_JAPDEVA\\Producto2\\";
    QDir directorio (path);
    directorio.setFilter(QDir::AllDirs);
    QStringList listaMadre = directorio.entryList(); //Crear lista con las carpetas principales
    for (int i = 2; i < listaMadre.length(); ++i)
    {
        QDir carpeta (path + listaMadre[i]);
        carpeta.setFilter(QDir::AllDirs);
        QStringList listaDos = carpeta.entryList(); //Crea lista con las carpetas que contiene cada carpeta principal
        for (int j = 2; j < listaDos.length(); ++j)
        {
            QDir ultima (path + listaMadre[i] + '/' + listaDos[j]);
            //Crea filtro solo para archivos pdf
            QStringList filtro;
            filtro << "*.pdf";
            ultima.setNameFilters(filtro);
            QStringList listaD = ultima.entryList(); //Crea lista con todos los archivos que tenga la carpeta secundaria

            int contadorSi = 0; //Contador si encuentra el archivo IL
            for (int k = 0; k < listaD.length(); ++k)
            {                
                QString name = listaDos[j] + "IL"; //Variable que contiene el nombre de la carpeta y la terminacion IL
                if (listaD[k].contains(name))
                {
                    contadorSi ++;
                }
            }
            if (contadorSi == 0) //Si el contador permanecio en 0, agrega el nombre de la carpeta a la lista!
            {
                ui->listaPDF->appendPlainText(listaMadre[i] + " -- " + listaDos[j]);
            }

        }
    }
}

void MainWindow::on_buscar_clicked()
{
    ui->listaPDF->clear();
    QMessageBox * m;
    m->information(this, "Buscando..", "Espere mientras se realiza la busqueda..");
    this->buscarPDF();
}
