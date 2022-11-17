#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QColorDialog>
#include "qgifimage.h"
#include "geometryengine.h"
#include "mainwidget.h"

#include "facade.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QColor *ColorBack = new QColor(214, 214, 214, 255);
    QColor *LineColor = new QColor(0, 0, 0, 255);
    QColor *VerColor = new QColor(190, 30, 20, 255);

    QSettings *settings;
    int time = 0;
    bool load_file = 0;
    QGifImage *gif;
    QImage *photo;
    QTimer *timer;
    QString path;

	s21::Facade facade;

private slots:
    void TimerSlot();
    void save_settings();
    void load_settings();
    void default_params1();
    void default_params2();
    void file_dialog();
    void widget_background();
    void on_facets_color_button_clicked();
    void on_vertexes_color_button_clicked();
    void on_move_x_slider_valueChanged(int value);
    void on_move_x_box_valueChanged(double arg1);
    void on_move_z_slider_valueChanged(int value);
    void on_move_y_slider_valueChanged(int value);
    void on_move_y_box_valueChanged(double arg1);
    void on_move_z_box_valueChanged(double arg1);
    void on_rotate_x_slider_valueChanged(int value);
    void on_rotate_x_box_valueChanged(double arg1);
    void on_rotate_y_box_valueChanged(double arg1);
    void on_rotate_y_slider_valueChanged(int value);
    void on_rotate_z_box_valueChanged(double arg1);
    void on_rotate_z_slider_valueChanged(int value);
    void on_scale_slider_valueChanged(int value);
    void on_scale_box_valueChanged(double arg1);
    void on_parallel_projection_clicked();
    void on_central_projection_clicked();
    void on_dotted_facets_clicked();
    void on_solid_facets_clicked();
    void on_facets_width_box_valueChanged(double arg1);
    void on_round_vertexes_clicked();
    void on_vertexes_size_box_valueChanged(double arg1);
    void on_square_vertexes_clicked();
    void on_none_vertexes_clicked();
    void on_save_image_button_clicked();
    void on_save_gif_button_clicked();
    void on_load_clicked();
    void on_load_set_clicked();
};



#endif // MAINWINDOW_H
