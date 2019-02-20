#include <stdio.h>
struct Dog
{
	int age;
	char* race;
	char vaccination;
	int legs;
};

typedef struct Dog dog_t;

int main(int argc, char *argv[])
{
	int reti = 0;

	dog_t somedog = { 6, "vlcak", 'c', 3 };
	dog_t anotherdog = { 10, "jezevcik", 'a', 4 };

	dog_t* ptrtodog = &somedog;

	printf("Vek: %i, rasa: %s\n", somedog.age, somedog.race);
	printf("Vek: %i, rasa: %s\n", (*ptrtodog).age, (*ptrtodog).race);
	printf("Vek: %i, rasa: %s\n", ptrtodog->age, ptrtodog->race);

	return reti;
}
