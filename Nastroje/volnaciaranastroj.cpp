#include "volnaciaranastroj.h"

#include <Komponenty/volnaciara.h>

using namespace Nastroje;

VolnaCiaraNastroj::VolnaCiaraNastroj(Dokumenty::Dokument *dokument) :Nastroj(dokument)
{

}

NastrojPresenterPtr VolnaCiaraNastroj::NastrojPresenter() const {
    return std::make_unique<VolnaCiaraPresenter>();
}

void Nastroje::VolnaCiaraNastroj::MysStlacena(QPointF bod)
{
    _polohaMysi = bod;
    _mysStlacena = true;

    auto k = _dokument->NajdiKomponentPodBodom(bod);

    if(auto s = dynamic_cast<Komponenty::Spojenie*>(k))
    {
        if(k->Manipulatory().size() > 0)
            k = s->Manipulatory().at(0).get();
    }

    if(auto m = dynamic_cast<Komponenty::Manipulator*>(k))
    {
        _manipulator = m;
        k = m->Vlastnik();
    }

    if (auto komponent = dynamic_cast<Komponenty::VolnaCiara*>(k)) {

        auto&& manipulator = std::find_if(komponent->Manipulatory().begin(),
                                          komponent->Manipulatory().end(),
                                          [bod](auto && m) { return m->Obsahuje(bod); });

        if (manipulator != komponent->Manipulatory().end())
            _manipulator = dynamic_cast<Komponenty::Manipulator*>((*manipulator).get());
        else
            _manipulator = dynamic_cast<Komponenty::Manipulator*>(komponent);

        _komponent = dynamic_cast<Komponenty::VolnaCiara*>(komponent);
    }
}

void Nastroje::VolnaCiaraNastroj::MysPohyb(QPointF bod)
{
    if (_mysStlacena)
    {
        if(_manipulator && _komponent && _novy)
        {
            _komponent->Body().push_back(bod);
            _komponent->Prepocitaj();
            _manipulator->setBod(bod);
        }

        else if(_manipulator)
            _manipulator->setBod(bod);

        else if(_komponent)
        {
            auto& body = _komponent->Body();

            for(auto& b : body)
                b += bod - _polohaMysi;

            for(auto& m : _komponent->Manipulatory())
            {
                if(auto manipulator = dynamic_cast<Komponenty::Manipulator*>(m.get()))
                    manipulator->setBod(manipulator->Bod() + bod - _polohaMysi);
            }

            _komponent->Prepocitaj();
        }
    }
    _polohaMysi = bod;
}

void Nastroje::VolnaCiaraNastroj::MysUvolnena(QPointF)
{
    _mysStlacena = false;
    _manipulator = nullptr;
    _komponent = nullptr;
    _novy = false;
}

void Nastroje::VolnaCiaraNastroj::MysDvojklik(QPointF bod)
{
    _novy = true;

    auto ciara = std::make_unique<Komponenty::VolnaCiara>();
    _komponent = ciara.get();
    _dokument->PridajKomponent(std::move(ciara));

    for (auto &&m : _komponent->Manipulatory())
        dynamic_cast<Komponenty::Manipulator *>(m.get())->setBod(bod);

    _manipulator =
            dynamic_cast<Komponenty::Manipulator *>(_komponent->Manipulatory().at(1).get());

    _mysStlacena = true;
}

Komponenty::Komponent *VolnaCiaraNastroj::VybranyKomponent() const{
    if(_komponent)
        return _komponent;
    else
        return _manipulator;
}

NastrojPtr VolnaCiaraPresenter::Nastroj(Dokumenty::Dokument *dokument) const {
    return std::make_unique<VolnaCiaraNastroj>(dokument);
}

Komponenty::KomponentPtr VolnaCiaraPresenter::Komponent() const
{
    return std::make_unique<Komponenty::VolnaCiara>();
}
