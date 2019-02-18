/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Mon 18 Feb 23:00:35 CET 2019 */
/* // raising critical exeption */
/* // */

#ifndef RAISE_H
# define RAISE_H

# include <stdio.h>
# include <stdlib.h>

# define raise(msg)\
    do {                                                            \
        fprintf(stderr, "%s: %u: %s\n", __FILE__, __LINE__, msg);   \
        abort();                                                    \
    } while (0)

#endif
