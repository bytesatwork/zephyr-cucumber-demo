#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include <zephyr/drivers/gpio/gpio_emul.h>

#define MAIN_LOOP_PERIOD_MS 100
#define TIME_SLACK_MS       2

namespace
{

const gpio_dt_spec proximity_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(example_sensor), input_gpios);
const gpio_dt_spec led_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(blink_led), led_gpios);

void set_proximity_sensor(int enabled)
{
	gpio_emul_input_set(proximity_gpio.port, proximity_gpio.pin, enabled);
}

int get_led_state(void)
{
	return gpio_emul_output_get(led_gpio.port, led_gpio.pin);
}

void wait_for_main_tick(void)
{
	k_sleep(K_TIMEOUT_ABS_MS(ROUND_UP(k_uptime_get() + 1, MAIN_LOOP_PERIOD_MS + 1)));
}

void check_led_state(bool state, std::uint64_t duration_ms)
{
	k_msleep(TIME_SLACK_MS - 1);

	ASSERT_EQ(state, get_led_state());
	k_msleep(duration_ms - 2 * TIME_SLACK_MS - 1);
	ASSERT_EQ(state, get_led_state());

	k_msleep(TIME_SLACK_MS - 1);
}

WHEN("^I trigger the proximity sensor$")
{
	set_proximity_sensor(1);
	wait_for_main_tick();
	set_proximity_sensor(0);
}

THEN("^the LED is on for (\\d+) milliseconds?$")
{
	REGEX_PARAM(std::uint64_t, ms);
	check_led_state(1, ms);
}

THEN("^the LED is off for (\\d+) milliseconds?$")
{
	REGEX_PARAM(std::uint64_t, ms);
	check_led_state(0, ms);
}

}
