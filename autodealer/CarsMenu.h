#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Car 
{
public:
    string name;
    int year;
    double engineSize;
    double price;

    Car(const string& n, int y, double es, double p)
        : name(n), year(y), engineSize(es), price(p) {}

    void display() const 
    {
        cout << "Name: " << name << ", Year: " << year << ", Engine Size: " << engineSize << ", Price: " << price << endl;
    }

    // Функтор для сравнения автомобилей по году выпуска
    struct CompareByYear
    {
        bool operator()(const Car& car1, const Car& car2) const 
        {
            return car1.year < car2.year;
        }
    };

    // Функтор для сравнения автомобилей по цене
    struct CompareByPrice 
    {
        bool operator()(const Car& car1, const Car& car2) const 
        {
            return car1.price < car2.price;
        }
    };

    //  Методы для сохранения и загрузки из файла
    static void saveToFile(const vector<Car>& cars, const string& filename)
    {
        ofstream file(filename);
        if (file.is_open()) 
        {
            for (const Car& car : cars)
            {
                file << car.name << ' ' << car.year << ' ' << car.engineSize << ' ' << car.price << endl;
            }
            file.close();
        }
        else 
        {
            cerr << "Ошибка при открытии файла для записи." << endl;
        }
    }

    static void loadFromFile(vector<Car>& cars, const string& filename) 
    {
        ifstream file(filename);
        if (file.is_open()) 
        {
            cars.clear();
            string name;
            int year;
            double engineSize, price;
            while (file >> name >> year >> engineSize >> price) 
            {
                cars.push_back(Car(name, year, engineSize, price));
            }
            file.close();
        }
        else 
        {
            cerr << "Ошибка при открытии файла для чтения." << endl;
        }
    }
};

class Menu 
{
public:
    void display() 
    {
        while (true) 
        {
            cout << "1. Добавить автомобиль\n2. Удалить автомобиль\n3. Отобразить автомобили\n4. Сортировка по году выпуска\n5. Сортировка по цене\n6. Поиск по названию\n7. Сохранить в файл\n8. Загрузить из файла\n9. Выход\n";
            int choice;
            cin >> choice;

            switch (choice) 
            {
            case 1: // Добавление автомобиля
                addCar();
                break;
            case 2: // Удаление автомобиля
                removeCar();
                break;
            case 3: // Отображение автомобилей
                displayCars();
                break;
            case 4: // Сортировка по году выпуска
                sortCarsByYear();
                break;
            case 5: // Сортировка по цене
                sortCarsByPrice();
                break;
            case 6: // Поиск по названию
                searchByName();
                break;
            case 7: // Сохранение в файл
                saveToFile();
                break;
            case 8: // Загрузка из файла
                loadFromFile();
                break;
            case 9: // Выход
                return;
            default:
                cout << "Некорректный ввод.\n";
            }
        }
    }

private:
    vector<Car> cars;

    void addCar() 
    {
        string name;
        int year;
        double engineSize, price;
        cout << "Введите название: ";
        cin >> name;
        cout << "Введите год выпуска: ";
        cin >> year;
        cout << "Введите объем двигателя: ";
        cin >> engineSize;
        cout << "Введите цену: ";
        cin >> price;
        cars.push_back(Car(name, year, engineSize, price));
    }

    void removeCar()
    {
        string name;
        cout << "Введите название автомобиля для удаления: ";
        cin >> name;
        cars.erase(remove_if(cars.begin(), cars.end(), [&name](const Car& car) {
            return car.name == name;
            }), cars.end());
    }

    void displayCars()
    {
        for (const Car& car : cars) 
        {
            car.display();
        }
    }

    void sortCarsByYear()
    {
        sort(cars.begin(), cars.end(), Car::CompareByYear());
    }

    void sortCarsByPrice()
    {
        sort(cars.begin(), cars.end(), Car::CompareByPrice());
    }

    void searchByName()
    {
        string name;
        cout << "Введите название автомобиля для поиска: ";
        cin >> name;
        for (const Car& car : cars)
        {
            if (car.name == name)
            {
                car.display();
            }
        }
    }

    void saveToFile() 
    {
        string filename;
        cout << "Введите имя файла для сохранения: ";
        cin >> filename;
        Car::saveToFile(cars, filename);
    }

    void loadFromFile()
    {
        string filename;
        cout << "Введите имя файла для загрузки: ";
        cin >> filename;
        Car::loadFromFile(cars, filename);
    }
};
