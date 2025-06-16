#include <iostream>
#include <memory>
#include <vector>
#include <functional>

class IFigure {
public:
    virtual double area() = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;
    virtual void printDetails() const = 0;
    virtual ~IFigure() {}
};

class FigureGeometry {
protected:
    double _area = -1;

    double getArea() const {
        return _area;
    }

    void saveArea(double val) {
        _area = val;
    }
};

class Triangle : public IFigure, public FigureGeometry {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}

    double area() override {
        if (_area < 0) {
            std::cout << "Calculating triangle area...\n";
            saveArea((base * height) / 2.0);
        }
        return getArea();
    }

    double perimeter() const override {
        return 3 * base;
    }

    void display() const override {
        std::cout << "Triangle:\nBase: " << base << ", Height: " << height << ", Area: " << _area << ", Perimeter: " << perimeter() << "\n";
    }

    void printDetails() const override {
        std::cout << "[Details] Triangle - base: " << base << ", height: " << height << ", area: " << _area << "\n";
    }
};

class Circle : public IFigure, public FigureGeometry {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() override {
        if (_area < 0) {
            std::cout << "Calculating circle area...\n";
            const double PI_APPROX = 355.0 / 113.0;
            saveArea(PI_APPROX * radius * radius);
        }
        return getArea();
    }

    double perimeter() const override {
        const double PI_APPROX = 355.0 / 113.0;
        return 2 * PI_APPROX * radius;
    }

    void display() const override {
        std::cout << "Circle:\nRadius: " << radius << ", Area: " << _area << ", Perimeter: " << perimeter() << "\n";
    }

    void printDetails() const override {
        std::cout << "[Details] Circle - radius: " << radius << ", area: " << _area << "\n";
    }
};

class Square : public IFigure, public FigureGeometry {
private:
    double side;
public:
    Square(double l) : side(l) {}

    double area() override {
        if (_area < 0) {
            std::cout << "Calculating square area...\n";
            saveArea(side * side);
        }
        return getArea();
    }

    double perimeter() const override {
        return 4 * side;
    }

    void display() const override {
        std::cout << "Square:\nSide: " << side << ", Area: " << _area << ", Perimeter: " << perimeter() << "\n";
    }

    void printDetails() const override {
        std::cout << "[Details] Square - side: " << side << ", area: " << _area << "\n";
    }
};

int main() {
    std::vector<std::function<std::unique_ptr<IFigure>()>> factories;

    factories.push_back([] { return std::make_unique<Triangle>(3.0, 4.0); });
    factories.push_back([] { return std::make_unique<Circle>(2.5); });
    factories.push_back([] { return std::make_unique<Square>(5.0); });

    std::vector<std::unique_ptr<IFigure>> figures;

    for (const auto& create : factories) {
        auto figure = create();
        figure->area();
        figure->display();
        figure->printDetails();
        figures.push_back(std::move(figure));
    }

    return 0;
}
