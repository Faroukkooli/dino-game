
```sh
# Clone this repo
git clone https://github.com/ZizouHuweidi/dino-game.git 
cd dino-game

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./dino-game  
```

***Note:*** To use SDL2_ttf, SDL2_net or SDL2_mixer, you should uncomment some
instructions in the CMakeLists.txt file and re-execute the `make` command.
