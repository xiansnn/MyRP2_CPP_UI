/**
 * @file probe.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "probe.h"
#include "hardware/gpio.h"

/**
 * @brief Construct a new Probe:: Probe object
 *
 * @param channel_ this is the channel number of the logic analyser
 */
Probe::Probe(uint channel_)
{
    this->_gpio = Probe::_channel_map[channel_];
    gpio_init(this->_gpio);
    gpio_set_dir(this->_gpio, GPIO_OUT);
}

/**
 * @brief send a HI level on the corresponding gpio
 *
 */
void Probe::hi()
{
    gpio_put(this->_gpio, 1);
}

/**
 * @brief send a LO level on the corresponding gpio
 *
 */
void Probe::lo()
{
    gpio_put(this->_gpio, 0);
}

void Probe::pulse_us(uint duration)
{
    hi();
    busy_wait_us(duration);
    lo();
}

void Probe::copy(bool value)
{
    gpio_put(this->_gpio, value);
}
