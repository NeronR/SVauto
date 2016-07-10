#ifndef CARIDS_H
#define CARIDS_H

#include <QMap>
#include <QList>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include "utils.h"

class CarIDs
{
public:
    struct VersionNode {QString Name;};
    struct ModelNode {QString Name; QList<VersionNode>* Versions;};
    struct BrandNode {QString Name; QList<ModelNode>* Models;};
    QList<BrandNode> Brands;

    static const short BRAND_ID_NUMBERS;
    static const short MODEL_ID_NUMBERS;
    static const short VERSION_ID_NUMBERS;

    CarIDs(){}
    CarIDs(QDomElement* IElement);
    void Save()
    {
        QDomDocument Document;
        QFile OutputFile(Utils::CARIDS_FILENAME+Utils::FILENAME_EXTENSION);
        OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream OutStream(&OutputFile);
        Document.appendChild(ToXML(&Document));
        OutStream << Document.toString();
        OutputFile.close();
    }
    void Load()
    {
        QFile InputFile(Utils::CARIDS_FILENAME+Utils::FILENAME_EXTENSION);
        InputFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QDomDocument Document;
        Document.setContent(&InputFile);
        InputFile.close();

        QDomElement Root = Document.documentElement();
        QDomNode NodeBrand = Root.firstChild();
        QDomElement Element;
        while(!NodeBrand.isNull())
        { //Brands cycle
            Element = NodeBrand.toElement();

            if(Element.tagName() == Utils::XML_BRAND_TAG && Element.hasAttribute(Utils::XML_NAME_TAG))
                AddBrand(Element.attribute(Utils::XML_NAME_TAG));
            else
                QMessageBox::about(0,"ERROR!","XML_BRAND_TAG ERROR");

            QDomNode NodeModel = NodeBrand.firstChild();
            while(!NodeModel.isNull())
            { //Models cycle
                Element = NodeModel.toElement();

                if(Element.tagName() == Utils::XML_MODEL_TAG && Element.hasAttribute(Utils::XML_NAME_TAG))
                    AddModel(Brands.size() - 1, Element.attribute(Utils::XML_NAME_TAG));
                else
                    QMessageBox::about(0,"ERROR!","XML_MODEL_TAG ERROR");

                QDomNode NodeVersion = NodeModel.firstChild();
                while(!NodeVersion.isNull())
                { //Versions cycle
                    Element = NodeVersion.toElement();

                    if(Element.tagName() == Utils::XML_VERSION_TAG && Element.hasAttribute(Utils::XML_NAME_TAG))
                        AddVersion(Brands.size() - 1, Brands.last().Models->size() - 1,
                                   Element.attribute(Utils::XML_NAME_TAG));
                    else
                        QMessageBox::about(0,"ERROR!","XML_VERSION_TAG ERROR");

                    NodeVersion = NodeVersion.nextSibling();
                }
                NodeModel = NodeModel.nextSibling();
            }
            /*if(!((Element = Node.toElement()).isNull()) && Element.tagName()==Utils::XML_OUT_ITEM_TAG)
            {
                OutItem NewItem(&Element);
                *this << NewItem;
            }
            else
                QMessageBox::about(0,"ERROR!","NOT XML_OUT_ITEM_TAG");*/
            NodeBrand = NodeBrand.nextSibling();
        }
    }
    void AddBrand(QString IName)
    {
        BrandNode NewBrand;
        NewBrand.Name = IName;
        NewBrand.Models = new QList<ModelNode>;
        Brands<<NewBrand;
    }
    void AddModel(long BrandID, QString IName)
    {
        ModelNode NewModel;
        NewModel.Name = IName;
        NewModel.Versions = new QList<VersionNode>;
        Brands.at(BrandID).Models->append(NewModel);
    }
    void AddVersion(long BrandID, long ModelID, QString IName)
    {
        VersionNode NewVersion;
        NewVersion.Name = IName;
        Brands.at(BrandID).Models->at(ModelID).Versions->append(NewVersion);
    }
    QStringList GetBrands()
    {
        QStringList OutList;
        for(int i=0; i<Brands.size(); ++i)
            OutList<<Brands.at(i).Name;
        return OutList;
    }
    QStringList GetModels (long IBrandID)
    {
        QStringList OutList;
        for(int i=0; i<Brands.at(IBrandID).Models->size(); ++i)
            OutList<<Brands.at(IBrandID).Models->at(i).Name;
        return OutList;
    }
    QStringList GetVersions (long IBrandID, long IModelID)
    {
        QStringList OutList;
        for(int i=0; i<Brands.at(IBrandID).Models->at(IModelID).Versions->size(); ++i)
            OutList<<Brands.at(IBrandID).Models->at(IModelID).Versions->at(i).Name;
        return OutList;
    }
    static QString GetCarID(long IBrandID = 0, long IModelID = 0, long IVersionID = 0)
    {
        QString BrandID = QString::number(IBrandID);
        while(BrandID.size() < BRAND_ID_NUMBERS)
            BrandID = "0" + BrandID;
        QString ModelID = QString::number(IModelID);
        while(ModelID.size() < MODEL_ID_NUMBERS)
            ModelID = "0" + ModelID;
        QString VersionID = QString::number(IVersionID);
        while(VersionID.size() < VERSION_ID_NUMBERS)
            VersionID = "0" + VersionID;
        return BrandID + ModelID + VersionID;
    }
    QDomElement ToXML(QDomDocument* IDocument);
};

#endif // CARIDS_H
