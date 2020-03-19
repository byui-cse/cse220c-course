#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

struct person {
    int age;
    double weight;
};

bool buildPerson(struct person** builtPerson){
	int personSize = sizeof(struct person);
    struct person* aPerson = (struct person*)malloc(personSize);
    *builtPerson = aPerson;
    //eventually we will get these values from the user
    aPerson->age = 3;
    aPerson->weight = 190.5;
    return true;
}

int main(int argc, const char * argv[]) {
    struct person* aPerson = NULL;//set the pointer to point at nothing (NULL)
    bool success = buildPerson(&aPerson);
    /*
     * more code here that uses success and aPerson
     */
    printf("%d %f\n",aPerson->age, aPerson->weight );
}