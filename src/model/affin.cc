#include "affin.h"

namespace s21 {
void ChangeMdlParams::change(affin_operetions_ operation, double value) {
	std::vector<double> vertex = Model::Instance().GetVertex();
	switch (operation) {
	case kMoveX:
		for (unsigned i = 0; i < vertex.size(); i += 3) vertex[i] += value;
		break;
	case kMoveY:
		for (unsigned i = 1; i < vertex.size(); i += 3) vertex[i] += value;
		break;
	case kMoveZ:
		for (unsigned i = 2; i < vertex.size(); i += 3) vertex[i] += value;
		break;
	default:
		return;
	}
	Model::Instance().SetVertex(vertex);
}

void ChangeMdlAngle::change(affin_operetions_ operation, double value) {
	std::vector<double> vertex = Model::Instance().GetVertex();
	switch(operation) {
	case kRotateX:
		for (unsigned i = 1; i < vertex.size(); i += 3) {
			double temp_y = vertex[i];
			double temp_z = vertex[i + 1];
			vertex[i] = cos(value) * temp_y - sin(value) * temp_z;
			vertex[i + 1] = sin(value) * temp_y + cos(value) * temp_z;
		}
		break;
	case kRotateY:
		for (unsigned i = 0; i < vertex.size(); i += 3) {
			double temp_x = vertex[i];
			double temp_z = vertex[i + 2];
			vertex[i] = cos(value) * temp_x - sin(value) * temp_z;
			vertex[i + 2] = sin(value) * temp_x + cos(value) * temp_z;
		}
		break;
	case kRotateZ:
		for (unsigned i = 0; i < vertex.size(); i += 3) {
			double temp_x = vertex[i];
			double temp_y = vertex[i + 1];
			vertex[i] = cos(value) * temp_x - sin(value) * temp_y;
			vertex[i + 1] = sin(value) * temp_x + cos(value) * temp_y;
		}
		break;
	default:
		return;
	}
	Model::Instance().SetVertex(vertex);
}

void ChangeMdlScale::change(affin_operetions_ operation, double value) {
	std::vector<double> vertex = Model::Instance().GetVertex();
	if (value != 0 && operation == kScale) {
		for (unsigned i = 0; i < vertex.size(); i++) vertex[i] *= value;
		Model::Instance().SetVertex(vertex);
	}
}

}  //  namespace s21
