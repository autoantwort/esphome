#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/one_wire/one_wire.h"
#include "esphome/components/binary_sensor/binary_sensor.h"


namespace esphome {
namespace dallas_2406 {

class Dallas2406 : public PollingComponent, public one_wire::OneWireDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  void set_channel_1_sensor(binary_sensor::BinarySensor *channel_1) { channel_1_ = channel_1; }
  void set_channel_2_sensor(binary_sensor::BinarySensor *channel_2) { channel_2_ = channel_2; }

protected:
  binary_sensor::BinarySensor *channel_1_{nullptr};
  binary_sensor::BinarySensor *channel_2_{nullptr};
};

}  // namespace dallas_2406
}  // namespace esphome
