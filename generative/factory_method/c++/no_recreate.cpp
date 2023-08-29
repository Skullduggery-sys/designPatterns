#include "memory"
#include "iostream"
using namespace std;

class Product
{
public:
    virtual ~Product() = default;
    virtual void run() = 0;
};

class ConProd1 : public Product {
public:
    ConProd1() {cout << "Calling ConProd1 constructor" << endl;};
    virtual ~ConProd1() override { cout << "Calling product destructor" << endl;}
    virtual void run() override {cout << "Calling method run" << endl;}
};


class Creator {
public:
    shared_ptr<Product> getProduct();
    virtual ~Creator() = default;
protected:
    virtual shared_ptr<Product> createProduct() = 0;
private:
    shared_ptr<Product> product;
};

shared_ptr<Product> Creator::getProduct() {
    if (!product) {
        product = createProduct();
    }
    return product;
}

template <typename Tprod>
class ConCreator : public Creator {
public:
    ConCreator() {cout << "Calling constuctor creator" << endl;};
    virtual ~ConCreator() override {cout << "ConCreator destructor" << endl;}
protected:
    virtual shared_ptr<Product> createProduct() override {
        return shared_ptr<Product>(new Tprod);
    };
};

int main() {
    shared_ptr<Creator> cr(new ConCreator<ConProd1>());
    shared_ptr<Product> prod = cr->getProduct();
    prod->run();
}