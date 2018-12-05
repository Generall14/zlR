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
#include <src/Data.hpp>
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>
#include <src/DataDefs.hpp>
#include <src/Data.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QDial>
#include <QPlainTextEdit>
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <QFontMetrics>
#include <math.h>
#include <QVariant>
#include <QToolButton>
#include <QIcon>
#include <QStyle>
#include <QCommonStyle>
#include "mtv.hpp"

MainGUI::MainGUI(QSharedPointer<Data> dat, QString iadr, QString tadr, QString oadr, QWidget *parent):
    QMainWindow(parent),
    _dat(dat),
    _currentFile(iadr),
    _currentTempFile(tadr),
    _currentOutFile(oadr)
{
    InitGUI();
    InitMenu();
    UpdTitle();
}

MainGUI::~MainGUI()
{

}

void MainGUI::InitGUI()
{
    this->window()->resize(800, 600);

    this->setCentralWidget(new QWidget());
    this->centralWidget()->setLayout(new QVBoxLayout());

    auto map = _dat->GetMap();
    for(auto it = map.begin();it!=map.end();it++)
        AppendTable(it.value());
}

void MainGUI::AppendTable(QSharedPointer<DataI> d)
{
    for(auto s: _noTable)
    {
        if(!s.compare(d->getMyName()))
            return;
    }

    QGroupBox* GB = new QGroupBox(d->getMyName());
    this->centralWidget()->layout()->addWidget(GB);
    GB->setLayout(new QHBoxLayout());

    mQTableView* TBV = new mQTableView();
    TBV->setSelectionMode(QAbstractItemView::SingleSelection);
    TBV->setModel(d.data());
    d->ApplyDelegatesForTable(TBV);
    GB->layout()->addWidget(TBV);

    TBV->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    TBV->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    for(int i=0;i<d->columnCount();i++)
    {
        QString td = d->getMaxTxts().at(i)+"MMM";
        QString hd = d->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString()+"MMM";
        TBV->horizontalHeader()->resizeSection(i,
                                               std::max(QFontMetrics(QApplication::font()).width(td),
                                                        QFontMetrics(QApplication::font()).width(hd)));
    }
    TBV->verticalHeader()->hide();

    for(auto s: _noEdits)
    {
        if(!s.compare(d->getMyName()))
            return;
    }

    QVBoxLayout* BL = new QVBoxLayout();
    static_cast<QBoxLayout*>(GB->layout())->addLayout(BL);

    BL->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Maximum, QSizePolicy::Expanding));

    QHBoxLayout* TL = new QHBoxLayout();
    BL->addLayout(TL);
    QToolButton* tbtn = new QToolButton();
    tbtn->setIcon(QCommonStyle().standardIcon(QStyle::SP_ArrowUp));
    auto fu = [d, TBV](){
        auto idx = TBV->currentIndex();
        if(d->Up(TBV->currentIndex().row()))
            idx = idx.sibling(idx.row()-1, idx.column());
        TBV->setCurrentIndex(idx);};
    connect(tbtn, &QToolButton::clicked, fu);
    TL->addWidget(tbtn);

    tbtn = new QToolButton();
    tbtn->setIcon(QCommonStyle().standardIcon(QStyle::SP_ArrowDown));
    auto fd = [d, TBV](){
        auto idx = TBV->currentIndex();
        if(d->Down(TBV->currentIndex().row()))
            idx = idx.sibling(idx.row()+1, idx.column());
        TBV->setCurrentIndex(idx);};
    connect(tbtn, &QToolButton::clicked, fd);
    TL->addWidget(tbtn);

    QPushButton* btn = new QPushButton("Dodaj");
    connect(btn, &QPushButton::clicked, d.data(), &DataRegion::Add);
    BL->addWidget(btn);
    btn = new QPushButton("Usuń");
    auto uf = [this, d, TBV](){
        auto idx = TBV->currentIndex();
        d->Remove(idx.row());
        if(TBV->model()->rowCount()<=idx.row())
            idx = idx.sibling(idx.row()-1, idx.column());
        TBV->setCurrentIndex(idx);};
    connect(btn, &QPushButton::clicked, uf);
    connect(TBV, &mQTableView::delete_req, uf);
    BL->addWidget(btn);
}

void MainGUI::InitMenu()
{
    QMenu* mPlik = new QMenu("&Plik");

    QAction* aClrD = new QAction("&Nowy", mPlik);
    connect(aClrD, &QAction::triggered, [this](){_dat->Clear();});
    mPlik->addAction(aClrD);

    mPlik->addSeparator();

    QAction* aOp = new QAction("&Otwórz", mPlik);
    aOp->setShortcut(QKeySequence::Open);
    connect(aOp, &QAction::triggered, this, &MainGUI::Open);
    mPlik->addAction(aOp);

    QAction* aSv = new QAction("&Zapisz", mPlik);
    aSv->setShortcut(QKeySequence::Save);
    connect(aSv, &QAction::triggered, this, &MainGUI::Save);
    mPlik->addAction(aSv);

    QAction* aSvA = new QAction("Zapisz &jako...", mPlik);
    aSvA->setShortcut(QKeySequence::SaveAs);
    connect(aSvA, &QAction::triggered, this, &MainGUI::SaveAs);
    mPlik->addAction(aSvA);

    mPlik->addSeparator();

    QAction* aCl = new QAction("&Zamknij", mPlik);
    aCl->setShortcut(QKeySequence::Close);
    connect(aCl, &QAction::triggered, this, &MainGUI::close);
    mPlik->addAction(aCl);
    this->menuBar()->addMenu(mPlik);



    QMenu* mDane = new QMenu("&Dane");

    QAction* aClr = new QAction("&Przetwórz szablon", mDane);
    connect(aClr, &QAction::triggered, this, &MainGUI::Make);
    mDane->addAction(aClr);

    this->menuBar()->addMenu(mDane);



    QMenu* mHelp = new QMenu("P&omoc");
    QAction* aAb = new QAction("&O", mHelp);
    aAb->setShortcut(QKeySequence::HelpContents);
    connect(aAb, &QAction::triggered, this, &MainGUI::About);
    mHelp->addAction(aAb);

    QAction* aMan = new QAction("&Składnia szablonu", mHelp);
    connect(aMan, &QAction::triggered, this, &MainGUI::Manual);
    mHelp->addAction(aMan);

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
    if(!_currentFile.isEmpty())
        _dat->Save(_currentFile);
    else
        SaveAs();
}

void MainGUI::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                "Podaj plik z definicjami danych do zapisu",
                                _currentFile,
                                "C header files (*.h);;All files (*)");

    if (!fileName.isEmpty())
    {
        _currentFile = fileName;
        Save();
        UpdTitle();
    }
}

void MainGUI::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                "Podaj plik z definicjami danych do wczytania",
                                _currentFile,
                                "C header files (*.h);;All files (*)");

    if (!fileName.isEmpty())
    {
        _currentFile = fileName;
        _dat->Load(fileName);
        UpdTitle();
    }
}

void MainGUI::UpdTitle()
{
    QString temp = "zlR";
    if(!_currentFile.isEmpty())
    {
        temp.append(" ( ");
        if(_currentFile.size()>(MAX_TITLE_LENGTH+3))
            temp.append("..."+_currentFile.right(MAX_TITLE_LENGTH));
        else
            temp.append(_currentFile);
        temp.append(" )");
    }
    this->setWindowTitle(temp);
}

void MainGUI::About()
{
    QString message = "Ble ble ble\n\n"
                      "Nie gwarantuje prawidłowego działania.\n\n"
                      "Zapewniam wsparcie techniczne do momentu aż mi się znudzi.\n\n"
                      "Wersja: "+QString(GIT_VERSION)+" z dnia "+QString(GIT_DATE)+".";
    QMessageBox::about(this, "About", message);
}

void MainGUI::Manual()
{
    class mm : public QDialog
    {
    public:
        mm(QWidget* p, QString txt):
            QDialog(p)
        {
            QPlainTextEdit* ple = new QPlainTextEdit(txt);
            ple->setReadOnly(true);
            this->setLayout(new QVBoxLayout());
            this->layout()->addWidget(ple);
            this->window()->resize(p->window()->size()*0.75);
        }
    };

    QFile hfile(":/template.txt");
    hfile.open(QIODevice::ReadOnly | QIODevice::Text);

    mm* dial = new mm(this, hfile.readAll());
    hfile.close();
    dial->setModal(true);
    dial->show();
}

void MainGUI::Make()
{
    QString templateFile = QFileDialog::getOpenFileName(this,
                                "Podaj plik szablonu",
                                _currentTempFile,
                                "Linker files (*.ld);;All files (*)");
    if(templateFile.isEmpty())
        return;

    QString outputFile = QFileDialog::getSaveFileName(this,
                                "Podaj plik wynikowy",
                                _currentOutFile,
                                "Linker files (*.ld);;All files (*)");
    if(outputFile.isEmpty())
        return;

    _currentTempFile = templateFile;
    _currentOutFile = outputFile;
    try
    {
        _dat->Make(_currentTempFile, _currentOutFile);
        QMessageBox::information(this, "To działa!", "Zrobione.");
    }
    catch(std::runtime_error e)
    {
        QMessageBox::critical(this, "ERROR", "Coś się zesrało: "+QString(e.what()));
    }
}
