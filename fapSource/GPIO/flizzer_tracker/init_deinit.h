#pragma once

#include "flizzer_tracker.h"
#include "flizzer_tracker_hal.h"

FlizzerTrackerApp* init_tracker(
    uint32_t sample_rate,
    uint8_t rate,
    bool external_audio_output,
    uint32_t audio_buffer_size);
void deinit_tracker(FlizzerTrackerApp* tracker);