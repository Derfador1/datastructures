

#include "search.h"

bool cbinary_search(const char needle,
		const char *arr, const size_t sz)
{
	if(!arr || sz == 0) {
		return false;
	}

	size_t step_size = sz/2;
	size_t n = step_size;

	while(arr[n] != needle) {
		if(step_size <= 1) {
			break;
		}
		step_size -= step_size/2;

		if(arr[n] > needle) {
			n -= step_size;
		} else {
			n += step_size;
		}
		if(n >= sz) {
			return false;
		}
	}

	return arr[n] == needle ||
		arr[0] == needle ||
		arr[sz-1] == needle;
}

