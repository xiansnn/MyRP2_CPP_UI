/**
 * @file probe.h
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PROBE_H
#define PROBE_H

#include "pico/stdlib.h"

/**
 * @brief 
 * 
 */
class Probe
{
private:
    /**
     * @brief 
     * 
     */
    uint _gpio;
    /**
     * @brief 
     * 
     */
    constexpr static int _channel_map[8] = {6, 7, 8, 9, 16, 17, 21, 26};

public:
    /**
     * @brief Construct a new Probe object
     * 
     * @param channel_ 
     */
    Probe(uint channel_);
    /**
     * @brief 
     * 
     */
    void hi();
    /**
     * @brief 
     * 
     */
    void lo();
    /**
     * @brief 
     * 
     * @param duration 
     */
    void pulse_us(uint duration);
    /**
     * @brief 
     * 
     * @param value 
     */
    void copy(bool value);
};

#endif