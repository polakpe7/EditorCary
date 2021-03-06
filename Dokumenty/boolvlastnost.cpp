#include "boolvlastnost.h"
#include "boolvlastnostmanager.h"

using namespace Dokumenty;



BoolVlastnost::BoolVlastnost(QString nazov, bool hodnota) : Vlastnost(nazov), _hodnota(hodnota)
{

}

VlastnostManagerPtr BoolVlastnost::NastrojVlastnosti()
{
    return std::make_unique<BoolVlastnostManager>(this);
}

bool BoolVlastnost::Hodnota() const
{
    return _hodnota;
}

void BoolVlastnost::setHodnota(bool hodnota)
{
    if(hodnota != _hodnota){
        _hodnota = hodnota;
        emit hodnotaZmenena(hodnota);
        emit VlastnostZmenena();
    }
}

void BoolVlastnost::obnovVlastnost(QDomElement &v)
{
    setHodnota(v.attribute("hodnota") == "1");
}

QDomElement BoolVlastnost::UlozVlastnost(QDomDocument &doc)
{
    auto v = doc.createElement("vlastnost");
    v.setAttribute("nazov", _nazov);
    v.setAttribute("hodnota", _hodnota);
    return v;
}
