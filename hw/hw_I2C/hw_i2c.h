#if !defined(HW_I2C_H)
#define HW_I2C_H

#include "hardware/i2c.h"
#include "pico/i2c_slave.h"
#include "pico/stdlib.h"
#include <set>
#include <string>

#define I2C_STANDARD_MODE 100 * 1000          // <= 100kb/s
#define I2C_FAST_MODE 400 * 1000              // <= 400kb/s
#define I2C_FAST_MODE_PLUS 1000 * 1000        // <= 1Mb/s
#define I2C_SLAVE_DEFAULT_MAX_MEMORY_SIZE 256 // default value used by context_t

struct StructI2CXferResult
{
    bool error = false;
    std::string context = "";
    int xfer_size = 0;
};

struct StructConfigMasterI2C
{
    i2c_inst_t *i2c = i2c0;
    uint sda_pin = 04;
    uint scl_pin = 05;
    uint baud_rate = I2C_STANDARD_MODE;
};

struct StructConfigSlaveI2C
{
    i2c_inst_t *i2c = i2c1;
    uint sda_pin = 06;
    uint scl_pin = 07;
    uint baud_rate = I2C_STANDARD_MODE;
    uint8_t slave_address = 0x55;
    size_t slave_memory_size = 256;
    i2c_slave_handler_t handler;
};

class HW_I2C_Master
{
private:
    i2c_inst_t *i2c;
    uint time_out_us_per_byte;

public:
    HW_I2C_Master(StructConfigMasterI2C master_config);
    StructI2CXferResult burst_byte_write(uint8_t slave_address, uint8_t mem_addr, uint8_t *src, size_t len);
    StructI2CXferResult single_byte_write(uint8_t slave_address, uint8_t mem_addr, uint8_t mem_value);
    StructI2CXferResult single_byte_read(uint8_t slave_address, uint8_t mem_addr, uint8_t *dest);
    StructI2CXferResult burst_byte_read(uint8_t slave_address, uint8_t mem_addr, uint8_t *dest, size_t len);
    std::set<uint8_t> bus_scan();
    bool device_is_connected(uint8_t slave_address);
    void show_bus_map();
};

struct StructSlaveMemory
{
    uint8_t mem[I2C_SLAVE_DEFAULT_MAX_MEMORY_SIZE]{};
    uint8_t mem_address = I2C_SLAVE_DEFAULT_MAX_MEMORY_SIZE - 1; // init: the slave points to its last memory address
    bool mem_address_written = false;
};

class HW_I2C_Slave
{
private:
    i2c_inst_t *i2c;

public:
    StructSlaveMemory context;
    HW_I2C_Slave(StructConfigSlaveI2C slave_config);
    void slave_isr(i2c_slave_event_t event);
};

#endif // HW_I2C_H
