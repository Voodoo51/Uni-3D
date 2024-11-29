#pragma once
#include <vector>

#define DEFAULT_RESERVE_VALUE 100
#define INDEX_TAKEN 0

/*!
		Struktura handle. Zawiera indeks i generacje danego handle'a.
*/
struct Handle
{
	unsigned int index;
	unsigned int gen;
};

/*!
		Klasa Pool pozwalająca na łatwe ponowne użycie pamieci. Pozwala na usuwanie i dodawanie do niej elementow w czasie O(1).
*/
template <typename T>
class Pool
{
public:
	/*!
		Konstruktor pozwalający na wczesną rezerwacje pamięci.
	*/
	Pool(int reserveAmount)
	{
		firstFree = 0;
		data.push_back(T());
		genIndexes.push_back(Handle());
		data.reserve(reserveAmount);
		genIndexes.reserve(reserveAmount);
	}
	Pool()
	{
		firstFree = 0;
		data.push_back(T());
		genIndexes.push_back(Handle());
		data.reserve(DEFAULT_RESERVE_VALUE);
		genIndexes.reserve(DEFAULT_RESERVE_VALUE);
	}

	/*!
		Funkcja dodawająca element do Pool'a i zwracająca strukture Handle do dodanego elementu.
	*/
	Handle Append(T value)
	{
		Handle handle = AppendEmpty();
		data[handle.index] = value;

		return handle;
	}

	/*!
		Funkcja usuwająca element z Pool'a.
	*/
	void Remove(Handle handle)
	{
		if (handle.index <= 0 || handle.index >= data.size())
			return;

		if (genIndexes[handle.index].gen != handle.gen)
			return;

		genIndexes[handle.index].gen += 1;

		//Consider returning it
		//T removedValue = data[handle.index];

		genIndexes[handle.index].index = firstFree;
		firstFree = handle.index;
	}

	/*!
		Funkcja sprawdzająca czy dany indeks istnieje w Pool'u.
	*/
	bool HasIndex(unsigned int index)
	{
		if (index < 0 || index >= data.size())
			return false;

		return genIndexes[index].index == 4294967295;
	}

	/*!
		Funkcja zwracająca element. Przyjmuje strukture Handle.
	*/
	T& Get(Handle handle)
	{
		return data[handle.index];
	}

	/*!
		Lista zawierająca elementy.
	*/
	std::vector<T> data;
private:

	Handle AppendEmpty()
	{
		unsigned int index = firstFree;
		if (index > 0 && index < data.size())
		{
			firstFree = genIndexes[index].index;
		}
		else
		{
			data.push_back(T());
			genIndexes.push_back(Handle());
			index = data.size() - 1;
		}

		genIndexes[index].index = 4294967295;

		return { index, genIndexes[index].gen };
	}

	unsigned int firstFree;
	std::vector<Handle> genIndexes;
};

