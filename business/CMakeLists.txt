cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(business)

add_library(nfirspp-business STATIC
      address.cpp
      address.h
      name.h
      bits/value_component.h
   )
