
#ifndef _SYS_DIR_H
#define _SYS_DIR_H

#include <features.h>

#include <dirent.h>
#ifndef _DIRENT_HAVE_D_NAMLEN
#define _D_EXACT_NAMLEN(d) ( strlen( (d)->d_name) )
#endif


#define direct dirent

#endif // sys/dir.h
