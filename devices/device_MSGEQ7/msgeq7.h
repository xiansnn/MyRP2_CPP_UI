#if !defined(MSGEQ7_H)
#define MSGEQ7_H

#include "pico/stdlib.h"
#include <vector>
#include "hardware/adc.h"
#include <array>

/**
 * @brief The MSGEQ7 is an 7-band audio filter.
 *
 * The band frequencies are centered around: 63Hz, 160Hz, 400Hz, 1000Hz, 2500Hz, 6250Hz, 16000Hz.
 * After a pulse on "reset_gpio" pin, a peak detector for each band is multiplexed on the pin "signal_out" at each pulse on pin "strobe_gpio".
 *
 */
class MSGEQ7
{
private:
    uint strobe_gpio;
    uint reset_gpio;
    uint signal_out;
    std::array<uint16_t, 7> band_results;

public:
    /**
     * @brief Construct a new MSGEQ7 object
     *
     * @param strobe_gpio the gpio connected to strobe
     * @param reset_gpio  the gpio connected to reset
     * @param signal_out the gpio connected to the analog multiplexed peak detector
     */
    MSGEQ7(uint strobe_gpio, uint reset_gpio, uint signal_out);
    /**
     * @brief Destroy the MSGEQ7 object
     *
     */
    ~MSGEQ7();
    /**
     * @brief Get the spectrum object
     *
     * @return std::array<uint16_t,7> a table with 16bit values for each band
     */
    std::array<uint16_t, 7> get_spectrum();
};

#endif // MSGEQ7_H
