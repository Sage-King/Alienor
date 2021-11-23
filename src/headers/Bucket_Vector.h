#ifndef BUCKET_VECTOR_H_GUARD
#define BUCKET_VECTOR_H_GUARD

#include <iostream>
#include <vector>
namespace Sage
{
	template <typename T>
	class Bucket_Vector
	{
	public:
		Bucket_Vector(unsigned int num_of_buckets)
		:
		num_of_buckets(num_of_buckets)
		{
			for (unsigned int i = 0; i < num_of_buckets; i++)
			{
				vector.push_back(std::vector<T>{});
			}
		}

		void insert(const T& inserted_element, unsigned int bucket)
		{
			if (bucket > (num_of_buckets - 1)) 
			{
				std::cout << "Bucket Vector does not have that many buckets! num_of_buckets = " + num_of_buckets + '\n';
				return;
			}
			else
			{
				vector[bucket].push_back(inserted_element);
			}
		}

		std::vector<T> get_full_list()
		{
			std::vector<T> return_vector{};
			for(int i = 0; i < vector.size(); i++)
				return_vector.insert(return_vector.end(), vector[i].begin(), vector[i].end());

			return return_vector;
		}
	private:
		unsigned int num_of_buckets;
		std::vector<std::vector<T>> vector;
	};

}
#endif