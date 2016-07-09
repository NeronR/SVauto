#include "outinvoicelist.h"
#include <QDir>

OutInvoiceList::OutInvoiceList(QString IFolderName)
{
    Load(IFolderName);
}
void OutInvoiceList::Load(QString IFolderName)
{
    InvoiceList.clear();
    QDir Dir(IFolderName);
    QStringList DirList = Dir.entryList();
    for(int i=0; i<DirList.length(); ++i)
    {
        QString ParsedID = "";
        int j;
        for(j=0; j<DirList[i].length(); ++j)
        {
            if (DirList[i][j].isDigit())
                ParsedID += DirList[i][j];
            else if(DirList[i][j] == '.')
                break;
        }
        if(DirList[i][j+1]=='x' && DirList[i][j+2]=='m' && DirList[i][j+3] == 'l')
            InvoiceList<<OutInvoice(ParsedID);
    }
}
int OutInvoiceList::SearchByID(QString IID)
{
    for(int i=0; i<Size(); ++i)
    {
        if(InvoiceList[i].GetID() == IID)
            return i;
    }
    return -1;
}
QString OutInvoiceList::GetNextID()
{
    if(InvoiceList.isEmpty())
        return "3200000000001";
    QString LastID = InvoiceList.last().GetID();
    for(int i=LastID.length()-1; i>-1; --i)
    {
        if(LastID[i] == '9')
        {
            LastID[i] = '0';
            continue;
        }
        if(LastID[i] == '0')
            LastID[i] = '1';
        else if(LastID[i] == '1')
            LastID[i] = '2';
        else if(LastID[i] == '2')
            LastID[i] = '3';
        else if(LastID[i] == '3')
            LastID[i] = '4';
        else if(LastID[i] == '4')
            LastID[i] = '5';
        else if(LastID[i] == '5')
            LastID[i] = '6';
        else if(LastID[i] == '6')
            LastID[i] = '7';
        else if(LastID[i] == '7')
            LastID[i] = '8';
        else if(LastID[i] == '8')
            LastID[i] = '9';
        break;
    }
    return LastID;
}
