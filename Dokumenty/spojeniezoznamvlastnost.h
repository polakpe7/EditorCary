#ifndef SPOJENIEZOZNAMVLASTNOST_H
#define SPOJENIEZOZNAMVLASTNOST_H

#include "vlastnost.h"
#include "Komponenty/spojenieslot.h"

namespace Dokumenty {
class SpojenieZoznamVlastnost : public Vlastnost {
  Q_OBJECT
public:
  SpojenieZoznamVlastnost(QString nazov, Komponenty::Komponent *spojenie);
  SpojenieZoznamVlastnost(QString nazov, Komponenty::Komponent *spojenie,
                          std::vector<Komponenty::SpojenieSlot *> hodnota);
  VlastnostManagerPtr NastrojVlastnosti();
  std::vector<Komponenty::SpojenieSlot *> hodnota() const;

  Komponenty::Komponent *spojenie();
  QDomElement Uloz(QDomDocument &doc);
  void Obnov(QDomNodeList l, Dokumenty::Dokument* dokument);

public slots:
  void setHodnota(std::vector<Komponenty::SpojenieSlot *> hodnota);

signals:
  void hodnotaZmenena(std::vector<Komponenty::SpojenieSlot *> &novaHodnota);


protected:
    void obnov(QDomElement &);

private:
  std::vector<Komponenty::SpojenieSlot *> _hodnota;
  Komponenty::Komponent *_spojenie;
};
using SpojenieZoznamVlastnostPtr = std::unique_ptr<SpojenieZoznamVlastnost>;
}

#endif // SPOJENIEZOZNAMVLASTNOST_H
