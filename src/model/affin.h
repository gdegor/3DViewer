#ifndef SRC_AFFIN_H_
#define SRC_AFFIN_H_

#include "model.h"

namespace s21 {
// Иерархия классов, определяющая алгоритмы изменения модели
class ChangeModel {
  public:
	typedef enum {kMoveX, kMoveY, kMoveZ, kRotateX, kRotateY, kRotateZ, kScale} affin_operetions_;
    virtual ~ChangeModel() {}
    virtual void change(affin_operetions_ operation, double value) = 0;

};
  
class ChangeMdlParams : public ChangeModel {
  public:
    void change(affin_operetions_ operation, double value);
};
  
class ChangeMdlAngle : public ChangeModel {
  public:
    void change(affin_operetions_ operation, double value);
};
  
class ChangeMdlScale : public ChangeModel {
  public:
    void change(affin_operetions_ operation, double value);
};

class Changer {
public:
    Changer(ChangeModel* strategy): p_(strategy) {}
    ~Changer() { delete p_; }
    void change(ChangeModel::affin_operetions_ operation, double value) { p_->change(operation, value); }
private:
    ChangeModel* p_;
};
}  //  namespace s21

#endif  //  SRC_AFFIN_H_

