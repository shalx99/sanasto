#include "mainwindow.h"
#include <QDebug>

MainWindow* MainWindow::instance;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}

MainWindow* MainWindow::getInstance()
{
    if(!instance)
    {
        instance = new MainWindow();
        instance->init();
    }
    return instance;
}

void MainWindow::init()
{
    setWindowTitle("Sanasto fin->rus");
    setMinimumSize(600, 400);
    createStatusBar();

    m_word_translation = new QPlainTextEdit;

    m_layout = new QVBoxLayout;
    m_central_widget = new QWidget;
    m_central_layout = new QHBoxLayout;

    m_dictionary = new Dictionary;

    m_filter = new Dictionary_Filter();
    m_filter->setSourceModel(m_dictionary);
    connect(m_filter, SIGNAL(setUserInput(QString)), this, SLOT(updateInputWord(QString)));

    m_dict_view = new QListView;
    m_dict_view->setModel(m_filter);
    m_dict_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_dict_view, SIGNAL(clicked(QModelIndex)), m_filter, SLOT(onDictViewClick(QModelIndex)) );

    m_user_input = new QLineEdit;
    connect(m_user_input, SIGNAL(returnPressed()), this, SLOT(updateTranslation()));
    connect(m_user_input, SIGNAL(textChanged(const QString&)), m_filter, SLOT(updateFilter(const QString&)));

    m_invitation = new QLabel(QString("Look for:"));

    m_layout->addWidget(m_invitation);
    m_layout->addWidget(m_user_input);
    m_layout->addWidget(m_dict_view);

    m_central_layout->addLayout(m_layout);
    m_central_layout->setStretchFactor(m_layout, 1);
    m_central_layout->addWidget(m_word_translation);
    m_central_layout->setStretchFactor(m_word_translation, 2);

    m_central_widget->setLayout(m_central_layout);

    setCentralWidget(m_central_widget);
}

void MainWindow::updateTranslation(QString word)
{
    if (word.size() == 0)
    {
        word = m_user_input->text();
    }
    QString translation = m_dictionary->getTranslation(word);

    // try to improve text
    translation.replace(QString("<p>"), QString("\n"));

    m_word_translation->setPlainText(translation);
}

void MainWindow::updateInputWord(QString word)
{
    updateTranslation(word);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::updateStatusBar(QString status)
{
    statusBar()->showMessage(status);
}
