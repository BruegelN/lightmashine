lightmashine
============

Use Arduino as a RC light controller

## TODO / known issues
- Add Backfire(Anti Lag) and Brakelights relative to the throttle signal.
- Add ThrottleCalibrateAdapter(?) and EepromAdapter to be able to configure your ThottleChannel neutralposition/endpoints and save them in EEPROM (and read on controller startup).
- Determine a good way to enter calibration mode (e.g. 5sec reverse). Needed later to reacalibrate while running lightmashine.
