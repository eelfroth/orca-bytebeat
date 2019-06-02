# ORCΛ BYTEBEAT

proof of concept that [orca-c](https://github.com/hundredrabbits/Orca-c) can be used as a synthesizer

## demo

[https://youtu.be/RCjxaDfU2bo](https://youtu.be/RCjxaDfU2bo)

## requirements

- Orca-c
- netcat
- aplay
- the base36 converter from this repo

## method

- compile the base36 converter
```
make
```
- start Orca-c, specifying a UDP port and some very high bpm:
```
orca --osc-port 49160 --strict-timing --bpm 30200
```
- then, in another terminal, run this:
```
netcat -lu localhost 49160 | base36 | aplay -f u8 -r 2000
```

now you can send UDP packets from orca with the `;` operator. `netcat` receives these packages which are then converted from orca's base36 encoding and normalised to the range 0-255. the resulting values are redirected to `aplay` so they get pushed to the sound card.

## caveats

this method currently does not ensure that orca outputs a steady sample-rate of 2000 Hz. when it goes too slow, it causes a buffer underrun in aplay which is audible as a stutter. when it goes to fast, it introduces latency. the chosen bpm value of 30200 seems to work okay on my computer, with not too much latency and only the occasional stutter.
