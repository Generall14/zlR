#include "maingui.hpp"
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <stdexcept>
#include <QDebug>
#include <src/Data.hpp>

MainGUI::MainGUI(QSharedPointer<Data> dat, QWidget *parent):
    QMainWindow(parent),
    _dat(dat)
{
    InitGUI();
    InitMenu();
}

MainGUI::~MainGUI()
{
    qDebug() << "MainGUI::~MainGUI()";
}

void MainGUI::InitGUI()
{
    this->window()->resize(640, 480);

    this->setCentralWidget(new QWidget());
    this->centralWidget()->setLayout(new QVBoxLayout());

    //========================= Regiony =======================================
    QGroupBox* regGB = new QGroupBox("Regiony");
    this->centralWidget()->layout()->addWidget(regGB);
    regGB->setLayout(new QVBoxLayout());

    regTBV = new QTableView();
    regTBV->setModel(_dat.data()->GetRegions().data());
    regGB->layout()->addWidget(regTBV);

    QHBoxLayout* regBL = new QHBoxLayout();
    static_cast<QBoxLayout*>(regGB->layout())->addLayout(regBL);

    regBL->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QPushButton* btn = new QPushButton("Dodaj");
    regBL->addWidget(btn);
    btn = new QPushButton("Usuń");
    regBL->addWidget(btn);

    //========================= Sekcje ========================================
    QGroupBox* secGB = new QGroupBox("Sekcje");
    this->centralWidget()->layout()->addWidget(secGB);
    secGB->setLayout(new QVBoxLayout());

    secTBV = new QTableView();
    secGB->layout()->addWidget(secTBV);

    QHBoxLayout* secBL = new QHBoxLayout();
    static_cast<QBoxLayout*>(secGB->layout())->addLayout(secBL);

    secBL->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    btn = new QPushButton("Dodaj");
    secBL->addWidget(btn);
    btn = new QPushButton("Usuń");
    secBL->addWidget(btn);
}

void MainGUI::InitMenu()
{
    QMenu* mPlik = new QMenu("&Plik");
    QAction* aCl = new QAction("&Zamknij", mPlik);
    aCl->setShortcut(QKeySequence::Close);
    connect(aCl, &QAction::triggered, this, &MainGUI::close);
    mPlik->addAction(aCl);
    this->menuBar()->addMenu(mPlik);



    QMenu* mDane = new QMenu("&Dane");

    QAction* aOp = new QAction("&Otwórz", mDane);
    aOp->setShortcut(QKeySequence::Open);
    mDane->addAction(aOp);

    QAction* aSv = new QAction("&Zapisz", mDane);
    aSv->setShortcut(QKeySequence::Save);
    mDane->addAction(aSv);

    QAction* aSvA = new QAction("Zapisz &jako...", mDane);
    aSvA->setShortcut(QKeySequence::SaveAs);
    mDane->addAction(aSvA);

    mDane->addSeparator();

    QAction* aClr = new QAction("&Przetwórz szablon", mDane);
    mDane->addAction(aClr);

    this->menuBar()->addMenu(mDane);



    QMenu* mHelp = new QMenu("P&omoc");
    QAction* aAb = new QAction("&O", mHelp);
    aAb->setShortcut(QKeySequence::HelpContents);
    mHelp->addAction(aAb);

    QAction* aTh = new QAction("Wyślij litanie &dziękczynne do autora", mHelp);
    connect(aTh, &QAction::triggered, [=](){
        QDesktopServices::openUrl(
                    QUrl("mailto:wojciech_kogut@o2.pl?subject=O najwspanialszy z wspaniałych&body=...",
                         QUrl::TolerantMode)
                    );});
    mHelp->addAction(aTh);
    this->menuBar()->addMenu(mHelp);
}
