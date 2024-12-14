#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class Product {
protected:
    string name;   
    double price;  

public:
    Product(string name, double price) : name(name), price(price) {}

    string getName() const {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    virtual double getFinalPrice() const = 0;

    virtual ~Product() {}
};

class Discountable {
public:
    virtual double applyDiscount(double price) const = 0;
    virtual ~Discountable() {}
};

class Book : public Product, public Discountable {
private:
    double discountPercent; 

public:
    Book(string name, double price, double discountPercent)
        : Product(name, price), discountPercent(discountPercent) {}

    double applyDiscount(double price) const override {
        return price * (1 - discountPercent / 100);
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

class Pen : public Product, public Discountable {
private:
    double fixedDiscount;

public:
    Pen(string name, double price, double fixedDiscount)
        : Product(name, price), fixedDiscount(fixedDiscount) {}

    double applyDiscount(double price) const override {
        if (price > fixedDiscount) {
            return price - fixedDiscount;
        }
        return price;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Book book1("Я бачу, вас цікавить пітьма", 435.0, 10);
    Book book2("Містична річка", 350, 20);

    Pen pen1("Синя ручка", 15.0, 5);
    Pen pen2("Чорна ручка", 25.0, 5);

    Product* products[] = { &book1, &book2, &pen1, &pen2 };

    for (Product* product : products) {
        cout << "Продукт: " << product->getName() << endl;
        cout << "Базова ціна: " << product->getPrice() << " грн" << endl;
        cout << "Фінальна ціна: " << product->getFinalPrice() << " грн" << endl;
    }

    return 0;
}
