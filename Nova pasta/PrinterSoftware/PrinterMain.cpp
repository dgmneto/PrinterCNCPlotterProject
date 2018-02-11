#include "Communication.h"

int main(){
    Printer print;
    std::cout<<print.attach(7)<<"\n";
    std::cout<<print.connect();
    while (1){
        int stepper;
        int steps;
        /*std::cout << "Type the stepper\n";
        std::cin >> stepper;
        std::cout << "Type the steps\n";
        std::cin >> steps;*/
        for (int i = 1; i<= 100; ++i){
            std::cout << print.move(1, -1);
            std::cout << print.move(2, 1);
        }
        for (int i = 1; i<= 100; ++i){
            std::cout << print.move(1, 1);
            std::cout << print.move(2, -1);
        }

    }
    return 0;
}
