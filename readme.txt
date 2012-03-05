Trivial notes





INSTALLATION ON UNIX
--------------------

TODO: Complete this tutorial

1. Make sure you set two environment variables:

CMAKE_INCLUDE_PATH 

CMAKE_LIBRARY_PATH 

Both of these should have at least the SFML include and lib paths. 






INSTALLATION ON WINDOWS
-----------------------

Getting started on Windows is simple, follow the steps and thats it.

Compiling SFML2

1. Download the latest sfml code from the repo - https://github.com/LaurentGomila/SFML

For Visual Studio 9 2008 on windows

2. run the cmake-gui

3. Select the folder where SFML2 is and hit Configure, this shouldn't throw any errors(cmake will test for working compiler as well)

4. under BUILD make sure BUILD_SHARED_LIBS is on

5. Hit Generate and you should have your soultion(.sln file) generated for you

6. Open the solution and build both Debug and Release configurations(should go without a hitch)

7. Make libs folder in the root (mine looked like was c:\sfml2\libs)

8. Copy all the newly created lib and dll files into this folder for ease of use (I copied the Debug and Release folders from from c:\sfml2\vcshared\lib to c:\sfml2\lib\)

For Code::Blocks with MingW GCC on windows

2. run the cmake-gui

(you will have to delete the cmake cache if you want to get the compiler/ide selection dialog again)
3. Select the folder where SFML2 is and hit Configure, this shouldn't throw any errors(cmake will test for working compiler as well)

4. under BUILD make sure BUILD_SHARED_LIBS is on

5. under CMAKE keep CMAKE_BUILD_TYPE to Release for now and later you will need to regenerate the CodeBlocksProject with this as DEBUG for the debug libs(make sure you change the Where to Build binaries text box to a new folder!! mine was C:/sfml2/cbSharedDebug and C:/sfml2/cbSharedRelease)

5. Hit Generate and you should have your soultion generated for you

6. Open the cbp and build all do this for the other project as well

7. Since I'm using both msvc and mingw, I have both my libs stored at the same place, with a small change, I copied all my msvc libs to c:\sfml2\lib\Debug and Release and all my mingw libs ..\lib\Debug\mingw and ..\lib\Release\mingw

NOTE: you might have to hit Configure in cmake-gui a couple of times to make sure all the red coloured labels are gone!

-- 

Things to do before compiling Trivial and the test application

1. copy all the dlls to appropriate Release and Debug folders, this includes the two dlls from the extlibs folder in sfml2 as well. 

2. Add sfml2\include to your header search path

3. Add sfml2\lib and sfml2\lib\* as required to your library search path