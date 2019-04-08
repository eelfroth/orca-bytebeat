# ORCΛ BYTEBEAT

proof of concept that [orca-c](https://github.com/hundredrabbits/Orca-c) can be used as a synthesizer

## demo

[https://youtu.be/RCjxaDfU2bo](https://youtu.be/RCjxaDfU2bo)

## requirements

- orca-c
- netcat
- aplay
- the base36 converter from this repo

## method

- modify the orca-c source code to set a very high bpm rate:
[tui_main.c:786](https://github.com/hundredrabbits/Orca-c/blob/master/tui_main.c#L786)
```
a->bpm = 30200;
```
- recompile and start orca-c:
```
make release
orca --osc-port 49160 --strict-timing
```
- then, in another terminal, run this:
```
netcat -lu localhost 49160 | base36 | aplay -f u8 -r 2000
```

now you can send UDP packets from orca with the `;` operator. `netcat` receives these packages which are then converted from orca's base36 encoding and normalised to the range 0-255. the resulting values are redirected to `aplay` so they get pushed to the sound card.

## caveats

this method currently does not ensure that orca outputs a steady sample-rate of 2000 Hz. when it goes too slow, it causes a buffer underrun in aplay which is audible as a stutter. when it goes to fast, it introduces latency. the chosen bpm value of 30200 seems to work okay on my computer, with little latency and only the occasional stutter.
