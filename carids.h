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

//TODO:
//Check IDs for existing

class UI;

class CarIDs
{
public:
    struct VersionNode {QString Name;};
    struct ModelNode {QString Name; QList<VersionNode>* Versions;};
    struct BrandNode {QString Name; QList<ModelNode>* Models;};
    struct CarName {QString Brand; QString Model; QString Version;};
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
    void Rename(long IBrandID, long IModelID, long IVersionID, QString IName)
    {
        if(IBrandID < 0)
            return;
        else if(IModelID < 0)
            (Brands.operator [](IBrandID)).Name = IName;
        else if(IVersionID < 0)
            ((Brands.operator [](IBrandID)).Models->operator [](IModelID)).Name = IName;
        else
            (((Brands.operator [](IBrandID)).Models->operator [](IModelID)).Versions->operator [](IVersionID)).Name = IName;
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
    static long long int GetCarIDInt(long IBrandID = 0, long IModelID = 0, long IVersionID = 0)
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
    static QString IntBrandIDToString(long IBrandID)
    {
        QString Answer = QString::number(IBrandID);
        while(Answer.size() < BRAND_ID_NUMBERS)
            Answer = "0" + Answer;
        return Answer;
    }
    static QString IntModelIDToString(long IModelID)
    {
        QString Answer = QString::number(IModelID);
        while(Answer.size() < MODEL_ID_NUMBERS)
            Answer = "0" + Answer;
        return Answer;
    }
    static QString IntVersionIDToString(long IVersionID)
    {
        QString Answer = QString::number(IVersionID);
        while(Answer.size() < VERSION_ID_NUMBERS)
            Answer = "0" + Answer;
        return Answer;
    }
    static long StringIDToBrandID(QString IBrandID)
    {
        if(IBrandID.length() < BRAND_ID_NUMBERS) return -1;
        QString Answer;
        for(int i=0; i<BRAND_ID_NUMBERS; ++i)
            Answer += IBrandID[i];
        return Answer.toLong();
    }
    static long StringIDToModelID(QString IModelID)
    {
        if(IModelID.length() < BRAND_ID_NUMBERS + MODEL_ID_NUMBERS) return -1;
        QString Answer;
        for(int i=BRAND_ID_NUMBERS; i<BRAND_ID_NUMBERS + MODEL_ID_NUMBERS; ++i)
            Answer += IModelID[i];
        return Answer.toLong();
    }
    static long StringIDToVersionID(QString IVersionID)
    {
        if(IVersionID.length() < BRAND_ID_NUMBERS + MODEL_ID_NUMBERS + VERSION_ID_NUMBERS) return -1;
        QString Answer;
        for(int i=BRAND_ID_NUMBERS + MODEL_ID_NUMBERS; i<BRAND_ID_NUMBERS + MODEL_ID_NUMBERS + VERSION_ID_NUMBERS; ++i)
            Answer += IVersionID[i];
        return Answer.toLong();
    }

    CarName GetCarNameByStringID(QString ICarID)
    {
        QString BrandID, ModelID, VersionID;
        for(int i=0; i<BRAND_ID_NUMBERS; ++i)
            BrandID += ICarID[i];
        for(int i=BRAND_ID_NUMBERS; i<BRAND_ID_NUMBERS + MODEL_ID_NUMBERS; ++i)
            ModelID += ICarID[i];
        for(int i=BRAND_ID_NUMBERS + MODEL_ID_NUMBERS; i<BRAND_ID_NUMBERS + MODEL_ID_NUMBERS + VERSION_ID_NUMBERS; ++i)
            VersionID += ICarID[i];
        CarName Answer;
        Answer.Brand = Brands[BrandID.toLong()].Name;
        Answer.Model = Brands[BrandID.toLong()].Models->at(ModelID.toLong()).Name;
        Answer.Version = Brands[BrandID.toLong()].Models->at(ModelID.toLong()).Versions->at(VersionID.toLong()).Name;
        return Answer;
    }
    CarName GetCarNameByIntID(long long ICarID)
    {
        return GetCarNameByStringID(IntCarIDToString(ICarID));
    }

    QDomElement ToXML(QDomDocument* IDocument);
};

#endif // CARIDS_H
