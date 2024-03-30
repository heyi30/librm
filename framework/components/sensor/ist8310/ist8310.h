/**
 * @file    components/sensor/ist8310.h
 * @brief   IST8310磁力计类
 */

#ifndef EC_LIB_COMPONENTS_SENSOR_IST8310_IST8310_H_
#define EC_LIB_COMPONENTS_SENSOR_IST8310_IST8310_H_

#include "hal_wrapper/hal.h"
#if defined(HAL_I2C_MODULE_ENABLED)

#include "hal_wrapper/i2c_device.h"
#include "modules/typedefs.h"

namespace irobot_ec::components::sensor {

enum class IST8310Status : uint8_t {
  NO_ERROR = 0x00,
  NO_SENSOR = 0x40,
  SENSOR_ERROR = 0x80,
};

/**
 * @brief IST8310磁力计
 */
class IST8310 : public irobot_ec::hal::I2cDevice {
 public:
  IST8310(I2C_HandleTypeDef &hi2c, GPIO_TypeDef *rst_port, uint16_t rst_pin);
  void Reset();
  void Update();
  [[nodiscard]] IST8310Status status() const;
  [[nodiscard]] fp32 mag_x() const;
  [[nodiscard]] fp32 mag_y() const;
  [[nodiscard]] fp32 mag_z() const;

 private:
  GPIO_TypeDef *rst_port_;
  uint16_t rst_pin_;
  IST8310Status status_;
  fp32 mag_[3]{0};
};

}  // namespace irobot_ec::components::sensor

#endif

#endif  // EC_LIB_COMPONENTS_SENSOR_IST8310_IST8310_H_