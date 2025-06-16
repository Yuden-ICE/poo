#include <iostream>
#include <string>
#include <memory>
#include <vector>

class IFigurePrinter {
public:
    virtual void printDetails() const = 0;
    virtual ~IFigurePrinter() = default;
};

class IFigure {
public:
    virtual double area() = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;
    virtual ~IFigure() = default;
};

class FigureGeometryBase {
protected:
    double _area = 0;
public:
    virtual double calculateAreaInternal() = 0;

    void saveArea() {
        if (_area == 0) {
            std::cout << "Calculating area...\n";
            _area = calculateAreaInternal();
        }
    }

    double getArea() const {
        return _area;
    }
};

class Triangle : public IFigure, public FigureGeometryBase, public IFigurePrinter {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}

    double calculateAreaInternal() override {
        return (base * height) / 2.0;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimeter() const override {
        return 3 * base;
    }

    void display() const override {
        std::cout << "Triangle:\n";
        std::cout << "Base: " << base << ", Height: " << height << std::endl;
        std::cout << "Area: " << _area << ", Perimeter: " << perimeter() << "\n\n";
    }

    void printDetails() const override {
        std::cout << "[PrintDetails] Triangle - base = " << base << ", height = " << height << ", area = " << _area << "\n";
    }
};

class Circle : public IFigure, public FigureGeometryBase, public IFigurePrinter {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double calculateAreaInternal() override {
        const double PI_APPROX = 355.0 / 113.0;
        return PI_APPROX * radius * radius;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimeter() const override {
        const double PI_APPROX = 355.0 / 113.0;
        return 2 * PI_APPROX * radius;
    }

    void display() const override {
        std::cout << "Circle:\n";
        std::cout << "Radius: " << radius << std::endl;
        std::cout << "Area: " << _area << ", Perimeter: " << perimeter() << "\n\n";
    }

    void printDetails() const override {
        std::cout << "[PrintDetails] Circle - radius = " << radius << ", area = " << _area << "\n";
    }
};

class Square : public IFigure, public FigureGeometryBase, public IFigurePrinter {
private:
    double side;
public:
    Square(double l) : side(l) {}

    double calculateAreaInternal() override {
        return side * side;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimeter() const override {
        return 4 * side;
    }

    void display() const override {
        std::cout << "Square:\n";
        std::cout << "Side: " << side << std::endl;
        std::cout << "Area: " << _area << ", Perimeter: " << perimeter() << "\n\n";
    }

    void printDetails() const override {
        std::cout << "[PrintDetails] Square - side = " << side << ", area = " << _area << "\n";
    }
};

class FigureFactory {
public:
    virtual std::unique_ptr<IFigure> createFigure() const = 0;
    virtual ~FigureFactory() = default;
};

class TriangleFactory : public FigureFactory {
    double base, height;
public:
    TriangleFactory(double b, double h) : base(b), height(h) {}
    std::unique_ptr<IFigure> createFigure() const override {
        return std::make_unique<Triangle>(base, height);
    }
};

class CircleFactory : public FigureFactory {
    double radius;
public:
    CircleFactory(double r) : radius(r) {}
    std::unique_ptr<IFigure> createFigure() const override {
        return std::make_unique<Circle>(radius);
    }
};

class SquareFactory : public FigureFactory {
    double side;
public:
    SquareFactory(double l) : side(l) {}
    std::unique_ptr<IFigure> createFigure() const override {
        return std::make_unique<Square>(side);
    }
};

class RepoFloatArray {
private:
    std::vector<float> data;
public:
    void save(float value) {
        data.push_back(value);
        std::cout << "Area saved [" << data.size() - 1 << "]: " << value << std::endl;
    }

    float getArea(size_t index) const {
        if (index < data.size()) {
            return data[index];
        } else {
            std::cout << "Invalid index\n";
            return -1;
        }
    }

    size_t getCount() const {
        return data.size();
    }
};

int main() {
    std::vector<std::unique_ptr<FigureFactory>> factories;
    factories.push_back(std::make_unique<TriangleFactory>(3.0, 4.0));
    factories.push_back(std::make_unique<CircleFactory>(2.5));
    factories.push_back(std::make_unique<SquareFactory>(5.0));

    RepoFloatArray repo;

    for (const auto& factory : factories) {
        std::unique_ptr<IFigure> figure = factory->createFigure();
        IFigurePrinter* printer = dynamic_cast<IFigurePrinter*>(figure.get());

        float area = figure->area();
        figure->display();

        if (printer) {
            printer->printDetails();
        }

        repo.save(area);
    }

    std::cout << "\n--- Areas stored in repository ---\n";
    for (size_t i = 0; i < repo.getCount(); ++i) {
        std::cout << "Area[" << i << "]: " << repo.getArea(i) << "\n";
    }

    return 0;
}
