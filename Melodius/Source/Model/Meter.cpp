#include "Meter.h"

#include "../Exceptions/InvalidArgumentException.h"

Meter::Meter(int beatsPerMeasure, int beatNoteType)
{
	if (!isValidBeatsPerMeasure(beatsPerMeasure) || !isValidNoteType(beatNoteType))
		throw InvalidArgumentException();

	this->beatsPerMeasure = beatsPerMeasure;
	this->beatNoteType = beatNoteType;
}

int Meter::getBeatsPerMeasure()
{
	return beatsPerMeasure;
}

int Meter::getBeatNoteType()
{
	return beatNoteType;
}

bool Meter::isValidBeatsPerMeasure(int beatsPerMeasure)
{
	return 0 < beatsPerMeasure && beatsPerMeasure <= 64;
}

bool Meter::isValidNoteType(int noteType)
{
	return (noteType > 0) && (noteType <= 64) &&
		((noteType & (noteType - 1)) == 0);
}
