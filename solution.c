#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256

typedef struct
{
    int id;                    // id numerico del contatto (valore univoco)
    char name[NAME_LEN + 1];   // nome della persona
    char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

contact_type *address_book[ADDRESS_BOOK_SIZE];
int counter = 0;
contact_type *create_contact(char *name, char *phone)
{
    contact_type *result = malloc(sizeof(contact_type));
    memset(result, 0, sizeof(contact_type));
    (*result).id = counter;
    memcpy((*result).name, name, NAME_LEN + 1);
    memcpy((*result).phone, phone, PHONE_LEN + 1);

    counter++;

    return result;
}

void print_contact(contact_type *person)
{
    printf("person: id=%d, name='%s', phone='%s'\n", person->id, person->name, person->phone);
}

int compare_contacts(contact_type *c1, contact_type *c2)
{
    if (c1 == NULL || c2 == NULL)
        return -1;
    int result_name = strcmp(c1->name, c2->name);
    int result_phone = strcmp(c1->phone, c2->phone);
    if (result_name == 0 && result_phone == 0)
        return 0;
    else
        return result_name;
}

int add_to_address_book(contact_type *c)
{
    if (c == NULL || address_book[ADDRESS_BOOK_SIZE - 1] != NULL)
        return -1;
    for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
    {
        if (address_book[i] == NULL)
        {   
            c->id = i;
            address_book[i] = c;
            return address_book[i]->id;
        }
    }

    return -1;
}

int remove_from_address_book(contact_type *c)
{
    int check = 0;
    for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
    {
        if (compare_contacts(c, address_book[i]) == 0)
        {
            address_book[i] = NULL;
            return c->id;
        }
        else
            check++;
    }
    if (check == ADDRESS_BOOK_SIZE)
        return -1;
        
    return -1;
}

int search_in_address_book(contact_type *c)
{
    int check = 0;
    for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
    {
        if (compare_contacts(c, address_book[i]) == 0)
        {
            return address_book[i]->id;
        }
        else
            check++;
    }
    if (check == ADDRESS_BOOK_SIZE)
        return -1;

    return -1;
}

void swap(contact_type *x, contact_type *y)
{
    contact_type t = *x;
    *x = *y;
    *y = t;
}

void sort_by_name()
{
    unsigned int length = 0;
    for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
    {
        if (address_book[i] != NULL)
            length++;
    }
    int newn = 0;
    while (length > 1)
    {
        for (int i = 1; i < length; i++)
        {
            if (compare_contacts(address_book[i - 1], address_book[i]) > 0)
            {
                swap(address_book[i - 1], address_book[i]);
                newn = i;
            }
        }
        length = newn;
    }
}

int main(int argc, char *argv[])
{
    contact_type *dino = create_contact("dino", "+391237");
    contact_type *filippo = create_contact("filippo", "+391239");
    contact_type *barbara = create_contact("barbara", "+391235");
    contact_type *antonio = create_contact("antonio", "+391234");
    contact_type *enrico = create_contact("enrico", "+391238");
    contact_type *chiara = create_contact("chiara", "+391236");
    //aggiungiamo i contatti alla rubrica
    if (add_to_address_book(dino) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    if (add_to_address_book(filippo) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    if (add_to_address_book(barbara) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    if (add_to_address_book(antonio) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    if (add_to_address_book(enrico) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    if (add_to_address_book(chiara) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    //eliminiamo ora antonio
    int delete = remove_from_address_book(antonio);
    if (delete == -1)
    {
        printf("\nerrore, contatto non trovato!\n");
        exit(1);
    }
    //creaimo contatto pino e aggiungiamolo
    contact_type *pino = create_contact("pino", "+399999");
    if (add_to_address_book(pino) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    //stampiamo la rubrica
    for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
    {
        if (address_book[i] != NULL)
            print_contact(address_book[i]);
    }
    if (add_to_address_book(antonio) == -1)
    {
        printf("\nerrore inserimento!!\n");
        exit(1);
    }
    //ordiniamo la rubrica per nome
    sort_by_name();
    printf("\n\n");
    for (int i = 0; i < ADDRESS_BOOK_SIZE; i++)
    {
        if (address_book[i] != NULL)
            print_contact(address_book[i]);
    }

    return 0;
}
