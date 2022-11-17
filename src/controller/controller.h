#ifndef SRC_CONTROLLER_HPP_
#define SRC_CONTROLLER_HPP_

#include "../model/affin.h"

namespace s21 {
class Controller {
public:
	void OpenModel(FILE* fp) { Model::Instance().ParseFileData(fp); }
	std::vector<double> GetVertex() { return Model::Instance().GetVertex(); }
	std::vector<int> GetFacets() { return  Model::Instance().GetFacets(); }

	void ChangeModelParams(ChangeModel::affin_operetions_ operation, double value) { 
        strat_ = new Changer(new ChangeMdlParams);
        strat_->change(operation, value);
        delete strat_;
	}

	void ChangeModelAngle(ChangeModel::affin_operetions_ operation, double value) { 
        strat_ = new Changer(new ChangeMdlAngle);
        strat_->change(operation, value);
        delete strat_;
	}

	void ChangeModelScale(ChangeModel::affin_operetions_ operation, double scale) {
        strat_ = new Changer(new ChangeMdlScale);
        strat_->change(operation, scale);
        delete strat_;
	}
private:
    Changer* strat_;
};

}  // namespace s21

#endif  //  SRC_CONTROLLER_HPP_
