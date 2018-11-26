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
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>
#include <src/DataDefs.hpp>
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
    regTBV->setSelectionMode(QAbstractItemView::SingleSelection);
    regTBV->setModel((_dat->GetRegions()).data());
    _dat->GetRegions()->ApplyDelegatesForTable(regTBV);
    regGB->layout()->addWidget(regTBV);

    QHBoxLayout* regBL = new QHBoxLayout();
    static_cast<QBoxLayout*>(regGB->layout())->addLayout(regBL);

    regBL->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QPushButton* btn = new QPushButton("Dodaj");
    connect(btn, &QPushButton::clicked, _dat->GetRegions().data(), &DataRegion::Add);
    regBL->addWidget(btn);
    btn = new QPushButton("Usuń");
    connect(btn, &QPushButton::clicked, [this](){_dat->GetRegions()->Remove(regTBV->currentIndex().row());});
    regBL->addWidget(btn);

    //========================= Sekcje ========================================
    QGroupBox* secGB = new QGroupBox("Sekcje");
    this->centralWidget()->layout()->addWidget(secGB);
    secGB->setLayout(new QVBoxLayout());

    secTBV = new QTableView();
    secTBV->setSelectionMode(QAbstractItemView::SingleSelection);
    secTBV->setModel((_dat->GetSections()).data());
    _dat->GetSections()->ApplyDelegatesForTable(secTBV);
    secGB->layout()->addWidget(secTBV);

    QHBoxLayout* secBL = new QHBoxLayout();
    static_cast<QBoxLayout*>(secGB->layout())->addLayout(secBL);

    secBL->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    btn = new QPushButton("Dodaj");
    connect(btn, &QPushButton::clicked, _dat->GetSections().data(), &DataRegion::Add);
    secBL->addWidget(btn);
    btn = new QPushButton("Usuń");
    connect(btn, &QPushButton::clicked, [this](){_dat->GetSections()->Remove(secTBV->currentIndex().row());});
    secBL->addWidget(btn);

    //========================= Definicje =====================================
    QGroupBox* defGB = new QGroupBox("Stałe");
    this->centralWidget()->layout()->addWidget(defGB);
    defGB->setLayout(new QHBoxLayout());

    defTBV = new QTableView();
    defTBV->setSelectionMode(QAbstractItemView::SingleSelection);
    defTBV->setModel((_dat->GetDefinitions()).data());
    _dat->GetDefinitions()->ApplyDelegatesForTable(defTBV);
    defGB->layout()->addWidget(defTBV);

    QVBoxLayout* defBL = new QVBoxLayout();
    static_cast<QBoxLayout*>(defGB->layout())->addLayout(defBL);

    defBL->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Maximum, QSizePolicy::Expanding));
    btn = new QPushButton("Dodaj");
    connect(btn, &QPushButton::clicked, _dat->GetDefinitions().data(), &DataRegion::Add);
    defBL->addWidget(btn);
    btn = new QPushButton("Usuń");
    connect(btn, &QPushButton::clicked, [this](){_dat->GetDefinitions()->Remove(defTBV->currentIndex().row());});
    defBL->addWidget(btn);
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
    connect(aSv, &QAction::triggered, this, &MainGUI::Save);
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

void MainGUI::Save()
{
    _dat->Save("out.h");
    //<TODO>
}
