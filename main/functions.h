//#ifndef _HEADERFILE_H    // Put these two lines at the top of your file.
//#define _HEADERFILE_H     // (Use a suitable name, usually based on the file name.)

#include <stdint.h>
#include <stdbool.h>

extern void zustandTuerGeschlossen();
extern void zustandTuerOffen();

extern uint8_t ReadKey();
extern void KeyGen();
extern void WriteLED();
extern void OutputTone();
extern bool CodeCheck();
extern bool CheckKey();
extern void SchlossAufTrue();

//#endif // _HEADERFILE_H    // Put this line at the end of your file.