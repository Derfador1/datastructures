
#include <stdio.h>
#include <stlib.h>
#include <string.h>

const char *data[] = {
	"Bashful", "Bashful",
	"Doc", "Doc", "Doc", "Doc", "Doc", "Doc", "Doc",
	"Dopey", "Dopey", "Dopey", "Dopey", "Dopey", "Dopey",
	"Grumpy", "Grumpy",
	"Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy", "Happy",
	"Sleepy",
	"Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy", "Sneezy"
};

size_t data_size(void)
{
	return sizeof(data)/sizeof(data[0]);
}


size_t needle_count(const char *needle, const char *arr[], size_t n)
{
	return 0;
}

int main(void)
{

	printf("Happy %d (20)\n", needle_count("Happy", data, data_size()));
	printf("Sleepy %d (1)\n", needle_count("Sleepy", data, data_size()));
	printf("Tyrion %d (0)\n", needle_count("Tyrion", data, data_size()));

}
