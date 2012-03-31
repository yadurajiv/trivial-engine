g++ -c `python-config --includes` -I../src/ -I/Users/nandeep/Projects/SFML/include trivial.cpp 

g++ -shared -Wl trivial.o `python-config --libs` -lboost_python-mt -lstdc++ -L../src/ -lTrivialEngine -L/Users/nandeep/Projects/SFML/lib -lsfml-graphics -lsfml-system -lsfml-window -o trivial.so 
