/*

        Compiler dependens define:

 _INTER
 _FAR
 _HUGE

*/

#ifndef __MTASK__
# define _INTER interrupt
# define _PASCAL pascal
#endif
#ifndef __FLAT__
# define _FAR far
# define _HUGE huge
#endif



#ifndef _FAR
# define _FAR
#endif
#ifndef _HUGE
# define _HUGE
#endif
#ifndef _INTER
# define _INTER
#endif
#ifndef _PASCAL
# define _PASCAL
#endif


