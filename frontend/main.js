const Tone = require('tone')
const { Note, Scale, scale, transpose } = require('Tonal')
var synth = new Tone.Synth().toMaster()

var seq = new Tone.Sequence((time, note) => {
    playNote(note, time)
//straight quater notes
}, makeSequence(), "4n");
// seq.start(0)
// seq.loop = 2

var part = new Tone.Part((time, event) => {
    playNote(event.note, event.dur, time)
}, makeTimedSequence(makeSequence()))
part.start(0)
part.loop = 2

function start() {
  Tone.Transport.start('+0.1')
}


function makeSequence() {
    const model = [0, 1, -1, 2]
    const baseNote = "A4"
    const s = scale('minor').map(transpose(baseNote))
    let cursor = 0
    const sequence = [baseNote]
    for(let i = 0; i < 4; i++){
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
            time: Tone.Time(currentTime).toBarsBeatsSixteenths(),
            dur,
            note,
        })
        currentTime += Tone.Time(dur)
    }
    // part = seq.map((note, i) => {
    //     return {
    //         time: i == 0 ? 0 : `${Math.floor(i/4)}:${i % 4}`,
    //         dur: '4n',
    //         note
    //     }
    // })    
    console.log(part)
    return part
}

// Util functions
function playMidiNote(note, dur='4n', time=0) {
	synth.triggerAttackRelease(Note.fromMidi(note), dur, time)
}
function playNote(note, dur='4n', time=0) {
	synth.triggerAttackRelease(note, dur, time)
}