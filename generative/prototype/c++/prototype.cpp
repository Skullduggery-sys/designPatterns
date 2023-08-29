#include <memory>
#include <iostream>

using namespace std;

class BaseProduct {
public:
    virtual ~BaseProduct() = default;
    virtual shared_ptr<BaseProduct> clone() = 0;
};

class Product : public BaseProduct {
public:
    Product() { cout << "Constructor" << endl;};
    virtual ~Product() override { cout << "Destructor" << endl;}
    Product(const Product&) { cout << "Copy constructor" << endl;}

    virtual shared_ptr<BaseProduct> clone() override {
        return shared_ptr<BaseProduct>(new Product(*this));
    }
};

int main() {
    shared_ptr<BaseProduct> product(new Product());
    shared_ptr<BaseProduct> clone = product->clone();
}