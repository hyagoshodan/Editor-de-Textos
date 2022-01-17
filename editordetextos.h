#ifndef EDITORDETEXTOS_H
#define EDITORDETEXTOS_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class EditorDeTextos; }
QT_END_NAMESPACE

class EditorDeTextos : public QMainWindow
{
    Q_OBJECT

public:
    EditorDeTextos(QWidget *parent = nullptr);
    QString localfilename;
    QString all_files = " Arquivos de texto (*.txt) ;; Arquivos Markdown (*.md)";
    ~EditorDeTextos();

private slots:
    void on_actionNovo_triggered();

    void on_actionAbrir_triggered();

    void on_actionSalvar_como_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

private:
    Ui::EditorDeTextos *ui;
};
#endif // EDITORDETEXTOS_H
