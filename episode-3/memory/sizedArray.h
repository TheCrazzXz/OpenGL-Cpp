template <typename T> class SizedArray
{
public:
	T* data;
	unsigned long size;

	SizedArray(T* data, float size)
		:	data(data), size(size)
	{

	}

	unsigned long getLength()
	{
		return size/sizeof(T);
	}
};