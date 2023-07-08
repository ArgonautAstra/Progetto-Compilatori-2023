#include "hashtable.h"

/* Auxiliary Functions*/

Group *create_group(char *name_group, char *code_group, int members, char *period, Booked rooms[])
{
    Group *group = malloc(sizeof(Group));
    group->name_group = strdup(name_group);
    group->code_group = strdup(code_group);
    group->members = members;
    group->period = strdup(period);
    group->nextroom = rooms; // Array of booked rooms
    group->next = NULL;
    return group;
}

Room *create_room(char *name, float cost)
{
    Room *room = malloc(sizeof(Room));
    room->name = strdup(name);
    room->cost = cost;
    room->next = NULL;
    return room;
}

Booked *create_booked(char *name, int booked)
{
    Booked *room = malloc(sizeof(Booked));
    room->name = strdup(name);
    room->booked = booked;
    return room;
}

/* Hash function*/

unsigned int hash(char *s)
{
    int h = 0, a = 127;
    for (; *s != '\0'; s++)
        h = (a * h + *s) % HASHSIZE;
    return h;
}

/* HASHTABLE  (int,Group) */

void insert_group(Group *group)
{
    if (lookup_group(group->name_group) != NULL)
        return;
    unsigned int key = hash(group->name_group);
    group->next = hashtable_group[key];
    hashtable_group[key] = group;
}

Group *lookup_group(char *name_group)
{
    Group *group_tmp = hashtable_group[hash(name_group)];
    while (group_tmp != NULL){
        if (strcmp(group_tmp->name_group, name_group) == 0)
            return group_tmp;
        group_tmp = group_tmp->next;
    }
    return NULL;
}

/* HASHTABLE (int,Room)*/

void insert_room(Room *room)
{
    if (lookup_group(room->name) != NULL)
        return;
    unsigned int key = hash(room->name);
    room->next = hashtable_group[key];
    hashtable_group[key] = room;
}

Room *lookup_room(char *name)
{
    Room *room_tmp = hashtable_room[hash(name)];
    while (room_tmp != NULL){
        if (strcmp(room_tmp->name, name) == 0)
            return room_tmp;
        room_tmp = room_tmp->next;
    }
    return NULL;
}

/* Print functions*/

float cost_calculator(Booked rooms[])
{
    float totalcost = 0.0;
    for (int i = 0; i < sizeof(rooms)/sizeof(rooms[0]); i++){
        Room *room = lookup_room(rooms[i].name);
        if (room == NULL)
            continue;
        totalcost += room->cost * rooms[i].booked;
    }
    return totalcost;
}

float cost_calculator_discount(Booked rooms[], int members)
{
    float total = cost_calculator(rooms);
    if (members >= 30 && members < 50)
        total -= (total * 15) / 100;
    else if (members >= 50)
        total -= (total * 25) / 100;
    return total;
}

void print_tot()
{
    float total_hotel;
    for (int i = 0; i < HASHSIZE; i++){
        Group *group = hashtable_group[i];
        if (group != NULL){
            float total = cost_calculator(group->nextroom), total_discount = cost_calculator_discount(group->nextroom, group->members);
            fprintf(yyout, "%s - %s - %s\n", group->name_group, group->code_group, group->period);
            fprintf(yyout, "Spesa totale del gruppo senza sconto: %f\n", total);
            if (total != total_discount)
                fprintf(yyout, "Spesa totale del gruppo con sconto: %f\n", total_discount);
            total_hotel += total_discount;
        }
        fprintf(yyout, "\n\n\n");
    }
    fprintf(yyout, "Spesa totale del albergo: %f", total_hotel);
}
