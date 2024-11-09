
#include "unitree_motor.hpp"
#include "librm/hal/serial_interface.h"
#include "librm/hal/spi_interface.h"
#include "librm/modules/algorithm/crc32.h"

using namespace rm::device;

UnitreeMotor::UnitreeMotor(hal::SerialInterface &serial, u8 motor_id) : serial_(&serial) {
  static hal::SerialRxCallbackFunction rx_callback =
      std::bind(&UnitreeMotor::RxCallback, this, std::placeholders::_1, std::placeholders::_2);
  this->serial_->AttachRxCallback(rx_callback);

  send_data_.head.motor_id = motor_id;
}

void UnitreeMotor::SetTau(f32 tau) {
  this->ctrl_param_.tau = tau;
  this->ctrl_param_.vel = 0;
  this->ctrl_param_.pos = 0;
  this->ctrl_param_.kp = 0;
  this->ctrl_param_.kd = 0;

  SetParam(this->ctrl_param_); 
}

void UnitreeMotor::SendCommend() { this->serial_->Write(tx_buffer_, sizeof(tx_buffer_)); }

void UnitreeMotor::RxCallback(const std::vector<u8> &data, u16 rx_len) {
  if (rx_len != 78) { return; }

  std::copy(data.begin(), data.end(), reinterpret_cast<u8 *>(&recv_data_));

  this->fb_param_.mode = recv_data_.data.mode;
  this->fb_param_.temp = recv_data_.data.temp;
  this->fb_param_.m_error = recv_data_.data.m_error;

  this->fb_param_.tau = (f32)((f32)recv_data_.data.tau / 256.0f);
  this->fb_param_.vel = (f32)((f32)recv_data_.data.vel / 128.0f);

  this->fb_param_.acc = (i16)recv_data_.data.acc;
  this->fb_param_.pos = (f32)((f32)recv_data_.data.pos * 6.2832f / 16384.0f);

  this->fb_param_.gyro[0] = (f32)(((f32)recv_data_.data.gyro[0]) * 0.00107993176f);
  this->fb_param_.gyro[1] = (f32)(((f32)recv_data_.data.gyro[1]) * 0.00107993176f);
  this->fb_param_.gyro[2] = (f32)(((f32)recv_data_.data.gyro[2]) * 0.00107993176f);

  this->fb_param_.accel[0] = (f32)(((f32)recv_data_.data.accel[0]) * 0.0023911132f);
  this->fb_param_.accel[1] = (f32)(((f32)recv_data_.data.accel[1]) * 0.0023911132f);
  this->fb_param_.accel[2] = (f32)(((f32)recv_data_.data.accel[2]) * 0.0023911132f);
}

void UnitreeMotor::SetParam(const control_param &ctrl_param) {
  send_data_.data.mode = 10;
  send_data_.data.modify_bit = 0xFF;
  send_data_.data.read_bit = 0x0;
  send_data_.data.reserved = 0x0;
  send_data_.data.Modify.L = 0;
  send_data_.data.tau = ctrl_param.tau * 256;
  send_data_.data.vel = ctrl_param.vel * 128;
  send_data_.data.pos = (f32)((ctrl_param.pos / 6.2832) * 16384.f);
  send_data_.data.kp = ctrl_param.kp * 2048;
  send_data_.data.kd = ctrl_param.kd * 1024;

  send_data_.data.LowHzMotorCmdIndex = 0;
  send_data_.data.LowHzMotorCmdByte = 0;

  send_data_.crc.ku32 = crc32_core((u32 *)(&send_data_), 7);

  std::copy(reinterpret_cast<u8 *>(&send_data_), reinterpret_cast<u8 *>(&send_data_) + sizeof(send_data_), tx_buffer_);
}