#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handle_rc(const err_t rc)
{
    if (!rc)
    {
        request_t draw_request = {.action = DRAW};
        handle_request(draw_request);
    }
    else
    {
        handle_error(rc);
    }
}

err_t MainWindow::read_params(QLineEdit *e1, QLineEdit *e2, QLineEdit *e3, transform_t &params)
{
    bool ok1, ok2, ok3;

    params.x = e1->text().toDouble(&ok1);
    params.y = e2->text().toDouble(&ok2);
    params.z = e3->text().toDouble(&ok3);

    if (!ok1 || !ok2 || !ok3)
        return ERR_TRANSFORM_READ;

    return ERR_OK;
}

void MainWindow::on_load_btn_clicked()
{
    request_t load_request = {.action = LOAD, .filename = "model.txt"};
    
    err_t rc = handle_request(load_request);

    handle_rc(rc);
}

void MainWindow::on_move_btn_clicked()
{
    transform_t move = {0, 0, 0};
    err_t rc = read_params(ui->dx_lineEdit, ui->dy_lineEdit, ui->dz_lineEdit, move);

    if (!rc)
    {
        request_t request = {.action = MOVE, .transform = move};
        rc = handle_request(request);
    }

    handle_rc(rc);
}

void MainWindow::on_scale_btn_clicked()
{
    transform_t scale = {0, 0, 0};
    err_t rc = read_params(ui->kx_lineEdit, ui->ky_lineEdit, ui->kz_lineEdit, scale);

    if (!rc)
    {
        request_t request = {.action = SCALE, .transform = scale};
        rc = handle_request(request);
    }

    handle_rc(rc);
}

void MainWindow::on_turn_btn_clicked()
{
    transform_t turn = {0, 0, 0};
    err_t rc = read_params(ui->xa_lineEdit, ui->ya_lineEdit, ui->za_lineEdit, turn);

    if (!rc)
    {
        request_t request = {.action = TURN, .transform = turn};
        rc = handle_request(request);
    }

    handle_rc(rc);
}

