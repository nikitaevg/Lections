make

cmake
CMakeLists.txt
cmake_minimum_required(Version 3.1)

project(project_name)

add_executable(name name.c)

лучше генерировать файлы в папку build. 
и из нее запускать cmake ..
фото