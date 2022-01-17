#include "editordetextos.h"
#include "ui_editordetextos.h"

EditorDeTextos::EditorDeTextos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorDeTextos)
{
    ui->setupUi(this);
    this->setCentralWidget( ui->textEdit );
}

EditorDeTextos::~EditorDeTextos()
{
    delete ui;
}


void EditorDeTextos::on_actionNovo_triggered()
{
    localfilename = "";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

void EditorDeTextos::on_actionAbrir_triggered()
{
    QString filename = QFileDialog::getOpenFileName( this, "Abrir", QDir::homePath(), all_files);
    QFile file( filename );
    localfilename = filename;

    if( file.exists() )
    {
        if( !file.open( QFile::ReadOnly | QFile::Text ) )
        {
            QMessageBox::warning( this, "Erro ao abrir arquivo", "Arquivo não pode ser aberto" );
            return;
        }

        QTextStream enter_file( &file );
        QString text = enter_file.readAll();
        ui->textEdit->setText(text);
    }

    file.close();
}

void EditorDeTextos::on_actionSalvar_como_triggered()
{
    QString filename = QFileDialog::getSaveFileName( this, "Abrir", QDir::homePath(), all_files);
    localfilename = filename;

    if( localfilename == "" )
    {
        return;
    }

    QFile file( filename );

    if( !file.open( QFile::WriteOnly | QFile::Text )  )
    {
        if( file.exists() )
        {
            QMessageBox::warning( this, "Erro ao salvar arquivo", "Arquivo não pode ser salvo" );

        }
        return;
    }

    QTextStream out_file( &file );
    QString text = ui->textEdit->toPlainText();
    out_file << text;

    file.flush();
    file.close();
}

void EditorDeTextos::on_actionSalvar_triggered()
{

    QFile file( localfilename );

    if( file.exists() )
    {
        if( !file.open( QFile::WriteOnly | QFile::Text) )
        {
           QMessageBox::warning( this, "Erro ao salvar arquivo", "Arquivo não pode ser salvo");
           return;
        }
    }else {
        on_actionSalvar_como_triggered();
    }

    QTextStream out_file( &file );
    QString text = ui->textEdit->toPlainText();
    out_file << text;

    file.flush();
    file.close();
}

void EditorDeTextos::on_actionSair_triggered()
{
    close();
}
