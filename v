C++

#include <iostream>
#include <vector>
#include <memory>

class IFigure {
protected:
    double _area = -1;

public:
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void display() const = 0;
    virtual void printDetails() const = 0;
    virtual ~IFigure() {}

    double getArea() {
        if (_area < 0) {
            std::cout << "Calculating area...\n";
            _area = calculateArea();
        }
        return _area;
    }
};

class Triangle : public IFigure {
private:
    double base, height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    double calculateArea() override {
        return (base * height) / 2.0;
    }

    double calculatePerimeter() const override {
        return 3 * base;
    }

    void display() const override {
        std::cout << "Triangle:\n";
        std::cout << "Base: " << base << ", Height: " << height << std::endl;
        std::cout << "Area: " << _area << ", Perimeter: " << calculatePerimeter() << "\n\n";
    }

    void printDetails() const override {
        std::cout << "[Details] Triangle - base = " << base << ", height = " << height << ", area = " << _area << "\n";
    }
};

class Circle : public IFigure {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double calculateArea() override {
        const double PI_APPROX = 355.0 / 113.0;
        return PI_APPROX * radius * radius;
    }

    double calculatePerimeter() const override {
        const double PI_APPROX = 355.0 / 113.0;
        return 2 * PI_APPROX * radius;
    }

    void display() const override {
        std::cout << "Circle:\n";
        std::cout << "Radius: " << radius << std::endl;
        std::cout << "Area: " << _area << ", Perimeter: " << calculatePerimeter() << "\n\n";
    }

    void printDetails() const override {
        std::cout << "[Details] Circle - radius = " << radius << ", area = " << _area << "\n";
    }
};

class Square : public IFigure {
private:
    double side;

public:
    Square(double l) : side(l) {}

    double calculateArea() override {
        return side * side;
    }

    double calculatePerimeter() const override {
        return 4 * side;
    }

    void display() const override {
        std::cout << "Square:\n";
        std::cout << "Side: " << side << std::endl;
        std::cout << "Area: " << _area << ", Perimeter: " << calculatePerimeter() << "\n\n";
    }

    void printDetails() const override {
        std::cout << "[Details] Square - side = " << side << ", area = " << _area << "\n";
    }
};

int main() {
    std::vector<std::unique_ptr<IFigure>> figures;

    figures.push_back(std::make_unique<Triangle>(3.0, 4.0));
    figures.push_back(std::make_unique<Circle>(2.5));
    figures.push_back(std::make_unique<Square>(5.0));

    for (const auto& figure : figures) {
        figure->getArea();
        figure->display();
        figure->printDetails();
    }

    return 0;
}
