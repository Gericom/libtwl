#include <nds.h>
#include "libtwl/sio/sio.h"
#include "libtwl/sio/sioRtc.h"

// rtc setup/hold duration
#define RTC_WAIT_200NS  0
// rtc clock pulse duration
#define RTC_WAIT_1US    7

/// @brief Waits the given number of iterations of a loop
///        that takes 4 cycles per iteration.
/// @note  Calling this method and returning takes at least 8 cycles.
///        As such the number of cycles is 8 + iterations * 4.
extern void rtc_waitByLoop(int iterations);

static inline void sendBit(u32 bit)
{
    REG_RCNT1 = (REG_RCNT1 & ~(RCNT1_DATA_RTC_SIO | RCNT1_DATA_RTC_SCK)) | (bit ? RCNT1_DATA_RTC_SIO : 0);
    rtc_waitByLoop(RTC_WAIT_1US);
    REG_RCNT1 |= RCNT1_DATA_RTC_SCK;
    rtc_waitByLoop(RTC_WAIT_1US);
}

static inline void sendByte(u32 byte)
{
    // all rtc pins to output, CS high
    sio_setRtcPins(
        RCNT1_DIR_RTC_CS_OUTPUT | RCNT1_DIR_RTC_SCK_OUTPUT | RCNT1_DIR_RTC_SIO_OUTPUT,
        RCNT1_DATA_RTC_CS);
    for (u32 i = 0; i < 8; i++)
    {
        sendBit((byte >> i) & 1);
    }
}

static inline u32 receiveBit(void)
{
    REG_RCNT1 &= ~(RCNT1_DATA_RTC_SIO | RCNT1_DATA_RTC_SCK);
    rtc_waitByLoop(RTC_WAIT_1US);
    u32 result = REG_RCNT1 & RCNT1_DATA_RTC_SIO;
    REG_RCNT1 |= RCNT1_DATA_RTC_SCK;
    rtc_waitByLoop(RTC_WAIT_1US);
    return result;
}

static inline u32 receiveByte(void)
{
    // CS and SCK output, SIO input, CS high
    sio_setRtcPins(
        RCNT1_DIR_RTC_CS_OUTPUT | RCNT1_DIR_RTC_SCK_OUTPUT,
        RCNT1_DATA_RTC_CS);
    u32 result = 0;
    for (u32 i = 0; i < 8; i++)
    {
        result = (result >> 1) | (receiveBit() << 7);
    }
    return result;
}

static void startTransfer(void)
{
    // to use the rtc pins we must be in gpio mode
    sio_setGpioMode(RCNT0_L_MODE_GPIO);
    // all rtc pins to output, SCK high
    sio_setRtcPins(
        RCNT1_DIR_RTC_CS_OUTPUT | RCNT1_DIR_RTC_SCK_OUTPUT | RCNT1_DIR_RTC_SIO_OUTPUT,
        RCNT1_DATA_RTC_SCK);
    rtc_waitByLoop(RTC_WAIT_200NS); // setup/hold
    // set CS high
    sio_setRtcChipSelect(true);
    rtc_waitByLoop(RTC_WAIT_200NS); // setup/hold
}

static void endTransfer(void)
{
    rtc_waitByLoop(RTC_WAIT_200NS); // setup/hold
    // set CS low
    sio_setRtcChipSelect(false);
    rtc_waitByLoop(RTC_WAIT_200NS); // setup/hold
}

static int bcdToDecimal(u8 bcd)
{
    u32 ones = bcd & 0xF;
    if (ones > 9)
        return -1;
    u32 tens = bcd >> 4;
    if (tens > 9)
        return -1;
    return tens * 10 + ones;
}

static u8 decimalToBcd(u32 decimal)
{
    u32 ones = decimal % 10;
    u32 tens = decimal / 10;
    return (tens << 4) | ones;
}

static void alarmTo24Hour(rtc_alarm_t* alarm)
{
    int alarm1Hour = bcdToDecimal(alarm->hour);
    if (alarm1Hour < 0 || alarm1Hour > 23)
    {
        alarm->hour = 0;
        alarm->amPm = RTC_AM;
    }
    else if (alarm->amPm != RTC_AM && alarm1Hour < 12)
    {
        alarm->hour = decimalToBcd(alarm1Hour + 12);
    }
    else if (alarm1Hour >= 12)
    {
        alarm->amPm = RTC_PM;
    }
}

void rtc_init(void)
{
    u32 status1 = rtc_readStatus1();
    u32 status2 = rtc_readStatus2();
    if ((status1 & (RTC_STATUS1_POC | RTC_STATUS1_BLD)) || (status2 & RTC_STATUS2_TEST))
    {
        status1 |= RTC_STATUS1_RESET;
        rtc_writeStatus1(status1);
    }
    if (status1 & (RTC_STATUS1_INT1 | RTC_STATUS1_INT2))
    {
        status2 &= ~(RTC_STATUS2_INT1FE | RTC_STATUS2_INT1ME | RTC_STATUS2_INT1AE | RTC_STATUS2_32KE);
        status2 &= ~RTC_STATUS2_INT2AE;
        rtc_writeStatus2(status2);
    }
    if (!(status1 & RTC_STATUS1_24HOUR))
    {
        status1 |= RTC_STATUS1_24HOUR;
        rtc_writeStatus1(status1);
        rtc_alarm_t alarm1;
        rtc_readAlarm1(&alarm1);
        alarmTo24Hour(&alarm1);
        rtc_writeAlarm1(&alarm1);
        rtc_alarm_t alarm2;
        rtc_readAlarm2(&alarm2);
        alarmTo24Hour(&alarm2);
        rtc_writeAlarm2(&alarm2);
    }
}

void rtc_readRegister(u32 reg, u8* dst, u32 length)
{
    reg |= 0x80; // read
    startTransfer();
    sendByte(reg);
    for (u32 i = 0; i < length; i++)
        dst[i] = receiveByte();
    endTransfer();
}

void rtc_writeRegister(u32 reg, const u8* src, u32 length)
{
    reg &= ~0x80; // write
    startTransfer();
    sendByte(reg);
    for (u32 i = 0; i < length; i++)
        sendByte(src[i]);
    endTransfer();
}
