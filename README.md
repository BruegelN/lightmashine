lightmashine
============

Use Arduino as a RC light controller

## TODO / known issues
- Determine a good way to enter calibration mode (e.g. 5sec reverse). Needed later to reacalibrate while running lightmashine.
- Check interrupt vectors of other processors to support them too. By now only Atmega328 is working and tested.
- Documentation & installations guide ( maybe gh-pages ?)



- :bug: If you move the throttle trigger of your radio fast enough from nearly full throttle to braking, it's possible that the backfire led stays on as long as your braking instead of just blinking.
