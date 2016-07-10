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

    CarIDs()
    {
        AddBrand("All", true);
    }
    void Save();
    void Load();
    void AddBrand(QString IName, bool ICreateAll = true)
    {
        BrandNode NewBrand;
        NewBrand.Name = IName;
        NewBrand.Models = new QList<ModelNode>;
        Brands<<NewBrand;
        if(ICreateAll)
            AddModel(Brands.size() - 1, "All", ICreateAll);
    }
    void AddModel(long BrandID, QString IName, bool ICreateAll = true)
    {
        ModelNode NewModel;
        NewModel.Name = IName;
        NewModel.Versions = new QList<VersionNode>;
        Brands.at(BrandID).Models->append(NewModel);
        if(ICreateAll)
            AddVersion(BrandID, Brands.at(BrandID).Models->size() - 1, "All");
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
    static long long GetCarIDInt(long IBrandID = 0, long IModelID = 0, long IVersionID = 0)
    {
        return GetCarID(IBrandID, IModelID, IVersionID).toLongLong();
    }
    static QString IntCarIDToString(long long ICarID)
    {
        QString Answer = QString::number(ICarID);
        while(Answer.size() < (BRAND_ID_NUMBERS + MODEL_ID_NUMBERS + VERSION_ID_NUMBERS))
            Answer = "0" + Answer;
        return Answer;
    }

    QDomElement ToXML(QDomDocument* IDocument);
};

#endif // CARIDS_H
