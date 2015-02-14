cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(business)

add_library(nfirspp-business STATIC
      entities/fire_department.h
      values/address.cpp
      values/address.h
      values/fdid.h
      values/name.h
      bits/value_component.h
   )
