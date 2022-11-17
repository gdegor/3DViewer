#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("SHLYAPA", "3DViewer", this);
    connect(ui->open_file,SIGNAL(clicked()),this,SLOT(file_dialog()));
    connect(ui->background_color_button,SIGNAL(clicked()),this,SLOT(widget_background()));
    connect(ui->standart_apply_button,SIGNAL(clicked()),this,SLOT(default_params1()));
    connect(ui->extra_apply_button,SIGNAL(clicked()),this,SLOT(default_params2()));
}

MainWindow::~MainWindow()
{
    save_settings();
    delete ui;
}

void MainWindow::file_dialog()
{
     QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "../../../../../src/obj/.", "*.obj");
     if (!filename.isEmpty()) {
         default_params1();
         default_params2();

         ui->openGLWidget->geometries->filepath = filename;
         ui->openGLWidget->geometries->initCubeGeometry();
         ui->filename_label->setText(filename);

         ui->number_vertexes->display(ui->openGLWidget->geometries->vertex_label);
         ui->number_facets->display(ui->openGLWidget->geometries->facets_label);
     }
}

void MainWindow::save_settings()
{
    settings->setValue("filepath", ui->openGLWidget->geometries->filepath);

    settings->setValue("color_back", *ui->openGLWidget->color_back);
    settings->setValue("color", *ui->openGLWidget->color);
    settings->setValue("color_ver", *ui->openGLWidget->color_ver);

    settings->setValue("flag_dot_round", ui->openGLWidget->geometries->flag_dot_round);
    settings->setValue("flag_dot_vert", ui->openGLWidget->geometries->flag_dot_vert);
    settings->setValue("dot_size", ui->openGLWidget->geometries->dot_size);

    settings->setValue("line_width", ui->openGLWidget->geometries->line_width);
    settings->setValue("flag_dotted", ui->openGLWidget->GetFlagDotted());

    settings->setValue("project_ortho", ui->openGLWidget->GetFlagOrtho());
}

void MainWindow::load_settings()
{
    QString temp = settings->value("filepath").toByteArray().constData();
    QFile inputFile(temp);
    if (!inputFile.exists()) {
        return;
    } else {
        if (load_file) {
            ui->filename_label->setText(temp);
            ui->openGLWidget->geometries->filepath = temp;
        }
        default_params1();
        ui->openGLWidget->SetFlagOrtho(settings->value("project_ortho").toBool());
        if (ui->openGLWidget->GetFlagOrtho()) ui->parallel_projection->setChecked(1);
        else ui->central_projection->setChecked(1);

        ui->openGLWidget->geometries->initCubeGeometry();
        ui->openGLWidget->resizeGL(4, 3);

        ui->number_vertexes->display(ui->openGLWidget->geometries->vertex_label);
        ui->number_facets->display(ui->openGLWidget->geometries->facets_label);

        *ColorBack = settings->value("color_back").toByteArray().constData();
        ui->openGLWidget->color_back = ColorBack;
        *LineColor = settings->value("color").toByteArray().constData();
        ui->openGLWidget->color = LineColor;
        *VerColor = settings->value("color_ver").toByteArray().constData();
        ui->openGLWidget->color_ver = VerColor;

        ui->openGLWidget->geometries->flag_dot_round = settings->value("flag_dot_round").toBool();
        ui->openGLWidget->geometries->flag_dot_vert = settings->value("flag_dot_vert").toBool();
        if (ui->openGLWidget->geometries->flag_dot_round) ui->round_vertexes->setChecked(1);
        else if (ui->openGLWidget->geometries->flag_dot_vert) ui->square_vertexes->setChecked(1);
        else ui->none_vertexes->setChecked(1);
        ui->openGLWidget->geometries->dot_size = settings->value("dot_size").toDouble();
        ui->vertexes_size_box->setValue(ui->openGLWidget->geometries->dot_size);

        ui->openGLWidget->SetFlagDotted(settings->value("flag_dotted").toBool());
        if (ui->openGLWidget->GetFlagDotted()) ui->dotted_facets->setChecked(1);
        else ui->solid_facets->setChecked(1);
        ui->openGLWidget->geometries->line_width = settings->value("line_width").toDouble();
        ui->facets_width_box->setValue(ui->openGLWidget->geometries->line_width);

        ui->openGLWidget->updating();
    }
}

void MainWindow::default_params1()
{
    ui->scale_box->setValue(1.0);
    ui->scale_slider->setValue(100);

    ui->move_x_box->setValue(0);
    ui->move_x_slider->setValue(0);

    ui->move_y_box->setValue(0);
    ui->move_y_slider->setValue(0);

    ui->move_z_box->setValue(0);
    ui->move_z_slider->setValue(0);

    ui->rotate_x_box->setValue(0);
    ui->rotate_x_slider->setValue(0);

    ui->rotate_y_box->setValue(0);
    ui->rotate_y_slider->setValue(0);

    ui->rotate_z_box->setValue(0);
    ui->rotate_z_slider->setValue(0);

    ui->openGLWidget->geometries->initCubeGeometry();
    ui->openGLWidget->updating();
}

void MainWindow::default_params2()
{
    ui->openGLWidget->color_back = new QColor(214, 214, 214, 255);
    ui->openGLWidget->color = new QColor(0, 0, 0, 0);;
    ui->openGLWidget->color_ver = new QColor(17, 242, 0, 255);

    ui->openGLWidget->SetFlagDotted(0);
    ui->solid_facets->setChecked(1);
    ui->openGLWidget->geometries->line_width = 1.0;
    ui->facets_width_box->setValue(1.0);

    ui->openGLWidget->SetFlagOrtho(0);
    ui->central_projection->setChecked(1);
    ui->openGLWidget->resizeGL(4, 3);

    ui->openGLWidget->geometries->flag_dot_round = 0;
    ui->openGLWidget->geometries->flag_dot_vert = 0;
    ui->vertexes_size_box->setValue(1.0);
    ui->none_vertexes->setChecked(1);

    ui->openGLWidget->updating();
}

void MainWindow::widget_background()
{
    QColor temp = QColorDialog::getColor();
    if (temp.isValid()) {
        *ColorBack = temp;
        ui->openGLWidget->color_back = ColorBack;
        ui->openGLWidget->updating();
    }
}

void MainWindow::on_facets_color_button_clicked()
{
    QColor temp = QColorDialog::getColor();
    if (temp.isValid()) {
        *LineColor = temp;
        ui->openGLWidget->color = LineColor;
        ui->openGLWidget->updating();
    }
}

void MainWindow::on_vertexes_color_button_clicked()
{
    QColor temp = QColorDialog::getColor();
    if (temp.isValid()) {
        *VerColor = temp;
        ui->openGLWidget->color_ver = VerColor;
        ui->openGLWidget->updating();
    }
}



////////////////////////////



void MainWindow::on_move_x_slider_valueChanged(int value) { facade.Move(s21::ChangeModel::kMoveX, (double)value/100, 1, *ui); }
void MainWindow::on_move_x_box_valueChanged(double arg1) { facade.Move(s21::ChangeModel::kMoveX, arg1, 0, *ui); }
void MainWindow::on_move_y_slider_valueChanged(int value) { facade.Move(s21::ChangeModel::kMoveY, (double)value/100, 1, *ui); }
void MainWindow::on_move_y_box_valueChanged(double arg1) { facade.Move(s21::ChangeModel::kMoveY, arg1, 0, *ui); }
void MainWindow::on_move_z_slider_valueChanged(int value) { facade.Move(s21::ChangeModel::kMoveZ, (double)value/100, 1, *ui); }
void MainWindow::on_move_z_box_valueChanged(double arg1) { facade.Move(s21::ChangeModel::kMoveZ, arg1, 0, *ui); }



////////////////////////////



void MainWindow::on_rotate_x_slider_valueChanged(int value) { 
	facade.Rotate(s21::ChangeModel::kRotateX, (double)value/100, 1, *ui); 
}
void MainWindow::on_rotate_x_box_valueChanged(double arg1) { facade.Rotate(s21::ChangeModel::kRotateX, arg1, 0, *ui); }
void MainWindow::on_rotate_y_slider_valueChanged(int value) { facade.Rotate(s21::ChangeModel::kRotateY, (double)value/100, 1, *ui); }
void MainWindow::on_rotate_y_box_valueChanged(double arg1) { facade.Rotate(s21::ChangeModel::kRotateY, arg1, 0, *ui); }
void MainWindow::on_rotate_z_slider_valueChanged(int value) { facade.Rotate(s21::ChangeModel::kRotateZ, (double)value/100, 1, *ui); }
void MainWindow::on_rotate_z_box_valueChanged(double arg1) { facade.Rotate(s21::ChangeModel::kRotateZ, arg1, 0, *ui); }



////////////////////////////



void MainWindow::on_scale_slider_valueChanged(int value) { facade.Scale((double)value/100, 1, *ui); }
void MainWindow::on_scale_box_valueChanged(double arg1) { facade.Scale(arg1, 0, *ui); }


////////////////////////////


void MainWindow::on_parallel_projection_clicked()
{
    ui->openGLWidget->SetFlagOrtho(1);
    ui->openGLWidget->resizeGL(4, 3);
    ui->openGLWidget->updating();
}

void MainWindow::on_central_projection_clicked()
{
    ui->openGLWidget->SetFlagOrtho(0);
    ui->openGLWidget->resizeGL(4, 3);
    ui->openGLWidget->updating();
}


////////////////////////////


void MainWindow::on_dotted_facets_clicked() { ui->openGLWidget->SetFlagDotted(1); }

void MainWindow::on_solid_facets_clicked() { ui->openGLWidget->SetFlagDotted(0); }

void MainWindow::on_facets_width_box_valueChanged(double arg1)
{
    ui->openGLWidget->geometries->line_width = arg1;
    ui->openGLWidget->updating();
}


////////////////////////////


void MainWindow::on_vertexes_size_box_valueChanged(double arg1)
{
    ui->openGLWidget->geometries->dot_size = arg1;
    ui->openGLWidget->updating();
}

void MainWindow::on_round_vertexes_clicked()
{
    ui->openGLWidget->geometries->flag_dot_vert = 1;
    ui->openGLWidget->geometries->flag_dot_round = 1;
}

void MainWindow::on_square_vertexes_clicked()
{
    ui->openGLWidget->geometries->flag_dot_vert = 1;
    ui->openGLWidget->geometries->flag_dot_round = 0;
}

void MainWindow::on_none_vertexes_clicked()
{
    ui->openGLWidget->geometries->flag_dot_vert = 0;
    ui->openGLWidget->geometries->flag_dot_round = 0;
}


////////////////////////////


void MainWindow::on_save_image_button_clicked()
{
    QDate date;
    QTime time;
    QString curtime = time.currentTime().toString();
    QString curdate = date.currentDate().toString();
    QString filepath = QFileDialog::getExistingDirectory();
    ui->openGLWidget->grabFramebuffer().save(filepath + "/" + curdate + curtime + ".BMP", NULL, 100);
    ui->openGLWidget->grabFramebuffer().save(filepath + "/" + curdate + curtime + ".JPG", NULL, 100);
}

void MainWindow::on_save_gif_button_clicked()
{
    path = QFileDialog::getExistingDirectory();
    gif = new QGifImage;
    photo = new QImage;
    time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    timer->start(100);
}

void MainWindow::TimerSlot()
{
    QDate date;
    QTime currtime;
    QString curtime = currtime.currentTime().toString();
    QString curdate = date.currentDate().toString();
    time++;
    *photo = ui->openGLWidget->grabFramebuffer();
    gif->addFrame(*photo);
    if (time == 50) {
        timer->stop();
        gif->save(path + "/" + curdate + " " + curtime + ".GIF");
    }
}


////////////////////////////


void MainWindow::on_load_clicked()
{
    load_file = 1;
    load_settings();
}


void MainWindow::on_load_set_clicked()
{
    load_file = 0;
    load_settings();
}

