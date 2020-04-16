#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 60
#define PHONE_LEN 24
#define ADDRESS_BOOK_SIZE 256

//Definizione della struct contact_type
typedef struct {
	int id;
	char name[NAME_LEN + 1];
	char phone[PHONE_LEN + 1];
} contact_type;


//Dichiarazioni di funzioni
contact_type * create_contact(char * name, char * phone);
void print_contact(contact_type * person);
int compare_contacts(contact_type * c1, contact_type * c2);
int add_to_address_book(contact_type * c);
int remove_from_address_book(contact_type * c);
int search_in_address_book(contact_type * c);
void sort_by_name();
void swap_contacts();
void bubble_sort();

//Variabili globali
int counter = 0;
contact_type * address_book[ADDRESS_BOOK_SIZE];


int main(int argc, char *arcv[]) {

	//1. Definisco tutti i contatti qua tramite la funzione create_contact
	contact_type * dino = create_contact("dino","+391237");
	contact_type * filippo = create_contact("filippo", "+391239");
	contact_type * barbara = create_contact("barbara","+391235");
	contact_type * antonio = create_contact("antonio","+391234");
	contact_type * enrico = create_contact("enrico","+391238");
	contact_type * chiara = create_contact("chiara","+391236");

	//Li aggiungo tutti all'array di puntatori di contact_type address_book
	add_to_address_book(dino);
	add_to_address_book(filippo);
	add_to_address_book(barbara);
	add_to_address_book(antonio);
	add_to_address_book(enrico);
	add_to_address_book(chiara);

	//2. Creo un altro antonio per provare la funzione di ricerca.
	antonio = create_contact("antonio","+391234");

	//Cerco il contatto "antonio" nella lista e se esiste lo elimina, liberando anche la memoria
	if(search_in_address_book(antonio) > 0) {
		remove_from_address_book(antonio);
		printf("Ho rimosso %s dalla lista con successo!\n", (*antonio).name);
		free(antonio);
		antonio = NULL;
	}

	//3. Creo il contatto pino e lo aggiungo alla lista.
	contact_type * pino = create_contact("pino","+399999");
	add_to_address_book(pino);

	//Scrivo su stdout tutti i valori non nulli dell'array address_book.
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
		if(address_book[i] != NULL) {
			print_contact(address_book[i]);
		}
	}
	printf("\n");

	//4. Riaggiungo antonio alla lista.
	antonio = create_contact("antonio","+391234");
	add_to_address_book(antonio);


	//5. Ordino la lista. I termini NULL vengono considerati "ultimi" e vengono ordinati in fondo all'array.
	sort_by_name();


	//6. Scrivo su stdout tutti i valori non nulli dell'array address_book ordinato.
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
		if(address_book[i] != NULL) {
			print_contact(address_book[i]);
		}
	}


	return 0;
}

/**
 * Questa funzione alloca la memoria, inizializza i valori e restituisce
 * il puntatore alla zona di memoria del contatto.
 */
contact_type * create_contact(char * name, char * phone) {
	contact_type *output;
	output = malloc(sizeof(contact_type));
	if(output == NULL) {
		printf("errore in create_contact!\n");
		exit(1);
		return NULL;
	}
	(*output).id = counter;
	counter++;
	for(int k = 0; k<NAME_LEN; k++) {
		(*output).name[k] = name[k];
	}
	for(int k = 0; k<PHONE_LEN; k++) {
		(*output).phone[k] = phone[k];
	}
	return output;
}

/**
 * Confronta due contatti. Prima confronta il nome,
 * e se esso è uguale confronta il numero di telefono.
 * Restituisce 0 se uguali, >0 se il primo è "maggiore" (lessicograficamente),
 * <0 se il primo è "minore".
 */
int compare_contacts(contact_type * c1, contact_type * c2) {
	int k = strcmp((*c1).name, (*c2).name);
	if(k != 0) {
		return k;
	} else
		return strcmp((*c1).phone, (*c2).phone);
}

/**
 * Aggiunge un contatto ad address_book. Cerca se esiste uno spazio libero nell'array (NULL)
 * e ci mette dentro il nuovo puntatore.
 * Restituisce la posizione che ha trovato, -1 se l'array è pieno.
 */
int add_to_address_book(contact_type * c) {
	int i = 0;
	while(address_book[i] != NULL && i < ADDRESS_BOOK_SIZE) {
		i++;
	}
	if(i >= ADDRESS_BOOK_SIZE) return -1;
	address_book[i] = c;
	return i;
}

/**
 * Rimuove un contatto dall'array (inizializza a NULL il valore), se esiste.
 * Restituisce la posizione del contatto che ha trovato, -1 se non ha trovato il contatto nell'array.
 */
int remove_from_address_book(contact_type * c) {
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
		if(compare_contacts(c, address_book[i]) == 0) {
			free(address_book[i]);
			address_book[i] = NULL;
			return i;
		}
	}
	return -1;
}

/**
 * Cerca il contatto nell'array.
 * Restituisce la posizione del contatto che ha trovato, -1 se non ha trovato il contatto nell'array.
 */
int search_in_address_book(contact_type * c) {
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
		if(compare_contacts(c, address_book[i]) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * Riordina l'array con l'algoritmo Bubble Sort.
 * Gli spazi NULL sono considerati "pesanti" e vengono spinti alla fine dell'array.
 */
void sort_by_name() {
	bubble_sort(address_book);
}

void swap_contacts(contact_type * c1, contact_type * c2) {
	contact_type t = *c1;
	*c1 = *c2;
	*c2 = t;
}

void bubble_sort(contact_type ** array) {
	int n, newn;

	n = ADDRESS_BOOK_SIZE;

	while (n > 1) {

		newn = 0;

		for (int i = 1; i < n; i++) {
			if(array[i] != NULL)
			if ((array[i-1] == NULL && array[i] != NULL) || compare_contacts(array[i-1], array[i]) > 0) {
				swap_contacts(array[i-1], array[i]);
				newn = i;
			}
		}

		n = newn;
	}
}

void print_contact(contact_type * person) {
	printf("person: id=%d, name=%s, phone=%s\n",(*person).id,(*person).name,(*person).phone);
}
