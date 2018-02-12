#pragma once
#include <string>
#include <iostream>
#include <string>
#include <sstream>

const int START_VEC_LEN = 15;
const int START_DEF = 0;
const int START_USED = 0;
const int START_OFF_LEN = 5;
const int START_VAL_LEN = 5;
const int USED_OFFSETS = 0;

void initialize_Vector_And_Values(int& vector_len, int v_vec_len, int& def, int v_def, int& used, int v_used, int*& pi_values, int& pi_values_len, int v_val_len, int*& pi_offsets, int& pi_offsets_len, int v_off_len);

int is_Offsets_Member(int off, int* pi_offsets, int& used_offsets);

void swap(int*& pi_values, int pi_values_len, int*& pi_offsets, int pi_offsets_len, int vec_len, int used, int def);

void change_Offsets_Len(int*& pi_offsets, int& pi_offsets_len, int& real_size);

void change_Value_Len(int*& pi_values, int& pi_values_len, int& real_size);

void cut_Offsets(int& def, int*& pi_offsets, int& pi_offsets_len, int& used_offsets, int*& pi_values, int& pi_values_len);

void assign_Value(int& def, int off, int val, int*& pi_offsets, int& pi_offsets_len, int& used_offsets, int*& pi_values, int& pi_values_len);

void cut_Offsets_And_Values(int& def, int new_vector_len, int*& pi_offsets, int& pi_offsets_len, int& used_offsets, int*& pi_values, int& pi_values_len);

void change_Vector_Length(int& def, int new_length, int& old_length, int*& pi_values, int& pi_values_len, int*& pi_offsets, int& pi_offsets_len, int& used_offsets);

bool set_Default_Value(int& old_def, int new_def, int& used_offsets);

int read_Value(int offset, int& def, int* pi_offsets, int* pi_values, int& used_offsets);

int find_In_Offsets(int number, int* pi_offsets, int& pi_offsets_len);

std::string vec_To_String(int& vector_len, int& def, int& arr_length, int* pi_values, int* pi_offsets);

bool is_Default_Value(int current_i, int* pi_offsets, int& pi_offsets_len);

void delete_All(int* pi_offsets, int* pi_values);