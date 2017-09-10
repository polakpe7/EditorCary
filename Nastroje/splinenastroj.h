#ifndef SPLINENASTROJ_H
#define SPLINENASTROJ_H

#include "dvojbodovynastroj.h"

namespace Nastroje {
class SplineNastroj : public DvojbodovyNastroj {
public:
  SplineNastroj(Dokumenty::Dokument *dokument);
  void vytvorNovyKomponent(QPointF bod);
  virtual NastrojPresenterPtr NastrojPresenter() const;
};
class SplinePresenter : public NastrojPresenter {
  QString Nazov() const { return "Spline"; }
  QString Ikonka() const { return ":/ikonky/spline.svg"; }
  NastrojPtr Nastroj(Dokumenty::Dokument *dokument) const {
    return std::make_unique<SplineNastroj>(dokument);
  }
};
}

#endif // SPLINENASTROJ_H
