#pragma once

#define CODEC_PAGE_0                                        0
#define CODEC_PAGE_1                                        1
#define CODEC_PAGE_3                                        3
#define CODEC_PAGE_4                                        4
#define CODEC_PAGE_255                                      255

#define CODEC_REG_PAGE_CONTROL                              0

// == PAGE 0 ==

#define CODEC_REG_PAGE0_RESET                               1

#define CODEC_REG_PAGE0_CLOCK_GEN_MUXING                    4
#define CODEC_REG_PAGE0_PLL_P_R                             5
#define CODEC_REG_PAGE0_PLL_J                               6
#define CODEC_REG_PAGE0_PLL_D_MSB                           7
#define CODEC_REG_PAGE0_PLL_D_LSB                           8

#define CODEC_REG_PAGE0_DAC_NDAC_VAL                        11
#define CODEC_REG_PAGE0_DAC_MDAC_VAL                        12
#define CODEC_REG_PAGE0_DAC_DOSR_VAL_MSB                    13
#define CODEC_REG_PAGE0_DAC_DOSR_VAL_LSB                    14
#define CODEC_REG_PAGE0_DAC_IDAC_VAL                        15
#define CODEC_REG_PAGE0_DAC_MINIDSP_INTERPOLATION           16

#define CODEC_REG_PAGE0_ADC_NADC_VAL                        18
#define CODEC_REG_PAGE0_ADC_MADC_VAL                        19
#define CODEC_REG_PAGE0_ADC_AOSR_VAL                        20
#define CODEC_REG_PAGE0_ADC_IDAC_VAL                        21
#define CODEC_REG_PAGE0_ADC_MINIDSP_DECIMATION              22

#define CODEC_REG_PAGE0_CLKOUT_MUX                          25
#define CODEC_REG_PAGE0_CLKOUT_M_VAL                        26
#define CODEC_REG_PAGE0_CODEC_INTERFACE_CONTROL             27
#define CODEC_REG_PAGE0_DATA_SLOT_OFFSET_PROGRAMMABILITY    28
#define CODEC_REG_PAGE0_CODEC_INTERFACE_CONTROL_2           29
#define CODEC_REG_PAGE0_BCLK_N_VAL                          30
#define CODEC_REG_PAGE0_CODEC_SECONDARY_INTERFACE_CONTROL_1 31
#define CODEC_REG_PAGE0_CODEC_SECONDARY_INTERFACE_CONTROL_2 32
#define CODEC_REG_PAGE0_CODEC_SECONDARY_INTERFACE_CONTROL_3 33
#define CODEC_REG_PAGE0_I2C_BUS_CONDITION                   34

#define CODEC_REG_PAGE0_ADC_FLAG_REGISTER                   36
#define CODEC_REG_PAGE0_DAC_FLAG_REGISTER_1                 37
#define CODEC_REG_PAGE0_DAC_FLAG_REGISTER_2                 38
#define CODEC_REG_PAGE0_OVERFLOW_FLAGS                      39

#define CODEC_REG_PAGE0_DAC_STICKY_INTERRUPT_FLAGS          44
#define CODEC_REG_PAGE0_ADC_STICKY_INTERRUPT_FLAGS          45
#define CODEC_REG_PAGE0_DAC_INTERRUPT_FLAGS                 46
#define CODEC_REG_PAGE0_ADC_INTERRUPT_FLAGS                 47
#define CODEC_REG_PAGE0_INT1_CONTROL_REGISTER               48
#define CODEC_REG_PAGE0_INT2_CONTROL_REGISTER               49
#define CODEC_REG_PAGE0_INT1_INT2_CONTROL_REGISTER          50
#define CODEC_REG_PAGE0_GPIO1_IN_OUT_PIN_CONTROL            51
#define CODEC_REG_PAGE0_GPIO2_IN_OUT_PIN_CONTROL            52
#define CODEC_REG_PAGE0_SDOUT_OUT_PIN_CONTROL               53
#define CODEC_REG_PAGE0_SDIN_IN_PIN_CONTROL                 54
#define CODEC_REG_PAGE0_MISO_OUT_PIN_CONTROL                55
#define CODEC_REG_PAGE0_SCLK_IN_PIN_CONTROL                 56
#define CODEC_REG_PAGE0_GPI1_GPI2_PIN_CONTROL               57
#define CODEC_REG_PAGE0_GPI3_PIN_CONTROL                    58

#define CODEC_REG_PAGE0_DAC_INSTRUCTION_SET                 60
#define CODEC_REG_PAGE0_ADC_INSTRUCTION_SET                 61
#define CODEC_REG_PAGE0_PROGRAMMABLE_INSTRUCTION_MODE_CONTROL_BITS  62
#define CODEC_REG_PAGE0_DAC_DATA_PATH_SETUP                 63
#define CODEC_REG_PAGE0_DAC_VOLUME_CONTROL                  64
#define CODEC_REG_PAGE0_DAC_LEFT_VOLUME_CONTROL             65
#define CODEC_REG_PAGE0_DAC_RIGHT_VOLUME_CONTROL            66
#define CODEC_REG_PAGE0_HEADSET_DETECTION                   67
#define CODEC_REG_PAGE0_DRC_CONTROL_1                       68
#define CODEC_REG_PAGE0_DRC_CONTROL_2                       69
#define CODEC_REG_PAGE0_DRC_CONTROL_3                       70
#define CODEC_REG_PAGE0_LEFT_BEEP_GENERATOR                 71
#define CODEC_REG_PAGE0_RIGHT_BEEP_GENERATOR                72
#define CODEC_REG_PAGE0_BEEP_LENGTH_MSB                     73
#define CODEC_REG_PAGE0_BEEP_LENGTH_MID                     74
#define CODEC_REG_PAGE0_BEEP_LENGTH_LSB                     75
#define CODEC_REG_PAGE0_BEEP_SIN_MSB                        76
#define CODEC_REG_PAGE0_BEEP_SIN_LSB                        77
#define CODEC_REG_PAGE0_BEEP_COS_MSB                        78
#define CODEC_REG_PAGE0_BEEP_COS_LSB                        79

#define CODEC_REG_PAGE0_ADC_DIGITAL_MIC                     81
#define CODEC_REG_PAGE0_ADC_DIGITAL_VOLUME_CONTROL_FINE_ADJUST      82
#define CODEC_REG_PAGE0_ADC_DIGITAL_VOLUME_CONTROL_COARSE_ADJUST    83

#define CODEC_REG_PAGE0_AGC_CONTROL_1                       86
#define CODEC_REG_PAGE0_AGC_CONTROL_2                       87
#define CODEC_REG_PAGE0_AGC_MAXIMUM_GAIN                    88
#define CODEC_REG_PAGE0_AGC_ATTACK_TIME                     89
#define CODEC_REG_PAGE0_AGC_DECAY_TIME                      90
#define CODEC_REG_PAGE0_AGC_NOISE_DEBOUNCE                  91
#define CODEC_REG_PAGE0_AGC_SIGNAL_DEBOUNCE                 92
#define CODEC_REG_PAGE0_AGC_GAIN_APPLIED_READING            93

#define CODEC_REG_PAGE0_ADC_DC_MEASUREMENT_1                102
#define CODEC_REG_PAGE0_ADC_DC_MEASUREMENT_2                103
#define CODEC_REG_PAGE0_ADC_DC_MEASUREMENT_OUTPUT_1         104
#define CODEC_REG_PAGE0_ADC_DC_MEASUREMENT_OUTPUT_2         105
#define CODEC_REG_PAGE0_ADC_DC_MEASUREMENT_OUTPUT_3         106

#define CODEC_REG_PAGE0_VOL_MICDET_PIN_SAR_ADC_VOLUME_CONTROL       116
#define CODEC_REG_PAGE0_VOL_MICDET_PIN_GAIN                 117

// == PAGE 1 ==

#define CODEC_REG_PAGE1_HEADPHONE_SPEAKER_AMPLIFIER_ERROR_CONTROL   30
#define CODEC_REG_PAGE1_HEADPHONE_DRIVERS                   31
#define CODEC_REG_PAGE1_CLASS_D_SPEAKER_AMPLIFIER           32
#define CODEC_REG_PAGE1_HP_OUTPUT_DRIVERS_POP_REMOVAL_SETTINGS      33
#define CODEC_REG_PAGE1_OUTPUT_DRIVER_PGA_RAMP_DOWN_PERIOD_CONTROL  34
#define CODEC_REG_PAGE1_DAC_L_DAC_R_OUTPUT_MIXER_ROUTING    35
#define CODEC_REG_PAGE1_LEFT_ANALOG_VOL_TO_HPL              36
#define CODEC_REG_PAGE1_RIGHT_ANALOG_VOL_TO_HPR             37
#define CODEC_REG_PAGE1_LEFT_ANALOG_VOL_TO_SPL              38
#define CODEC_REG_PAGE1_RIGHT_ANALOG_VOL_TO_SPR             39
#define CODEC_REG_PAGE1_HPL_DRIVER                          40
#define CODEC_REG_PAGE1_HPR_DRIVER                          41
#define CODEC_REG_PAGE1_SPL_DRIVER                          42
#define CODEC_REG_PAGE1_SPR_DRIVER                          43
#define CODEC_REG_PAGE1_HP_DRIVER_CONTROL                   44

#define CODEC_REG_PAGE1_MICBIAS                             46
#define CODEC_REG_PAGE1_MIC_PGA                             47
#define CODEC_REG_PAGE1_DELTA_SIGMA_MONO_ADC_CHANNEL_FINE_GAIN_INPUT_SELECTION_FOR_P_TERMINAL   48
#define CODEC_REG_PAGE1_ADC_INPUT_SELECTION_FOR_M_TERMINAL  49
#define CODEC_REG_PAGE1_INPUT_CM_SETTINGS                   50

// == PAGE 3 ==

#define CODEC_REG_PAGE3_SAR_ADC_CONTROL_1                   2
#define CODEC_REG_PAGE3_SAR_ADC_CONTROL_2                   3
#define CODEC_REG_PAGE3_PRECHARGE_SENSE                     4
#define CODEC_REG_PAGE3_PANEL_VOLTAGE_STABILIZATION         5
#define CODEC_REG_PAGE3_VOLTAGE_REFERENCE                   6

#define CODEC_REG_PAGE3_STATUS_1                            9
#define CODEC_REG_PAGE3_STATUS_2                            10

#define CODEC_REG_PAGE3_BUFFER_MODE                         13

#define CODEC_REG_PAGE3_SCAN_MODE_TIMER                     15
#define CODEC_REG_PAGE3_SCAN_MODE_TIMER_CLOCK               16
#define CODEC_REG_PAGE3_SAR_ADC_CLOCK                       17
#define CODEC_REG_PAGE3_DEBOUNCE_TIME_PEN_UP_DETECTION      18
#define CODEC_REG_PAGE3_AUTO_AUX_MEASUREMENT_SELECTION      19
#define CODEC_REG_PAGE3_TOUCH_SCREEN_PEN_DOWN               20
#define CODEC_REG_PAGE3_THRESHOLD_CHECK_FLAGS_REGISTER      21
#define CODEC_REG_PAGE3_AUX1_MAXIMUM_VALUE_CHECK_MSB        22
#define CODEC_REG_PAGE3_AUX1_MAXIMUM_VALUE_CHECK_LSB        23
#define CODEC_REG_PAGE3_AUX1_MINIMUM_VALUE_CHECK_MSB        24
#define CODEC_REG_PAGE3_AUX1_MINIMUM_VALUE_CHECK_LSB        25
#define CODEC_REG_PAGE3_AUX2_MAXIMUM_VALUE_CHECK_MSB        26
#define CODEC_REG_PAGE3_AUX2_MAXIMUM_VALUE_CHECK_LSB        27
#define CODEC_REG_PAGE3_AUX2_MINIMUM_VALUE_CHECK_MSB        28
#define CODEC_REG_PAGE3_AUX2_MINIMUM_VALUE_CHECK_LSB        29
#define CODEC_REG_PAGE3_TEMPERATURE_MAXIMUM_VALUE_CHECK_MSB 30
#define CODEC_REG_PAGE3_TEMPERATURE_MAXIMUM_VALUE_CHECK_LSB 31
#define CODEC_REG_PAGE3_TEMPERATURE_MINIMUM_VALUE_CHECK_MSB 32
#define CODEC_REG_PAGE3_TEMPERATURE_MINIMUM_VALUE_CHECK_LSB 33

#define CODEC_REG_PAGE3_TOUCHSCREEN_X_COORDINATE_DATA_MSB   42
#define CODEC_REG_PAGE3_TOUCHSCREEN_X_COORDINATE_DATA_LSB   43
#define CODEC_REG_PAGE3_TOUCHSCREEN_Y_COORDINATE_DATA_MSB   44
#define CODEC_REG_PAGE3_TOUCHSCREEN_Y_COORDINATE_DATA_LSB   45
#define CODEC_REG_PAGE3_TOUCHSCREEN_Z1_PRESSURE_REGISTER_MSB        46
#define CODEC_REG_PAGE3_TOUCHSCREEN_Z1_PRESSURE_REGISTER_LSB        47
#define CODEC_REG_PAGE3_TOUCHSCREEN_Z2_PRESSURE_REGISTER_MSB        48
#define CODEC_REG_PAGE3_TOUCHSCREEN_Z2_PRESSURE_REGISTER_LSB        49

#define CODEC_REG_PAGE3_AUX1_DATA_MSB                       54
#define CODEC_REG_PAGE3_AUX1_DATA_LSB                       55
#define CODEC_REG_PAGE3_AUX2_DATA_MSB                       56
#define CODEC_REG_PAGE3_AUX2_DATA_LSB                       57
#define CODEC_REG_PAGE3_VBAT_DATA_MSB                       58
#define CODEC_REG_PAGE3_VBAT_DATA_LSB                       59

#define CODEC_REG_PAGE3_TEMPERATURE_TEMP1_DATA_REGISTER_MSB 66
#define CODEC_REG_PAGE3_TEMPERATURE_TEMP1_DATA_REGISTER_LSB 67
#define CODEC_REG_PAGE3_TEMPERATURE_TEMP2_DATA_REGISTER_MSB 68
#define CODEC_REG_PAGE3_TEMPERATURE_TEMP2_DATA_REGISTER_LSB 69

// == PAGE 255 ==

#define CODEC_REG_PAGE255_DS_AUDIO_CONTROL                  1
#define CODEC_REG_PAGE255_DS_MICROPHONE_CONTROL             2
#define CODEC_REG_PAGE255_DS_MICROPHONE_GAIN                3
#define CODEC_REG_PAGE255_BACKWARDS_COMPATIBILITY_MODE      5
#define CODEC_REG_PAGE255_PAGE_CONTROL                      127

#define CODEC_PAGE255_BACKWARDS_COMPATIBILITY_MODE_ON       0
#define CODEC_PAGE255_BACKWARDS_COMPATIBILITY_MODE_OFF      1

#ifdef __cplusplus
extern "C" {
#endif

u8 codec_readRegister(u8 reg);
void codec_writeRegister(u8 reg, u8 data);

/// @brief Sets the current codec register page. This function cannot be used
///        when the current page is 255.
/// @param page The new register page to use.
void codec_setPage(u8 page)
{
    codec_writeRegister(CODEC_REG_PAGE_CONTROL, page);
}

#ifdef __cplusplus
}
#endif
