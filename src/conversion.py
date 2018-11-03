import sys
_flats = ["Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G"]
_sharps = ["G#", "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G"]
_preferFlats = True


def transposeChords(chords, index):
    global _flats, _sharps, _preferFlats
    newChords = []
    notes = _flats if _preferFlats else _sharps

    for chord in chords:
        noteParts = (chord[:1], chord[1:])
        if (chord.find("b") == 1 or chord.find("#") == 1):
            noteParts = (chord[:2], chord[2:])

        oldNoteIndex = -1
        if (noteParts[0] in _flats):
            oldNoteIndex = _flats.index(noteParts[0])
        elif (noteParts[0] in _sharps):
            oldNoteIndex = _sharps.index(noteParts[0])

        if (oldNoteIndex == -1):  # Not a note
            newChords.append("".join(noteParts))
        else:
            newNote = notes[(oldNoteIndex + index) % len(notes)]
            newChords.append("".join([newNote, noteParts[1]]))

    return newChords


def main(args):
    if (len(args) == 0):
        print ("Input followed by a list of chords seperated by spaces")
    else:
        b = ""
        for i in range(0, len(_flats)):
            newChords = transposeChords(args, i)
            a = " ".join(newChords)
            b += " "+a[2:]
            print (a)
        print("This is " +b)

if __name__ == "__main__":
    main(sys.argv[1:])