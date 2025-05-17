#include <iostream>

double calcularAreaCirculo(double radio) {
    if (radio < 0) {
        return -1.0; 
    }
    return ((355.0/113) * (radio*radio));
}

double calcularAreaTriangulo(double base, double altura) {
    if (base < 0 || altura < 0) {
        return -1.0; 
    }
    return 0.5 * base * altura;
}

double calcularAreaCuadrado(double lado) {
    if (lado < 0) {
        return -1.0; 
    }
    return lado*lado;
}

int main() {
    double radioCirculo;
    std::cout<<"Introduzca el radio del circulo\n";
    std::cin>>radioCirculo;
    double areaCirculo = calcularAreaCirculo(radioCirculo);
    if (areaCirculo >= 0) {
        std::cout << "El área del círculo con radio " << radioCirculo << " es: " << areaCirculo << std::endl;
    } else {
        std::cout << "Error: El radio del círculo no puede ser negativo." << std::endl;
    }

    double baseTriangulo;
    double alturaTriangulo;
        std::cout<<"Introduzca la base del triangulo\n";
    std::cin>>baseTriangulo;
        std::cout<<"Introduzca la altura del triangulo\n";
    std::cin>>alturaTriangulo;
    double areaTriangulo = calcularAreaTriangulo(baseTriangulo, alturaTriangulo);
    if (areaTriangulo >= 0) {
        std::cout << "El área del triangulo con base " << baseTriangulo << " y altura " << alturaTriangulo << " es: " << areaTriangulo << std::endl;
    } else {
        std::cout << "Error: La base y/o la altura del triángulo no pueden ser negativas." << std::endl;
    }

    double ladoCuadrado;
    std::cout<<"Introduzca el lado del cuadrado\n";
    std::cin>>ladoCuadrado;
    double areaCuadrado = calcularAreaCuadrado(ladoCuadrado);
    if (areaCuadrado >= 0) {
        std::cout << "El área del cuadrado con lado " << ladoCuadrado << " es: " << areaCuadrado << std::endl;
    } else {
        std::cout << "Error: El lado del cuadrado no puede ser negativo." << std::endl;
    }

    return 0;
}
