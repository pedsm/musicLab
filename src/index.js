const fs = require('fs')
const MIDIFile = require('midifile')

const { log, warn, error } = console

const file = fs.readFileSync('midis/intro.mid')
const midi = new MIDIFile(file)

log(midi.tracks[0])