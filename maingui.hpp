#ifndef MAINGUI_HPP
#define MAINGUI_HPP

/**
  * @class MainGUI
  * @author Wojciech Kogut
  *
  * Jak sama nazwa wskazuje - tworzy GUI programu.
  */

#include <QMainWindow>
#include <QLabel>

class Data;
class DataI;

class MainGUI : public QMainWindow
{
    Q_OBJECT
public:
    MainGUI(QSharedPointer<Data> dat, QString iadr="", QString tadr="", QString oadr="", QWidget *parent = 0);
    ~MainGUI();

private:
    void InitGUI();
    void InitAdrGUI();
    void AppendTable(QSharedPointer<DataI> d);
    void InitMenu();

    QSharedPointer<Data> _dat;

    QString _currentFile;
    QString _currentTempFile;
    QString _currentOutFile;

    void UpdTitle();

    static const int MAX_TITLE_LENGTH = 40;

    const QStringList _noEdits = {"DREG"}; /**<Lista nazw sekcji dla których nie zostaną dodane przyciski edycji.*/
    const QStringList _noTable = {"DSTCK", ""}; /**<Lista nazw sekcji dla których nie zostanie dodana tabela.*/

    QLabel* _liadr = nullptr;
    QLabel* _ltadr = nullptr;
    QLabel* _loadr = nullptr;

private slots:
    void Save();
    void SaveAs();
    void Open();
    void GetTemplate();
    void GetOutput();
    void About();
    void Make();
    void Manual();
};

#endif // MAINGUI_HPP
