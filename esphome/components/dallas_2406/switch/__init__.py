import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv

from .. import CONF_DALLAS_2406_ID, Dallas2406, dallas_2406_ns

DEPENDENCIES = ["dallas_2406"]

Dallas2406Switch = dallas_2406_ns.class_("Dallas2406Switch", switch.Switch)

CONF_CHANNEL = "channel"
CHANNELS = [1, 2]

CONFIG_SCHEMA = switch.switch_schema(Dallas2406Switch).extend(
    {
        cv.GenerateID(CONF_DALLAS_2406_ID): cv.use_id(Dallas2406),
        cv.Required(CONF_CHANNEL): cv.one_of(*CHANNELS, int=True),
    }
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_parented(var, config[CONF_DALLAS_2406_ID])
    cg.add(var.set_channel(config[CONF_CHANNEL]))
