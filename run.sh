export DYLD_LIBRARY_PATH="/Users/nandeep/Projects/SFML/lib:/Users/nandeep/Projects/SFML/extlibs/libs-osx/Frameworks/sndfile.framework/Versions/A/"

ln -s ./test/data data

./test/TrivialTest

rm -f data
