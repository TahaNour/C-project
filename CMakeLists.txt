cmake_minimum_required(VERSION 3.16)
project(URL_Shortener C)

set(CMAKE_C_STANDARD 11)

# Ajouter les fichiers SQLite
include_directories("C:/ApacheServer/www/App_c")
add_library(sqlite3 sqlite3.c)

# Ajouter votre fichier principal (main.c ou autre)
add_executable(URL_Shortener main.c)

# Lier SQLite à votre exécutable
target_link_libraries(URL_Shortener sqlite3)
