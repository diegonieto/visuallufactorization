#include "lu_main_window.h"
#include "ui_lu_main_window.h"
#include "Squarematrix.hpp"
#include <sstream>

LU_main_window::LU_main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LU_main_window)
{
    ui->setupUi(this);
    setWindowTitle("Visual LU factorization");
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
    for ( unsigned int i=0; i<static_cast<unsigned int>(table.rowCount()); i++ )
    {
        for ( unsigned int j=0; j<static_cast<unsigned int>(table.columnCount()); j++ )
        {
            try {
                if ( table.item(i,j) != NULL ) {
                    tmp = table.item(i,j)->text().toDouble();
                    matrix.set(i,j,tmp);
                } else
                    throw -20;
            } catch (int) {
                ui->statusBar->showMessage("Please, initialize the matrix");
                return false;
            }
        }
    }

    ui->statusBar->showMessage("Matrix readed");
    return true;
}

void LU_main_window::on_pushButtonFactorize_clicked()
{
    if (readMatrix(*(ui->tableWidgetMatrix), *_matrix) ) {
        // Factorize
        _matrix->lu();
        ui->statusBar->showMessage("Matrix factorized");

        updateQTableWidgetFromMatrix(*(ui->tableWidgetMatrix), *_matrix);
    }
}

void LU_main_window::fillMatrix(QTableWidget *qtableWidget)
{
    unsigned int nrows = qtableWidget->rowCount();
    unsigned int ncols = qtableWidget->columnCount();

    std::ostringstream buffer;
    int totalValue;

    for ( unsigned int i=0; i<nrows; i++ )
    {
        for ( unsigned int j=0; j<ncols; j++ )
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            totalValue = 1+(i*ncols+j);
            std::ostringstream buffer;
            buffer << totalValue;
            newItem->setText(buffer.str().c_str());
            qtableWidget->setItem(i, j, newItem);
        }
    }
}

void LU_main_window::updateQTableWidgetFromMatrix(QTableWidget &qTableWidget, Matrix<NumericType> &matrix)
{
    for ( unsigned int i=0; i<static_cast<unsigned int>(qTableWidget.rowCount()); i++ )
    {
        for ( unsigned int j=0; j<static_cast<unsigned int>(qTableWidget.columnCount()); j++ )
        {
            // Update C values
            std::ostringstream buffer;
            buffer << matrix.get(i, j);
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setText(buffer.str().c_str());
            qTableWidget.setItem(i, j, newItem);
        }
    }
}

void LU_main_window::on_pushButtonFill_clicked()
{
    fillMatrix(ui->tableWidgetMatrix);
}
