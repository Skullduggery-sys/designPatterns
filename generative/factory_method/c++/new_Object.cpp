# include <iostream>
# include <memory>
using namespace std;
# pragma region Product
class Product
{
public:
    virtual ~Product() = default;
    virtual void run() = 0;
};

class ConProd1 : public Product
{
public:
    ConProd1() { cout << "Calling the ConProd1 constructor;" << endl; }
    ~ConProd1() override { cout << "Calling the ConProd1 destructor;" << endl; }
    void run() override { cout << "Calling the run method;" << endl; }
};

class ConProd2 : public Product
{
public:
    ConProd2() { cout << "Calling the ConProd2 constructor;" << endl; }
    ~ConProd2() override { cout << "Calling the ConProd2 destructor;" << endl; }
    void run() override { cout << "Calling the run method 2;" << endl; }
};

# pragma endregion

class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> createProduct() = 0;
};

template <typename Derived, typename Base>
concept Derivative = is_abstract_v<Base> && is_base_of_v<Base, Derived>;
template <Derivative<Product> Tprod>
class ConCreator : public Creator
{
public:
    unique_ptr<Product> createProduct() override
    {
        return unique_ptr<Tprod>(new Tprod());
    }
};

class User {
public:
    void run(std::shared_ptr<Creator>& cr) {
        std::shared_ptr<Product> ptr = cr->createProduct();
        ptr->run();
    }
};

int main()
{
    shared_ptr<Creator> cr = make_shared<ConCreator<ConProd1>>();
    shared_ptr<Creator> cr2 = make_shared<ConCreator<ConProd2>>();
    unique_ptr<User> us = std::make_unique<User>();
    us->run(cr);
    us->run(cr2);
}