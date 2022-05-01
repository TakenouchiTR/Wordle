#ifndef DIALOGRESULT_H
#define DIALOGRESULT_H

namespace view
{

/**
    Represents the result of a dialog box.

    Author: Team C
    Version: Spring 2022
 */
enum DialogResult
{
    /**
        The primary option for the dialog was selected.
     */
    PRIMARY,

    /**
        The secondary option for the dialog was selected.
     */
     SECONDARY,

    /**
        The dialog was closed using the X button.
     */
    CANCELLED,
};

}

#endif // DIALOGRESULT_H
