#include "memory"
#include "iostream"
#include "map"

using namespace std;

class Product {
public:
    virtual ~Product() = default;
    virtual void run() = 0;
};

class ConProd1 : public Product {
public:
    ConProd1() { cout << "Calling Prod1 Constuctor" << endl; }
    virtual void run() override { cout << "Calling run method ConProd1" << endl;}
    virtual ~ConProd1() override {cout << "Calling destructor ConProd1" << endl;}
};

class ConProd2 : public Product {
public:
    ConProd2() { cout << "Calling Prod2 Constuctor" << endl; }
    virtual void run() override { cout << "Calling run method ConProd2" << endl;}
    virtual ~ConProd2() override {cout << "Calling destructor ConProd2" << endl;}
};

class Creator {
public:
    virtual ~Creator() = default;
    virtual unique_ptr<Product> create() = 0;
};

template <typename Tprod>
class ConCreator : public Creator {
public:
    virtual unique_ptr<Product> create() override {
        return unique_ptr<Product>(new Tprod());
    }
};

class Solution {
public:
    typedef unique_ptr<Creator> (*CreateCreator)();
    bool registration(size_t id, CreateCreator crFunc) {
        bool res = callbacks.insert(CallBackMap::value_type(id, crFunc)).second;
        return res;
    }
    bool check(size_t id) { return callbacks.erase(id) == 1; }

    unique_ptr<Creator> create(size_t id)
    {
        CallBackMap::const_iterator it = callbacks.find(id);

        if (it == callbacks.end())
        {
            throw;
        }

        return unique_ptr<Creator>((it->second)());
    }

private:
    using CallBackMap = map<size_t, CreateCreator>;

    CallBackMap callbacks;
};

unique_ptr<Creator> createConCreator()
{
    return unique_ptr<Creator>(new ConCreator<ConProd1>());
}

unique_ptr<Creator> createConCreator2()
{
    return unique_ptr<Creator>(new ConCreator<ConProd2>());
}

int main()
{
    Solution solution;

    solution.registration(1, createConCreator);
    solution.registration(2, createConCreator2);

    shared_ptr<Creator> cr(solution.create(1));
    shared_ptr<Product> ptr = cr->create();

    shared_ptr<Creator> cr2(solution.create(2));
    shared_ptr<Product> ptr2 = cr2->create();
    ptr->run();
    ptr2->run();
}

