#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QMainWindow>

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
    void AppendTable(QSharedPointer<DataI> d);
    void InitMenu();

    QSharedPointer<Data> _dat;

    QString _currentFile;
    QString _currentTempFile;
    QString _currentOutFile;

    void UpdTitle();

    static const int MAX_TITLE_LENGTH = 40;

private slots:
    void Save();
    void SaveAs();
    void Open();
    void About();
    void Make();
    void Manual();
};

#endif // MAINGUI_HPP
