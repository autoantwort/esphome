import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_CHANNEL
from . import Dallas2406, CONF_DALLAS_2406_ID

DEPENDENCIES = ["dallas_2406"]

CHANNELS = [1, 2]

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema().extend(
    {
        cv.GenerateID(CONF_DALLAS_2406_ID): cv.use_id(Dallas2406),
        cv.Required(CONF_CHANNEL): cv.one_of(*CHANNELS, int=True),
    }
)

async def to_code(config):
    hub = await cg.get_variable(config[CONF_DALLAS_2406_ID])
    var = await binary_sensor.new_binary_sensor(config)
    func = getattr(hub, f"set_channel_{config[CONF_CHANNEL]}_binary_sensor")
    cg.add(func(var))
