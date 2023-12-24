
@echo off

if not exist build mkdir w:\clox_project\build
pushd w:\clox_project\build

set code_path= ..\code\

::GENERAL COMPILER OPTIONS
set compiler= 		   -MTd      &:: Include CRT library with static linking
									:: using "d" makes it link w/t debug version
set compiler=%compiler%  -W4      &:: Display up to level 4 (-WALL for all warnings)
set compiler=%compiler%  -WX      &:: Consider warnings as ERROR
set compiler=%compiler%  -wd4201  &:: Nameless struct/union warning
set compiler=%compiler%  -wd4189  &:: initialized but not used variable
set compiler=%compiler%  -wd4100  &:: Unused function paramters
set compiler=%compiler%  -wd4505  &:: Unused function paramters
set compiler=%compiler%  -Gm-     &:: Disable minimal build.
                                   :: This does nothing for unity builds (C++)
set compiler=%compiler%  -GR-     &:: Disable Run_Time_Type_Information  (C++)
set compiler=%compiler%  -EHa-    &:: Disable Exception Handling         (C++)
set compiler=%compiler%  -nologo  &:: Remove compiler info on result screen
set compiler=%compiler%  -Oi      &:: Change instruction to intrinsic if possible

::DEBUG VARIABLES
set debugOpt=               -FC &:: Produce full pathof the srcFile for dignostics
set debugOpt=%debugOpt%     -Zi &:: Older -Zi. Does not produce larger pdb 

::CROSS_PLATFORM DEFINES
set defines= 		 -DCLOX_SLOW=1 
set defines=%defines% -DCLOX_INTERNAL=1

:: No Optimization (slow) -Od
:: All Optimization (fast) -O2

del *.pdb > NUL 2> NUL

cl -Od %compiler% -DWIN32_CLOX=1 %defines% %code_path%main.c /Fe: clox.exe 


popd
