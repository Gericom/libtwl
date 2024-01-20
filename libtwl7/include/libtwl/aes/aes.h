#pragma once

typedef union
{
    u8 bytes[16];
    u32 words[4];
} aes_u128_t;

#define REG_AES_CNT         (*(vu32*)0x04004400)
#define REG_AES_ASO_LEN     (*(vu16*)0x04004404)
#define REG_AES_PLD_LEN     (*(vu16*)0x04004406)
#define REG_AES_IFIFO       (*(vu32*)0x04004408)
#define REG_AES_OFIFO       (*(vu32*)0x0400440C)
#define REG_AES_NNC_CTR     (*(volatile aes_u128_t*)0x04004420)
#define REG_AES_MAC         (*(volatile aes_u128_t*)0x04004430)
#define REG_AES_KEY0        (*(volatile aes_u128_t*)0x04004440)
#define REG_AES_ID0         (*(volatile aes_u128_t*)0x04004450)
#define REG_AES_SEED0       (*(volatile aes_u128_t*)0x04004460)
#define REG_AES_KEY1        (*(volatile aes_u128_t*)0x04004470)
#define REG_AES_ID1         (*(volatile aes_u128_t*)0x04004480)
#define REG_AES_SEED1       (*(volatile aes_u128_t*)0x04004490)
#define REG_AES_KEY2        (*(volatile aes_u128_t*)0x040044A0)
#define REG_AES_ID2         (*(volatile aes_u128_t*)0x040044B0)
#define REG_AES_SEED2       (*(volatile aes_u128_t*)0x040044C0)
#define REG_AES_KEY3        (*(volatile aes_u128_t*)0x040044D0)
#define REG_AES_ID3         (*(volatile aes_u128_t*)0x040044E0)
#define REG_AES_SEED3       (*(volatile aes_u128_t*)0x040044F0)

#define AES_CNT_INPUT_FIFO_COUNT_SHIFT          0
#define AES_CNT_INPUT_FIFO_COUNT_MASK           (0x1F << AES_CNT_INPUT_FIFO_COUNT_SHIFT)

#define AES_CNT_OUTPUT_FIFO_COUNT_SHIFT         5
#define AES_CNT_OUTPUT_FIFO_COUNT_MASK          (0x1F << AES_CNT_OUTPUT_FIFO_COUNT_SHIFT)

#define AES_CNT_INPUT_FIFO_FLUSH                (1 << 10)
#define AES_CNT_OUTPUT_FIFO_FLUSH               (1 << 11)

#define AES_CNT_INPUT_FIFO_DMA_SIZE_16_BYTES    (0 << 12)
#define AES_CNT_INPUT_FIFO_DMA_SIZE_12_BYTES    (1 << 12)
#define AES_CNT_INPUT_FIFO_DMA_SIZE_8_BYTES     (2 << 12)
#define AES_CNT_INPUT_FIFO_DMA_SIZE_4_BYTES     (3 << 12)
#define AES_CNT_INPUT_FIFO_DMA_SIZE_MASK        (3 << 12)

#define AES_CNT_OUTPUT_FIFO_DMA_SIZE_4_BYTES    (0 << 14)
#define AES_CNT_OUTPUT_FIFO_DMA_SIZE_8_BYTES    (1 << 14)
#define AES_CNT_OUTPUT_FIFO_DMA_SIZE_12_BYTES   (2 << 14)
#define AES_CNT_OUTPUT_FIFO_DMA_SIZE_16_BYTES   (3 << 14)
#define AES_CNT_OUTPUT_FIFO_DMA_SIZE_MASK       (3 << 14)

#define AES_CNT_MAC_SIZE_4_BYTES                (1 << 16)
#define AES_CNT_MAC_SIZE_6_BYTES                (2 << 16)
#define AES_CNT_MAC_SIZE_8_BYTES                (3 << 16)
#define AES_CNT_MAC_SIZE_10_BYTES               (4 << 16)
#define AES_CNT_MAC_SIZE_12_BYTES               (5 << 16)
#define AES_CNT_MAC_SIZE_14_BYTES               (6 << 16)
#define AES_CNT_MAC_SIZE_16_BYTES               (7 << 16)

#define AES_CNT_ASSOCIATED_DATA_TO_OUTPUT_FIFO  (1 << 19)

#define AES_CNT_MAC_SOURCE_INPUT_FIFO           (0 << 20)
#define AES_CNT_MAC_SOURCE_MAC_REGISTER         (1 << 20)
#define AES_CNT_MAC_SOURCE_MASK                 (1 << 20)

#define AES_CNT_MAC_RESULT_INVALID              (0 << 21)
#define AES_CNT_MAC_RESULT_VERIFIED             (1 << 21)

#define AES_CNT_KEY_APPLY                       (1 << 24)
#define AES_CNT_KEY_BUSY                        (1 << 25)

#define AES_CNT_KEY_SLOT_SHIFT                  26
#define AES_CNT_KEY_SLOT_MASK                   (3 << AES_CNT_KEY_SLOT_SHIFT)

#define AES_CNT_MODE_CCM_DECRYPT                (0 << 28)
#define AES_CNT_MODE_CCM_ENCRYPT                (1 << 28)
#define AES_CNT_MODE_CTR                        (2 << 28)
#define AES_CNT_MODE_MASK                       (3 << 28)

#define AES_CNT_IRQ                             (1 << 30)
#define AES_CNT_ENABLE                          (1 << 31)

#ifdef __cplusplus
extern "C" {
#endif

static inline u32 aes_getInputFifoCount(void)
{
    return (REG_AES_CNT & AES_CNT_INPUT_FIFO_COUNT_MASK) >> AES_CNT_INPUT_FIFO_COUNT_SHIFT;
}

static inline u32 aes_getOutputFifoCount(void)
{
    return (REG_AES_CNT & AES_CNT_OUTPUT_FIFO_COUNT_MASK) >> AES_CNT_OUTPUT_FIFO_COUNT_SHIFT;
}

static inline void aes_flushInputFifo(void)
{
    REG_AES_CNT |= AES_CNT_INPUT_FIFO_FLUSH;
}

static inline void aes_flushOutputFifo(void)
{
    REG_AES_CNT |= AES_CNT_OUTPUT_FIFO_FLUSH;
}

static inline void aes_setMessageAuthenticationCodeSource(u32 macSource)
{
    REG_AES_CNT = (REG_AES_CNT & ~AES_CNT_MAC_SOURCE_MASK) | macSource;
}

static inline bool aes_getMessageAuthenticationCodeResult(void)
{
    return REG_AES_CNT & AES_CNT_MAC_RESULT_VERIFIED;
}

static inline void aes_waitKeyBusy(void)
{
    while (REG_AES_CNT & AES_CNT_KEY_BUSY);
}

static inline void aes_setKeySlot(u32 keySlot)
{
    aes_waitKeyBusy();
    REG_AES_CNT = (REG_AES_CNT & ~AES_CNT_KEY_SLOT_MASK) | (keySlot << AES_CNT_KEY_SLOT_SHIFT) | AES_CNT_KEY_APPLY;
}

static inline void aes_start(u32 inputDmaBlockSize, u32 outputDmaBlockSize, u32 mode, bool irq)
{
    REG_AES_CNT = (irq ? AES_CNT_IRQ : 0) | AES_CNT_ENABLE | mode | inputDmaBlockSize | outputDmaBlockSize;
}

static inline void aes_waitBusy(void)
{
    while (REG_AES_CNT & AES_CNT_ENABLE);
}

static inline void aes_setAssociatedBlockCount(u16 associatedBlockCount)
{
    REG_AES_ASO_LEN = associatedBlockCount;
}

static inline void aes_setPayloadBlockCount(u16 payloadBlockCount)
{
    REG_AES_PLD_LEN = payloadBlockCount;
}

static inline void aes_setInitializationVector(const aes_u128_t* initializationVector)
{
    REG_AES_NNC_CTR.words[0] = initializationVector->words[0];
    REG_AES_NNC_CTR.words[1] = initializationVector->words[1];
    REG_AES_NNC_CTR.words[2] = initializationVector->words[2];
    REG_AES_NNC_CTR.words[3] = initializationVector->words[3];
}

static inline void aes_setMessageAuthenticationCode(const aes_u128_t* messageAuthenticationCode)
{
    REG_AES_MAC.words[0] = messageAuthenticationCode->words[0];
    REG_AES_MAC.words[1] = messageAuthenticationCode->words[1];
    REG_AES_MAC.words[2] = messageAuthenticationCode->words[2];
    REG_AES_MAC.words[3] = messageAuthenticationCode->words[3];
}

static inline void aes_setKey(u32 keySlot, const aes_u128_t* key)
{
    aes_waitKeyBusy();
    (&REG_AES_KEY0)[keySlot * 3].words[0] = key->words[0];
    (&REG_AES_KEY0)[keySlot * 3].words[1] = key->words[1];
    (&REG_AES_KEY0)[keySlot * 3].words[2] = key->words[2];
    (&REG_AES_KEY0)[keySlot * 3].words[3] = key->words[3];
}

static inline void aes_setKeyX(u32 keySlot, const aes_u128_t* keyX)
{
    aes_waitKeyBusy();
    (&REG_AES_ID0)[keySlot * 3].words[0] = keyX->words[0];
    (&REG_AES_ID0)[keySlot * 3].words[1] = keyX->words[1];
    (&REG_AES_ID0)[keySlot * 3].words[2] = keyX->words[2];
    (&REG_AES_ID0)[keySlot * 3].words[3] = keyX->words[3];
}

static inline void aes_setKeyY(u32 keySlot, const aes_u128_t* keyY)
{
    aes_waitKeyBusy();
    (&REG_AES_SEED0)[keySlot * 3].words[0] = keyY->words[0];
    (&REG_AES_SEED0)[keySlot * 3].words[1] = keyY->words[1];
    (&REG_AES_SEED0)[keySlot * 3].words[2] = keyY->words[2];
    (&REG_AES_SEED0)[keySlot * 3].words[3] = keyY->words[3];
}

static inline void aes_setKeyXY(u32 keySlot, const aes_u128_t* keyX, const aes_u128_t* keyY)
{
    aes_waitKeyBusy();
    (&REG_AES_ID0)[keySlot * 3].words[0] = keyX->words[0];
    (&REG_AES_ID0)[keySlot * 3].words[1] = keyX->words[1];
    (&REG_AES_ID0)[keySlot * 3].words[2] = keyX->words[2];
    (&REG_AES_ID0)[keySlot * 3].words[3] = keyX->words[3];
    (&REG_AES_SEED0)[keySlot * 3].words[0] = keyY->words[0];
    (&REG_AES_SEED0)[keySlot * 3].words[1] = keyY->words[1];
    (&REG_AES_SEED0)[keySlot * 3].words[2] = keyY->words[2];
    (&REG_AES_SEED0)[keySlot * 3].words[3] = keyY->words[3];
}

#ifdef __cplusplus
}
#endif
