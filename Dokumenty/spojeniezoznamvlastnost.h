#ifndef SPOJENIEZOZNAMVLASTNOST_H
#define SPOJENIEZOZNAMVLASTNOST_H

#include "vlastnost.h"
#include "Komponenty/komponent.h"

namespace Dokumenty {
class SpojenieZoznamVlastnost : public Vlastnost {
  Q_OBJECT
public:
  SpojenieZoznamVlastnost(QString nazov, Komponenty::Komponent* spojenie, std::vector<Komponenty::Komponent *> hodnota);
  VlastnostManagerPtr NastrojVlastnosti();
  std::vector<Komponenty::Komponent *> hodnota() const;


public slots:
  void setHodnota(std::vector<Komponenty::Komponent *> hodnota);

signals:
  void hodnotaZmenena(std::vector<Komponenty::Komponent *>& novaHodnota);

private:
  std::vector<Komponenty::Komponent *> _hodnota;
  Komponenty::Komponent* _spojenie;
};
using SpojenieZoznamVlastnostPtr = std::unique_ptr<SpojenieZoznamVlastnost>;
}

#endif // SPOJENIEZOZNAMVLASTNOST_H