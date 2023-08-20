#pragma once

#define RTC_AM              0
#define RTC_PM              1

#define RTC_STATUS1_RESET   (1 << 0)
#define RTC_STATUS1_24HOUR  (1 << 1)
#define RTC_STATUS1_SC0     (1 << 2)
#define RTC_STATUS1_SC1     (1 << 3)
#define RTC_STATUS1_INT1    (1 << 4)
#define RTC_STATUS1_INT2    (1 << 5)
#define RTC_STATUS1_BLD     (1 << 6)
#define RTC_STATUS1_POC     (1 << 7)

#define RTC_STATUS2_INT1FE  (1 << 0)
#define RTC_STATUS2_INT1ME  (1 << 1)
#define RTC_STATUS2_INT1AE  (1 << 2)
#define RTC_STATUS2_32KE    (1 << 3)
#define RTC_STATUS2_SC2     (1 << 4)
#define RTC_STATUS2_SC3     (1 << 5)
#define RTC_STATUS2_INT2AE  (1 << 6)
#define RTC_STATUS2_TEST    (1 << 7)

#define RTC_REG_STATUS1     0b00000110
#define RTC_REG_STATUS2     0b01000110
#define RTC_REG_DATA1       0b00100110
#define RTC_REG_DATA2       0b01100110
#define RTC_REG_ALARM1        0b00010110
#define RTC_REG_ALARM2        0b01010110
#define RTC_REG_ADJUST      0b00110110
#define RTC_REG_FREE        0b01110110

#define RTC_EXREG_UPCOUNT   0b00001110
#define RTC_EXREG_FOUT1     0b01001110
#define RTC_EXREG_FOUT2     0b00101110
#define RTC_EXREG_ALARM_EX1 0b00011110
#define RTC_EXREG_ALARM_EX2 0b01011110

typedef struct
{
    /// @brief Represents the year 20xx as the last 2 digits in BCD format.
    u8 year;
    /// @brief Month of the year from 01 to 12 in BCD format.
    u8 month;
    /// @brief Day of the month from 01 to 31 in BCD format.
    u8 monthDay;
    /// @brief Day of the week from 0 to 6.
    /// @note  This is only a counter value. The RTC increases the counter
    ///        each day, and wraps from 6 back to 0. As such which number
    ///        corresponds to Monday is user defined.
    u8 weekDay;
} rtc_date_t;

typedef struct
{
    u8 hour : 6;
    u8 amPm : 2;
    /// @brief Minute from 00 to 59 in BCD format.
    u8 minute;
    /// @brief Second from 00 to 59 in BCD format.
    u8 second;
} rtc_time_t;

typedef struct
{
    rtc_date_t date;
    rtc_time_t time;
} rtc_datetime_t;

typedef struct
{
    u8 weekDay : 7;
    u8 weekDayEnable : 1;
    u8 hour : 6;
    u8 amPm : 1;
    u8 hourEnable : 1;
    u8 minute : 7;
    u8 minuteEnable : 1;
} rtc_alarm_t;

#ifdef LIBTWL_ARM7

#ifdef __cplusplus
extern "C" {
#endif

void rtc_init(void);
void rtc_readRegister(u32 reg, u8* dst, u32 length);
void rtc_writeRegister(u32 reg, const u8* src, u32 length);

static inline u32 rtc_readStatus1(void)
{
    u8 status1;
    rtc_readRegister(RTC_REG_STATUS1, &status1, 1);
    return status1;
}

static inline void rtc_writeStatus1(u8 status1)
{
    rtc_writeRegister(RTC_REG_STATUS1, &status1, 1);
}

static inline u32 rtc_readStatus2(void)
{
    u8 status2;
    rtc_readRegister(RTC_REG_STATUS2, &status2, 1);
    return status2;
}

static inline void rtc_writeStatus2(u8 status2)
{
    rtc_writeRegister(RTC_REG_STATUS2, &status2, 1);
}

static inline void rtc_readDateTime(rtc_datetime_t* dateTime)
{
    rtc_readRegister(RTC_REG_DATA1, (u8*)dateTime, 7);
}

static inline void rtc_readDate(rtc_date_t* date)
{
    rtc_readRegister(RTC_REG_DATA1, (u8*)date, 4);
}

static inline void rtc_readTime(rtc_time_t* time)
{
    rtc_readRegister(RTC_REG_DATA2, (u8*)time, 3);
}

static inline void rtc_readAlarm1(rtc_alarm_t* alarm1)
{
    rtc_readRegister(RTC_REG_ALARM1, (u8*)alarm1, 3);
}

static inline void rtc_writeAlarm1(const rtc_alarm_t* alarm1)
{
    rtc_writeRegister(RTC_REG_ALARM1, (const u8*)alarm1, 3);
}

static inline void rtc_readAlarm2(rtc_alarm_t* alarm2)
{
    rtc_readRegister(RTC_REG_ALARM2, (u8*)alarm2, 3);
}

static inline void rtc_writeAlarm2(const rtc_alarm_t* alarm2)
{
    rtc_writeRegister(RTC_REG_ALARM2, (const u8*)alarm2, 3);
}

static inline u32 rtc_readAdjust(void)
{
    u8 adjust;
    rtc_readRegister(RTC_REG_ADJUST, &adjust, 1);
    return adjust;
}

static inline u32 rtc_readFree(void)
{
    u8 free;
    rtc_readRegister(RTC_REG_FREE, &free, 1);
    return free;
}

#ifdef __cplusplus
}
#endif

#endif
