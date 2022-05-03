#ifndef GUESSSTATUS_H
#define GUESSSTATUS_H

namespace model
{

/**
    Represents the status of a letter of a guess. Enums with higher numerical values
    are "more correct" than those with lower values.

    Author: Shawn Carter and Alexander Ayers
    Version: Spring 2022
*/
enum GuessStatus
{
    /**
        The letter has not been checked yet.
    */
    UNKNOWN,

    /**
        The letter is confirmed to not be present in the word.
    */
    DOES_NOT_EXIST,

    /**
        The letter is present in the word, but is not in the correct position.
    */
    INCORRECT_POSITION,

    /**
        The letter is present in the word and is in the correct position.
    */
    CORRECT_POSITION,
};

}

#endif // GUESSSTATUS_H
