import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import one_wire, sensor, binary_sensor
from esphome.const import (
    CONF_RESOLUTION,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    #CONF_CHANNEL_1,
    #CONF_CHANNEL_2,
)

CONF_CHANNEL_1 = "channel_1"
CONF_CHANNEL_2 = "channel_2"

dallas_2406_ns = cg.esphome_ns.namespace("dallas_2406")

Dallas2406Sensor = dallas_2406_ns.class_(
    "Dallas2406",
    cg.PollingComponent,
    one_wire.OneWireDevice,
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Dallas2406Sensor),
            cv.Optional(CONF_CHANNEL_1): binary_sensor.binary_sensor_schema(),
            cv.Optional(CONF_CHANNEL_2): binary_sensor.binary_sensor_schema(),
        }
    )
    .extend(one_wire.one_wire_device_schema())
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await one_wire.register_one_wire_device(var, config)

    if CONF_CHANNEL_1 in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_CHANNEL_1])
        cg.add(var.set_channel_1_sensor(sens))
    
    if CONF_CHANNEL_2 in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_CHANNEL_2])
        cg.add(var.set_channel_2_sensor(sens))
