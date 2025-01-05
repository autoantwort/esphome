#include "dallas_2406_switch.h"

namespace esphome {
namespace dallas_2406 {

void Dallas2406Switch::write_state(bool state) {
  if (this->channel_ != 0) {
    this->parent_->write_state(this->channel_, state);
  }
}

}  // namespace dallas_2406
}  // namespace esphome
