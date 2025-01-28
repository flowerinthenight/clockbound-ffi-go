#ifndef _CB_FFI_H
#define _CB_FFI_H

/* Wrapper to clockbound_open(). */
int cb_open();

/* Wrapper to clockbound_close(). */
int cb_close();

/* Wrapper to clockbound_now(). */
int cb_now(int *, int *, int *, int *, int *);

#endif // _CB_FFI_H
