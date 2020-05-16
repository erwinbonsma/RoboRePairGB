/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "SoundFx.h"

namespace Gamebuino_Meta {

const NoteSpec sfxSwitchTilesNotes[2] = {
    NoteSpec { .note=Note::Cs5, .vol=3, .wav=WaveForm::PHASER, .fx=Effect::FADE_IN },
    NoteSpec { .note=Note::Gs5, .vol=3, .wav=WaveForm::PHASER, .fx=Effect::DROP },
};
const TuneSpec sfxSwitchTiles = TuneSpec {
    .noteDuration = 4, .loopStart = 2, .numNotes = 2, .notes = sfxSwitchTilesNotes
};

const NoteSpec sfxNoCanDoNotes[3] = {
    NoteSpec { .note=Note::Cs4, .vol=8, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::F3, .vol=8, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::A2, .vol=7, .wav=WaveForm::TILTED_SAW, .fx=Effect::DROP },
};
const TuneSpec sfxNoCanDo = TuneSpec {
    .noteDuration = 2, .loopStart = 3, .numNotes = 3, .notes = sfxNoCanDoNotes
};

const NoteSpec sfxPlaceTileNotes[2] = {
    NoteSpec { .note=Note::Gs3, .vol=8, .wav=WaveForm::TRIANGLE, .fx=Effect::NONE },
    NoteSpec { .note=Note::G4, .vol=8, .wav=WaveForm::TRIANGLE, .fx=Effect::NONE },
};
const TuneSpec sfxPlaceTile = TuneSpec {
    .noteDuration = 4, .loopStart = 2, .numNotes = 2, .notes = sfxPlaceTileNotes
};

const NoteSpec sfxCrashNotes[11] = {
    NoteSpec { .note=Note::Cs5, .vol=8, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::Cs5, .vol=8, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::C5, .vol=7, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::A4, .vol=6, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::F4, .vol=5, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::A3, .vol=4, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::Cs3, .vol=4, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::As2, .vol=2, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::Fs2, .vol=2, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::F2, .vol=2, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::Ds2, .vol=2, .wav=WaveForm::NOISE, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxCrash = TuneSpec {
    .noteDuration = 2, .loopStart = 11, .numNotes = 11, .notes = sfxCrashNotes
};

const NoteSpec sfxDeathNotes[19] = {
    NoteSpec { .note=Note::F3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::F3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::F3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    SILENCE,
    NoteSpec { .note=Note::E3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::E3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::E3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    SILENCE,
    NoteSpec { .note=Note::D3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::D3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::D3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    SILENCE,
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::C3, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::NONE },
};
const TuneSpec sfxDeath = TuneSpec {
    .noteDuration = 8, .loopStart = 19, .numNotes = 19, .notes = sfxDeathNotes
};

const NoteSpec sfxFallingNotes[13] = {
    NoteSpec { .note=Note::G3, .vol=5, .wav=WaveForm::PHASER, .fx=Effect::FADE_IN },
    NoteSpec { .note=Note::Fs3, .vol=5, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F3, .vol=5, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::E3, .vol=5, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Ds3, .vol=4, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::D3, .vol=4, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Cs3, .vol=4, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::C3, .vol=4, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::B2, .vol=3, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::As2, .vol=3, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::A2, .vol=3, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Gs2, .vol=2, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::G2, .vol=2, .wav=WaveForm::PHASER, .fx=Effect::SLIDE },
};
const TuneSpec sfxFalling = TuneSpec {
    .noteDuration = 9, .loopStart = 13, .numNotes = 13, .notes = sfxFallingNotes
};

const NoteSpec sfxScoreIncNotes[1] = {
    NoteSpec { .note=Note::F5, .vol=6, .wav=WaveForm::TRIANGLE, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxScoreInc = TuneSpec {
    .noteDuration = 2, .loopStart = 1, .numNotes = 1, .notes = sfxScoreIncNotes
};

const NoteSpec sfxScoreDecNotes[1] = {
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::TRIANGLE, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxScoreDec = TuneSpec {
    .noteDuration = 2, .loopStart = 1, .numNotes = 1, .notes = sfxScoreDecNotes
};

const NoteSpec sfxGetReadyNotes[16] = {
    NoteSpec { .note=Note::C4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::C4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::C4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::C4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::FADE_OUT },
    SILENCE,
    SILENCE,
    NoteSpec { .note=Note::E4, .vol=7, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::E4, .vol=7, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::E4, .vol=7, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::E4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F4, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F4, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::F4, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxGetReady = TuneSpec {
    .noteDuration = 3, .loopStart = 16, .numNotes = 16, .notes = sfxGetReadyNotes
};

const NoteSpec sfxTimedOutNotes[25] = {
    NoteSpec { .note=Note::A3, .vol=6, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::C4, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::D4, .vol=4, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::D4, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::D4, .vol=2, .wav=WaveForm::TILTED_SAW, .fx=Effect::FADE_OUT },
    SILENCE,
    SILENCE,
    NoteSpec { .note=Note::E3, .vol=6, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::F3, .vol=6, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Fs3, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::G3, .vol=4, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::G3, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::G3, .vol=2, .wav=WaveForm::TILTED_SAW, .fx=Effect::FADE_OUT },
    SILENCE,
    SILENCE,
    NoteSpec { .note=Note::A2, .vol=6, .wav=WaveForm::TILTED_SAW, .fx=Effect::NONE },
    NoteSpec { .note=Note::A2, .vol=6, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::As2, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::As2, .vol=5, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::B2, .vol=4, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::B2, .vol=4, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Cs3, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Cs3, .vol=3, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Cs3, .vol=2, .wav=WaveForm::TILTED_SAW, .fx=Effect::SLIDE },
    NoteSpec { .note=Note::Cs3, .vol=2, .wav=WaveForm::TILTED_SAW, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxTimedOut = TuneSpec {
    .noteDuration = 6, .loopStart = 25, .numNotes = 25, .notes = sfxTimedOutNotes
};

const NoteSpec sfxLevelDoneNotes[16] = {
    NoteSpec { .note=Note::E4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::E4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::E4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::E4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::FADE_OUT },
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::NONE },
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::FADE_OUT },
    NoteSpec { .note=Note::G4, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::G4, .vol=8, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::F4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::G4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::G4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::G4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::G4, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxLevelDone = TuneSpec {
    .noteDuration = 10, .loopStart = 16, .numNotes = 16, .notes = sfxLevelDoneNotes
};

const NoteSpec sfxGameOverNotes[19] = {
    NoteSpec { .note=Note::F2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::NONE },
    NoteSpec { .note=Note::F2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::NONE },
    NoteSpec { .note=Note::F2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::NONE },
    NoteSpec { .note=Note::F2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::FADE_OUT },
    NoteSpec { .note=Note::E2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::NONE },
    NoteSpec { .note=Note::E2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::NONE },
    NoteSpec { .note=Note::E2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::E2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::FADE_OUT },
    NoteSpec { .note=Note::D2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::NONE },
    NoteSpec { .note=Note::D2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::D2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::D2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::FADE_OUT },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::VIBRATO },
    NoteSpec { .note=Note::C2, .vol=8, .wav=WaveForm::ORGAN, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxGameOver = TuneSpec {
    .noteDuration = 16, .loopStart = 19, .numNotes = 19, .notes = sfxGameOverNotes
};

const NoteSpec sfxLiveBonusNotes[4] = {
    NoteSpec { .note=Note::Gs5, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::ARPEGGIO_FAST },
    NoteSpec { .note=Note::D6, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::ARPEGGIO_FAST },
    NoteSpec { .note=Note::Gs5, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::ARPEGGIO_FAST },
    NoteSpec { .note=Note::F6, .vol=6, .wav=WaveForm::PHASER, .fx=Effect::FADE_OUT },
};
const TuneSpec sfxLiveBonus = TuneSpec {
    .noteDuration = 10, .loopStart = 4, .numNotes = 4, .notes = sfxLiveBonusNotes
};

const NoteSpec sfxClashNotes[3] = {
    NoteSpec { .note=Note::F3, .vol=6, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::E3, .vol=4, .wav=WaveForm::NOISE, .fx=Effect::NONE },
    NoteSpec { .note=Note::A2, .vol=2, .wav=WaveForm::NOISE, .fx=Effect::DROP },
};
const TuneSpec sfxClash = TuneSpec {
    .noteDuration = 10, .loopStart = 3, .numNotes = 3, .notes = sfxClashNotes
};

const NoteSpec sfxWiggle1Notes[1] = {
    NoteSpec { .note=Note::C5, .vol=4, .wav=WaveForm::PHASER, .fx=Effect::NONE },
};
const TuneSpec sfxWiggle1 = TuneSpec {
    .noteDuration = 8, .loopStart = 1, .numNotes = 1, .notes = sfxWiggle1Notes
};

const NoteSpec sfxWiggle2Notes[1] = {
    NoteSpec { .note=Note::G4, .vol=4, .wav=WaveForm::PHASER, .fx=Effect::NONE },
};
const TuneSpec sfxWiggle2 = TuneSpec {
    .noteDuration = 8, .loopStart = 1, .numNotes = 1, .notes = sfxWiggle2Notes
};

} // Namespace

const Gamebuino_Meta::TuneSpec* switchTilesSfx = &Gamebuino_Meta::sfxSwitchTiles;
const Gamebuino_Meta::TuneSpec* noCanDoSfx = &Gamebuino_Meta::sfxNoCanDo;
const Gamebuino_Meta::TuneSpec* placeTileSfx = &Gamebuino_Meta::sfxPlaceTile;
const Gamebuino_Meta::TuneSpec* crashSfx = &Gamebuino_Meta::sfxCrash;
const Gamebuino_Meta::TuneSpec* deathSfx = &Gamebuino_Meta::sfxDeath;
const Gamebuino_Meta::TuneSpec* fallingSfx = &Gamebuino_Meta::sfxFalling;
const Gamebuino_Meta::TuneSpec* scoreIncSfx = &Gamebuino_Meta::sfxScoreInc;
const Gamebuino_Meta::TuneSpec* scoreDecSfx = &Gamebuino_Meta::sfxScoreDec;
const Gamebuino_Meta::TuneSpec* getReadySfx = &Gamebuino_Meta::sfxGetReady;
const Gamebuino_Meta::TuneSpec* timedOutSfx = &Gamebuino_Meta::sfxTimedOut;
const Gamebuino_Meta::TuneSpec* levelDoneSfx = &Gamebuino_Meta::sfxLevelDone;
const Gamebuino_Meta::TuneSpec* gameOverSfx = &Gamebuino_Meta::sfxGameOver;
const Gamebuino_Meta::TuneSpec* liveBonusSfx = &Gamebuino_Meta::sfxLiveBonus;
const Gamebuino_Meta::TuneSpec* clashSfx = &Gamebuino_Meta::sfxClash;
const Gamebuino_Meta::TuneSpec* wiggle1Sfx = &Gamebuino_Meta::sfxWiggle1;
const Gamebuino_Meta::TuneSpec* wiggle2Sfx = &Gamebuino_Meta::sfxWiggle2;
