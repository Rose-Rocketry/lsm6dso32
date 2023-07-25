# General notes on the LSM6DSO32

My unit seems to have a very incorrect internal clock, by a factor of 5% or so.
This is pretty normal for a capacitative oscillator, but it seems a bit
concerning for the purposes of timestamping FIFO packets; should this be
corrected for manually, or in some other way? It would be really cool to be
able to use FIFO as the main way of receiving data from the sensor.

Drift with a standard interrupt-based implementation at 833Hz is pretty decent
at least when stationary. It does seem to accumulate at an accelerating rate -
I wonder if it would be better to store a "state quaternion" rather than rotate
a vector repeatedly.

Addendum, I tried to do a drift test on this but it seemed to circle back to
lower drift values after sitting on a table for a long time - why? Oh and it
NaN'ed out after about 9 and a half minutes, so RIP that.

833 Hz seems to be about the practical limit for 100kHz I2C communication. This
sounds pretty reasonable, this allows 120 clocks per reading which is cutting it
pretty close. 400kHz should be able to manage 3332 Hz in theory for one sensor,
or probably 1666 on two; but best is probably to just go SPI for data basically
as fast as we could ever want (presuming we have enough spare pins). It looks
like it might be a good idea to have two SPI buses on the board, a stupid fast
one (maybe QSPI) for flash storage and a peasant 10MHz one for sensors since
most don't support high speeds very well.