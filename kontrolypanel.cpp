#include "kontrolypanel.h"
#include "Kontroly/kontrolaokrajov.h"
#include "Kontroly/kontrolazakrivenia.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <Kontroly/kontroladlzky.h>
#include <Kontroly/kontrolaspojeni.h>

KontrolyPanel::KontrolyPanel(QWidget *parent) : QWidget(parent)
{

}

void KontrolyPanel::nastavKontroly(Dokumenty::Dokument *dokument)
{
    _kontroly.push_back(std::make_unique<Kontroly::KontrolaOkrajov>(dokument));
    _kontroly.push_back(std::make_unique<Kontroly::KontrolaZakrivenia>(dokument));
    _kontroly.push_back(std::make_unique<Kontroly::KontrolaDlzky>(dokument));
    _kontroly.push_back(std::make_unique<Kontroly::KontrolaSpojeni>(dokument));
}

void KontrolyPanel::NastavDokument(Dokumenty::Dokument *dokument)
{
    if(_dokument == dokument)
        return;

    _dokument = dokument;

    _kontroly.clear();

    nastavKontroly(dokument);

    auto layout = new QVBoxLayout(this);
    setLayout(layout);

    for(auto& k : _kontroly)
    {
        auto ch = new QCheckBox(this);
        ch->setText(k->Nazov());
        ch->setChecked(k->Povolena());

        auto kontrola = k.get();

        connect(ch, &QCheckBox::clicked, [kontrola](bool checked){
            kontrola->setPovolena(checked);
        });

        connect(kontrola, &Kontroly::KontrolaOkrajov::KontrolaPovolenaZmena,
                [kontrola, ch, this](){
            ch->setChecked(kontrola->Povolena());

            /*QPalette pal = ch->palette();

            if(kontrola->Vysledok())
                pal.setColor(QPalette::Button, QColor(Qt::green));
            else
                pal.setColor(QPalette::Button, QColor(Qt::red));

            ch->setAutoFillBackground(true);
            ch->setPalette(pal);
            ch->update();*/

            emit KontrolyZmenene();
        });

        layout->addWidget(ch);
    }

    layout->addStretch(1);

    emit KontrolyZmenene();
}

std::vector<Kontroly::Chyba> KontrolyPanel::VykonajKontroly()
{
    std::vector<Kontroly::Chyba> chyby;
    for(auto& k : _kontroly)
    {
        auto ch = k->VykonajKontrolu();
        chyby.insert(chyby.end(), ch.begin(), ch.end());
    }
    return chyby;
}
