#ifndef LU_MAIN_WINDOW_H
#define LU_MAIN_WINDOW_H

#include <QMainWindow>
#include "Squarematrix.hpp"
#include <QTableWidget>

const unsigned char defaultSize = 3;
const unsigned char minSize = 3;
const unsigned char maxSize = 8;
typedef double NumericType;

namespace Ui {
class LU_main_window;
}

class LU_main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit LU_main_window(QWidget *parent = 0);
    ~LU_main_window();
    void initialize();
    void restart();
    void changeSize(const unsigned int size);
    bool readMatrix(QTableWidget &table, SquareMatrix<NumericType> &matrix);
    void updateQTableWidgetFromMatrix(QTableWidget &qTableWidget, Matrix<NumericType> &matrix);
    void fillMatrix(QTableWidget *qtableWidget);

private slots:
    void on_spinSize_valueChanged(const QString &arg1);

    void on_pushButtonFactorize_clicked();

    void on_pushButtonFill_clicked();

private:
    Ui::LU_main_window *ui;
    SquareMatrix<NumericType> *_matrix;
    bool _initialized;
};

#endif // LU_MAIN_WINDOW_H
