#include "lu_main_window.h"
#include "ui_lu_main_window.h"
#include "Squarematrix.hpp"

LU_main_window::LU_main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LU_main_window)
{
    ui->setupUi(this);
    initialize();
}

LU_main_window::~LU_main_window()
{
    delete ui;
}

void LU_main_window::restart()
{
    // QtTableWidget initialization
    ui->tableWidgetMatrix->setRowCount(ui->spinSize->value());
    ui->tableWidgetMatrix->setColumnCount(ui->spinSize->value());


    // Matrix initialization

    if ( _matrix != NULL ) {
        delete _matrix;
        _matrix = NULL;
    }
    _matrix = new SquareMatrix<NumericType>(ui->spinSize->value());
}

void LU_main_window::initialize()
{
    _matrix = NULL;

    // SpinSize initialization (only once)
    ui->spinSize->setMaximum(maxSize);
    ui->spinSize->setMinimum(minSize);
    ui->spinSize->setValue(defaultSize);
}

void LU_main_window::changeSize(const unsigned int size)
{
    ui->spinSize->setValue(size);
    restart();
}

void LU_main_window::on_spinSize_valueChanged(const QString &arg1)
{
    changeSize(arg1.toInt());
}

bool LU_main_window::readMatrix(QTableWidget &table, SquareMatrix<NumericType> &matrix)
{
    matrix.setZero();

    // Read values from widgets
    NumericType tmp;
    for ( unsigned int i=0; i<_matrix->getSize(); i++ )
    {
        for ( unsigned int j=0; j<_matrix->getSize(); j++ )
        {
            try {
                if ( table.item(i,j) != NULL ) {
                    tmp = table.item(i,j)->text().toDouble();
                    matrix.set(i,j,tmp);
                } else
                    throw -20;
            } catch (int) {
                ui->statusBar->showMessage("Please, initialize the matrices");
                return false;
            }
        }
    }

    ui->statusBar->showMessage("Matrix readed");
    return true;
}

void LU_main_window::on_pushButtonFactorize_clicked()
{
    readMatrix(*(ui->tableWidgetMatrix), *_matrix);
}
