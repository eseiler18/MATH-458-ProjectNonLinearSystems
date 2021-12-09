#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <sstream>
#include "Newton.h"
#include "ClassicChord.h"

int main() {

    std::cout << "Main Emilien" << std::endl;
    for (int i=0; i<3; i++) {
        try {
            if (i == 1) {
                throw std::invalid_argument("ahaha");
            } else {
                std::cout << i << std::endl;
            }
        } catch (std::invalid_argument &e) {
            std::cout <<  e.what() << std::endl;
        }
    }
    return 0;
}
