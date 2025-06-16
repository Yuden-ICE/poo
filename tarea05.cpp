#include <iostream>

class IFigure {
public:
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void display() const = 0;
    virtual ~IFigure() {}
};

class FigureBase : public IFigure {
protected:
    double _area = -1;

public:
    double calculateArea() override {
        if (_area < 0) {
            std::cout << "Calculating area...\n";
            _area = calculateRealArea();
        }
        return _area;
    }

    virtual double calculateRealArea() = 0;
};

class Triangle : public FigureBase {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}

    double calculateRealArea() override {
        return (base * height) / 2.0;
    }

    double calculatePerimeter() const override {
        return 3 * base;
    }

    void display() const override {
        std::cout << "Triangle:\n";
        std::cout << "Base: " << base << ", Height: " << height << "\n";
        std::cout << "Area: " << _area << ", Perimeter: " << calculatePerimeter() << "\n\n";
    }
};

class Circle : public FigureBase {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateRealArea() override {
        const double PI_APPROX = 355.0 / 113.0;
        return PI_APPROX * radius * radius;
    }

    double calculatePerimeter() const override {
        const double PI_APPROX = 355.0 / 113.0;
        return 2 * PI_APPROX * radius;
    }

    void display() const override {
        std::cout << "Circle:\n";
        std::cout << "Radius: " << radius << "\n";
        std::cout << "Area: " << _area << ", Perimeter: " << calculatePerimeter() << "\n\n";
    }
};

class Square : public FigureBase {
private:
    double side;
public:
    Square(double l) : side(l) {}

    double calculateRealArea() override {
        return side * side;
    }

    double calculatePerimeter() const override {
        return 4 * side;
    }

    void display() const override {
        std::cout << "Square:\n";
        std::cout << "Side: " << side << "\n";
        std::cout << "Area: " << _area << ", Perimeter: " << calculatePerimeter() << "\n\n";
    }
};

int main() {
    IFigure* figures[] = {
        new Triangle(3.0, 4.0),
        new Circle(2.5),
        new Square(5.0)
    };

    for (IFigure* fig : figures) {
        fig->calculateArea();
        fig->display();
        delete fig;
    }

    return 0;
}
