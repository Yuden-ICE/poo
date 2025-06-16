#include <iostream>
#include <string>
#include <memory>
#include <vector>

class IAreaRepository {
public:
    virtual void save(float value) = 0;
    virtual float getArea(int index) const = 0;
    virtual int getCount() const = 0;
    virtual std::string getName() const = 0;
    virtual ~IAreaRepository() {}
};

class ArrayFloatRepository : public IAreaRepository {
private:
    float data[100];
    int count = 0;
public:
    void save(float value) override {
        if (count < 100) {
            data[count++] = value;
            std::cout << "Saved [" << count - 1 << "] in Array: " << value << std::endl;
        } else {
            std::cout << "Array repository full\n";
        }
    }

    float getArea(int index) const override {
        return (index >= 0 && index < count) ? data[index] : -1;
    }

    int getCount() const override {
        return count;
    }

    std::string getName() const override {
        return "Array";
    }
};

class VectorRepository : public IAreaRepository {
private:
    std::vector<float> data;
public:
    void save(float value) override {
        data.push_back(value);
        std::cout << "Saved [" << data.size() - 1 << "] in Vector: " << value << std::endl;
    }

    float getArea(int index) const override {
        return (index >= 0 && index < data.size()) ? data[index] : -1;
    }

    int getCount() const override {
        return static_cast<int>(data.size());
    }

    std::string getName() const override {
        return "Vector";
    }
};

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
    virtual ~IFigure() {}
};

class FigureGeometryBase {
protected:
    double _area = 0;
public:
    virtual double calculateAreaInternal() = 0;

    void saveArea() {
        if (_area == 0) {
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

    double calculateAreaInternal() override { return (base * height) / 2.0; }
    double area() override { saveArea(); return getArea(); }
    double perimeter() const override { return 3 * base; }

    void display() const override {
        std::cout << "Triangle: base = " << base << ", height = " << height << "\n";
        std::cout << "Area = " << _area << ", Perimeter = " << perimeter() << "\n";
    }

    void printDetails() const override {
        std::cout << "[PrintDetails] Triangle: base = " << base << ", height = " << height << ", area = " << _area << "\n";
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
    double area() override { saveArea(); return getArea(); }
    double perimeter() const override {
        const double PI_APPROX = 355.0 / 113.0;
        return 2 * PI_APPROX * radius;
    }

    void display() const override {
        std::cout << "Circle: radius = " << radius << "\n";
        std::cout << "Area = " << _area << ", Perimeter = " << perimeter() << "\n";
    }

    void printDetails() const override {
        std::cout << "[PrintDetails] Circle: radius = " << radius << ", area = " << _area << "\n";
    }
};

class Square : public IFigure, public FigureGeometryBase, public IFigurePrinter {
private:
    double side;
public:
    Square(double l) : side(l) {}

    double calculateAreaInternal() override { return side * side; }
    double area() override { saveArea(); return getArea(); }
    double perimeter() const override { return 4 * side; }

    void display() const override {
        std::cout << "Square: side = " << side << "\n";
        std::cout << "Area = " << _area << ", Perimeter = " << perimeter() << "\n";
    }

    void printDetails() const override {
        std::cout << "[PrintDetails] Square: side = " << side << ", area = " << _area << "\n";
    }
};

class FigureFactory {
public:
    virtual std::unique_ptr<IFigure> createFigure() const = 0;
    virtual ~FigureFactory() {}
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
        return std::make_unique<Square>(l);
    }
};

int main() {
    std::vector<std::unique_ptr<FigureFactory>> factories;
    factories.push_back(std::make_unique<TriangleFactory>(3.0, 4.0));
    factories.push_back(std::make_unique<CircleFactory>(2.5));
    factories.push_back(std::make_unique<SquareFactory>(5.0));

    std::unique_ptr<IAreaRepository> repo = std::make_unique<VectorRepository>();

    for (auto& factory : factories) {
        std::unique_ptr<IFigure> figure = factory->createFigure();
        IFigurePrinter* printer = dynamic_cast<IFigurePrinter*>(figure.get());

        float a = figure->area();
        figure->display();
        if (printer) printer->printDetails();

        repo->save(a);
        std::cout << "-----------------------\n";
    }

    std::cout << "\n--- Areas stored in REPO (" << repo->getName() << ") ---\n";
    for (int i = 0; i < repo->getCount(); ++i) {
        std::cout << "Area[" << i << "] = " << repo->getArea(i) << "\n";
    }

    return 0;
}
