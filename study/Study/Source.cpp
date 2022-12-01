#include "pch.h"
#include "Vector.h"
#include "Array.h"
#include "String.h"












int main() {
#if 0
	{
		String name("James");
		cout << name << endl;
		String name2 = name;
		name2[3] = 's';
		cout << name2 << endl;
	}
	WAIT();

	PrintArray(std::array<int, 5>{1, 2, 3, 4, 5});
	int a = 1000;
	std::function<void(int)> func = [&](int x) {
		LOG("annonymous!");
		LOG(a);
		LOG(x); 
	};
	func(1);

	std::shared_ptr<SomeData> data = create_data();
	LOG(data->x);
	LOG(data->y);

	WAIT();
	
	const Array<int, 5> arr;
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << endl;
	}

	Array<int, 5> arr2;

	for (int i = 0; i < arr2.size(); i++) {
		arr2[i] = 3;
	}
	for (int i = 0; i < arr2.size(); i++) {
		cout << arr2[i] << endl;
	}
	LOG(data);
#endif
	{
		Vector<Vector3> vectors;

		//Vector3 vec_1(1);
		//Vector3 vec_2 = vec_1;

		vectors.EmplaceBack(5);
		vectors.EmplaceBack();
		vectors.PushBack(Vector3(3, 3, 1));
		vectors.PushBack(new Vector3(1, 5, 5));
		vectors.EmplaceBack(5, 5, 1);
		vectors.EmplaceBack(6);
		vectors.EmplaceBack(7);
		vectors.EmplaceBack(5, 5, 2);
		vectors.EmplaceBack(2, 2, 1);
		vectors.PopBack();
		vectors.PopBack();
		//PrintVector(vectors);

		for (Vector3& vector : vectors) {
			std::cout << vector << std::endl;
		}
	}	

	std::cin.get();
}