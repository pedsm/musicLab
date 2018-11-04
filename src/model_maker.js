const got = require('./got.json')
// console.log(got.tracks[1].notes)
const baseNote = got.tracks[1].notes[0].midi
const model = []
let prevNote = baseNote
for(note of got.tracks[1].notes) {
    model.push(note.midi - prevNote)
    prevNote = note.midi
}
console.log(model)

const fs = require('fs')
fs.writeFileSync('./frontend/gotModel.json', JSON.stringify(model))