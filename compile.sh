g++ -Wall -Wextra -o chess ./src/*.cpp -L/usr/local/lib -Wl,--whole-archive -lSDL2 -lSDL2_image -lSDL2_ttf -Wl,--no-whole-archive -static-libgcc -static-libstdc++
