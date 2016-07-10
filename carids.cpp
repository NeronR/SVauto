#include "carids.h"
#include "utils.h"

QDomElement CarIDs::ToXML(QDomDocument *IDocument)
{
    QDomElement RootElement = IDocument->createElement(Utils::XML_ROOT_TAG);
    for(int i=0; i<Brands.size(); ++i) //Brands cycle
    {
        QDomElement BrandElement = IDocument->createElement(Utils::XML_BRAND_TAG);
        BrandElement.setAttribute(Utils::XML_NAME_TAG, Brands[i].Name);
        for(int j=0; j<Brands[i].Models->size(); ++j) //Models cycle
        {
            QDomElement ModelElement = IDocument->createElement(Utils::XML_MODEL_TAG);
            ModelElement.setAttribute(Utils::XML_NAME_TAG, Brands[i].Models->at(j).Name);
            for(int k=0; k<Brands[i].Models->at(j).Versions->size(); ++k) // Versions cycle
            {
                QDomElement VersionElement = IDocument->createElement(Utils::XML_VERSION_TAG);
                VersionElement.setAttribute(Utils::XML_NAME_TAG, Brands[i].Models->at(j).Versions->at(k).Name);
                ModelElement.appendChild(VersionElement);
            }
            BrandElement.appendChild(ModelElement);
        }
        RootElement.appendChild(BrandElement);
    }
    return RootElement;
}
void CarIDs::Save()
{
    QDomDocument Document;
    QFile OutputFile(Utils::CARIDS_FILENAME+Utils::FILENAME_EXTENSION);
    OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream OutStream(&OutputFile);
    Document.appendChild(ToXML(&Document));
    OutStream << Document.toString();
    OutputFile.close();
}
void CarIDs::Load()
{
    qDebug()<<Brands.size();
    Brands.clear();
    qDebug()<<Brands.size();
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
            AddBrand(Element.attribute(Utils::XML_NAME_TAG), false);
        else
            QMessageBox::about(0,"ERROR!","XML_BRAND_TAG ERROR");

        QDomNode NodeModel = NodeBrand.firstChild();
        while(!NodeModel.isNull())
        { //Models cycle
            Element = NodeModel.toElement();

            if(Element.tagName() == Utils::XML_MODEL_TAG && Element.hasAttribute(Utils::XML_NAME_TAG))
                AddModel(Brands.size() - 1, Element.attribute(Utils::XML_NAME_TAG), false);
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
        NodeBrand = NodeBrand.nextSibling();
    }
}

const short CarIDs::BRAND_ID_NUMBERS = 3;
const short CarIDs::MODEL_ID_NUMBERS = 2;
const short CarIDs::VERSION_ID_NUMBERS = 2;

