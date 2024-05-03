#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_uart.h>
#include <hi_io.h>
#include "iot_gpio.h"
#include "iot_uart.h"
#include "hi_io.h"
#include "hi_gpio.h"
#include "hi_time.h"
#include "iot_i2c.h"
#include "iot_errno.h"
#include "hal_pz_i2c.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/misc.h"
#include "py/mperrno.h"
#include "py/mperrno.h"
#include "machine/modmachine.h"
#include "machine/machine_i2c.h"
#include "mod_Sentry.h"

#define SENTRY_DEBUG_ENABLE 0

MP_STATIC uint8_t LOG_OUTPUT = 0;

MP_STATIC const mp_rom_map_elem_t mp_sentry_obj_info_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kStatus), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kXValue), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kYValue), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kWidthValue), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kHeightValue), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kLabel), MP_ROM_INT(6)},
    {MP_ROM_QSTR(MP_QSTR_kRValue), MP_ROM_INT(7)},
    {MP_ROM_QSTR(MP_QSTR_kGValue), MP_ROM_INT(8)},
    {MP_ROM_QSTR(MP_QSTR_kBValue), MP_ROM_INT(9)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry_obj_info_e_locals_dict, mp_sentry_obj_info_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry_obj_info_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry_obj_info_e,
    .locals_dict = (void *)&mp_sentry_obj_info_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry_led_color_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kLedClose), MP_ROM_INT(0)},
    {MP_ROM_QSTR(MP_QSTR_kLedRed), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kLedGreen), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kLedYellow), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kLedBlue), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kLedPurple), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kLedCyan), MP_ROM_INT(6)},
    {MP_ROM_QSTR(MP_QSTR_kLedWhite), MP_ROM_INT(7)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry_led_color_e_locals_dict, mp_sentry_led_color_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry_led_color_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry_led_color_e,
    .locals_dict = (void *)&mp_sentry_led_color_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry_camera_white_balance_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kAutoWhiteBalance), MP_ROM_INT(0)},
    {MP_ROM_QSTR(MP_QSTR_kLockWhiteBalance), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kWhiteLight), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kYellowLight), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kWhiteBalanceCalibrating), MP_ROM_INT(4)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry_camera_white_balance_e_locals_dict, mp_sentry_camera_white_balance_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry_camera_white_balance_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry_camera_white_balance_e,
    .locals_dict = (void *)&mp_sentry_camera_white_balance_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry_color_label_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kColorBlack), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kColorWhite), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kColorRed), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kColorGreen), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kColorBlue), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kColorYellow), MP_ROM_INT(6)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry_color_label_e_locals_dict, mp_sentry_color_label_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry_color_label_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry_color_label_e,
    .locals_dict = (void *)&mp_sentry_color_label_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry1_vision_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kVisionColor), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kVisionBlob), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kVisionBall), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kVisionLine), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kVisionCard), MP_ROM_INT(6)},
    {MP_ROM_QSTR(MP_QSTR_kVisionBody), MP_ROM_INT(7)},
    {MP_ROM_QSTR(MP_QSTR_kVisionQrCode), MP_ROM_INT(9)},
    {MP_ROM_QSTR(MP_QSTR_kVisionMotionDetect), MP_ROM_INT(11)},
    {MP_ROM_QSTR(MP_QSTR_kVisionMaxType), MP_ROM_INT(12)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry1_vision_e_locals_dict, mp_sentry1_vision_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry1_vision_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry1_vision_e,
    .locals_dict = (void *)&mp_sentry1_vision_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry1_card_label_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kCardForward), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kCardLeft), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kCardRight), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kCardTurnAround), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kCardPark), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kCardCheck), MP_ROM_INT(11)},
    {MP_ROM_QSTR(MP_QSTR_kCardCross), MP_ROM_INT(12)},
    {MP_ROM_QSTR(MP_QSTR_kCardCircle), MP_ROM_INT(13)},
    {MP_ROM_QSTR(MP_QSTR_kCardSquare), MP_ROM_INT(14)},
    {MP_ROM_QSTR(MP_QSTR_kCardTriangle), MP_ROM_INT(15)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry1_card_label_e_locals_dict, mp_sentry1_card_label_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry1_card_label_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry1_card_label_e,
    .locals_dict = (void *)&mp_sentry1_card_label_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry2_vision_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kVisionColor), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kVisionBlob), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kVisionAprilTag), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kVisionLine), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kVisionLearning), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kVisionCard), MP_ROM_INT(6)},
    {MP_ROM_QSTR(MP_QSTR_kVisionFace), MP_ROM_INT(7)},
    {MP_ROM_QSTR(MP_QSTR_kVision20Classes), MP_ROM_INT(8)},
    {MP_ROM_QSTR(MP_QSTR_kVisionQrCode), MP_ROM_INT(9)},
    {MP_ROM_QSTR(MP_QSTR_kVisionCustom), MP_ROM_INT(10)},
    {MP_ROM_QSTR(MP_QSTR_kVisionMotionDetect), MP_ROM_INT(11)},
    {MP_ROM_QSTR(MP_QSTR_kVisionMaxType), MP_ROM_INT(12)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry2_vision_e_locals_dict, mp_sentry2_vision_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry2_vision_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry2_vision_e,
    .locals_dict = (void *)&mp_sentry2_vision_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry2_card_label_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kCardForward), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kCardLeft), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kCardRight), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kCardTurnAround), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kCardPark), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kCardGreenLight), MP_ROM_INT(6)},
    {MP_ROM_QSTR(MP_QSTR_kCardRedLight), MP_ROM_INT(7)},
    {MP_ROM_QSTR(MP_QSTR_kCardSpeed40), MP_ROM_INT(8)},
    {MP_ROM_QSTR(MP_QSTR_kCardSpeed60), MP_ROM_INT(9)},
    {MP_ROM_QSTR(MP_QSTR_kCardSpeed80), MP_ROM_INT(10)},
    {MP_ROM_QSTR(MP_QSTR_kCardCheck), MP_ROM_INT(11)},
    {MP_ROM_QSTR(MP_QSTR_kCardCross), MP_ROM_INT(12)},
    {MP_ROM_QSTR(MP_QSTR_kCardCircle), MP_ROM_INT(13)},
    {MP_ROM_QSTR(MP_QSTR_kCardSquare), MP_ROM_INT(14)},
    {MP_ROM_QSTR(MP_QSTR_kCardTriangle), MP_ROM_INT(15)},
    {MP_ROM_QSTR(MP_QSTR_kCardPlus), MP_ROM_INT(16)},
    {MP_ROM_QSTR(MP_QSTR_kCardMinus), MP_ROM_INT(17)},
    {MP_ROM_QSTR(MP_QSTR_kCardDivide), MP_ROM_INT(18)},
    {MP_ROM_QSTR(MP_QSTR_kCardEqual), MP_ROM_INT(19)},
    {MP_ROM_QSTR(MP_QSTR_kCardZero), MP_ROM_INT(20)},
    {MP_ROM_QSTR(MP_QSTR_kCardOne), MP_ROM_INT(21)},
    {MP_ROM_QSTR(MP_QSTR_kCardTwo), MP_ROM_INT(22)},
    {MP_ROM_QSTR(MP_QSTR_kCardThree), MP_ROM_INT(23)},
    {MP_ROM_QSTR(MP_QSTR_kCardFour), MP_ROM_INT(24)},
    {MP_ROM_QSTR(MP_QSTR_kCardFive), MP_ROM_INT(25)},
    {MP_ROM_QSTR(MP_QSTR_kCardSix), MP_ROM_INT(26)},
    {MP_ROM_QSTR(MP_QSTR_kCardSeven), MP_ROM_INT(27)},
    {MP_ROM_QSTR(MP_QSTR_kCardEight), MP_ROM_INT(28)},
    {MP_ROM_QSTR(MP_QSTR_kCardNine), MP_ROM_INT(29)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry2_card_label_e_locals_dict, mp_sentry2_card_label_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry2_card_label_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry2_card_label_e,
    .locals_dict = (void *)&mp_sentry2_card_label_e_locals_dict,
};
MP_STATIC const mp_rom_map_elem_t mp_sentry_class20_label_e_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_kAirplane), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_kBicycle), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_kBird), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_kBoat), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_kBottle), MP_ROM_INT(5)},
    {MP_ROM_QSTR(MP_QSTR_kBus), MP_ROM_INT(6)},
    {MP_ROM_QSTR(MP_QSTR_kCar), MP_ROM_INT(7)},
    {MP_ROM_QSTR(MP_QSTR_kCat), MP_ROM_INT(8)},
    {MP_ROM_QSTR(MP_QSTR_kChair), MP_ROM_INT(9)},
    {MP_ROM_QSTR(MP_QSTR_kCow), MP_ROM_INT(10)},
    {MP_ROM_QSTR(MP_QSTR_kTable), MP_ROM_INT(11)},
    {MP_ROM_QSTR(MP_QSTR_kDog), MP_ROM_INT(12)},
    {MP_ROM_QSTR(MP_QSTR_kHorse), MP_ROM_INT(13)},
    {MP_ROM_QSTR(MP_QSTR_kMotorBike), MP_ROM_INT(14)},
    {MP_ROM_QSTR(MP_QSTR_kPerson), MP_ROM_INT(15)},
    {MP_ROM_QSTR(MP_QSTR_kPlant), MP_ROM_INT(16)},
    {MP_ROM_QSTR(MP_QSTR_kSheep), MP_ROM_INT(17)},
    {MP_ROM_QSTR(MP_QSTR_kSofa), MP_ROM_INT(18)},
    {MP_ROM_QSTR(MP_QSTR_kTrain), MP_ROM_INT(19)},
    {MP_ROM_QSTR(MP_QSTR_kMonitor), MP_ROM_INT(20)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_sentry_class20_label_e_locals_dict, mp_sentry_class20_label_e_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_sentry_class20_label_e_type = {
    {&mp_type_type},
    .name = MP_QSTR_sentry_class20_label_e,
    .locals_dict = (void *)&mp_sentry_class20_label_e_locals_dict,
};

typedef struct _sentry_stream_base_t
{
    mp_obj_base_t *port;
    uint8_t dev_addr;
    sentry_err_t (*Get)(struct _sentry_stream_base_t *self, const uint8_t reg_address, uint8_t *value);
    sentry_err_t (*Set)(struct _sentry_stream_base_t *self, const uint8_t reg_address, const uint8_t value);
    sentry_err_t (*SetParam)(struct _sentry_stream_base_t *self, int vision_type, sentry_object_t *param, int param_id);
    sentry_err_t (*Read)(struct _sentry_stream_base_t *self, int vision_type, sentry_vision_state_t *vision_state);
    sentry_err_t (*Write)(struct _sentry_stream_base_t *self, int vision_type, const sentry_vision_state_t *vision_state);
} sentry_stream_base_t;

/************SentryI2CStream***************/

MP_STATIC uint8_t I2CRead(mp_machine_i2c_obj_t *i2c, uint8_t dev_addr, uint8_t reg_address, uint8_t *temp)
{
    uint32_t ret = SENTRY_OK;

    ret = hal_pz_i2c_write(i2c->id, dev_addr, &reg_address, 1);

    if (ret != HI_ERR_SUCCESS)
    {
        printf("[R:%02x, ERR W:%02x addr:%02x],", reg_address, ret, dev_addr);
        return SENTRY_WRITE_TIMEOUT;
    }

    ret = hal_pz_i2c_read(i2c->id, dev_addr, temp, 1);

    if (ret != HI_ERR_SUCCESS)
    {
        printf("[R:%02x, ERR R:%02x addr:%02x],", reg_address, ret, dev_addr);
        return SENTRY_READ_TIMEOUT;
    }

    // Debug Output
#if SENTRY_DEBUG_ENABLE
    printf("[R:%02x, %02x],", reg_address, *temp);
#endif

    return SENTRY_OK;
}

MP_STATIC uint8_t I2CWrite(mp_machine_i2c_obj_t *i2c, uint8_t dev_addr, uint8_t reg_address, uint8_t value)
{
    uint32_t ret = SENTRY_OK;
    uint8_t buff[2] = {reg_address, value};

    ret = hal_pz_i2c_write(i2c->id, dev_addr, buff, 2);
    if (ret != HI_ERR_SUCCESS)
    {
        printf("[W:%02x,%02x ERR:%02x],", reg_address, value, ret);
        return SENTRY_WRITE_TIMEOUT;
    }
    // Debug Output
#if SENTRY_DEBUG_ENABLE
    printf("[W:%02x,%02x],", reg_address, value);
#endif
    return SENTRY_OK;
}

MP_STATIC sentry_err_t SentryI2CStreamGet(struct _sentry_stream_base_t *self, const uint8_t reg_address, uint8_t *value)
{
    return I2CRead(self->port, self->dev_addr, reg_address, value);
}
MP_STATIC sentry_err_t SentryI2CStreamSet(struct _sentry_stream_base_t *self, const uint8_t reg_address, const uint8_t value)
{
    return I2CWrite(self->port, self->dev_addr, reg_address, value);
}
MP_STATIC sentry_err_t SentryI2CStreamSetParam(struct _sentry_stream_base_t *self, int vision_type, sentry_object_t *param, int param_id)
{
    sentry_err_t err;

    err = I2CWrite(self->port, self->dev_addr, kRegVisionId, vision_type);
    if (err)
        return err;
    err = I2CWrite(self->port, self->dev_addr, kRegParamId, param_id);
    if (err)
        return err;
    I2CWrite(self->port, self->dev_addr, kRegParamValue1H, (param->result_data1 >> 8) & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue1L, param->result_data1 & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue2H, (param->result_data2 >> 8) & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue2L, param->result_data2 & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue3H, (param->result_data3 >> 8) & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue3L, param->result_data3 & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue4H, (param->result_data4 >> 8) & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue4L, param->result_data4 & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue5H, (param->result_data5 >> 8) & 0xFF);
    I2CWrite(self->port, self->dev_addr, kRegParamValue5L, param->result_data5 & 0xFF);

    return SENTRY_OK;
}
MP_STATIC sentry_err_t SentryI2CStreamRead(struct _sentry_stream_base_t *self, int vision_type, sentry_vision_state_t *vision_state)
{
    sentry_err_t err;
    uint8_t result_data_tmp[2];
    err = I2CWrite(self->port, self->dev_addr, kRegVisionId, vision_type);
    if (err)
        return err;
    err = I2CRead(self->port, self->dev_addr, kRegFrameCount, &vision_state->frame);
    if (err)
        return err;
    err = I2CRead(self->port, self->dev_addr, kRegResultNumber, &vision_state->detect);
    if (err)
        return err;
    if (!vision_state->detect)
        return SENTRY_OK;
    vision_state->detect = SENTRY_MAX_RESULT < vision_state->detect
                               ? SENTRY_MAX_RESULT
                               : vision_state->detect;
    for (uint8_t i = 0; i < vision_state->detect; ++i)
    {
        err = I2CWrite(self->port, self->dev_addr, kRegResultId, i + 1);
        if (err)
            return err;
        I2CRead(self->port, self->dev_addr, kRegResultData1L, result_data_tmp);
        I2CRead(self->port, self->dev_addr, kRegResultData1H, result_data_tmp + 1);
        vision_state->vision_result[i].result_data1 =
            result_data_tmp[1] << 8 | result_data_tmp[0];
        I2CRead(self->port, self->dev_addr, kRegResultData2L, result_data_tmp);
        I2CRead(self->port, self->dev_addr, kRegResultData2H, result_data_tmp + 1);
        vision_state->vision_result[i].result_data2 =
            result_data_tmp[1] << 8 | result_data_tmp[0];
        I2CRead(self->port, self->dev_addr, kRegResultData3L, result_data_tmp);
        I2CRead(self->port, self->dev_addr, kRegResultData3H, result_data_tmp + 1);
        vision_state->vision_result[i].result_data3 =
            result_data_tmp[1] << 8 | result_data_tmp[0];
        I2CRead(self->port, self->dev_addr, kRegResultData4L, result_data_tmp);
        I2CRead(self->port, self->dev_addr, kRegResultData4H, result_data_tmp + 1);
        vision_state->vision_result[i].result_data4 =
            result_data_tmp[1] << 8 | result_data_tmp[0];
        I2CRead(self->port, self->dev_addr, kRegResultData5L, result_data_tmp);
        I2CRead(self->port, self->dev_addr, kRegResultData5H, result_data_tmp + 1);
        vision_state->vision_result[i].result_data5 =
            result_data_tmp[1] << 8 | result_data_tmp[0];

        if (kVisionQrCode == vision_type)
        {
            for (uint16_t i = 0; i < vision_state->vision_qr_result[0].length; ++i)
            {
                uint8_t result_id = i / 5 + 2;
                uint8_t offset = i % 5;
                if (0 == i % 5)
                {
                    err = I2CWrite(self->port, self->dev_addr, kRegResultId, result_id);
                }
                if (err)
                    return err;
                I2CRead(self->port, self->dev_addr, kRegResultData1L + 2 * offset, (uint8_t *)(vision_state->vision_qr_result[0].str + i));
            }
            vision_state->vision_qr_result[0].str[vision_state->vision_qr_result[0].length] = 0;
            vision_state->detect = 1;
            break;
        }
    }
    return SENTRY_OK;
}
MP_STATIC sentry_err_t SentryI2CStreamWrite(struct _sentry_stream_base_t *self, int vision_type, const sentry_vision_state_t *vision_state)
{
    sentry_err_t err = SENTRY_OK;

    if (vision_state->detect >= SENTRY_MAX_RESULT)
    {
        return SENTRY_FAIL;
    }

    err = I2CWrite(self->port, self->dev_addr, kRegVisionId, vision_type);
    if (err)
        return err;
    err = I2CWrite(self->port, self->dev_addr, kRegResultNumber, vision_state->detect);
    if (err)
        return err;
    for (uint8_t i = 0; i < vision_state->detect; ++i)
    {
        I2CWrite(self->port, self->dev_addr, kRegResultId, i + 1);
        I2CWrite(self->port, self->dev_addr, kRegResultData1L, vision_state->vision_result[i].result_data1 & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData1H, (vision_state->vision_result[i].result_data1 >> 8) & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData2L, vision_state->vision_result[i].result_data2 & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData2H, (vision_state->vision_result[i].result_data2 >> 8) & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData3L, vision_state->vision_result[i].result_data3 & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData3H, (vision_state->vision_result[i].result_data3 >> 8) & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData4L, vision_state->vision_result[i].result_data4 & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData4H, (vision_state->vision_result[i].result_data4 >> 8) & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData5L, vision_state->vision_result[i].result_data5 & 0xFF);
        I2CWrite(self->port, self->dev_addr, kRegResultData5H, (vision_state->vision_result[i].result_data5 >> 8) & 0xFF);
    }

    return err;
}

MP_STATIC sentry_stream_base_t *mp_SentryI2CStream_make_new(mp_obj_base_t *i2c, uint8_t dev_addr)
{
    sentry_stream_base_t *self = m_new_obj(sentry_stream_base_t);
    if (self == NULL)
    {
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("micropython run out of memory"));
    }

    self->port = i2c;
    self->dev_addr = dev_addr;

    self->Get = SentryI2CStreamGet;
    self->Set = SentryI2CStreamSet;
    self->SetParam = SentryI2CStreamSetParam;
    self->Read = SentryI2CStreamRead;
    self->Write = SentryI2CStreamWrite;

    return self;
}

/************SentryI2CStream***************/

/************SentryUARTStream**************/
MP_STATIC sentry_stream_base_t *mp_SentryUARTStream_make_new(mp_obj_base_t *uart, uint8_t dev_addr)
{
    sentry_stream_base_t *self = m_new_obj(sentry_stream_base_t);
    if (self == NULL)
    {
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("micropython run out of memory"));
    }

    self->port = uart;
    self->dev_addr = dev_addr;

    // self->Get = ;
    // self->Set = ;
    // self->SetParam = ;
    // self->Read = ;
    // self->Write = ;

    return self;
}
/************SentryUARTStream**************/

typedef struct _mp_obj_Sentry_t
{
    mp_obj_base_t base;
    sentry_mode_e mode_;
    uint8_t device_id_;
    uint8_t address_;
    uint16_t img_w_;
    uint16_t img_h_;
    sentry_stream_base_t *stream_;
    sentry_vision_state_t *vision_state_[kVisionMaxType];
} mp_obj_Sentry_t;

MP_STATIC bool malloc_vision_buffer(mp_obj_Sentry_t *self, int vision_type)
{
    if (vision_type && vision_type < kVisionMaxType)
    {
        if (self->vision_state_[vision_type - 1] == NULL)
        {
            self->vision_state_[vision_type - 1] = m_new_obj(sentry_vision_state_t);
        }

        return true;
    }
    return false;
}

MP_STATIC bool free_vision_buffer(mp_obj_Sentry_t *self, int vision_type)
{
    if (vision_type && vision_type < kVisionMaxType)
    {
        m_free(self->vision_state_[vision_type - 1]);
        self->vision_state_[vision_type - 1] = NULL;
    }
    return true;
}

MP_STATIC mp_obj_t mp_Sentry_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 2, 2, false);
    mp_obj_Sentry_t *self = m_new_obj(mp_obj_Sentry_t);
    self->base.type = type;
    self->address_ = mp_obj_get_int(args[1]);
    self->device_id_ = mp_obj_get_int(args[0]);
    self->mode_ = kUnknownMode;

    return MP_OBJ_FROM_PTR(self);
}

MP_STATIC mp_obj_t mp_Sentry_SetDebug(mp_obj_t self_obj, mp_obj_t log_level_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    LOG_OUTPUT = mp_obj_get_int(log_level_obj);

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_Sentry_SetDebug_obj, mp_Sentry_SetDebug);

MP_STATIC sentry_err_t mp_Sentry_SensorLockReg(mp_obj_Sentry_t *self, bool lock)
{
    sentry_err_t err = SENTRY_OK;
    uint8_t status;
    for (;;)
    {
        self->stream_->Get(self->stream_, kRegLock, &status);
        if (err)
            return err;
        if (status == lock)
        {
            return SENTRY_OK;
        }
        err = self->stream_->Set(self->stream_, kRegLock, lock);
        if (err)
            return err;
    }
    return err;
}

MP_STATIC sentry_err_t mp_Sentry_SensorStartupCheck(mp_obj_Sentry_t *self)
{
    sentry_sensor_conf_t conf1;
    int err_count = 0;
    sentry_err_t err;
    for (;;)
    {
        if (++err_count > 100)
            return SENTRY_FAIL; // set max retry times
        err = self->stream_->Get(self->stream_, kRegSensorConfig1, &conf1.sensor_config_reg_value);
        if (!err && conf1.start_up)
            break;
        int32_t delay = 1000000;
        while (delay--)
            ;
    }
    return err;
}

MP_STATIC sentry_err_t mp_Sentry_ProtocolVersionCheck(mp_obj_Sentry_t *self)
{
    uint8_t device_id = 0;
    uint8_t firmware_version = 0;
    int err_count = 0;
    sentry_err_t err;
    for (;;)
    {
        if (++err_count > 3)
            return SENTRY_UNKNOWN_PROTOCOL;
        err = self->stream_->Get(self->stream_, kRegDeviceId, &device_id);
        // TODO: 版本号遵循 MMP(Major.Minor.Patch) 规范，库本身只检查
        // Major.Minor，若版本不对发出警告。 err =
        // self->stream_->Get(self->stream_, kRegFirmwareVersion, &firmware_version); if (!err &&
        // firmware_version > SENTRY_FIRMWARE_VERSION) {
        //   printf("Hardware firmware version is latter than library support
        //   firmware version,\n"
        //          "it may cause");
        // }
        if (!err && device_id == self->device_id_)
            break;
    }
    return err;
}

MP_STATIC sentry_err_t mp_Sentry_GetImageShape(mp_obj_Sentry_t *self)
{
    sentry_err_t err;
    uint8_t tmp[2] = {0};

    err = self->stream_->Get(self->stream_, kRegFrameWidthL, tmp);
    if (err)
        return err;
    err = self->stream_->Get(self->stream_, kRegFrameWidthH, tmp + 1);
    if (err)
        return err;
    self->img_w_ = tmp[1] << 8 | tmp[0];
    err = self->stream_->Get(self->stream_, kRegFrameHeightL, tmp);
    if (err)
        return err;
    err = self->stream_->Get(self->stream_, kRegFrameHeightH, tmp + 1);
    if (err)
        return err;
    self->img_h_ = tmp[1] << 8 | tmp[0];

    return SENTRY_OK;
}

MP_STATIC mp_obj_t mp_Sentry_SensorSetDefault(size_t n_args, const mp_obj_t *args)
{
    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t vision_default_only = 1;
    sentry_sensor_conf_t sensor_config1;
    sentry_err_t err;
    if (n_args == 2)
    {
        vision_default_only = mp_obj_get_int(args[1]);
    }

    err =
        self->stream_->Get(self->stream_, kRegSensorConfig1, &sensor_config1.sensor_config_reg_value);
    if (err)
        return mp_obj_new_int(err);
    if (vision_default_only)
    {
        sensor_config1.disable_vison = 1;
        err =
            self->stream_->Set(self->stream_, kRegSensorConfig1, sensor_config1.sensor_config_reg_value);
        while (sensor_config1.disable_vison)
        {
            err = self->stream_->Get(self->stream_, kRegSensorConfig1,
                                     &sensor_config1.sensor_config_reg_value);
            if (err)
                return mp_obj_new_int(err);
        }
    }
    else
    {
        sensor_config1.default_setting = 1;
        err =
            self->stream_->Set(self->stream_, kRegSensorConfig1, sensor_config1.sensor_config_reg_value);
        while (sensor_config1.default_setting)
        {
            err = self->stream_->Get(self->stream_, kRegSensorConfig1,
                                     &sensor_config1.sensor_config_reg_value);
            if (err)
                return mp_obj_new_int(err);
        }
    }

    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_Sentry_SensorSetDefault_obj,1, 2, mp_Sentry_SensorSetDefault);

MP_STATIC mp_obj_t mp_Sentry_SensorInit(size_t n_args, const mp_obj_t *args)
{
    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t set_default = 1;
    sentry_err_t err;

    if (n_args == 2)
    {
        set_default = mp_obj_get_int(args[1]);
    }

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    /* Check sensor startup*/
    err = mp_Sentry_SensorStartupCheck(self);
    if (err)
        return mp_obj_new_int(err);
    /* Check sentry protocol version */
    err = mp_Sentry_ProtocolVersionCheck(self);

    if (err)
        return mp_obj_new_int(err);
    if (set_default)
    {
        mp_obj_t d_args[1] = {args[0]};
        /* Sensor set default if version is correction. */
        err = MP_OBJ_SMALL_INT_VALUE(mp_Sentry_SensorSetDefault(sizeof(d_args) / sizeof(d_args[0]), &d_args));
        if (err)
            return mp_obj_new_int(err);
    }
    /* Get sensor image shape. */
    err = mp_Sentry_GetImageShape(self);
    if (err)
        return mp_obj_new_int(err);

    return mp_obj_new_int(SENTRY_OK);
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_Sentry_SensorInit_obj, 1, 2, mp_Sentry_SensorInit);

MP_STATIC mp_obj_t mp_Sentry_rows(mp_obj_t self_obj)
{
    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);

    return mp_obj_new_int(self->img_w_);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_Sentry_rows_obj, mp_Sentry_rows);

MP_STATIC mp_obj_t mp_Sentry_cols(mp_obj_t self_obj)
{
    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);

    return mp_obj_new_int(self->img_h_);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_Sentry_cols_obj, mp_Sentry_cols);

MP_STATIC mp_obj_t mp_Sentry_begin(size_t n_args, const mp_obj_t *args)
{
    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(args[0]);
    mp_obj_base_t *communication_port = (mp_obj_base_t *)MP_OBJ_TO_PTR(args[1]);
    mp_int_t set_default = 1;
    sentry_err_t err = SENTRY_OK;

    if (MP_QSTR_I2C == communication_port->type->name)
    {
        if (self->mode_ != kI2CMode)
        {
            if (self->stream_)
            {
                m_free(self->stream_);
                self->stream_ = NULL;
            }
            mp_obj_t d_args[] = {args[0], set_default};
            self->stream_ = mp_SentryI2CStream_make_new(communication_port, self->address_);
            err = MP_OBJ_SMALL_INT_VALUE(mp_Sentry_SensorInit(sizeof(d_args) / sizeof(d_args[0]), &d_args));
            if (err)
            {
                m_free(self->stream_);
                self->stream_ = NULL;
                return mp_obj_new_int(err);
            }
            self->mode_ = kI2CMode;
        }
    }

    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_Sentry_begin_obj, 2, 3, mp_Sentry_begin);

MP_STATIC uint8_t VisionSetStatus(mp_obj_Sentry_t *self, int vision_type, bool enable)
{
    sentry_err_t err;
    sentry_vision_conf1_t vision_config1;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    err = self->stream_->Set(self->stream_, kRegVisionId, vision_type);
    if (err)
        return err;
    err =
        self->stream_->Get(self->stream_, kRegVisionConfig1, &vision_config1.vision_config_reg_value);
    if (err)
        return err;
    if (vision_config1.status != enable)
    {
        vision_config1.status = enable;
        err =
            self->stream_->Set(self->stream_, kRegVisionConfig1, vision_config1.vision_config_reg_value);
        if (err)
            return err;
    }
    if (enable)
    {
        malloc_vision_buffer(self, vision_type);
    }
    else
    {
        free_vision_buffer(self, vision_type);
    }

    return SENTRY_OK;
}

MP_STATIC mp_obj_t mp_Sentry_SetParamNum(mp_obj_t self_obj, mp_obj_t vision_type_obj, mp_obj_t max_num_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t vision_type = mp_obj_get_int(vision_type_obj);
    mp_int_t max_num = mp_obj_get_int(max_num_obj);
    sentry_err_t err;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    max_num = max_num > SENTRY_MAX_RESULT ? SENTRY_MAX_RESULT : max_num;
    err = self->stream_->Set(self->stream_, kRegVisionId, vision_type);
    if (err)
        return mp_obj_new_int(err);

    err = self->stream_->Set(self->stream_, kRegParamNum, max_num);

    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_3(mp_Sentry_SetParamNum_obj, mp_Sentry_SetParamNum);

MP_STATIC mp_obj_t mp_Sentry_SetParam(size_t n_args, const mp_obj_t *args)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t vision_type = mp_obj_get_int(args[1]);
    mp_int_t *param_array = NULL;
    mp_int_t param_id = mp_obj_get_int(args[3]);
    sentry_err_t err;
    sentry_object_t param = {0};

    size_t param_array_len = 0;
    mp_obj_get_array(args[2], &param_array_len, &param_array);
    if (param_array_len == 5)
    {
        param.bot_x_value = mp_obj_get_int(param_array[0]);
        param.bot_y_value = mp_obj_get_int(param_array[1]);
        param.width = mp_obj_get_int(param_array[2]);
        param.height = mp_obj_get_int(param_array[3]);
        param.label = mp_obj_get_int(param_array[4]);
    }
    else
    {
        mp_raise_msg_varg(&mp_type_TypeError, MP_ERROR_TEXT("function missing array 5 arguments"));
    }

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    err = self->stream_->SetParam(self->stream_, vision_type, &param, param_id);
    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_VAR(mp_Sentry_SetParam_obj, 4, mp_Sentry_SetParam);

int mp_Sentry_GetParamNum(mp_obj_Sentry_t *self, int vision_type)
{
    sentry_err_t err;
    uint8_t max_num;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    err = self->stream_->Set(self->stream_, kRegVisionId, vision_type);
    if (err)
        return -1;
    err = self->stream_->Get(self->stream_, kRegParamNum, &max_num);
    if (err)
        return -1;

    return (int)max_num;
}

MP_STATIC mp_obj_t mp_Sentry_VisionBegin(mp_obj_t self_obj, mp_obj_t vision_type_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t vision_type = mp_obj_get_int(vision_type_obj);
    sentry_err_t err;
    uint8_t max_num;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    /* Set Max Result */
    max_num = mp_Sentry_GetParamNum(self, vision_type);
    if (0 > max_num)
    {
        return mp_obj_new_int(SENTRY_FAIL);
    }
    else if (SENTRY_MAX_RESULT < max_num || 0 == max_num)
    {
        err = mp_Sentry_SetParamNum(self_obj, vision_type_obj, mp_obj_new_int(SENTRY_MAX_RESULT));
    }
    err = VisionSetStatus(self, vision_type, true);
    if (err)
        return mp_obj_new_int(err);

    return mp_obj_new_int(SENTRY_OK);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_Sentry_VisionBegin_obj, mp_Sentry_VisionBegin);

MP_STATIC mp_obj_t mp_Sentry_VisionEnd(mp_obj_t self_obj, mp_obj_t vision_type_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t vision_type = mp_obj_get_int(vision_type_obj);
    return mp_obj_new_int(VisionSetStatus(self, vision_type, false));
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_Sentry_VisionEnd_obj, mp_Sentry_VisionEnd);

MP_STATIC uint8_t mp_Sentry_UpdateResult(mp_obj_Sentry_t *self, int vision_type)
{
    sentry_err_t err;
    uint8_t frame;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    /* Must make sure register is unlock! */
    while (SENTRY_OK != mp_Sentry_SensorLockReg(self, false))
        ;
    err = self->stream_->Get(self->stream_, kRegFrameCount, &frame);
    if (err)
        return SENTRY_FAIL;
    if (self->vision_state_[vision_type - 1])
    {
        if (frame != self->vision_state_[vision_type - 1]->frame)
        {
            sentry_vision_state_t vision_state;
            while (SENTRY_OK != mp_Sentry_SensorLockReg(self, true))
                ;
            err = self->stream_->Read(self->stream_, vision_type, &vision_state);
            while (SENTRY_OK != mp_Sentry_SensorLockReg(self, false))
                ;
            if (err)
                return err;
            memcpy(self->vision_state_[vision_type - 1], &vision_state,
                   sizeof(sentry_vision_state_t));
        }
        else
        {
            /* Result not update */
            return SENTRY_FAIL;
        }
    }
    else
    {
        /* Vision uninitialize */
        return SENTRY_FAIL;
    }

    return SENTRY_OK;
}

MP_STATIC int mp_Sentry_read(mp_obj_Sentry_t *self, int vision_type, sentry_obj_info_e obj_info,
                             uint8_t obj_id)
{
    uint8_t vision_idx = vision_type - 1;

    if (obj_id < 1 || obj_id > SENTRY_MAX_RESULT)
    {
        return 0;
    }
    obj_id -= 1;
    if (!self->vision_state_[vision_idx] || vision_idx >= kVisionMaxType)
        return 0;
    switch (obj_info)
    {
    case kStatus:
        return self->vision_state_[vision_idx]->detect;
    case kXValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].x_value;
    case kYValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].y_value;
    case kWidthValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].width;
    case kHeightValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].height;
    case kLabel:
        return self->vision_state_[vision_idx]->vision_result[obj_id].label;
    case kGValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].color_g_value;
    case kRValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].color_r_value;
    case kBValue:
        return self->vision_state_[vision_idx]->vision_result[obj_id].color_b_value;
    default:
        return 0;
    }
}

MP_STATIC mp_obj_t mp_Sentry_GetValue(size_t n_args, const mp_obj_t *args)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t vision_type = mp_obj_get_int(args[1]);
    mp_int_t obj_info = mp_obj_get_int(args[2]);
    mp_int_t obj_id = 1;

    if (n_args == 4)
    {
        obj_id = mp_obj_get_int(args[3]);
    }

    if (obj_info == kStatus)
    {
        if (self->vision_state_[vision_type - 1] == NULL)
        {
            /* Vison not enable */
            return mp_obj_new_int(0);
        }
        while (mp_Sentry_UpdateResult(self, vision_type))
            ;
    }

    return mp_obj_new_int(mp_Sentry_read(self, vision_type, obj_info, obj_id));
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_Sentry_GetValue_obj, 3, 4, mp_Sentry_GetValue);

MP_STATIC mp_obj_t mp_Sentry_VisionSetStatus(mp_obj_t self_obj, mp_obj_t vision_type_obj, mp_obj_t enable_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t vision_type = mp_obj_get_int(vision_type_obj);
    mp_int_t enable = mp_obj_get_int(enable_obj);

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    return mp_obj_new_int(VisionSetStatus(self, vision_type, enable));
}
MP_DEFINE_CONST_FUN_OBJ_3(mp_Sentry_VisionSetStatus_obj, mp_Sentry_VisionSetStatus);

MP_STATIC mp_obj_t mp_Sentry_VisionSetDefault(mp_obj_t self_obj, mp_obj_t vision_type_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t vision_type = mp_obj_get_int(vision_type_obj);
    sentry_err_t err;
    sentry_vision_conf1_t vision_config1;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    err = self->stream_->Set(self->stream_, kRegVisionId, vision_type);
    if (err)
        return mp_obj_new_int(err);
    err =
        self->stream_->Get(self->stream_, kRegVisionConfig1, &vision_config1.vision_config_reg_value);
    if (err)
        return mp_obj_new_int(err);
    vision_config1.default_setting = 1;
    err = self->stream_->Set(self->stream_, kRegVisionConfig1, vision_config1.vision_config_reg_value);
    if (err)
        return mp_obj_new_int(err);
    while (vision_config1.default_setting)
    {
        err = self->stream_->Get(self->stream_, kRegVisionConfig1,
                                 &vision_config1.vision_config_reg_value);
        if (err)
            return mp_obj_new_int(err);
    }

    return mp_obj_new_int(SENTRY_OK);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_Sentry_VisionSetDefault_obj, mp_Sentry_VisionSetDefault);

MP_STATIC mp_obj_t mp_Sentry_VisionGetStatus(mp_obj_t self_obj, mp_obj_t vision_type_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t vision_type = mp_obj_get_int(vision_type_obj);
    uint16_t vision_status;
    uint8_t vision_status_l;
    uint8_t vision_status_h;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    self->stream_->Get(self->stream_, kRegVisionStatus1, &vision_status_l);
    self->stream_->Get(self->stream_, kRegVisionStatus2, &vision_status_h);
    vision_status = (vision_status_h << 8) | vision_status_l;

    return mp_obj_new_int((0x01UL << (vision_type - 1)) & vision_status);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_Sentry_VisionGetStatus_obj, mp_Sentry_VisionGetStatus);

MP_STATIC mp_obj_t mp_Sentry_GetQrCodeValue(mp_obj_t self_obj)
{
    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    if (self->vision_state_[kVisionQrCode - 1] != NULL)
    {
        const char *str = self->vision_state_[kVisionQrCode - 1]->vision_qr_result[0].str;
        return mp_obj_new_str(str, strlen(str));
    }

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_Sentry_GetQrCodeValue_obj, mp_Sentry_GetQrCodeValue);

MP_STATIC mp_obj_t mp_Sentry_SensorSetRestart(mp_obj_t self_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    sentry_err_t err;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    err = self->stream_->Set(self->stream_, kRegRestart, 1);
    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_Sentry_SensorSetRestart_obj, mp_Sentry_SensorSetRestart);

MP_STATIC mp_obj_t mp_Sentry_LedSetColor(size_t n_args, const mp_obj_t *args)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t detected_color = mp_obj_get_int(args[1]);
    mp_int_t undetected_color = mp_obj_get_int(args[2]);
    mp_int_t level = mp_obj_get_int(args[3]);

    sentry_led_conf_t led_config;
    sentry_err_t err;
    uint8_t led_level;
    uint8_t manual;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    /* Set LED brightness level */
    err = self->stream_->Get(self->stream_, kRegLedLevel, &led_level);
    if (err)
        return mp_obj_new_int(err);
    err = self->stream_->Set(self->stream_, kRegLedLevel, (led_level & 0xF0) | (level & 0x0F));
    if (err)
        return mp_obj_new_int(err);
    /* Set LED color */
    err = self->stream_->Get(self->stream_, kRegLedConfig, &led_config.led_reg_value);
    if (err)
        return mp_obj_new_int(err);
    if (detected_color == undetected_color)
    {
        manual = 1;
    }
    else
    {
        manual = 0;
    }
    if (led_config.detected_color != detected_color ||
        led_config.undetected_color != undetected_color ||
        led_config.manual != manual)
    {
        led_config.detected_color = detected_color;
        led_config.undetected_color = undetected_color;
        led_config.manual = manual;
        err = self->stream_->Set(self->stream_, kRegLedConfig, led_config.led_reg_value);
        if (err)
            return mp_obj_new_int(err);
    }

    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_VAR(mp_Sentry_LedSetColor_obj, 4, mp_Sentry_LedSetColor);

MP_STATIC mp_obj_t mp_Sentry_CameraSetAwb(mp_obj_t self_obj, mp_obj_t awb_obj)
{

    mp_obj_Sentry_t *self = (mp_obj_Sentry_t *)MP_OBJ_TO_PTR(self_obj);
    mp_int_t awb = mp_obj_get_int(awb_obj);

    sentry_camera_conf1_t camera_config1;
    sentry_err_t err;

    if (!self->stream_)
        mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Sentry not begein!"));

    /* Waiting for camera white balance calibrating */
    do
    {
        err = self->stream_->Get(self->stream_, kRegCameraConfig1, &camera_config1.camera_reg_value);
    } while (camera_config1.white_balance >= kWhiteBalanceCalibrating);
    camera_config1.white_balance = awb;
    err = self->stream_->Set(self->stream_, kRegCameraConfig1, camera_config1.camera_reg_value);
    if (awb == kLockWhiteBalance)
    {
        // waiting for lock white balance
        do
        {
            err = self->stream_->Get(self->stream_, kRegCameraConfig1, &camera_config1.camera_reg_value);
        } while (camera_config1.white_balance >= kWhiteBalanceCalibrating);
    }
    return mp_obj_new_int(err);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_Sentry_CameraSetAwb_obj, mp_Sentry_CameraSetAwb);

MP_STATIC const mp_rom_map_elem_t mp_Sentry_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_SetDebug), MP_ROM_PTR(&mp_Sentry_SetDebug_obj)},
    {MP_ROM_QSTR(MP_QSTR_rows), MP_ROM_PTR(&mp_Sentry_rows_obj)},
    {MP_ROM_QSTR(MP_QSTR_cols), MP_ROM_PTR(&mp_Sentry_cols_obj)},
    {MP_ROM_QSTR(MP_QSTR_SensorInit), MP_ROM_PTR(&mp_Sentry_SensorInit_obj)},
    {MP_ROM_QSTR(MP_QSTR_begin), MP_ROM_PTR(&mp_Sentry_begin_obj)},
    {MP_ROM_QSTR(MP_QSTR_VisionBegin), MP_ROM_PTR(&mp_Sentry_VisionBegin_obj)},
    {MP_ROM_QSTR(MP_QSTR_VisionEnd), MP_ROM_PTR(&mp_Sentry_VisionEnd_obj)},
    {MP_ROM_QSTR(MP_QSTR_GetValue), MP_ROM_PTR(&mp_Sentry_GetValue_obj)},
    {MP_ROM_QSTR(MP_QSTR_SetParamNum), MP_ROM_PTR(&mp_Sentry_SetParamNum_obj)},
    {MP_ROM_QSTR(MP_QSTR_SetParam), MP_ROM_PTR(&mp_Sentry_SetParam_obj)},
    {MP_ROM_QSTR(MP_QSTR_VisionSetStatus), MP_ROM_PTR(&mp_Sentry_VisionSetStatus_obj)},
    {MP_ROM_QSTR(MP_QSTR_VisionSetDefault), MP_ROM_PTR(&mp_Sentry_VisionSetDefault_obj)},
    {MP_ROM_QSTR(MP_QSTR_VisionGetStatus), MP_ROM_PTR(&mp_Sentry_VisionGetStatus_obj)},
    {MP_ROM_QSTR(MP_QSTR_GetQrCodeValue), MP_ROM_PTR(&mp_Sentry_GetQrCodeValue_obj)},
    {MP_ROM_QSTR(MP_QSTR_SensorSetRestart), MP_ROM_PTR(&mp_Sentry_SensorSetRestart_obj)},
    {MP_ROM_QSTR(MP_QSTR_SensorSetDefault), MP_ROM_PTR(&mp_Sentry_SensorSetDefault_obj)},
    {MP_ROM_QSTR(MP_QSTR_LedSetColor), MP_ROM_PTR(&mp_Sentry_LedSetColor_obj)},
    {MP_ROM_QSTR(MP_QSTR_CameraSetAwb), MP_ROM_PTR(&mp_Sentry_CameraSetAwb_obj)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_Sentry_locals_dict, mp_Sentry_locals_dict_table);

MP_STATIC const mp_obj_type_t mp_Sentry_type = {
    {&mp_type_type},
    .name = MP_QSTR_Sentry,
    .make_new = mp_Sentry_make_new,
    .locals_dict = (void *)&mp_Sentry_locals_dict,
};

MP_STATIC const mp_rom_map_elem_t mp_module_Sentry_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_Sentry)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_OK), MP_ROM_INT(0)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_FAIL), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_WRITE_TIMEOUT), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_READ_TIMEOUT), MP_ROM_INT(3)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_CHECK_ERROR), MP_ROM_INT(4)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_UNSUPPORT_PARAM), MP_ROM_INT(16)},
    {MP_ROM_QSTR(MP_QSTR_SENTRY_UNKNOWN_PROTOCOL), MP_ROM_INT(17)},
    {MP_ROM_QSTR(MP_QSTR_sentry_obj_info_e), MP_ROM_PTR(&mp_sentry_obj_info_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry_led_color_e), MP_ROM_PTR(&mp_sentry_led_color_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry_camera_white_balance_e), MP_ROM_PTR(&mp_sentry_camera_white_balance_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry_color_label_e), MP_ROM_PTR(&mp_sentry_color_label_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry1_vision_e), MP_ROM_PTR(&mp_sentry1_vision_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry1_card_label_e), MP_ROM_PTR(&mp_sentry1_card_label_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry2_vision_e), MP_ROM_PTR(&mp_sentry2_vision_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry2_card_label_e), MP_ROM_PTR(&mp_sentry2_card_label_e_type)},
    {MP_ROM_QSTR(MP_QSTR_sentry_class20_label_e), MP_ROM_PTR(&mp_sentry_class20_label_e_type)},
    {MP_ROM_QSTR(MP_QSTR_Sentry), MP_ROM_PTR(&mp_Sentry_type)},
};
MP_STATIC MP_DEFINE_CONST_DICT(mp_module_Sentry_globals, mp_module_Sentry_globals_table);

const mp_obj_module_t mp_module_Sentry = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&mp_module_Sentry_globals,
};
