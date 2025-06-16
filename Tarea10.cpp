#include <iostream>
#include <memory>

int main() {
    int stackValue = 4;
    int* ptrToStack = &stackValue;

    std::cout << "--- Stack Memory Example ---\n";
    std::cout << "Address pointed to by ptrToStack: " << ptrToStack << "\n";
    std::cout << "Value pointed to by ptrToStack: " << *ptrToStack << "\n";

    (*ptrToStack)++;
    std::cout << "Value after incrementing via ptrToStack: " << *ptrToStack << "\n";
    std::cout << "Original stackValue after pointer modification: " << stackValue << "\n\n";

    std::unique_ptr<int> uniquePtrToHeap = std::make_unique<int>(2);

    std::cout << "--- Heap Memory Example (with std::unique_ptr) ---\n";
    std::cout << "Address pointed to by uniquePtrToHeap: " << uniquePtrToHeap.get() << "\n";
    std::cout << "Value pointed to by uniquePtrToHeap: " << *uniquePtrToHeap << "\n";

    return 0;
}
