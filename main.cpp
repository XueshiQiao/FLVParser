#include <iostream>
#include "FLVParser.h"
#include <memory>

int main() {
    std::unique_ptr<FLVParser> parser = std::make_unique<FLVParser>("G:\\Code\\FLVParser\\888888.flv");
    parser->parse();

    return 0;
}