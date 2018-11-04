const Tone = require('tone')
const { Chord, Note, Scale, scale, transpose } = require('Tonal')
const gotModel = require('./gotModel.json')
var synth = new Tone.Synth().toMaster()
var chordSynth =  new Tone.PolySynth(6, Tone.Synth).toMaster();
var drummer = new Tone.MembraneSynth().toMaster();
var clapper = new Tone.Sampler({
    "C3": "./samples/clap.mp3"
}).toMaster()

// Music stuff things
let patterns = [makeTimedSequence(makeSequence())]

const toggles = [
    {value: false, name: 'Melody Line', shuffle: () => {
        patterns[0] = makeTimedSequence(makeSequence())
    }},
    {value: false, name: 'Chord player', shuffle: () => {
        chordI = Math.floor(Math.random() * chords.length)
    }},
    {value: false, name: 'Kick'},
    {value: false, name: 'Clap'}
]

// Vue definitions
const app = new Vue({
    el: '#patterns',
    data: {
        patterns,
        toggles
    },
})

// Players
let i = 0
Tone.Transport.scheduleRepeat(time => {
    // console.log(Tone.Time(time).toBarsBeatsSixteenths())
    const note = patterns[0][++i % patterns[0].length]
    if (toggles[0].value) {
        playNote(note.note, note.dur, time)
    }
}, "0:1");
// Chords
let chordIndex = 0
const chords = [
    ['G', 'Em', 'C', 'D'],
    ['G','D','Em','C'],
    ['G','Am','C','D'],
    ['G','Em','Am','D'],
    ['G','Em','C','D']
]
let chordI = Math.floor(Math.random() * chords.length)
Tone.Transport.scheduleRepeat(time => {
    if (toggles[1].value) {
        playChord(chords[chordI][++chordIndex % chords[chordI].length], '1n', time)
    }
}, '1:0')
// Drum
Tone.Transport.start()
let kickPattern = 'x---x---x---x---'
let clapPattern = '-x----x---x---x-'
let drumIndex = 0
Tone.Transport.scheduleRepeat(time => {
    const t = Tone.Time(time).toBarsBeatsSixteenths().split('')
    const kick = kickPattern.split('')[(drumIndex) % 16] == 'x'
    const clap = clapPattern.split('')[(drumIndex) % 16] == 'x'
    if (toggles[2].value && kick) { playKick('C2', '2n', time) }
    if (toggles[3].value && clap) { if(clap){ clapper.triggerAttackRelease('C3', '2n', time) } }
    drumIndex++
}, '16n')
Tone.Transport.start()
//Start


// Generators
function makeSequence() {
    // const model = [0, 1, -1, 2]
    const model = gotModel
    const baseNote = "G4"
    const s = scale('dorian').map(transpose(baseNote))
    let cursor = 0
    const sequence = [baseNote]
    for (let i = 0; i <= 14; i++) {
        cursor += Math.round(Math.random() * model.length)
        sequence.push(s[cursor % s.length])
    }
    return sequence
}

function makeTimedSequence(seq) {
    const model = ['0:1', '0:1', '0:1', '0:1', '0:1', '0:2']
    let currentTime = 0
    let part = []
    for (note of seq) {
        const dur = model[Math.round(Math.random() * model.length) % model.length]
        // Stop making loop over 16
        if(currentTime >= Tone.Time('4:0').toSeconds()) {
            continue
        }
        part.push({
            // time: Tone.Time(currentTime).toBarsBeatsSixteenths(),
            dur,
            note,
            durS: Tone.Time(dur),
            timeS: currentTime,
            midi: Note.midi(note)
        })
        currentTime += Tone.Time(dur)
    }
    const minMidi = Math.min.apply(null, part.map(a => a.midi))
    return part
}

// Util functions
function playMidiNote(note, dur = '4n', time = 0) {
    synth.triggerAttackRelease(Note.fromMidi(note), dur, time)
}
function playNote(note, dur = '4n', time = 0) {
    synth.triggerAttackRelease(note, dur, time)
}
function playChord(chord, dur = '1n', time = 0) {
    chordSynth.triggerAttackRelease(Chord.notes(chord).map(a => a + '3'), dur, time)
}
function playKick(note, dur='4n', time =0) {
    drummer.triggerAttackRelease(note, dur, time)
}

//Export midi
function exportMidi() {
    const { dialog } = require('electron').remote
    const MidiConvert = require('midiconvert')
    const fs = require('fs')
    var midi = MidiConvert.create()
    // add a track
    let melody = midi.track()
        .patch(1)
    let chordTrack = midi.track()
        .patch(1)

    for (note of patterns[0]) {
        melody.note(note.midi, note.timeS, note.durS)
    }
    for (i in chords[chordI]) {
        const notes = Chord.notes(chords[i]).map(a => a + '3')
        for (note of notes) {
            chordTrack.note(Note.midi(note), Tone.Time(`${i}:0`).toSeconds(), Tone.Time('1:0').toSeconds())
        }
    }

    // write the output
    dialog.showSaveDialog({
        title: 'Save midi file...',
        defaultPath: 'musicLab.mid'
    }, (path) => {
        fs.writeFileSync(path, midi.encode(), "binary")
    })
}