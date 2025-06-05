#include <iostream>
using namespace std;
const double MY_PI = 355.0 / 113.0;

class Circle {
private:
    double radius;
    double area;
    bool areaCalculated;

public:
    Circle(double r) : radius(r), area(0), areaCalculated(false) {}

    void calculateArea() {
        if (!areaCalculated) {
            area = MY_PI * radius * radius;
            areaCalculated = true;
        }
    }


    double getArea() {
        calculateArea(); 
        return area;
    }
};

class Square {
private:
    double side;
    double area;
    bool areaCalculated;

public:
    Square(double l) : side(l), area(0), areaCalculated(false) {}

    void calculateArea() {
        if (!areaCalculated) {
            area = side * side;
            areaCalculated = true;
        }
    }

    double getArea() {
        calculateArea();
        return area;
    }
};

class Triangle {
private:
    double base;
    double height;
    double area;
    bool areaCalculated;

public:
    Triangle(double b, double h) : base(b), height(h), area(0), areaCalculated(false) {}

    void calculateArea() {
        if (!areaCalculated) {
            area = (base * height) / 2.0;
            areaCalculated = true;
        }
    }

    double getArea() {
        calculateArea();
        return area;
    }
};

int main() {
    Circle c(4);
    Square s(5); 
    Triangle t(6, 3);

    cout << "Circle Area: " << c.getArea() << endl;
    cout << "Square Area: " << s.getArea() << endl;
    cout << "Triangle Area: " << t.getArea() << endl;

    return 0;
}
