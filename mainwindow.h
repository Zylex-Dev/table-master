#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <cmath>

#define MAX_MAS_SIZE 200 //максимальный размер массива


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Функиця принимает на вход ссылку на массив
    // функция возвращает кол-во элементов в массиве/таблице (целые числа
    // функция возвращает корректность считанных данных через flagError
    int readMassive (double *mas, bool *flagError); // функция для чтения массива

    // функция принимает на вход ссылку на массив и его кол-во элементов
    void writeMassive (double *mas, int size); // функция для записи массива в таблицу

    // функция принимает на вход ссылку на массив
    void sortComb (double *mas, int size); // функция Сортировки Расчески

    void sortBubble (double *mas, int size); // функция Сортировки Пузырьком

    void sortGnome (double *mas, int size); // функция Сортировки Гномья

    void sortQuick (double *mas, int size); // функция Сортировки Быстрая

    void sortMonke (double *mas, int size); // функция Сортировки Обезьянья

    bool not_sorted(double *mas, int size); // функция для проверки отсортирован ли массив

    void shuffle(double *mas, int size); // функция рандомного перемешивания массива для bogo sort

    void BinarySearch (double *mas, int n, int k, bool flag);

private slots:
    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_Addrow_clicked();

    void on_pushButton_DelRow_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_Random_clicked();

    void on_pushButton_Sum_clicked();

    void on_pushButton_Max_clicked();

    void on_pushButton_Min_clicked();

    void on_pushButton_Average_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Bubble_clicked();

    void on_pushButton_Gnome_clicked();

    void on_pushButton_Quick_clicked();

    void on_pushButton_Comb_clicked();

    void on_pushButton_Monke_clicked();

    void on_pushButton_Duplicates_clicked();

    void on_pushButton_Search_clicked();


    void on_pushButton_OpenTxt_clicked();

    void on_pushButton_OpenBin_clicked();

    void on_pushButton_SaveTxt_clicked();

    void on_pushButton_SaveBin_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change; // флаг ручного/автоматического заполнения таблицы
    int mas_table [MAX_MAS_SIZE][MAX_MAS_SIZE]; // наш массив для работы
};

#endif // MAINWINDOW_H
