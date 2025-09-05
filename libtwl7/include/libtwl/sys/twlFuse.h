#pragma once

#define REG_FUSE_ID         (*(vu64*)0x04004D00)
#define REG_FUSE_ID0        (*(vu32*)0x04004D00)
#define REG_FUSE_ID1        (*(vu32*)0x04004D04)
#define REG_FUSE_VERIFY     (*(vu8*)0x04004D08)

#define FUSE_VERIFY_ERROR   1
