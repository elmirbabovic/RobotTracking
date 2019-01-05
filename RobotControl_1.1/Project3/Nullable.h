#pragma once
#include <cstddef>
//https://gist.github.com/bekasov/1e30ba3c29388b4f1627
template <class T>
class NullableType
{
protected:
	T * value;

public:
	NullableType<T>() : value(NULL) {};
	NullableType<T>(T value)
	{
		this->value = new T(value);
	};
	NullableType<T>(T* value)
	{
		if (value != NULL) {
			this->value = new T(*value);
		}
		else {
			this->value = NULL;
		}
	};
	NullableType<T>(const NullableType<T>& value)
	{
		T* tmp = (T*)value;
		if (tmp == NULL) {
			this->value = NULL;
		}
		else {
			this->value = new T(*tmp);
		}
	};
	virtual ~NullableType<T>()
	{
		if (this->value != NULL) {
			delete this->value;
		}
	};
	
	virtual operator T()
	{
	if (this->value == NULL) {
	T tmp;
	#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	#pragma GCC diagnostic ignored "-Wuninitialized"
	return tmp;
	#pragma GCC diagnostic warning "-Wmaybe-uninitialized"
	#pragma GCC diagnostic warning "-Wuninitialized"
	//return 0;
	}
	return *this->value;
	}
	
	virtual operator T*() const
	{
		return this->value;
	}

	virtual NullableType<T>& operator=(const T* const value)
	{
		if (NULL == value) {
			if (this->value != NULL) {
				delete this->value;
			}
			this->value = NULL;
			return *this;
		}

		if (this->value == NULL) {
			this->value = new T(*value);
		}
		else {
			*this->value = *value;
		}
		return *this;
	}

	virtual NullableType<T>& operator=(const T& value)
	{
		if (NULL == &value) {

			if (this->value != NULL) {
				delete this->value;
			}
			this->value = NULL;
			return *this;
		}

		if (this->value == NULL) {
			this->value = new T(value);
		}
		else {
			*this->value = value;
		}
		return *this;
	}

	virtual NullableType<T>& operator=(const NullableType<T>& value)
	{
		if (this == &value) {
			return *this;
		}
		T* tmp = (T*)value;
		if (tmp == NULL) {
			if (this->value != NULL) {
				delete this->value;
			}
			this->value = NULL;
		}
		else {
			if (this->value == NULL) {
				this->value = new T;
			}
			*this->value = *tmp;
		}
		return *this;
	}
};

