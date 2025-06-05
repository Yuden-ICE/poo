#include <iostream>
using namespace std;

const double MY_PI = 355.0 / 113.0;

class Circle {
private:
    double radius;

public:
    Circle(double r = 1) {
        radius = r;
    }

    double getRadius() {
        return radius;
    }

    double calculateArea() {
        return MY_PI * radius * radius;
    }
};

class Triangle {
private:
    double base;
    double height;

public:
    Triangle(double b = 1, double h = 1) {
        base = b;
        height = h;
    }

    double calculateArea() {
        return (base * height) / 2;
    }

    double getBase() {
        return base;
    }

    double getHeight() {
        return height;
    }
};

int main() {
    Triangle t;
    Circle c;
    cout << "Triangle Area: " << t.calculateArea() << endl;
    cout << "Circle Area: " << c.calculateArea() << endl;
    cout << "Circle Radius: " << c.getRadius() << endl;

    return 0;
}
