//
// Created by raytine on 2019/4/13.
//

#ifndef TEST_FLVBASETAGDATA_H
#define TEST_FLVBASETAGDATA_H

#include <string>

class FLVBaseTagData {

public:
    virtual ~FLVBaseTagData() {}
    virtual std::string desc() const;
};


#endif //TEST_FLVBASETAGDATA_H
