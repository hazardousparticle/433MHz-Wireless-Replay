# 433MHz-Wireless-Replay
Fun with embedded systems and household wireless devices.

A few programs for a cheap STM32F103 ARM cortex board to control 433MHz wireless devices.

I haven't included STMicro's HAL libraries. The code should be generic enough to port to other devices.

Connect a cheap 433MHz ASK (OOK) transceiver to GPIO pin A3 or A8.

Project 1: Doorbell
    Funny prank for watching people run to answer a door when no one is there.

Project 2: Gate remote
    I managed to intercept the signal from a wireless remote for my front gate. This kind of highligts a security vulnerability where an adversary could open the gate to a private residence. Most cheaper electric gate systems do not use random numbers and transmit without authentication. The remotes usually have 10 DIP switches for pairing a remote unit to a gate controller. In a communal setting the first 4 are usually to identify the common gate and the rest are for each resident. It would be trivial for one to brute force the 10 bit number, therfore opening all gates in a gated community within range.
    Do not use this for illegal purposes. The code is largely the same as Project 1, I have not attached the code for security reasons.
