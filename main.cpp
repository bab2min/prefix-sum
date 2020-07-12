#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <xmmintrin.h>
#include <immintrin.h>

class BenchmarkHelper
{
	std::map<std::string, double>& timing;
	std::map<std::string, double>& timingSq;
	std::map<std::string, double>& err;

	template<typename _Ty>
	class ScopeMeasure
	{
		BenchmarkHelper& bh;
		const std::vector<_Ty>& a;
		const std::vector<_Ty>& b;
		std::string name;
		std::chrono::high_resolution_clock::time_point start;
	public:
		ScopeMeasure(BenchmarkHelper& _bh,
			const std::vector<_Ty>& _a,
			const std::vector<_Ty>& _b,
			const std::string& _name) :
			bh{ _bh }, a{ _a }, b{ _b }, name{ _name },
			start{ std::chrono::high_resolution_clock::now() }
		{
		}

		~ScopeMeasure()
		{
			if (!name.empty())
			{
				double t = (std::chrono::high_resolution_clock::now() - start).count() / 1e+6;
				bh.timing[name] += t;
				bh.timingSq[name] += t * t;

				bh.err[name] = 0;
				for (size_t i = 0; i < a.size(); ++i)
				{
					double err = std::abs(a[i] - b[i]);
					bh.err[name] += err;
				}
			}
		}
	};
public:
	BenchmarkHelper(std::map<std::string, double>& _timing,
		std::map<std::string, double>& _timingSq,
		std::map<std::string, double>& _err)
		: timing{ _timing }, timingSq{ _timingSq }, err{ _err }
	{
	}

	template<typename _Ty>
	ScopeMeasure<_Ty> measure(const std::string& name, const std::vector<_Ty>& a, const std::vector<_Ty>& b)
	{
		return ScopeMeasure<_Ty>{*this, a, b, name};
	}
};

template<typename _Ty>
void simple(_Ty* arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        arr[i] += arr[i - 1];
    }
}

template<typename _Ty>
void simple_double(_Ty* arr, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += arr[i];
		arr[i] = sum;
	}
}

template<typename _Ty>
void kahan(_Ty* arr, int n)
{
	_Ty sum = 0, c = 0;
	for (int i = 0; i < n; ++i)
	{
		_Ty y = arr[i] - c;
		_Ty t = sum + y;
		c = (t - sum) - y;
		arr[i] = sum = t;
	}
}

template<typename _Ty>
void unroll4(_Ty* arr, int n)
{
	int n4 = n & ~3;
	_Ty acc = 0;
	for (int i = 0; i < n4; i += 4)
	{
		arr[i] += acc;
		arr[i + 1] += arr[i];
		arr[i + 2] += arr[i + 1];
		arr[i + 3] += arr[i + 2];
		acc = arr[i + 3];
	}

	for (int i = n4; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll4_reorder1(_Ty* arr, int n)
{
	int n4 = n & ~3;
	_Ty acc = 0;
	for (int i = 0; i < n4; i += 4)
	{
		arr[i] += acc;
		arr[i + 1] += arr[i];
		arr[i + 3] += arr[i + 2];

		arr[i + 2] += arr[i + 1];
		arr[i + 3] += arr[i + 1];
		acc = arr[i + 3];
	}

	for (int i = n4; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll8(_Ty* arr, int n)
{
	int n8 = n & ~7;
	_Ty acc = 0;
	for (int i = 0; i < n8; i += 8)
	{
		arr[i] += acc;
		arr[i + 1] += arr[i];
		arr[i + 2] += arr[i + 1];
		arr[i + 3] += arr[i + 2];
		arr[i + 4] += arr[i + 3];
		arr[i + 5] += arr[i + 4];
		arr[i + 6] += arr[i + 5];
		arr[i + 7] += arr[i + 6];
		acc = arr[i + 7];
	}

	for (int i = n8; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll8_reorder1(_Ty* arr, int n)
{
	int n8 = n & ~7;
	_Ty acc = 0;
	for (int i = 0; i < n8; i += 8)
	{
		arr[i] += acc;
		// first accumulation
		arr[i + 1] += arr[i];
		arr[i + 5] += arr[i + 4];
		arr[i + 2] += arr[i + 1];
		arr[i + 6] += arr[i + 5];
		arr[i + 3] += arr[i + 2];
		arr[i + 7] += arr[i + 6];

		// final accumulation
		arr[i + 4] += arr[i + 3];
		arr[i + 5] += arr[i + 3];
		arr[i + 6] += arr[i + 3];
		arr[i + 7] += arr[i + 3];
		acc = arr[i + 7];
	}

	for (int i = n8; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll8_reorder2(_Ty* arr, int n)
{
	int n8 = n & ~7;
	_Ty acc = 0;
	for (int i = 0; i < n8; i += 8)
	{
		arr[i] += acc;
		// first accumulation
		arr[i + 1] += arr[i];
		arr[i + 3] += arr[i + 2];
		arr[i + 5] += arr[i + 4];
		arr[i + 7] += arr[i + 6];

		// second accumulation
		arr[i + 2] += arr[i + 1];
		arr[i + 3] += arr[i + 1];

		arr[i + 6] += arr[i + 5];
		arr[i + 7] += arr[i + 5];

		// final accumulation
		arr[i + 4] += arr[i + 3];
		arr[i + 5] += arr[i + 3];
		arr[i + 6] += arr[i + 3];
		arr[i + 7] += arr[i + 3];

		acc = arr[i + 7];
	}

	for (int i = n8; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll16(_Ty* arr, int n)
{
	int n16 = n & ~15;
	_Ty acc = 0;
	for (int i = 0; i < n16; i += 16)
	{
		arr[i] += acc;
		arr[i + 1] += arr[i];
		arr[i + 2] += arr[i + 1];
		arr[i + 3] += arr[i + 2];
		arr[i + 4] += arr[i + 3];
		arr[i + 5] += arr[i + 4];
		arr[i + 6] += arr[i + 5];
		arr[i + 7] += arr[i + 6];
		arr[i + 8] += arr[i + 7];
		arr[i + 9] += arr[i + 8];
		arr[i + 10] += arr[i + 9];
		arr[i + 11] += arr[i + 10];
		arr[i + 12] += arr[i + 11];
		arr[i + 13] += arr[i + 12];
		arr[i + 14] += arr[i + 13];
		arr[i + 15] += arr[i + 14];
		acc = arr[i + 15];
	}

	for (int i = n16; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll16_reorder1(_Ty* arr, int n)
{
	int n16 = n & ~15;
	_Ty acc = 0;
	for (int i = 0; i < n16; i += 16)
	{
		arr[i] += acc;
		// first accumulation
		arr[i + 1] += arr[i];
		arr[i + 9] += arr[i + 8];
		arr[i + 2] += arr[i + 1];
		arr[i + 10] += arr[i + 9];
		arr[i + 3] += arr[i + 2];
		arr[i + 11] += arr[i + 10];
		arr[i + 4] += arr[i + 3];
		arr[i + 12] += arr[i + 11];
		arr[i + 5] += arr[i + 4];
		arr[i + 13] += arr[i + 12];
		arr[i + 6] += arr[i + 5];
		arr[i + 14] += arr[i + 13];
		arr[i + 7] += arr[i + 6];
		arr[i + 15] += arr[i + 14];
		
		// final accumulation
		arr[i + 8] += arr[i + 7];
		arr[i + 9] += arr[i + 7];
		arr[i + 10] += arr[i + 7];
		arr[i + 11] += arr[i + 7];
		arr[i + 12] += arr[i + 7];
		arr[i + 13] += arr[i + 7];
		arr[i + 14] += arr[i + 7];
		arr[i + 15] += arr[i + 7];
		
		acc = arr[i + 15];
	}

	for (int i = n16; i < n; ++i)
	{
		arr[i] += acc;
	}
}

template<typename _Ty>
void unroll16_reorder2(_Ty* arr, int n)
{
	int n16 = n & ~15;
	_Ty acc = 0;
	for (int i = 0; i < n16; i += 16)
	{
		arr[i] += acc;
		// first accumulation
		arr[i + 1] += arr[i];
		arr[i + 5] += arr[i + 4];
		arr[i + 9] += arr[i + 8];
		arr[i + 13] += arr[i + 12];

		arr[i + 2] += arr[i + 1];
		arr[i + 6] += arr[i + 5];
		arr[i + 10] += arr[i + 9];
		arr[i + 14] += arr[i + 13];

		arr[i + 3] += arr[i + 2];
		arr[i + 7] += arr[i + 6];
		arr[i + 11] += arr[i + 10];
		arr[i + 15] += arr[i + 14];

		// second accumulation
		arr[i + 4] += arr[i + 3];
		arr[i + 5] += arr[i + 3];
		arr[i + 6] += arr[i + 3];
		arr[i + 7] += arr[i + 3];

		arr[i + 12] += arr[i + 11];
		arr[i + 13] += arr[i + 11];
		arr[i + 14] += arr[i + 11];
		arr[i + 15] += arr[i + 11];

		// final accumulation
		arr[i + 8] += arr[i + 7];
		arr[i + 9] += arr[i + 7];
		arr[i + 10] += arr[i + 7];
		arr[i + 11] += arr[i + 7];
		arr[i + 12] += arr[i + 7];
		arr[i + 13] += arr[i + 7];
		arr[i + 14] += arr[i + 7];
		arr[i + 15] += arr[i + 7];

		acc = arr[i + 15];
	}

	for (int i = n16; i < n; ++i)
	{
		arr[i] += acc;
	}
}

#ifdef __AVX__
inline __m256 scan_AVX(__m256 x)
{
	__m256 t0, t1;
	//shift1_AVX + add
	// x: [0, 1, 2, 3, 4, 5, 6, 7]
	t0 = _mm256_permute_ps(x, _MM_SHUFFLE(2, 1, 0, 3));
	// t0: [3, 0, 1, 2, 7, 4, 5, 6]
	t1 = _mm256_permute2f128_ps(t0, t0, 41);
	// t1: [., ., ., ., 3, 0, 1, 2]
	x = _mm256_add_ps(x, _mm256_blend_ps(t0, t1, 0x11));
	// x += [., 0, 1, 2, 3, 4, 5, 6] : [0, 01, 12, 23, 34, 45, 56, 67]
	//shift2_AVX + add
	t0 = _mm256_permute_ps(x, _MM_SHUFFLE(1, 0, 3, 2));
	t1 = _mm256_permute2f128_ps(t0, t0, 41);
	x = _mm256_add_ps(x, _mm256_blend_ps(t0, t1, 0x33));
	//shift3_AVX + add
	x = _mm256_add_ps(x, _mm256_permute2f128_ps(x, x, 41));
	return x;
}

inline void prefix_sum_AVX(float* a, size_t n)
{
	__m256 offset = _mm256_setzero_ps();
	for (size_t i = 0; i < n; i += 8)
	{
		__m256 x = _mm256_loadu_ps(&a[i]);
		__m256 out = scan_AVX(x);
		out = _mm256_add_ps(out, offset);
		_mm256_storeu_ps(&a[i], out);
		//broadcast last element
		__m256 t0 = _mm256_permute2f128_ps(out, out, 0x11);
		offset = _mm256_permute_ps(t0, 0xff);
	}
}

inline void avx_sum(float* arr, size_t K)
{
	size_t Kf = (K >> 3) << 3;
	if (Kf) prefix_sum_AVX(arr, Kf);
	else Kf = 1;
	for (size_t i = Kf; i < K; ++i)
	{
		arr[i] += arr[i - 1];
	}
}
#endif

#ifdef __SSE2__
inline __m128 scan_SSE(__m128 x)
{
	x = _mm_add_ps(x, _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(x), 4)));
	x = _mm_add_ps(x, _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(x), 8)));
	return x;
}

inline void prefix_sum_SSE(float* a, size_t n)
{
	__m128 offset = _mm_setzero_ps();
	for (size_t i = 0; i < n; i += 4)
	{
		__m128 x = _mm_load_ps(&a[i]);
		__m128 out = scan_SSE(x);
		out = _mm_add_ps(out, offset);
		_mm_store_ps(&a[i], out);
		offset = _mm_shuffle_ps(out, out, _MM_SHUFFLE(3, 3, 3, 3));
	}
}

inline void sse_sum(float* arr, size_t K)
{
	size_t Kf = (K >> 2) << 2;
	if (Kf) prefix_sum_SSE(arr, Kf);
	else Kf = 1;
	for (size_t i = Kf; i < K; ++i)
	{
		arr[i] += arr[i - 1];
	}
}
#endif

template<typename _Ty>
void set_arr(std::vector<_Ty>& arr)
{
    std::mt19937_64 rng;
    std::uniform_real_distribution<_Ty> ur;

    for (auto& f : arr) f = ur(rng);
}

int main()
{
    int arr_size = 1000000;
	int repeat = 50;
    std::vector<float> arrf(arr_size), goldf(arr_size);
	std::vector<float> arrd(arr_size), goldd(arr_size);
	std::map<std::string, double> time, timeSq, err;
	BenchmarkHelper bh{ time, timeSq, err };

	set_arr(goldf);
	simple_double(goldf.data(), arr_size);

	set_arr(goldd);
	kahan(goldd.data(), arr_size);

	for (int i = 0; i < repeat; ++i)
	{
		set_arr(arrf);
		{			
			auto s = bh.measure("simple/float", goldf, arrf);
			simple(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("simple_double/float", goldf, arrf);
			simple_double(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("kahan/float", goldf, arrf);
			kahan(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll4/float", goldf, arrf);
			unroll4(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll8/float", goldf, arrf);
			unroll8(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll16/float", goldf, arrf);
			unroll16(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll4_reorder1/float", goldf, arrf);
			unroll4_reorder1(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll8_reorder1/float", goldf, arrf);
			unroll8_reorder1(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll8_reorder2/float", goldf, arrf);
			unroll8_reorder2(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll16_reorder1/float", goldf, arrf);
			unroll16_reorder1(arrf.data(), arr_size);
		}

		set_arr(arrf);
		{
			auto s = bh.measure("unroll16_reorder2/float", goldf, arrf);
			unroll16_reorder2(arrf.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("simple/double", goldd, arrd);
			simple(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("kahan/double", goldd, arrd);
			kahan(arrd.data(), arr_size);
		}
		
		set_arr(arrd);
		{
			auto s = bh.measure("unroll4/double", goldd, arrd);
			unroll4(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll8/double", goldd, arrd);
			unroll8(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll16/double", goldd, arrd);
			unroll16(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll4_reorder1/double", goldd, arrd);
			unroll4_reorder1(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll8_reorder1/double", goldd, arrd);
			unroll8_reorder1(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll8_reorder2/double", goldd, arrd);
			unroll8_reorder2(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll16_reorder1/double", goldd, arrd);
			unroll16_reorder1(arrd.data(), arr_size);
		}

		set_arr(arrd);
		{
			auto s = bh.measure("unroll16_reorder2/double", goldd, arrd);
			unroll16_reorder2(arrd.data(), arr_size);
		}

#ifdef __SSE2__
		set_arr(arrf);
		{
			auto s = bh.measure("sse/float", goldf, arrf);
			sse_sum(arrf.data(), arr_size);
		}
#endif

#ifdef __AVX__
		set_arr(arrf);
		{
			auto s = bh.measure("avx/float", goldf, arrf);
			avx_sum(arrf.data(), arr_size);
		}
#endif
	}

	std::cout << "Prefix Sum of 1M" << std::endl;

	for (auto& p : time)
	{
		double mean = p.second / repeat;
		double var = timeSq[p.first] / repeat - mean * mean;
		std::cout << std::left << std::setw(24) << p.first;
		std::cout << ": " << mean << " (" << std::sqrt(var) << ") : " << err[p.first] << std::endl;
	}

	std::cout << std::endl;

    return 0;
}
