#include <iostream>

enum arg {
    ENCODE,
    DECODE,
    VALIDATE,
    ERROR
};

arg Parse(int argc, char** argv) {

    return arg::ERROR;
}

int main(int argc, char** argv) {
    std::cout << "Hello, World!\n";
    return 0;
}