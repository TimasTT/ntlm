#include <vector>
#include <iostream>

#include "ntlm.hpp"

int main() {
    std::string base64Code = "TlRMTVNTUAABAAAABzIAAAYABgArAAAACwALACAAAABXT1JLU1RBVElPTkRPTUFJTg==";
    std::string decodedCode = base64_decode(base64Code);
    std::cout << decodedCode << std::endl;


    /*std::string encCo = base64_encode_(encC, base64Code.size());
    std::cout << encCo << std::endl;*/

    std::string encodeCode = base64_encode(decodedCode);
    std::cout << encodeCode << std::endl;

    if (base64Code == encodeCode) {
        std::cout << "it works!" << std::endl;
    }

    std::vector<unsigned char> hexCode;
    hexCode.emplace_back((static_cast<int>(base64Code[0]) & 0xFF));

    for (auto i : hexCode) {
        std::cout << i;
    }

    return 0;
}