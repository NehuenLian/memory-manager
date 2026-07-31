cmake_minimum_required(VERSION 3.10)
project(memory-manager C)

set(SOURCES
  data_manipulation/data_access.c
  runtime_memory/manage_runtime_memory.c
  user_interaction/user_interaction.c
  main.c
)

add_executable(manager ${SOURCES})
