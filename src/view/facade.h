#ifndef SRC_FACADE_HPP_
#define SRC_FACADE_HPP_

#include "mainwidget.h"
#include "ui_mainwindow.h"

namespace s21 {
class MoveAroundX {
private:
    double x_new = 0;
public:
    void MoveX(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->move_x_box->setValue(val);
        else ui->move_x_slider->setValue(val*100);
        ui->openGLWidget->geometries->control.ChangeModelParams(ChangeModel::kMoveX, val - x_new);
        x_new = val;
        ui->openGLWidget->updating();
	}
};

class MoveAroundY {
private:
    double y_new = 0;
public:
    void MoveY(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->move_y_box->setValue(val);
        else ui->move_y_slider->setValue(val*100);
        ui->openGLWidget->geometries->control.ChangeModelParams(ChangeModel::kMoveY, val - y_new);
        y_new = val;
        ui->openGLWidget->updating();
    }
};


class MoveAroundZ {
private:
    double z_new = 0;
public:
    void MoveZ(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->move_z_box->setValue(val);
        else ui->move_z_slider->setValue(val*100);
        ui->openGLWidget->geometries->control.ChangeModelParams(ChangeModel::kMoveZ, val - z_new);
        z_new = val;
        ui->openGLWidget->updating();
    }
};

class RotateAroundX {
private:
    double x_new_rotate = 0;
public:
    void RotateX(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->rotate_x_box->setValue(val);
		else ui->rotate_x_slider->setValue(val*100);
		ui->openGLWidget->geometries->control.ChangeModelAngle(ChangeModel::kRotateX, val - x_new_rotate);
		x_new_rotate = val;
		ui->openGLWidget->updating();
	}
};

class RotateAroundY {
private:
    double y_new_rotate = 0;
public:
    void RotateY(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->rotate_y_box->setValue(val);
		else ui->rotate_y_slider->setValue(val*100);
		ui->openGLWidget->geometries->control.ChangeModelAngle(ChangeModel::kRotateY, val - y_new_rotate);
		y_new_rotate = val;
		ui->openGLWidget->updating();
    }
};


class RotateAroundZ {
private:
    double z_new_rotate = 0;
public:
    void RotateZ(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->rotate_z_box->setValue(val);
		else ui->rotate_z_slider->setValue(val*100);
		ui->openGLWidget->geometries->control.ChangeModelAngle(ChangeModel::kRotateZ, val - z_new_rotate);
		z_new_rotate = val;
		ui->openGLWidget->updating();
    }
};

class ScaleXYZ {
private:
    double scale_new = 1;
public:
    void Scale(double val, bool slider, Ui::MainWindow *ui) {
        if (slider) ui->scale_box->setValue(val);
		else ui->scale_slider->setValue(val*100);
		if (val != 0.0) {
			ui->openGLWidget->geometries->control.ChangeModelScale(ChangeModel::kScale, val / scale_new);
			scale_new = val;
		}
		ui->openGLWidget->updating();
    }
};


class Facade {
private:
	MoveAroundX mx_;
    MoveAroundY my_;
    MoveAroundZ mz_;

	RotateAroundX rx_;
    RotateAroundY ry_;
    RotateAroundZ rz_;

    ScaleXYZ sc;
public:
    void Move(ChangeModel::affin_operetions_ operation, double val, bool slider, Ui::MainWindow ui) {
		switch (operation) {
		case ChangeModel::kMoveX:
            mx_.MoveX(val, slider, &ui);
			break;
        case ChangeModel::kMoveY:
            my_.MoveY(val, slider, &ui);
            break;
        case ChangeModel::kMoveZ:
            mz_.MoveZ(val, slider, &ui);
            break;
		default:
			return;
		}
	}
	void Rotate(ChangeModel::affin_operetions_ operation, double val, bool slider, Ui::MainWindow ui) {
		switch (operation) {
		case ChangeModel::kRotateX:
            rx_.RotateX(val, slider, &ui);
			break;
        case ChangeModel::kRotateY:
            ry_.RotateY(val, slider, &ui);
            break;
        case ChangeModel::kRotateZ:
            rz_.RotateZ(val, slider, &ui);
            break;
		default:
			return;
		}
	}
	void Scale(double val, bool slider, Ui::MainWindow ui) {
        sc.Scale(val, slider, &ui);
	}
};
}  //  namespace s21

#endif  //  SRC_FACADE_HPP_
