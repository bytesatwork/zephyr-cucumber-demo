#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include <zephyr/drivers/gpio/gpio_emul.h>

#define MAIN_LOOP_PERIOD_MS 100
#define TIME_SLACK_MS       2

namespace
{

const gpio_dt_spec proximity_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(example_sensor), input_gpios);

void set_proximity_sensor(int enabled)
{
	gpio_emul_input_set(proximity_gpio.port, proximity_gpio.pin, enabled);
}

void wait_for_main_tick(void)
{
	k_sleep(K_TIMEOUT_ABS_MS(ROUND_UP(k_uptime_get() + 1, MAIN_LOOP_PERIOD_MS + 1)));
}

WHEN("^I trigger the proximity sensor$")
{
	set_proximity_sensor(1);
	wait_for_main_tick();
	set_proximity_sensor(0);
}

}
