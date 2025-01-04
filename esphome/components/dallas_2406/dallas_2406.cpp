#include "dallas_2406.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dallas_2406 {

// Datasheet: https://www.analog.com/media/en/technical-documentation/data-sheets/ds2406.pdf

static const char *const TAG = "dallas.2406";

static const uint8_t DALLAS_COMMAND_CHANNEL_ACCESS = 0xF5;

void Dallas2406::dump_config() {
  ESP_LOGCONFIG(TAG, "Dallas 2406 Sensor:");
  if (this->address_ == 0) {
    ESP_LOGW(TAG, "  Unable to select an address");
    return;
  }
  LOG_ONE_WIRE_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
#ifdef USE_BINARY_SENSOR
  LOG_BINARY_SENSOR("  ", "Channel 1", this->channel_1_);
  LOG_BINARY_SENSOR("  ", "Channel 2", this->channel_2_);
#endif
}

void Dallas2406::update() {
  if (this->address_ == 0)
    return;

  this->send_command_(DALLAS_COMMAND_CHANNEL_ACCESS);
  // CHANNEL CONTROL BYTE 1
  // BIT 7  BIT 6  BIT 5  BIT 4  BIT 3  BIT 2  BIT 1  BIT 0
  // ALR    IM     TOG    IC     CHS1   CHS0   CRC1   CRC0
  uint8_t channel_control_byte_1 = 0b10000100; // select channel A only
  this->bus_->write8(channel_control_byte_1);
  uint8_t channel_control_byte_2 = 0xFF; // per datasheet
  this->bus_->write8(channel_control_byte_2);

  // read CHANNEL INFO BYTE
  const uint8_t channel_info_byte = this->bus_->read8();
  const bool pio_a_flipflop = channel_info_byte & 0x01;
  const bool pio_b_flipflop = channel_info_byte & 0x02;
  const bool pio_a_sensed_level = channel_info_byte & 0x04;
  const bool pio_b_sensed_level = channel_info_byte & 0x08;
  const bool pio_a_activity_latch = channel_info_byte & 0x10;
  const bool pio_b_activity_latch = channel_info_byte & 0x20;
  const bool has_channel_b = channel_info_byte & 0x40;
  const bool has_supply = channel_info_byte & 0x80;
  ESP_LOGD(TAG, "Got pio_a_flipflop=%d, pio_b_flipflop=%d, pio_a_sensed_level=%d, pio_b_sensed_level=%d, pio_a_activity_latch=%d, pio_b_activity_latch=%d, has_channel_b=%d, has_supply=%d",
         pio_a_flipflop, pio_b_flipflop, pio_a_sensed_level, pio_b_sensed_level,
         pio_a_activity_latch, pio_b_activity_latch, has_channel_b, has_supply);
  
#ifdef USE_BINARY_SENSOR
  if (this->channel_1_)
    this->channel_1_->publish_state(pio_a_sensed_level);
  if (this->channel_2_) {
    if (!has_channel_b) {
      this->channel_2_->publish_state(pio_b_sensed_level);
      this->status_clear_warning();
    } else {
      this->status_set_warning("Channel 2 not available");
    }
  }
#endif
  this->bus_->reset();
}

void Dallas2406::setup() {

}

}  // namespace dallas_2406
}  // namespace esphome
