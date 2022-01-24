# SPDX-FileCopyrightText: 2022 Blitz City DIY
# SPDX-License-Identifier: MIT
#  MIDI UART out with NeoPixel

import time
import board
import busio
import adafruit_midi
import neopixel
from adafruit_midi.control_change import ControlChange
from adafruit_midi.note_off import NoteOff
from adafruit_midi.note_on import NoteOn
from digitalio import DigitalInOut, Direction, Pull

pixel = neopixel.NeoPixel(board.NEOPIXEL, 1)

pixel.brightness = 0.05

uart = busio.UART(board.TX, board.RX, baudrate=31250, timeout=0.001)  # init UART
midi_in_channel = 2
midi_out_channel = 1
midi = adafruit_midi.MIDI(
    midi_in=uart,
    midi_out=uart,
    in_channel=(midi_in_channel - 1),
    out_channel=(midi_out_channel - 1),
    debug=True,
)

print("MIDI UART Out")
print("Default output channel:", midi.out_channel + 1)

while True:

    midi.send(NoteOn(48, 100))  
    pixel.fill((127, 127, 0))
    time.sleep(1)  
    midi.send(NoteOff(48, 0))  
    pixel.fill((0, 0, 0))
    time.sleep(1)

    midi.send(NoteOn(55, 100))
    pixel.fill((127, 0, 0))
    time.sleep(1)
    midi.send(NoteOff(55, 0))
    pixel.fill((0, 0, 0))
    time.sleep(1)

    midi.send(NoteOn(49, 100))
    pixel.fill((0, 127, 0))
    time.sleep(1)
    midi.send(NoteOff(49, 0))
    pixel.fill((0, 0, 0))
    time.sleep(1)

    midi.send(NoteOn(57, 100))
    pixel.fill((0, 127, 127))
    time.sleep(1)
    midi.send(NoteOff(57, 0))
    pixel.fill((0, 0, 0))
    time.sleep(1)
