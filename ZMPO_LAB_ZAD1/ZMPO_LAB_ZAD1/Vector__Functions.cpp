#include "stdafx.h"
#include "Vector__Functions.h"

int is_Offsets_Member(int off, int* pi_offsets, int& used_offsets)
{
	for (int i = 0; i < used_offsets; i++)
	{
		if (pi_offsets[i] == off)
		{
			return i;
		}
	}
	return -1;
}


void swap(int*& pi_values, int pi_values_len, int*& pi_offsets, int pi_offsets_len, int vec_len, int used, int def)
{
	if (is_Offsets_Member(0, pi_offsets, used) != -1 && is_Offsets_Member((vec_len) - 1, pi_offsets, used) == -1)
	{
		pi_offsets[is_Offsets_Member(0, pi_offsets, used)] = vec_len - 1;
	}
	else if (is_Offsets_Member(0, pi_offsets, used) == -1 && is_Offsets_Member((vec_len) - 1, pi_offsets, used) != -1)
	{
		pi_offsets[is_Offsets_Member((vec_len) - 1, pi_offsets, used)] = 0;
	}
	else if (is_Offsets_Member(0, pi_offsets, used) != -1 && is_Offsets_Member((vec_len) - 1, pi_offsets, used) != -1)
	{
		pi_offsets[is_Offsets_Member((vec_len)-1, pi_offsets, used)] = 0;
		pi_offsets[is_Offsets_Member(0, pi_offsets, used)] = vec_len - 1;
	}
}

void change_Offsets_Len(int*& pi_offsets, int& pi_offsets_len, int& real_size)
{
	int* pi_offsets_new;
	pi_offsets_new = new int[pi_offsets_len * 2];
	for (int i = 0; i < real_size; i++)
	{
		pi_offsets_new[i] = pi_offsets[i];
	}
	delete[] pi_offsets;
	pi_offsets_len *= 2;
	pi_offsets = pi_offsets_new;
}

void change_Value_Len(int*& pi_values, int& pi_values_len, int& real_size)
{
	int* pi_values_new;
	pi_values_new = new int[pi_values_len * 2];
	for (int i = 0; i < real_size; i++)
	{
		pi_values_new[i] = pi_values[i];
	}
	delete[] pi_values;
	pi_values_len *= 2;
	pi_values = pi_values_new;
}

//przepisuje bez wartosci domyslnych, ucina ich offsety
void cut_Offsets(int& def, int*& pi_offsets, int& pi_offsets_len, int& used_offsets, int*& pi_values, int& pi_values_len)
{
	int* pi_offsets_new = new int[pi_offsets_len];
	int* pi_values_new = new int[pi_values_len];
	int countner = 0;
	for (int i = 0; i < pi_offsets_len; i++)
	{
		if (pi_values[i] != def)
		{
			pi_values_new[i - countner] = pi_values[i];
			pi_offsets_new[i - countner] = pi_offsets[i];
		}
		else
		{
			countner++;
			(used_offsets)--;
		}
	}
	delete[] pi_offsets;
	pi_offsets_len = pi_offsets_len;
	pi_offsets = pi_offsets_new;

	delete[] pi_values;
	pi_values_len = pi_values_len;
	pi_values = pi_values_new;
}

void assign_Value(int& def, int off, int val, int*& pi_offsets, int& pi_offsets_len, int& used_offsets, int*& pi_values, int& pi_values_len)
{
	int tmp = is_Offsets_Member(off, pi_offsets, used_offsets);
	if (tmp != -1)
	{
		pi_values[tmp] = val;
		if (val == def)
		{
			cut_Offsets(def, pi_offsets, pi_offsets_len, used_offsets, pi_values, pi_values_len);
		}
	}
	else
	{
		if (val != def && used_offsets < pi_offsets_len)
		{
			pi_offsets[used_offsets] = off;
			pi_values[used_offsets] = val;
			(used_offsets)++;
		}
		else if (val != def && used_offsets >= pi_offsets_len)
		{
			change_Offsets_Len(pi_offsets, pi_offsets_len, used_offsets);
			change_Value_Len(pi_values, pi_values_len, used_offsets);
			pi_offsets[used_offsets] = off;
			pi_values[used_offsets] = val;
			(used_offsets)++;
		}
	}
}

//skraca tablice offsetow i wartosci przy skracaniu wektora
void cut_Offsets_And_Values(int& def, int new_vector_len, int*& pi_offsets, int& pi_offsets_len, int& used_offsets, int*& pi_values, int& pi_values_len)
{
	for (int i = 0; i < used_offsets; i++)
	{
		if (pi_offsets[i] >= new_vector_len)
		{
			pi_values[i] = def;
		}
	}
	int* pi_offsets_new = new int[pi_offsets_len];
	int* pi_values_new = new int[pi_values_len];
	int countner = 0;
	for (int i = 0; i < pi_offsets_len; i++)
	{
		if (pi_values[i] != def)
		{
			pi_values_new[i - countner] = pi_values[i];
			pi_offsets_new[i - countner] = pi_offsets[i];
		}
		else
		{
			countner++;
			(used_offsets)--;
		}
	}
	delete[] pi_offsets;
	pi_offsets_len = pi_offsets_len;
	pi_offsets = pi_offsets_new;

	delete[] pi_values;
	pi_values_len = pi_values_len;
	pi_values = pi_values_new;
}

//zmiana dlugosci wektora rzadkiego   used_offsets = realna ilosc offsetow, czyli elementow, ktore sa rozne od domyslnej wartosci wektora
void change_Vector_Length(int& def, int new_length, int& old_length, int*& pi_values, int& pi_values_len, int*& pi_offsets, int& pi_offsets_len, int& used_offsets)
{
	if (old_length < new_length)
	{
		old_length = new_length;
	}
	if (old_length > new_length)
	{
		cut_Offsets_And_Values(def, new_length, pi_offsets, pi_offsets_len, used_offsets, pi_values, pi_values_len);
		old_length = new_length;
	}
}

bool set_Default_Value(int& old_def, int new_def, int& used_offsets)
{
	if (used_offsets == 0)
	{
		old_def = new_def;
		return true;
	}
	return false;
}

//pobiera okreslon¹ wartosc z okreslonego offsetu
int read_Value(int offset, int& def, int* pi_offsets, int* pi_values, int& used_offsets)
{
	for (int i = 0; i < used_offsets; i++)
	{
		if (pi_offsets[i] == offset)
		{
			return pi_values[i];
		}
	}
	return def;
}

std::string vec_To_String(int& vector_len, int& def, int& arr_len, int* pi_values, int* pi_offsets) //zwraca informacje o wektorze jako string
{
	std::stringstream result;
	result << "len: " << vector_len << " values: ";
	for (int i = 0; i < vector_len; i++)
	{
		if (find_In_Offsets(i, pi_offsets, arr_len) == -1)
		{
			result << def;
		}
		else
		{
			result << pi_values[(find_In_Offsets(i, pi_offsets, arr_len))];
		}
		if (i != vector_len - 1) result << ",";
	}
	return result.str();
}

//zwraca indeks tablicy offsets, w którym odnaleziono podany numer, jesli nie odnaleziono to zwraca -1
int find_In_Offsets(int number, int* pi_offsets, int& pi_offsets_len)
{
	for (int i = 0; i < pi_offsets_len; i++)
	{
		if (number == pi_offsets[i]) return i;
	}
	return -1;
}

bool is_Default_Value(int current_i, int* pi_offsets, int& pi_offsets_len)
{
	for (int i = 0; i < pi_offsets_len; i++)
	{
		if (pi_offsets[i] == current_i)
		{
			return false;
		}
	}
	return true;
}

void delete_All(int* pi_offsets, int* pi_values)
{
	delete[] pi_offsets;
	delete[] pi_values;
}

void initialize_Vector_And_Values(int& vector_len, int v_vec_len, int& def, int v_def, int& used, int v_used, int*& pi_values, int& pi_values_len, int v_val_len, int*& pi_offsets, int& pi_offsets_len, int v_off_len)
{
	vector_len = v_vec_len;
	def = v_def;
	used = v_used;
	pi_values_len = v_val_len;
	pi_values = new int[pi_values_len];
	pi_offsets_len = v_off_len;
	pi_offsets = new int[pi_offsets_len];
}