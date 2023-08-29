#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Product
{
private:
    static size_t count;
public:
    Product() { cout << "Constructor(" << ++count << ");" << endl; }
    ~Product() { cout << "Destructor(" << count-- << ");" << endl; }

    void clear() { cout << "Method clear: 0x" << this << endl; }
};

size_t Product::count = 0;

template <typename T>
class ObjectPool {
public:
    static shared_ptr<ObjectPool<T>> instance() {
        static shared_ptr<ObjectPool<T>> myInstance(new ObjectPool<T>());
        return myInstance;
    }

    shared_ptr<T> getObject();
    bool releaseObject(const shared_ptr<T>& obj);
    size_t getSize() const { return pool.size();};

    iterator<output_iterator_tag, const pair<bool, shared_ptr<T>>> begin() const;
    iterator<output_iterator_tag, const pair<bool, shared_ptr<T>>> end() const;

    ObjectPool(const ObjectPool<T>&) = delete;
    ObjectPool<T>& operator=(const ObjectPool<T>&) = delete;
private:
    ObjectPool() {}
    vector<pair<bool, shared_ptr<T>>> pool;

    pair<bool, shared_ptr<T>> create();

    template<typename Type>
    friend ostream& operator << (ostream& os, const ObjectPool<Type>& pl);

};

template <typename T>
shared_ptr<T> ObjectPool<T>::getObject() {
    size_t i = 0;
    for (i = 0; i < pool.size() && pool[i].first; i++);
    if (i < pool.size()) {
        pool[i].first = true;
    } else {
        pool.push_back(create());
    }
    return pool[i].second;
}

template <typename T>
bool ObjectPool<T>::releaseObject(const shared_ptr<T>& obj) {
    size_t i = 0;
    for (i = 0; i < pool.size() && pool[i].second != obj; i++);
    if (i < pool.size()) {
        pool[i].first = false;
        //obj.reset();
        pool[i].second->clear();
    } else {
        return false;
    }
    return true;
}

template <typename T>
pair<bool, shared_ptr<T>> ObjectPool<T>::create()
{
    return pair<bool, shared_ptr<T>>(true, shared_ptr<T>(new T()));
}

template <typename T>
ostream& operator << (ostream& os, const ObjectPool<T>& pl)
{
    for (auto elem : pl.pool)
        os << "{" << elem.first << ", 0x" << elem.second << "} ";

    return os;
}

int main()
{
    shared_ptr<ObjectPool<Product>> pool(ObjectPool<Product>::instance());

    vector<shared_ptr<Product>> vec(4);

    for (auto& elem : vec)
        elem = pool->getObject();

    pool->releaseObject(vec[1]);

    cout << *pool << endl;

    shared_ptr<Product> ptr = pool->getObject();
    vec[1] = pool->getObject();

    cout << *pool << endl;
}


