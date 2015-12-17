


	#include "gstd/typename.h"


template<> const char* type_name(int8_t&) { return "int8"; }
template<> const char* type_name(int16_t&) { return "int16"; }
template<> const char* type_name(int32_t&) { return "int32"; }
template<> const char* type_name(int64_t&) { return "int64"; }

template<> const char* type_name<int8_t>() { return "int8"; }
template<> const char* type_name<int16_t>() { return "int16"; }
template<> const char* type_name<int32_t>() { return "int32"; }
template<> const char* type_name<int64_t>() { return "int64"; }

template<> const char* type_name(uint8_t&) { return "uint8"; }
template<> const char* type_name(uint16_t&) { return "uint16"; }
template<> const char* type_name(uint32_t&) { return "uint32"; }
template<> const char* type_name(uint64_t&) { return "uint64"; }

template<> const char* type_name<uint8_t>() { return "uint8"; }
template<> const char* type_name<uint16_t>() { return "uint16"; }
template<> const char* type_name<uint32_t>() { return "uint32"; }
template<> const char* type_name<uint64_t>() { return "uint64"; }



template<> const char* type_name(const char*&) { return "const char*"; }
template<> const char* type_name(char*&) { return "char*"; }
template<> const char* type_name(char&) { return "char"; }
template<> const char* type_name<const char*>() { return "const char*"; }
template<> const char* type_name<char*>() { return "char*"; }
template<> const char* type_name<char>() { return "char"; }



template<> const char* type_name(float&) { return "float"; }
template<> const char* type_name(double&) { return "double"; }
template<> const char* type_name<float>() { return "float"; }
template<> const char* type_name<double>() { return "double"; }	

