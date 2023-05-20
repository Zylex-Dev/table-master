#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setRange(1, MAX_MAS_SIZE);
    ui->label_Max->hide();
    ui->label_Min->hide();
    ui->label_Sum->hide();
    ui->label_Average->hide();
    ui->label_SearchCount->hide();
    no_auto_change = true;
    QWidget::showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column) // изменили ячейку
{
    if (no_auto_change)
    {
        bool flag;
        ui->tableWidget->item(row,column)->text().toDouble(&flag);
        if (flag)
        {
            ui->tableWidget->item(row,column)->setBackground(Qt::green);
            ui->label_Max->hide();
            ui->label_Min->hide();
            ui->label_Sum->hide();
            ui->label_Average->hide();
            ui->label_SearchCount->clear();
            ui->textEdit_Coincidences->clear();
            ui->lineEdit_Search->clear();
        }
        else
        {
            ui->tableWidget->item(row,column)->setBackground(Qt::red);
            ui->label_Max->hide();
            ui->label_Min->hide();
            ui->label_Sum->hide();
            ui->label_Average->hide();
            ui->label_SearchCount->clear();
            ui->textEdit_Coincidences->clear();
            ui->lineEdit_Search->clear();
        }
    }
}

void MainWindow::on_pushButton_Addrow_clicked() // добавить строку
{
    ui->spinBox->setValue(ui->spinBox->value()+1);
    ui->label_Max->hide();
    ui->label_Min->hide();
    ui->label_Sum->hide();
    ui->label_Average->hide();
    ui->label_SearchCount->clear();
    ui->textEdit_Coincidences->clear();
    //ui->lineEdit_Search->clear();
}

void MainWindow::on_pushButton_DelRow_clicked() // удалить строку
{
    ui->spinBox->setValue(ui->spinBox->value()-1);
    ui->label_Max->hide();
    ui->label_Min->hide();
    ui->label_Sum->hide();
    ui->label_Average->hide();
    ui->label_SearchCount->clear();
    ui->textEdit_Coincidences->clear();
    //ui->lineEdit_Search->clear();
}

void MainWindow::on_spinBox_valueChanged(int arg1) // изменяем спинбокс
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_pushButton_Random_clicked() // кнопка рандома
{
    no_auto_change = false;
    int row=ui->tableWidget->rowCount();
    int value;

    ui->label_Max->hide();
    ui->label_Min->hide();
    ui->label_Sum->hide();
    ui->label_Average->hide();
    ui->label_SearchCount->clear();
    ui->textEdit_Coincidences->clear();
    ui->lineEdit_Search->clear();

    for (int i=0;i<row;i++)
    {
        if (ui->tableWidget->item(i,0)==nullptr)
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу
        }
        ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);

        value=rand()%201-100; // от -100 до 100
        ui->tableWidget->item(i,0)->setText(QString::number(value));
    }
    no_auto_change = true;
}

void MainWindow::on_pushButton_Sum_clicked() // кнопка суммы
{
    no_auto_change = false;
    ui->label_Sum->show();
    int row=ui->tableWidget->rowCount();
    double sum=0;
    bool flag;
    bool error = false;

    for (int i=0;i<row;i++)
        if (ui->tableWidget->item(i,0) != nullptr) //проверка существования ячейки
        {//есть ячейка
            sum+=ui->tableWidget->item(i,0)->text().toDouble(&flag);
            if (flag)
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::green);
            }
            else
            {
                //ui->label_Sum->hide();
                error = true;
                ui->tableWidget->item(i,0)->setBackground(Qt::yellow);
                //QMessageBox::information(this, "Error", "Неправильно введенное значение", QMessageBox::Ok);
            }
        }
        else
        { // нет ячейки
            //создаем
            ui->label_Sum->hide();
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,0)->setBackground(Qt::yellow);
        }

    if (error == true)
    {
        ui->label_Sum->hide();
        QMessageBox::information(this, "Error", "Неправильно введенное значение", QMessageBox::Ok);
    }
    ui->label_Sum->setNum(sum);
    no_auto_change = true;
}

void MainWindow::on_pushButton_Max_clicked() // кнопка поиска макс знач
{
    no_auto_change = false;
    ui->label_Max->show();
    int row = ui->tableWidget->rowCount();
    double max;
    bool error=false;

    for(int i=0; i < row; i++)
    {
        //Получаем указатель
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);

        //проверяем ,что память выделена
        if (item==nullptr)
        {
            item= new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,item);
        }

        //Получаем значение
        QString text = item->text();
        bool flag=false;
        double val=text.toDouble(&flag);

        if(flag) //Если знач корректно
        {
            item->setBackground(Qt::green);
        }
        else {
            error=true;
            item->setBackground(Qt::yellow);
        }
        if(i==0)
        {
            max=val;
        }
        if (val>max)
        {
            max=val;
        }

    }
    if (error==true)
    {
        ui->label_Max->hide();
        QMessageBox::information(this,"Error","Введено неверное значение", QMessageBox::Ok);
    }
    else
    {
        ui->label_Max->setNum(max);
    }
    no_auto_change = true;
}

void MainWindow::on_pushButton_Min_clicked() // кнопка поиска мин знач
{
    no_auto_change = false;
    ui->label_Min->show();
    int row = ui->tableWidget->rowCount();
    double min;
    bool error=false;

    for(int i=0; i < row; i++)

    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);

        //проверяем ,что память выделена
        if (item==nullptr)
        {
            item= new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,item);
        }

        //Получаем значение
        QString text = item->text();
        bool flag=false;
        double val=text.toDouble(&flag);

        if(flag) //Если знач корректно
        {
            item->setBackground(Qt::green);
        }
        else
        {
            error=true;
            item->setBackground(Qt::yellow);
        }
        if(i == 0)
        {
            min=val;
        }
        if (val<min)
        {
            min=val;
        }

    }
    if (error==true)
    {
        ui->label_Min->hide();
        QMessageBox::information(this,"Error","Введено неверное значение", QMessageBox::Ok);
    }
    else
    {
        ui->label_Min->setNum(min);
    }
    no_auto_change = true;
}

void MainWindow::on_pushButton_Average_clicked() // кнопка поиска сред знач
{
    no_auto_change = false;
    ui->label_Average->show();
    int row=ui->tableWidget->rowCount();
    double sum = 0;
    bool flag;
    bool error = false;

    for (int i=0;i<row;i++)
        if (ui->tableWidget->item(i,0) != nullptr) //проверка существования ячейки
        {//есть ячейка
            sum += ui->tableWidget->item(i,0)->text().toDouble(&flag);
            if (flag)
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::green);
            }
            else
            {
                //ui->label_Sum->hide();
                error = true;
                ui->tableWidget->item(i,0)->setBackground(Qt::yellow);
                //QMessageBox::information(this, "Error", "Неправильно введенное значение", QMessageBox::Ok);
            }
        }
        else
        { // нет ячейки
            //создаем
            ui->label_Average->hide();
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,0)->setBackground(Qt::magenta);
        }
    if (error == true)
    {
        ui->label_Average->hide();
        QMessageBox::information(this, "Error", "Неправильно введенное значение", QMessageBox::Ok);
    }
    int amount = ui->spinBox->value() * 2;
    double average = (sum / amount);
    ui->label_Average->setNum(average);
    //ui->label_Average->setNum(sum / amount);
    //ui->label_Average->setText(QString::number(sum / amount) + "." + QString::number(sum % amount)); // (sum / amount) + (sum % amount)
    no_auto_change = true;
}

void MainWindow::on_pushButton_Clear_clicked() // кнопка очистки
{
    no_auto_change = false;
    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        if (ui->tableWidget->item(i,0) != nullptr)
        {
            ui->tableWidget->item(i,0)->setText("");
            ui->tableWidget->item(i,0)->setBackground(Qt::white);
        }
    }
    ui->label_Max->clear();
    ui->label_Min->clear();
    ui->label_Sum->clear();
    ui->label_Average->clear();
    ui->label_SearchCount->clear();
    ui->textEdit_Coincidences->clear();
    ui->lineEdit_Search->clear();

    no_auto_change = true;
}

void MainWindow::on_pushButton_Bubble_clicked() // КНОПКА сортировка пузырек DONE
{
    no_auto_change = false;


    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }



    double mas[200]; // создаем массив в 200 элементов

    // делаем считывание массива
    bool flagError; // флаг наличия ошибок
    int size = readMassive(mas, &flagError); // используем функцию для считывания массива

    if (flagError) // если есть ошибки
    {
        QMessageBox::warning(this, "Error", "Неккоректные значения!");
    }
    else
    { // если массив корректный
        // сортировка
        sortBubble(mas, size);

        // вывод отсортированного массива в таблицу
        writeMassive(mas, size);
    }
    no_auto_change = true;
}

void MainWindow::on_pushButton_Gnome_clicked() // КНОПКА сортировка гномья DONE
{
    no_auto_change = false;



    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }



    double mas[200]; // создаем массив в 200 элементов

    // делаем считывание массива
    bool flagError; // флаг наличия ошибок
    int size = readMassive(mas, &flagError); // используем функцию для считывания массива

    if (flagError) // если есть ошибки
    {
        QMessageBox::warning(this, "Error", "Неккоректные значения!");
    }
    else
    { // если массив корректный
        // сортировка
        sortGnome(mas, size);

        // вывод отсортированного массива в таблицу
        writeMassive(mas, size);
        QMessageBox::information(this,"Congratulations!", "Гном успешно расставил горшки!!!");

    }
    no_auto_change = true;
}

void MainWindow::on_pushButton_Quick_clicked() // КНОПКА сортировка быстрая
{
    no_auto_change = false;


    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }



    double mas[200]; // создаем массив в 200 элементов

    // делаем считывание массива
    bool flagError; // флаг наличия ошибок
    int size = readMassive(mas, &flagError); // используем функцию для считывания массива

    if (flagError) // если есть ошибки
    {
        QMessageBox::warning(this, "Error", "Неккоректные значения!");
    }
    else
    { // если массив корректный
        // сортировка
        sortQuick(mas, size);

        // вывод отсортированного массива в таблицу
        writeMassive(mas, size);

    }
    no_auto_change = true;
}

void MainWindow::on_pushButton_Comb_clicked() // КНОПКА сортировка расческа DONE
{
    no_auto_change = false;



    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }



    double mas[200]; // создаем массив в 200 элементов

    // делаем считывание массива
    bool flagError; // флаг наличия ошибок
    int size = readMassive(mas, &flagError); // используем функцию для считывания массива

    if (flagError) // если есть ошибки
    {
        QMessageBox::warning(this, "Error", "Неккоректные значения!");
    }
    else
    { // если массив корректный
        // сортировка
        sortComb(mas, size);

        // вывод отсортированного массива в таблицу
        writeMassive(mas, size);
    }
    no_auto_change = true;

}

void MainWindow::on_pushButton_Monke_clicked() // КНОПКА сортировка обезьянья DONE
{
    no_auto_change = false;



    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }




    double mas[200]; // создаем массив в 200 элементов

    // делаем считывание массива
    bool flagError; // флаг наличия ошибок
    int size = readMassive(mas, &flagError); // используем функцию для считывания массива

    if (flagError) // если есть ошибки
    {
        QMessageBox::warning(this, "Error", "Неккоректные значения!");
    }
    else
    { // если массив корректный
        // сортировка
        if (ui->tableWidget->rowCount()<= 10)
        {
            sortMonke(mas, size);

            // вывод отсортированного массива в таблицу
            writeMassive(mas, size);
        }
        else
        {
            QMessageBox::information(this,"Внимание!","Кол-во строк больше 10, может занять много времени");
        }

    }
    no_auto_change = true;
}

void MainWindow::writeMassive(double *mas, int size) // функция для записи массива в таблицу
{
    // вывод отсортированного массива в таблицу

    for (int i = 0; i < size; i++)
    {
        QString str;
        str.setNum(mas[i]);

        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        item->setText(str); // выводим строковое значение массива в ячейку таблицу
    }
}

int MainWindow::readMassive(double *mas, bool *flagError) // функция для чтения массива
{
    *flagError = false; // флаг наличия ошибок

    int size = ui->tableWidget->rowCount(); // получаем кол-во строк
    for (int i = 0; i < size; i ++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);

        if (item == nullptr) // если ячейка пустая
        {
            *flagError = true; // ставит что ошибка есть
            item = new QTableWidgetItem; // выделяем память под ячейку
            ui->tableWidget->setItem(i, 0, item); // задаем созданную ячейку в таблицу
        }
        QString str = item->text(); // получаем текстовое значение ячейки
        bool ok;
        double value = str.toDouble(&ok); // переводим строковое значение в число
        if (ok) // если число корректное
        {
            mas[i] = value; // записываем значение в массив
        }
        else // если число не корректное
        {
            *flagError = true; // ставим флаг ошибки
        }
    }
    return size; // возвращаем размер массива
}

void MainWindow::sortComb(double *mas, int size) // ФУНКЦИЯ Сортировки Расчески +-DONE
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (mas[i]<mas[j])
            {
                double temp = mas[i];
                mas[i] = mas[j];
                mas[j] = temp;
            }
        }
    }
}

void MainWindow::sortGnome(double *mas, int size) // ФУНКЦИЯ Сортировки Гномья DONE
{
    int i = 0;
    while (i < size)
    {
        if ( (i == 0) or (mas[i-1]<=mas[i]))
        {
            i = i + 1;
        }
        else
        {
            int j = i - 1;
            double temp = mas[i];
            mas[i] = mas[j];
            mas[j] = temp;
            i = j;
        }
    }
}

void MainWindow::sortMonke(double *mas, int size) // ФУНКЦИЯ Сортировки Обезьянья DONE
{
    while (not_sorted(mas, size) )
    {
          shuffle(mas, size);
    }
}

void MainWindow::sortQuick(double *mas, int size) // ФУНКЦИЯ Сортировки Быстрая DONE
{
    // указатели в начало и конец массива
    int i = 0; // начало массива
    int j = size - 1; // конец массива
    int mid = mas[size / 2]; // опорный элемент - центральный элемент массива

    // делим массив
    do
    {
        // пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        // В левой части массива пропускаем (оставляем на месте) элементы, которые меньше
        while (mas[i] < mid)
        {
            i++;
        }

        // В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > mid)
        {
            j--;
        }

        // Меняем элементы местами
        if (i <= j)
        {
            double temp = mas[i];
            mas[i] = mas[j];
            mas[j] = temp;

            i++;
            j--;
        }
    } while (i <= j);


    // Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0)
    {// Левая часть
        sortQuick(mas, j + 1);
    }
    if (i < size)
    {// Прававя часть
        sortQuick(&mas[i], size - i);
    }
}

void MainWindow::sortBubble(double *mas, int size) // ФУНКЦИЯ Сортировки Пузырьком DONE
{
    int i = 0;

    while (i < size - 1)
    {
        int j = i + 1;

        while (j < size)
        {
            if (mas[i] > mas[j])
            {
                double temp = mas[i];
                mas[i] = mas[j];
                mas[j] = temp;
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

bool MainWindow::not_sorted(double *mas, int size) // функция проверки отсортирован ли массив
{
   while ( --size > 0 )
   {
      if ( mas[size - 1] > mas[size] )
      {
         return true;
      }
   }
   return false;
}

void MainWindow::shuffle(double *mas, int size) // функция перемешивания массива
{
    for (int i = 0; i < size; ++i)
    {
        // std::swap(mas[i], mas[(rand() % size)]); // способ с использованием пространства имен std (стандартная библ.)
        //                                             и метода swap
        int temp, r;
        for(int i=0; i < size; i++)
        {
            temp = mas[i];
            r = rand() % size;
            mas[i] = mas[r];
            mas[r] = temp;
        }

    }

}

void MainWindow::on_pushButton_Duplicates_clicked() // кнопка удаления дубликатов
{
    no_auto_change = false;


    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }


    int size = ui->tableWidget->rowCount();
    bool error = false;  // изначально ошибки нет
    double *mas = new double [size]; // динамически создаем массив

    readMassive(mas, &error);

    if (error) // если есть ошибки
    {
        QMessageBox::information(this, "Ошибка", "Таблица заполнена некорректно!");

        delete [] mas; // удаляем массив
        mas = nullptr; // зануляем указатель

        return;
    }

    if (not_sorted(mas,size)) // если массив не отсортирован
    {
        QMessageBox::warning(this, "Ошибка", "Сначала отсортируйте массив");
        delete [] mas;
        mas = nullptr;
        return;
    }
    // удаление дубликатов
    int noDublicateCount = 1;

    for (int i = 1; i < size ; i++)
    {
        if (abs(mas[i] - mas[i-1]) > 1e-7) // сравниваем на неравенство числа
        {
            noDublicateCount ++; // если числа разные, увеличиваем кол-во
        }
    }

    // зная точное кол-во, создаем массив без дубликатов
    double *masNoDublicates = new double [noDublicateCount];
    int k = 1; // номер элемента, в который записывает число в массив без дубликатов

    masNoDublicates[0] = mas[0]; // первый элемент всегда уникальный, поэтому добавляем его

    for (int i = 1; i < size; i++)
    {
        if (abs(mas[i] - mas[i-1]) > 1e-7) // сравниеваем на неравенство числа
        {
            masNoDublicates[k] = mas[i]; // записываем в массив без дубликатов
            k++; //  смещаем на 1 номер элемента

        }
    }
    // выводим в таблицу массив без дубликатов
    ui->spinBox->setValue(noDublicateCount); // размер таблицы равен размеру массива без дубликатов

    writeMassive(masNoDublicates, noDublicateCount); // выводим массив без дубликатов

    delete [] mas;
    delete [] masNoDublicates;
    mas = nullptr;
    masNoDublicates = nullptr;

    no_auto_change = true;


}

void MainWindow::on_pushButton_Search_clicked() // поиск значения в массиве
{
    no_auto_change = false;
    int row = ui->tableWidget->rowCount();
    for (int i = 0; i < row; i ++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white); // для того, чтобы при новом поиске старая подсветка убиралась
    }

    double mas[200];
    int size = ui->tableWidget->rowCount();
    bool error = false; // изначально ошибки нет

    readMassive(mas, &error);
    if (error)
    {
        QMessageBox::information(this, "Ошибка", "Таблица заполнена некоррректно!");
        ui->label_SearchCount->clear();
        ui->textEdit_Coincidences->clear();

        return;
    }

    // выполняем поиск
    bool ok = false;
    double searchValue = ui->lineEdit_Search->text().toDouble(&ok); // считываем искомое число (ключ)
    if (!ok)
    {// если не ок :(
        QMessageBox::information(this, "Ошибка", "Некорреткное искомое значение!");
        ui->label_SearchCount->clear();
        ui->textEdit_Coincidences->clear();

        return;


    }
    int count = 0; // кол=во найденных элементов (одинаковых)
    QString SearchRows; // строка для записи номеров строк, в которых было найдено искомое значение


    if (!not_sorted(mas,size)) // если массив отсортирован
    {

        // бинарный поиск
        /*BinarySearch(mas,size,searchValue, &ok);
        if (ok)
        {
            for (int i = 0; i<size; i++)
            {
                count++; // увеличиваем кол-во найденных элементов на 1

                int foundRow = i + 1; // номер найденной строки
                QString str;
                str.setNum(foundRow); // переводим номер найденной строки в номер

                SearchRows += str + " "; // добавляем номер найденной строки в общий список


                ui->tableWidget->item(i, 0)->setBackground(Qt::yellow); // подсвечиваем найденные элементы

            }
        }
        */


        /*
        bool flag;
        int find_num = ui-> lineEdit_Search-> text().toInt(&flag);
        int row = ui-> tableWidget-> rowCount();
        int column = 0;
        int *mas = new int [row];
        int bad_value = -1;





        bool error = false;
        for (int i = 0; i<row; i++)
        {
            QTableWidgetItem * item = ui-> tableWidget->item(i,column);

            // проверяем, что память под ячейку выделена
            if (item == nullptr)
            {

                item = new QTableWidgetItem();
                ui-> tableWidget-> setItem(i,column,item);

            }
            if (ui->tableWidget->item(i,column)!=nullptr)
            {
                mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
                if (mas[i]>100)
                    mas[i]= 98989;
                if (!flag)
                {
                    error = true;

                    bad_value= i;
                    //ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                    ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                    mas[bad_value]= 98989;
                }

                else
                {
                    ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
                }

            }
            else
            {
                QTableWidgetItem * ti; //создали указатель
                ti =  new QTableWidgetItem(); //выделяем память
                ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
                //красим
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

            }


        }
        QString q;
        if (!error)
        {
            int count = 0;    
            int l = 0;
            int r = row; // в этом случае присваивается именно n
            int mid;

            while (l < r)
            {
                count+=1;
                mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]

                if (mas[mid] > find_num)
                    r = mid-1; // проверяем, какую часть нужно отбросить с поиска
                else if (mas[mid] < find_num)
                    l = mid+1;
                else
                    break;
            }


            while (mas[mid]==find_num)
            {
                mid-=1;
            }
            mid+=1;
            while (mas[mid]==find_num)
            {
                q +=  QString:: number(mid+1) +" ";
                mid+=1;
                ui-> label_SearchCount-> setNum(count);
            }

        }


                while (mas[mid]==find_num)
                {
                    mid-=1;
                }
                mid+=1;
                while (mas[mid]==find_num)
                {
                    q +=  QString:: number(mid+1) +" ";
                    mid+=1;
                    ui-> label_SearchCount-> setNum(count);
                }


            }

            else
            {
                QMessageBox::information(this,"Ошибка","Отсортируйте список!");


            }


        }


        else
        {
            QPixmap pix (":/pix/img/error.png");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            QMessageBox::information (this, "Ошибка", "Введены неверные значения");


        }
         int end_time= clock();
         int time = end_time -time_start;
         ui-> label_time-> setNum(time/1000);
         delete [] mas;
         mas = nullptr;
         */






    }

    else
    {// если массив не отсортирован
        // используем перебор (линейный поиск)
        for (int i = 0; i < size; i ++)
        {
            if (abs(mas[i] - searchValue) < 1e-7) // сравниваем два вещественных числа на равенство
            {
                count++; // увеличиваем кол-во найденных элементов на 1

                int foundRow = i + 1; // номер найденной строки
                QString str;
                str.setNum(foundRow); // переводим номер найденной строки в номер

                SearchRows += str + " "; // добавляем номер найденной строки в общий список


                ui->tableWidget->item(i, 0)->setBackground(Qt::blue); // подсвечиваем найденные элементы


            }
        }
    }
    // вывод
    ui->label_SearchCount->show();
    ui->label_SearchCount->setNum(count); // кол-во найденных элементов по запросу
    ui->textEdit_Coincidences->setText(SearchRows); //
    no_auto_change = true;
}

void MainWindow::BinarySearch(double *mas, int n, int k, bool flag) //??????????????????????????????????????????????
{
    int L = 0;
    int R = n;
    int m;
    int z = 0;
    flag = false;

    while (L < R)
    {
        z++;
        m = (L + R) / 2;
        if (k > mas[m])
        {
            L = m;
        }
        if (k < mas[m])
        {
            R = m;
        }
        if (k == mas[m])
        {
            break;
            flag = true;
        }
    }
}

void MainWindow::on_pushButton_OpenTxt_clicked() // OPEN TXT
{

}

void MainWindow::on_pushButton_OpenBin_clicked() // OPEN BIN
{

}

void MainWindow::on_pushButton_SaveTxt_clicked() // SAVE TXT
{

}

void MainWindow::on_pushButton_SaveBin_clicked() // SAVE BIN
{

}