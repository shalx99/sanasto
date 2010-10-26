#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QListView>
#include <QLineEdit>
#include <QLabel>
#include <QStandardItemModel>

#include "dictionary.h"
#include "dictionary_filter.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();

    static MainWindow* getInstance();

    void createStatusBar();
    void updateStatusBar(QString status);

protected:
    explicit MainWindow(QWidget *parent = 0);
    void init();

private slots:
    void updateTranslation(QString word = QString(""));
    void updateInputWord(QString word);

private:
    static MainWindow* instance;

    QVBoxLayout* m_layout;
    QHBoxLayout* m_central_layout;
    QPlainTextEdit* m_word_translation;
    QWidget* m_central_widget;
    QListView* m_dict_view;
    QLineEdit* m_user_input;
    QLabel* m_invitation;

    Dictionary* m_dictionary;
    Dictionary_Filter* m_filter;

};

#endif // MAINWINDOW_H
