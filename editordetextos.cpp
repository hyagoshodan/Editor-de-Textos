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

void EditorDeTextos::on_actionCopia_triggered()
{
    ui->textEdit->copy();
}

void EditorDeTextos::on_actionColar_triggered()
{
    ui->textEdit->paste();
}

void EditorDeTextos::on_actionRecortar_triggered()
{
    ui->textEdit->cut();
}

void EditorDeTextos::on_actionRefazer_triggered()
{
    ui->textEdit->redo();

}

void EditorDeTextos::on_actionDesfazer_triggered()
{
    ui->textEdit->undo();

}

void EditorDeTextos::on_actionCor_triggered()
{
   QColor color = QColorDialog::getColor( Qt::black, this, "Escolha uma cor");
   if( color.isValid() )
   {
       ui->textEdit->setTextColor( color );
   }
}

void EditorDeTextos::on_actionBackground_triggered()
{
    QColor color = QColorDialog::getColor( Qt::black, this, "Escolha uma cor");
    if( color.isValid() )
    {
        ui->textEdit->setTextBackgroundColor( color );
    }
}

void EditorDeTextos::on_actionFonte_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont( &ok, this);
    if( ok )
    {
        ui->textEdit->setFont(font);
    }else{
        return;
    }
}

void EditorDeTextos::on_actionSobre_triggered()
{
    QMessageBox::about(this, "Sobre esse programa", "Desenvolvido no Curso de Qt Moderno com C++. <br>"
                       "<a href='https://terminalroot.com.br/'>Acesse https://terminalroot.com.br/</a><br>");
}

void EditorDeTextos::on_actionImprimir_triggered()
{
    QPrinter printer;
    QPrintDialog dialog_printer;

    if( dialog_printer.exec() == QDialog::Rejected )
    {
        return;
    }

    ui->textEdit->print( &printer );
}
