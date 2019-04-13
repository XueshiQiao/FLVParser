//
// Created by raytine on 2019/4/9.
//

#ifndef TEST_FLVPARSER_H
#define TEST_FLVPARSER_H

#include <string>
#include <iostream>

class FLVParser {
private:
    std::string filePath;

public:

    FLVParser(std::string filePath): filePath(filePath) {

    }

    ~FLVParser() {}

    void parse();



};


#endif //TEST_FLVPARSER_H
