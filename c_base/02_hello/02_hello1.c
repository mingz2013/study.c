/* This file has been generated by the Hex-Rays decompiler.
   Copyright (c) 2007-2017 Hex-Rays <info@hex-rays.com>

   Detected compiler: GNU C++
*/

#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

int __cdecl main(int argc, const char **argv, const char **envp);
// int printf(const char *, ...);

//-------------------------------------------------------------------------
// Data declarations

char asc_100000F7D = 'H'; // weak


//----- (0000000100000F60) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  printf("hello, linux\n", argv, envp);
  JUMPOUT(*(_QWORD *)asc_100000F7D);
}
// 100000F7D: using guessed type char;

// ALL OK, 1 function(s) have been successfully decompiled