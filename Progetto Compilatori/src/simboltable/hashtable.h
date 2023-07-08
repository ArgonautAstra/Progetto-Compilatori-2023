#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/**
 * "Pippobaudo" - 6666/GT - Periodo
 * Spesa totale del gruppo senza sconto: %lf
 * Spesa totale del gruppo con sconto: %lf
 *
 *
 *
 *
 *
 * Spesa totale dell'albergo: %lf
 */
/**
 * Nome gruppo - codice gruppo - membri totale del gruppo - Periodo
 *
 * Nome delle camera - prezzo delle camera
 *
 *
 * mese/anno
 *
 */
extern FILE *yyout;
#define HASHSIZE 127
typedef struct group
{
    char *name_group;
    char *code_group;
    int members;
    char *period;
    Booked* nextroom;
    Group *next;

} Group;

typedef struct booked{
    char * name;
    int booked;
    Booked* next;
} Booked;

typedef struct room
{
    char *name;
    float cost;
    Room *next;
} Room;

/* Auxiliary Functions*/
Group *create_group(char *name_group, char *code_group, int members, char *period, Booked* rooms);

Room *create_room(char *name, float cost);

Booked *create_booked(char *name, int booked);

/* HASHTABLE  (int,Group) */
Group *hashtable_group[HASHSIZE] = {0};

unsigned int hash(char *s);

void insert_group(Group *group);

Group *lookup_group(char *name_group);

/* HASHTABLE (int,Room)*/
Room *hashtable_room[HASHSIZE] = {0};

void insert_room(Room *room);

Room *lookup_room(char *name);

/* LinkedList */
void insert_booked(Booked** booked_list, Booked *booked);

void stampalista(Booked *node);

void print_tot();
