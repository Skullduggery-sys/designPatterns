#include <iostream>
#include <memory>

using namespace std;

class Product {
public:
    static shared_ptr<Product> instance() {
        static shared_ptr<Product> ptr(new Product);
        return ptr;
    }
    void run() {cout << "Run method" << endl;}
    Product(const Product&) = delete;
    Product& operator=(const Product&) = delete;

    ~Product() { cout << "Destructor" << endl; };
private:
    Product() {cout << "Constructor" << endl; }
};

int main() {
    shared_ptr<Product> product(Product::instance());
    product->run();
    auto p = Product::instance();
    p->run();
}