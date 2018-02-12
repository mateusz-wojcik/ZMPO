#include "stdafx.h"
#include "Vector__Functions.h"
#define INCORRECTARGS  "Incorrect arguments format, enter arguments in correct form\n"
#define INCORRECTOFF "Incorrect offset value"
#define INCORRECTLEN "Incorrect length value"
#define INCORRECTINPUT "Incorrect input"
#define INCORRECTCOM "Incorrect command"
#define INCORRECTARG "Incorrect argument"
#define NOTINITIALIZED "Vector is not initialized"
#define OPFAILED "Operation failed"
#define TOSHORT "Vector length should be > 0"

using namespace std;

int main()
{
	int vector_len = START_VEC_LEN;
	int def = START_DEF;
	int used = START_USED;
	int pi_values_len = START_VAL_LEN;
	int pi_offsets_len = START_OFF_LEN;
	int* pi_values = new int[pi_values_len];
	int* pi_offsets = new int[pi_offsets_len];

	bool is_initialized = false;

	while (true)
	{
		string s;
		cin >> s;
		if (s == "mvec")
		{
			int vec_len, def_val;
			cin >> vec_len;
			cin >> def_val;
			while (!cin.good())
			{
				cout << INCORRECTARGS<< "mvec ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> vec_len;
				cin >> def_val;
			}
			if (vec_len >= 0)
			{
				if (is_initialized)
				{
					delete_All(pi_offsets, pi_values);
				}
				initialize_Vector_And_Values(vector_len, vec_len, def, def_val, used, START_USED, pi_values, pi_values_len, START_VAL_LEN, pi_offsets, pi_offsets_len, START_OFF_LEN);
				is_initialized = true;
			}
			else
			{
				cout << TOSHORT << endl;
			}
		}
		else if (s == "print")
		{
			if (!is_initialized)
			{
				cout << NOTINITIALIZED << endl;
			}
			else
			{
				cout << vec_To_String(vector_len, def, pi_offsets_len, pi_values, pi_offsets) << endl;
			}
		}
		else if (s == "def")
		{
			int off, val;
			cin >> off >> val;
			while (!cin.good())
			{
				cout << INCORRECTARGS << "def" ;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> off >> val;
			}
			if (off < 0 || off >= vector_len)
			{
				cout << INCORRECTOFF << endl;
			}
			else
			{
				assign_Value(def, off, val, pi_offsets, pi_offsets_len, used, pi_values, pi_values_len);
			}
		}
		else if (s == "len")
		{
			if (is_initialized) {
				int new_len;
				cin >> new_len;
				if (new_len < 0)
				{
					cout << INCORRECTLEN << endl;
				}
				else
				{
					change_Vector_Length(def, new_len, vector_len, pi_values, pi_values_len, pi_offsets, pi_offsets_len, used);
				}
			}
			else
			{
				cout << NOTINITIALIZED << endl;
			}
		}
		else if (s == "get")
		{
			int index;
			cin >> index;
			if (cin.good()) {
				if (is_initialized)
				{
					if (index >= 0 && index <vector_len)
					{
						cout << read_Value(index, def, pi_offsets, pi_values, used) << endl;
					}
					else
					{
						cout << INCORRECTOFF << endl;
					}
				}
				else
				{
					cout << NOTINITIALIZED << endl;
				}
			}
			else
			{
				cout << INCORRECTINPUT << endl;
				cin.clear();
			}
		}
		else if (s == "defval")
		{
			int n_def;
			cin >> n_def;
			if (is_initialized)
			{
				if (cin.good())
				{
					if (!set_Default_Value(def, n_def, used))
					{
						cout << OPFAILED << endl;
					}
				}
				else
				{
					cout << INCORRECTARG << endl;
				}
			}
			else
			{
				cout << NOTINITIALIZED << endl;
			}
		}
		else if (s == "del")
		{
			if (is_initialized)
			{
				delete_All(pi_offsets, pi_values);
				is_initialized = false;
			}
			else
			{
				cout << NOTINITIALIZED << endl;
			}
		}
		else if (s == "swap")
		{
			swap(pi_values, pi_values_len, pi_offsets, pi_offsets_len, vector_len, used, def);
		}
		else if (s == "exit")
		{
			delete_All(pi_offsets, pi_values);
			exit(0);
		}
		else
		{
			cin.clear();
			cout << INCORRECTCOM << endl;
		}
	}

	getchar();
	return 0;
}

