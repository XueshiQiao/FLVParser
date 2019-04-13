//
// Created by raytine on 2019/4/13.
//

#include "FLVDataTagFactory.h"
#include "FLVAudioTag.h"
#include "FLVVideoTag.h"
#include "FLVScriptTag.h"

std::shared_ptr<FLVBaseTagData> FLVDataTagFactory::createTagDataWith(uint8_t type, char *data, uint32_t length) {
    FLVBaseTagData *tagData;
    if (type == 18) {
        tagData = new FLVScriptTag(data, length);
    } else if (type == 8) {
        tagData = new FLVAudioTag(data, length);
    } else if (type == 9) {
        tagData = new FLVVideoTag(data, length);
    }
    return std::shared_ptr<FLVBaseTagData>(tagData);
}
