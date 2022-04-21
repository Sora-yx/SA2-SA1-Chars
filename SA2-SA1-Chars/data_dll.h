#pragma once


namespace data_dll {
	extern HMODULE dll_module;

	void initialize();

	template <typename T>
	static T get_data(LPCSTR name)
	{
		return reinterpret_cast<T>(*GetProcAddress(dll_module, name));
	}

	template <typename T>
	static void set_data(LPCSTR name, T data)
	{
		T* addr = reinterpret_cast<T*>(GetProcAddress(dll_module, name));

		if (addr) {
			*addr = data;
		}
	}
}