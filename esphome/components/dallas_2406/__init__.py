import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import one_wire, binary_sensor
from esphome.const import (
    CONF_ID,
)

CODEOWNERS = ["@autoantwort"]

DEPENDENCIES = ["one_wire"]
MULTI_CONF = True
CONF_DALLAS_2406_ID = "dallas_2406_id"


dallas_2406_ns = cg.esphome_ns.namespace("dallas_2406")

Dallas2406 = dallas_2406_ns.class_(
    "Dallas2406",
    cg.PollingComponent,
    one_wire.OneWireDevice,
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Dallas2406Sensor),
        }
    )
    .extend(one_wire.one_wire_device_schema())
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await one_wire.register_one_wire_device(var, config)

