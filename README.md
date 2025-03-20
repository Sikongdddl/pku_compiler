## useful commands

#### start docker container
docker run -it --rm -v .:/root/compiler maxxing/compiler-dev bash

#### cmake build
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build

#### autotest offline in /root/compiler
autotest -koopa -s lv$level_idx .

#### use your own compiler to compile an example program:
./build/compiler -koopa $input_file_path -o $output_file_path