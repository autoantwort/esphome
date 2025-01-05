#pragma once

#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"

#include "../dallas_2406.h"

namespace esphome {
namespace dallas_2406 {

class Dallas2406Switch : public switch_::Switch, public Parented<Dallas2406> {
 public:
  void write_state(bool state) override;
  void set_channel(uint8_t channel) { this->channel_ = channel; }

 protected:
  uint8_t channel_{0};
};

}  // namespace dallas_2406
}  // namespace esphome
