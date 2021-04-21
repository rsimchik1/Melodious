#pragma once

/**
 * Enum that assigns names to valid note types.
 */
enum NoteType
{
	WHOLE = 1,
	HALF = 2,
	QUARTER = 4,
	EIGHTH = 8,
	SIXTEENTH = 16,
	THIRTY_SECOND = 32,
	SIXTY_FOURTH = 64
};

/**
 * Class for structuring musical time.
 *
 * @author Richard Simchik
 */
class Meter
{
public:
	/**
	 * Create a new Meter object.
	 *
	 * @throw InvalidArgumentException If either value is out of bounds.
	 * @param beatsPerMeasure The number of beats in a single measure.
	 *		  { 0 < beatsPerMeasure <= 64 }
	 * @param beatNoteType The type of note that will mark the duration of one
	 * beat (e.g. quarter note = 4, eighth note = 8)
	 *		  { beatNoteType = 2^n where 0 <= n <= 6 }
	 */
	Meter(int beatsPerMeasure, int beatNoteType);

	/**
	 * Get the number of beats in a measure (numerator of a time signature).
	 *
	 * @return The number of beats per measure.
	 */
	int getBeatsPerMeasure();

	/**
	 * Get the type of note that marks one beat (denominator of a time signature).
	 *
	 * @return The type of note that marks one beat.
	 *
	 * TODO consider returning NoteType?
	 */
	int getBeatNoteType();
private:
	int beatsPerMeasure;
	int beatNoteType;

	/**
	 * Checks whether an integer is a valid number of beats per measure. All
	 * values 0 < n <= 64 are valid.
	 *
	 * @param beatsPerMeasure The integer to check.
	 * @return true if the integer is a valid number of beats per measure, false
	 * otherwise.
	 */

	bool isValidBeatsPerMeasure(int beatsPerMeasure);
	/**
	 * Checks whether an integer is a valid note type. All values 2^n are valid
	 * for 0 <= n <= 6.
	 *
	 * @param noteType The integer to check.
	 * @return true if the integer is a valid note type, false otherwise.
	 */
	bool isValidNoteType(int noteType);
};
