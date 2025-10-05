#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

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

    void setFunction(std::function<Result(X, Y)> f) {
        func = f;
    }
};

int main() {
    TrackingClass<int, int, int> tracker([](int x, int y) { return x + y; }); // Default init
    bool yn = true;

    while (yn) {
        char op;
        std::cout << "\nChoose an operation (+, -, *, /): ";
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
            continue; 
        }

        tracker.setFunction(selectedFunc);  

        int x, y;
        std::cout << "Enter two numbers: ";
        std::cin >> x >> y;

        int result = tracker.apply(x, y);
        std::cout << "Result: " << result << "\n";
        std::cout << "Function was applied " << tracker.getCount() << " time(s).\n";

        string yesno;
        cout << "Would you like to run the function again? (y/n): ";
        cin >> yesno;

        while (yesno != "y" && yesno != "n") {
            cout << "Invalid input. Please enter 'y' or 'n': ";
            cin >> yesno;
        }

        yn = (yesno == "y");
    }

    return 0;
}
