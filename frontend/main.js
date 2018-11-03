const Tone = require('tone')
const { Chord, Note, Scale, scale, transpose } = require('Tonal')
var synth = new Tone.Synth().toMaster()
var chordSynth =  new Tone.PolySynth(6, Tone.Synth).toMaster();

var seq = new Tone.Sequence((time, note) => {
    playNote(note, time)
//straight quater notes
}, makeSequence(), "4n");
// seq.start(0)
seq.loop = "16n"

let patterns = [makeTimedSequence(makeSequence())]
part = new Tone.Part((time, event) => {
    playNote(event.note, event.dur, time)
}, patterns[0])
const app = new Vue({
    el: '#patterns',
    data: {
        name: 'First Pattern',
        patterns,
    }
})

let i = 0
// Tone.Transport.scheduleRepeat(function(time){
//     // console.log(Tone.Time(time).toBarsBeatsSixteenths())
//     const note = patterns[0][++i % patterns[0].length]
//     console.log(note.dur)
//     playNote(note.note, note.dur, time)

// }, "0:1");
let chordIndex = 0
const chords = ['G', 'Em', 'C', 'D', 'G']
Tone.Transport.scheduleRepeat(time => {
    playChord(chords[++i % chords.length], '1n', time)
}, '1:0')

//Start
Tone.Transport.start()


// Generators
function makeSequence() {
    const model = [0, 1, -1, 2]
    const baseNote = "A4"
    const s = scale('minor').map(transpose(baseNote))
    let cursor = 0
    const sequence = [baseNote]
    for(let i = 0; i <= 8; i++){
        cursor += Math.round(Math.random() * model.length)
        sequence.push(s[cursor % s.length])
    }
    console.log(sequence)
    return sequence
}

function makeTimedSequence(seq) {
    const model = ['0:1', '0:1', '0:1', '0:1', '0:1', '0:2']
    let currentTime = 0
    let part = []
    for(note of seq) {
        const dur = model[Math.round(Math.random() * model.length) % model.length]
        part.push({
            // time: Tone.Time(currentTime).toBarsBeatsSixteenths(),
            dur,
            note,
            // durS: Tone.Time(dur),
            // timeS: currentTime,
            // midi: Note.midi(note)
        })
        currentTime += Tone.Time(dur)
    }
    const minMidi = Math.min.apply(null, part.map(a => a.midi))
    console.log(part.map(note => Object.assign(note, {relNote: note.midi - minMidi})))
    return part
}

// Util functions
function playMidiNote(note, dur='4n', time=0) {
	synth.triggerAttackRelease(Note.fromMidi(note), dur, time)
}
function playNote(note, dur='4n', time=0) {
	synth.triggerAttackRelease(note, dur, time)
}
function playChord(chord, dur='1n', time=0) {
    chordSynth.triggerAttackRelease(Chord.notes(chord).map(a => a+'3'),dur,time)
}