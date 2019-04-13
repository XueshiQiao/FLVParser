//
// Created by raytine on 2019/4/11.
//

#ifndef TEST_FLVSCRIPTTAG_H
#define TEST_FLVSCRIPTTAG_H

#include <cstdint>
#include "FLVBaseTagData.h"

class FLVScriptTag : public FLVBaseTagData {
private:
    char *data;
    uint32_t length;

public:
    FLVScriptTag(char *data, uint32_t length);
    FLVScriptTag(const FLVScriptTag &tag);
    FLVScriptTag &operator= (const FLVScriptTag & tag);

    virtual ~FLVScriptTag();

    std::string desc() const override;
};


#endif //TEST_FLVSCRIPTTAG_H
