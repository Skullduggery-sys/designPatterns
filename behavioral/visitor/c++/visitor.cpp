#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Предварительные объявления классов
class Circle;
class Rectangle;

// Базовый класс посетителя (Visitor)
class Visitor
{
public:
    virtual ~Visitor() = default;

    // Чисто виртуальные функции для посещения Circle и Rectangle
    virtual void visit(Circle& ref) = 0;
    virtual void visit(Rectangle& ref) = 0;
};

// Базовый класс фигуры (Shape)
class Shape
{
public:
    virtual ~Shape() = default;

    // Чисто виртуальная функция для принятия посетителя
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
};

// Класс Circle, наследующийся от Shape
class Circle : public Shape
{
public:
    // Реализация функции accept для Circle
    void accept(shared_ptr<Visitor> visitor) override { visitor->visit(*this); }
};

// Класс Rectangle, наследующийся от Shape
class Rectangle : public Shape
{
public:
    // Реализация функции accept для Rectangle
    void accept(shared_ptr<Visitor> visitor) override { visitor->visit(*this); }
};

// Класс ConVisitor, наследующийся от Visitor
class ConVisitor : public Visitor
{
public:
    // Реализация функций visit для Circle и Rectangle
    void visit(Circle& ref) override { cout << "Circle;" << endl; }
    void visit(Rectangle& ref) override { cout << "Rectangle;" << endl; }
};

// Класс Figure, наследующийся от Shape
class Figure : public Shape
{
    using Shapes = vector<shared_ptr<Shape>>;

private:
    Shapes shapes;

public:
    // Конструктор, принимающий список shared_ptr<Shape>
    Figure(initializer_list<shared_ptr<Shape>> list)
    {
        for (auto&& elem : list)
            shapes.emplace_back(elem);
    }

    // Реализация функции accept для Figure
    void accept(shared_ptr<Visitor> visitor) override
    {
        for (auto& elem : shapes)
            elem->accept(visitor);
    }
};

int main()
{
    // Создание фигуры из кругов и прямоугольников
    shared_ptr<Shape> figure = make_shared<Figure>(
            initializer_list<shared_ptr<Shape>>(
                    { make_shared<Circle>(), make_shared<Rectangle>(), make_shared<Circle>() }
            ));

    // Создание посетителя (ConVisitor)
    shared_ptr<Visitor> visitor = make_shared<ConVisitor>();

    // Применение посетителя к фигуре
    figure->accept(visitor);
}