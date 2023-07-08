#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern FILE *yyout;
#define HASHSIZE 127

typedef struct booked{
    char * name;
    int booked;
} Booked;

typedef struct room{
    char *name;
    float cost;
    struct room* next;
} Room;

typedef struct group{
    char *name_group;
    char *code_group;
    int members;
    int period;
    struct booked** nextroom;
    struct group* next;
} Group;

/* Auxiliary Functions*/
Group *create_group(char *name_group, char *code_group, int members, int period, Booked* rooms[]);
Room *create_room(char *name, float cost);
Booked *create_booked(char *name, int booked);

/* Hash function*/
unsigned int hash(char *s);

/* HASHTABLE  (int,Group) */
extern Group *hashtable_group[HASHSIZE];
void insert_group(Group *group);
Group *lookup_group(char *name_group);

/* HASHTABLE (int,Room)*/
extern Room *hashtable_room[HASHSIZE];
void insert_room(Room *room);
Room *lookup_room(char *name);


/* Print functions*/
void print_tot();
