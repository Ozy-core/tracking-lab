#include <iostream>
#include <functional>
#include <cassert>

template<typename X, typename Y, typename Result>


class TrackingClass {
private:
    std::function<Result(X, Y)> func;
    int count;
    Result lastResult;

public:
    TrackingClass(std::function<Result(X, Y)> f)
        : func(f), count(0), lastResult() {}

    Result apply(X x, Y y) {
        lastResult = func(x, y);
        ++count;
        return lastResult;
    }

    int getCount() const {
        return count;
    }

    Result getLastResult() const {
        return lastResult;
    }
};

int main() {
    
    char op;
    std::cout << "Choose an operation (+, -, *, /): ";
    std::cin >> op;

    std::function<int(int, int)> selectedFunc;

    if (op == '+') {
        selectedFunc = [](int x, int y) { return x + y; };
    } else if (op == '-') {
        selectedFunc = [](int x, int y) { return x - y; };
    } else if (op == '*') {
        selectedFunc = [](int x, int y) { return x * y; };
    } else if (op == '/') {
        selectedFunc = [](int x, int y) {
            if (y == 0) {
                std::cout << "Error: Division by zero!\n";
                return 0;
            }
            return x / y;
        };
    } else {
        std::cout << "Invalid operation.\n";
        return 1;
    }

    TrackingClass<int, int, int> tracker(selectedFunc);

    int x, y;
    std::cout << "Enter two numbers: ";
    std::cin >> x >> y;

    int result = tracker.apply(x, y);
    std::cout << "Result: " << result << "\n";
    std::cout << "Function was applied " << tracker.getCount() << " time(s).\n";

    return 0;
}
