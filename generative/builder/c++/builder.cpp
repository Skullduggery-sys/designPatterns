#include "iostream"
#include "memory"

using namespace std;

class Product{
public:
    Product() {cout << "Product constructor" << endl;};
    ~Product() {cout << "Product destructor" << endl;};
    void run() {cout << "Run method" << endl;}
};

class Builder {
public:
    virtual bool buildPart1() = 0;
    virtual bool buildPart2() = 0;
    shared_ptr<Product> getProduct();
protected:
    virtual shared_ptr<Product> createProduct() = 0;
    shared_ptr<Product> product;
};

class ConcreteBuilder : public Builder {
public:
    virtual bool buildPart1() override {cout << "building part 1" << endl; parts++; return true;};
    virtual bool buildPart2() override {cout << "building part 2" << endl; parts++; return true;};
protected:
    virtual shared_ptr<Product> createProduct() override {
        if (parts == 2) {
            product = shared_ptr<Product>(new Product());
        }
        return product;
    };
private:
    size_t parts{0};
};

class Director {
public:
    shared_ptr<Product> create(shared_ptr<Builder> builder) {
        if (builder->buildPart1() && builder->buildPart2()) {
            return builder->getProduct();
        }
        return shared_ptr<Product>();
    }
};

shared_ptr<Product> Builder::getProduct() {
    if (!product) {
        product = createProduct();
    }

    return product;
}

int main() {
    shared_ptr<Builder> builder(new ConcreteBuilder());
    shared_ptr<Director> director(new Director());
    auto p = director->create(builder);
    p->run();
}