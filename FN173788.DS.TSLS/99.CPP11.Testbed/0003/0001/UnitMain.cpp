#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
//------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> v { 1, 2, 3, 4, 5};

	// for_each()
	std::cout << "for_each() test:" << std::endl;
	for_each(v.begin(), v.end(), [](int i){ std::cout << i << " "; });

	// count_if()
	const int c = count_if(v.begin(), v.end(), [](int i)->bool{ return (i <= 3); });
	std::cout << std::endl << std::endl << "count_if( <= 3) test:" << std::endl << c;

	// replace_if()
	replace_if(v.begin(), v.end(), [](int i)->bool{ return (i == 5); }, 10);
	std::cout << std::endl << std::endl << "replace_if( == 5) test:" << std::endl;
	for_each(v.begin(), v.end(), [](int i){ std::cout << i << " "; });

	// sort()
	std::vector<int> v2 { 7, 5, 6, 5, 4, 3, 8, 4};
	sort(v2.begin(), v2.end());
	std::cout << std::endl << std::endl << "sort() test:" << std::endl;
	for_each(v2.begin(), v2.end(), [](int i){ std::cout << i << " "; });

	// stable_sort()
	// stable sorts preserve the physical order of semantically equivalent values
	// cannot be performed quite as efficiently in terms of execution time,
	// unless "additional memory is available"
	std::vector<std::wstring> v3 { L"C", L"B'", L"A", L"B"};
	stable_sort(v3.begin(), v3.end());
	std::cout << std::endl << std::endl << "stable_sort() test:" << std::endl;
	for_each(v3.begin(), v3.end(), [](std::wstring s){ std::wcout << s.c_str() << " "; });

	// min_element(), max_element()
	// elements should be sorted in advance; returns iterators, thus should *deref;
	std::cout << std::endl  << std::endl << "min: " << *min_element(v2.begin(), v2.end()) << std::endl
										 << "max: " << *max_element(v2.begin(), v2.end()) << std::endl;

	// unique()
	// Stage #1
	auto it = unique(v2.begin(), v2.end());
	std::cout << std::endl << std::endl << "unique() test stage #1:" << std::endl;
	for_each(v2.begin(), v2.end(), [](int i){ std::cout << i << " "; });
	//
	// Stage #2: erase of trail left after Stage #1
	v2.erase(it, v2.end());
	std::cout << std::endl << std::endl << "unique() test stage #2:" << std::endl;
	for_each(v2.begin(), v2.end(), [](int i){ std::cout << i << " "; });

	// set_intersection()
	std::vector<int> v4(v.size() + v2.size());
	auto it2 = set_intersection(v.begin(), v.end(), v2.begin(), v2.end(), v4.begin());
	std::cout << std::endl << std::endl << "set_intersection() test:" << std::endl;
	for_each(v.begin(), v.end(), [](int i){ std::cout << i << " "; });
	std::cout << std::endl;
	for_each(v2.begin(), v2.end(), [](int i){ std::cout << i << " "; });
	std::cout << std::endl << "Intersection of two above vectors:" << std::endl;
	for_each(v4.begin(), it2, [](int i){ std::cout << i << " "; });

	// reverse()
	reverse(v2.begin(), v2.end());
	std::cout << std::endl << std::endl << "reverse() test:" << std::endl;
	for_each(v2.begin(), v2.end(), [](int i){ std::cout << i << " "; });

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

