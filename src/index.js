const fs = require('fs')
const MIDIFile = require('midifile')

const { log, warn, error } = console

const file = fs.readFileSync('midis/intro.mid')
const midi = new MIDIFile(file)

keys = midi.getTrackEvents(0)
fs.writeFileSync('output.json', JSON.stringify(keys))